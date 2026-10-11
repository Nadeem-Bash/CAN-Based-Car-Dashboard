
#include <xc.h>
#include <string.h>
#include<stdio.h>
#include <xc.h>
#include "adc.h"
#include "dkp.h"
#include "can.h"
#include "id.h"

static unsigned char gear[] = "N12345R";
void main(void) 
{
    unsigned int speed;
    unsigned char key;
    
    char gear_bufer[3];
    uint8_t gear_len = 0;
    
    char speed_buffer[5];          
    uint8_t speed_len = 0;
    
    //initializing the peripherals
    init_adc();
    init_digital_keypad();
    init_can();
    
    while(1)
    {
        speed = read_adc(CHANNEL4) / 10;
//        speed = (read_adc(CHANNEL4)/10.23);                     //getting speed from adc
        snprintf(speed_buffer,sizeof(speed_buffer),"%d",speed); //converting and copying to string
        speed_len = strlen(speed_buffer);                       
        
        can_transmit(SPEED_MSG_ID,speed_buffer,speed_len);      //transmitting speed
        for(int i = 0;i<3000;i++);                              //delay
        
        key = read_digital_keypad(EDGE);              
        check_digital_keypad(key);                              //checking if key is pressed and incrementing the gear
        gear_bufer[0] = gear[count];
        gear_bufer[1] = '\0';
        
        gear_len = strlen(gear_bufer);
        
        can_transmit(GEAR_MSG_ID, gear_bufer,gear_len);         //transmitting gear
        for(int i=0; i<3000; i++);
    }
    return;
}

void check_digital_keypad(unsigned char key)
{
	if (key == SWITCH1)
	{
        if(count <6)
        {
            count++;
        }
	}
	else if(key == SWITCH2)
	{
		if(count > 0)
        {
            count--;   
        }
	}
}