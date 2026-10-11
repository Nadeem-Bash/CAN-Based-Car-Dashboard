#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "uart.h"
#include"dkp.h"
#include<string.h>
#include <xc.h>
#include<stdio.h>

void main()
{
    //call the functions
    init_adc();
    init_can();
//  init_matrix_keypad(); 
    init_digital_keypad();
    
    unsigned int rpm;
    unsigned char key;
    
    //TRANSMIT
    char rpm_buffer[6]; 
    char key_buffer[6];
    uint8_t key_len = 0;
    uint8_t rpm_len = 0;
    
    while(1)
    {
        rpm = get_rpm();
        rpm = (rpm/10.23)*60;

        snprintf(rpm_buffer, sizeof(rpm_buffer),"%d",rpm);

        rpm_len = strlen(rpm_buffer);
        can_transmit(RPM_MSG_ID,rpm_buffer,strlen(rpm_buffer));
        for(int i = 0; i < 3000; i++); // delay
        
        key = process_indicator();
        
        if (key != 0xFF)
        {
        can_transmit(INDICATOR_MSG_ID, &key, 1);
        }
        for(int i = 0; i < 3000; i++);  
    }
    return;
}
