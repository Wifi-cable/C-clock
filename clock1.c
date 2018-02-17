#include <avr/io.h>
//#include <util/delay.h>
#include <avr/interrupt.h> 	// intterupts instead of delay


int main(void);
//unsigned char counter=0;
uint8_t second=0;
uint8_t minute=0;
uint8_t hour=3;	// so i can see if the LEDs turn on
volatile uint8_t flag; //stop and check if a second is over
uint8_t softtimer;

   ISR(TIMER0_COMP_vect) {// 125.00 times per second interrupt service routine.
     flag=1;	// flag = true;
    }

int main (void){
	PORTA=0;	// portA digital
	PORTC=0;	//portb digital
	PORTD=0;
	
	DDRA=0xff;	//output :seconds
	DDRC=0xff;	//otput :mintes
	DDRD=0xff;	//output	:hours
	
	TCCR0 = 0x0b;
	OCR0 = 124;
	TIMSK = 0x02;
	
	sei();	// enable flags 
	
//	    ISR(TIMER0_COMP_vect) {// 125.00 times per second interrupt service routine.
//       flag=1;	// flag = true;
//       }
	 
	while(1){	// forever
		if(second>=60){	//second overfows 
			second=0;
			minute++;
			
			if(minute>=60){	//minute overflow
				minute=0;
				hour++;
				
				if(hour>=12){		//hour overflow
					hour=0;
					}
			}
	}
	//PORTC=minute;	
		PORTA=second;	//binary output
		PORTD=minute;
		PORTC=hour;
	//	_delay_ms(995);
	//second++;
	   if (flag){
        flag = 0; // divide time to get a full second
        softtimer++;
        if (softtimer >= 125){	// 125 == 1second passed
            softtimer = 0;
            second++;
        }  
    }
    
	
	}
	return 1;	//unreachable code to make the C language happy
}
