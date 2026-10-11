#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "dkp.h"
//#include "uart.h"

uint16_t get_rpm()
{
    //Implement the rpm function
    uint16_t rpm = read_adc(CHANNEL4);
    return rpm;
}

//uint16_t get_engine_temp()
//{
//    //Implement the engine temperature function
//}

unsigned char process_indicator()
{
    unsigned char key = read_digital_keypad(EDGE);
    return key;
    //Implement the indicator function
}
