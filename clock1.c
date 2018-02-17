#include <avr/io.h>
#include <util/delay.h>

// changed

int main(void);
//unsigned char counter=0;
uint8_t second=0;
uint8_t minute=0;
uint8_t hour=3;


int main (void){
	PORTA=0;	// portA digital
	PORTC=0;	//portb digital
	PORTD=0;
	
	DDRA=0xff;	//output :seconds
	DDRC=0xff;	//otput :mintes
	DDRD=0xff;	//output	:hours
	
	
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
		_delay_ms(995);
		second++;
	}
	return 1;
}
