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
uint8_t buttonTimer;
int setMinute;
int setHour;

   ISR(TIMER0_COMP_vect) {// 125.00 times per second interrupt service routine.
     flag=1;	// flag = true;
    }

int main (void){
	PORTA=0;	// portA digital
	PORTC=0;	//portb digital
	PORTD=0;
	PORTB=0x03;
		
	DDRA=0xff;	//output :seconds
	DDRC=0xff;	//otput :mintes
	DDRD=0xff;	//output	:hours
		
	TCCR0 = 0x0b;
	OCR0 = 124;
	TIMSK = 0x02;
	
	sei();	// enable flags 
	 
	while(1){	// forever
		setHour=PINB&0x01;
		setMinute=PINB&0x02;
		
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
	
		PORTA=second;	//binary output
		PORTD=minute;
		PORTC=hour;

	   if (flag){
        flag = 0; // divide time to get a full second
        softtimer++;
        
        if (softtimer >= 125){	// 125 == 1second passed
            softtimer = 0;
            second++;
        }  
            buttonTimer++;	//if half a second is over
            if(buttonTimer>=75){
   		
    		buttonTimer=0;
				if(!setMinute){	//and minute button is pressed, increase minute
				 minute++;
			 if(minute>=60){
			 	minute=0;
			 	}
		}
		if(!setHour){	// same for hours. if half a second has passed and button is pressed
			 hour++;
				if(hour>=12){
					hour=0;
					}
				}
			}
   	 }
	}	//end big while true loop
	return 1;	//unreachable code to make the C language happy
}
