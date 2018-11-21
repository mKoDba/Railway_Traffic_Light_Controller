/*
 * eeprom_test.c
 *
 *  Created on: 20. stu 2018.
 *      Author: Mario
 */

#include <avr/eeprom.h>
#include <avr/io.h>
#include <util/delay.h>

#define EEPROM_KB 1			//depending on mcu used
#define WAIT 100

void error(){
	exit(1);
}

inline void pattern_test(uint16_t pattern) {

	volatile uint16_t* ptr = 0;
	//using 16bits or 2bytes
	for(ptr = (uint16_t*)0x0000; ptr <= (uint16_t*)(EEPROM_KB*512); ptr += 2){
		eeprom_busy_wait();
		//wait for eeprom to be ready
		eeprom_write_word(ptr, pattern);
		//write a given pattern
	}
	_delay_ms(WAIT);
	for(ptr = (uint16_t*)0x0000; ptr <= (uint16_t*)(EEPROM_KB*512); ptr += 2){
		eeprom_busy_wait();
		if(eeprom_read_word(ptr) != pattern) {
			error();
		}
		//check if a given pattern is at correct memory location
	}
}

void eeprom_test(void) {
	pattern_test(0xFFFF);
	pattern_test(0xAAAA);
	pattern_test(0x5555);
	pattern_test(0x0000);
	//check memory using typical patterns,
	//using all the patterns possible would take too much time
	exit(0);
}
