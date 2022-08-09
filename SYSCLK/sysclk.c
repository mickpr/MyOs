#include "sysclk.h"
#include <avr/interrupt.h>


volatile t_process process[TASKS];

void init_sysclk()
{
  //TCCR0   7    6     5     4     3     2    1    0
  //      FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00
  //
  //   CS02, CS01, CS00 - wybor preskalera (1024 =>  (b)101
  //   WGM00 WGM01      - tryb (00 normal, 01 PWM, 10 - CTC, 11 FastPWM)
  //   COM01, COM00     - compare ouptut mode
  cli();
  TCCR0 |= (1<<CS00) | (1<<CS02); // wybierz preskaler 1/1024
  TIMSK |= (1<<TOIE0); // w³¹cz przerwanie od przepe³nienia licznika
  TCNT0 = 0xF5;        // wartosc timera (timer zlicza w górê)...
  sei();
}


//timer okolo 1mS (1.0185 mSec)
/////// dla 10mS per tick zmieniamy TCNT0 na 0x94 (wtedy blad wynosi 0!)
ISR(TIMER0_OVF_vect)
{
  //cli();
  for (uint8_t i=0;i<TASKS;i++)
  {

    if (process[i].counter) { process[i].counter--; }
    else {
	  if (process[i].handler) process[i].handler();  //execute handler
	  process[i].counter = process[i].delay;
    }
    TCNT0 = 0xF5; //odnow wartosc, bo w trybie normal tego nie robi.
  }
  //sei();
}

void process_add(uint8_t task, void * handler, uint32_t delay) {
	process[task].handler = handler;
	process[task].delay = delay;
	process[task].counter=delay; //init at start
}

