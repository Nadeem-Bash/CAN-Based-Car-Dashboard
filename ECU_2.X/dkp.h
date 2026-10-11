#ifndef DKP_H
#define DKP_H

#define LEVEL					     	0
#define EDGE        			       	1

#define KEY_PORT					PORTC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F

//
#define ON					1
#define OFF					0

#define _XTAL_FREQ 20000000

/* Defines the data */
#define TRUE			1
#define FALSE			0

void check_digital_keypad(unsigned char key);
int count = 0;
//

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);
void check_digital_keypad(unsigned char key);

#endif