#include <avr/io.h>
#include <avr/interrupt.h> 	// intterupts instead of delay

int main(void);
uint8_t minuteShifter(uint8_t in);

uint8_t second=0;
uint8_t minute=0;
uint8_t hour=11;	// so i can see if the LEDs turn on
volatile uint8_t flag; //stop and check if a second is over
uint8_t softtimer;
int setMinute;
int setHour;
uint8_t timer;
uint8_t buttonTime;
//uint8_t hourArray[12] = {0,8,4,12,2,10,6,14,1,9,5,13};

   ISR(TIMER0_COMP_vect) {// 125.00 times per second interrupt service routine.
     flag=1;	// flag = true;
    }

int main (void){
	PORTA= 0;	// portA digital
	PORTC= 0;	//portb digital
	PORTD= 0;
	PORTB= 0x03;	// push buttons
		
	DDRA= 0xff;	//output :seconds
	DDRC= 0xff;	//otput :(mintes) is now hour
	DDRD= 0xff;	//output	:(hours) is now minute needs helper method
		
	TCCR0 = 0x0b;	// pre devisor
	OCR0 = 127;
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
				hour++;
		//		index++;
					
				if(hour>=12){		//hour overflow
					hour=0;
					}
//				if(index>=12){
//					index=0;
//					}
				}
			}
			
		PORTA=second;	//binary output
		//PORTD=minute;
		PORTD= hour;
	//PORTC=hourArray[index];
		PORTC=  minuteShifter(minute);

	   if (flag){
        flag = 0; // divide time to get a full second
        softtimer++;
        
            
        if (softtimer >= 100){	// 125 == 1second passed
            softtimer = 0;
            timer++;
            buttonTime++;
            
            if(timer>=18){
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
// method to make little endian out of big endian nummbers, turn on other LEDs
uint8_t minuteShifter(uint8_t in){
	uint8_t reverse=0;
			if(in & 1){
				reverse |= 32;
	}
			if (in & 2){
				reverse |= 16;
		}
			if (in & 4){
				reverse |= 8;
		}
			if (in & 8){
				reverse |= 4;
		}
			if (in &16){
				reverse |= 2;
		}
			if (in &32){
				reverse |= 1;
		}

	
	return reverse;
	}
