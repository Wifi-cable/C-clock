#include <avr/io.h>
#include <avr/interrupt.h> 	// intterupts instead of delay

int main(void);
uint8_t second=0;
uint8_t minute=0;
//uint8_t hour=0;	// so i can see if the LEDs turn on
volatile uint8_t flag; //stop and check if a second is over
uint8_t softtimer;
int setMinute;
int setHour;
uint8_t timer;
uint8_t buttonTime;
uint8_t hourArray[12] = {0,8,4,12,2,10,6,14,1,9,5,13};

   ISR(TIMER0_COMP_vect) {// 125.00 times per second interrupt service routine.
     flag=1;	// flag = true;
    }

int main (void){
	PORTA= 0;	// portA digital
	PORTC= 0;	//portb digital
	PORTD= 0;
	PORTB= 0x03;
		
	DDRA= 0xff;	//output :seconds
	DDRC= 0xff;	//otput :mintes
	DDRD= 0xff;	//output	:hours
		
	TCCR0 = 0x0b;
	OCR0 = 124;
	TIMSK = 0x02;
	uint8_t index=0;
	
	sei();	// enable flags 
	 
	while(1){	// forever
		setHour=PINB&0x01;
		setMinute=PINB&0x02;
		
		if(second>=60){	//second overfows 
			second=0;
			minute++;
			
			if(minute>=60){	//minute overflow
				minute=0;
				//hour++;
				index++;
					
//				if(hour>=12){		//hour overflow
//					hour=0;
//					}
				if(index>=12){
					index=0;
					}
				}
			}
			
		PORTA=second;	//binary output
		PORTD=minute;
		PORTC=hourArray[index];

	   if (flag){
        flag = 0; // divide time to get a full second
        softtimer++;
        
            
        if (softtimer >= 123){	// 125 == 1second passed
            softtimer = 0;
            timer++;
            buttonTime++;
            
            if(timer>=15){
	            second++;
	            timer=0;
            }
        }  
        if(buttonTime>=7){
        	buttonTime=0;
					if(!setMinute){	//and minute button is pressed, increase minute
						 minute++;
			 if(minute>=60){
			 		minute=0;
			 	}
		}
		if(!setHour){	// same for hours. if half a second has passed and button is pressed
			 index++;
				if(index>=12){
					index=0;
					}
				}
			}
   	 }
	}	//end big while true loop
	return 1;	//unreachable code to make the C language happy
}
