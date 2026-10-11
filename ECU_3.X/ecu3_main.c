#include "can.h"
#include "msg_id.h"
//#include "uart.h"
//#include"matrix_keypad.h"
#include"clcd.h"

#include<string.h>
#include <xc.h>

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07


//#define MK_SW1					1
//#define MK_SW2					2
//#define MK_SW3					3
//#define MK_SW4					4

void main()
{
    //for LED since 2 pins are used by the CAN
    TRISB = 0x08;
    
    //call the functions
    init_can();
    init_clcd();
    
    //RECEIVE
    char recv_buffer[6];               
    unsigned int recv_msg_id = 0x00;    
    uint16_t  *msg_id = &recv_msg_id;   
    uint8_t rcv = 0;
    uint8_t* rcv_len = &rcv;
    
            clcd_print("SPED RPM GR IND ",LINE1(0)); 
    while(1)
    {
           
        can_receive(msg_id, recv_buffer, rcv_len);                  //can receive

        if (*rcv_len > 0)
        {
           recv_buffer[*rcv_len] = '\0';                            //NULL terminating the buffer
        }
        
//        if(*rcv_len == 0)
//        {
//            clcd_print("NO DATA         ",LINE2(0));
//        }
        
        //for speed
        if (*msg_id == SPEED_MSG_ID)
        {
            clcd_print("    ", LINE2(0));
            clcd_print(recv_buffer, LINE2(0));
        }
        
        if (*msg_id == GEAR_MSG_ID)
        {
            clcd_print(recv_buffer, LINE2(10));
        }
        
        if (*msg_id == RPM_MSG_ID)
        {
            clcd_print("    ", LINE2(5));
            clcd_print(recv_buffer, LINE2(5));
        }
        
        if (*msg_id == INDICATOR_MSG_ID && *rcv_len == 1)
        {
            uint8_t key = recv_buffer[0];
            
            switch(key)
            {
                case SWITCH1: 
                    clcd_print("<- ", LINE2(13)); 
                    PORTB = (PORTB & 0x3C) | 0x03;
                    break;
                case SWITCH2: 
                    clcd_print("-> ", LINE2(13)); 
                    PORTB = (PORTB & 0x3C) | 0xC0;
                    break;
                case SWITCH3: 
                    clcd_print("<->", LINE2(13)); 
                    PORTB = (PORTB & 0x3C) | 0xC3;
                    break;
                case SWITCH4: 
                    clcd_print("OFF", LINE2(13)); 
                    PORTB = (PORTB & 0x3C);
                    break;
            }
        }
    }
}
