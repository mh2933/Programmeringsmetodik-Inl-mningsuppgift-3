#include "blink.h"

// blink.c implementerar blinksekvensen

bool leds_blink()//const volatile uint16_t* blink_speed_ms
{
	while(true)
	{
		LEDS_OFF;
		LED1_ON;
		_delay_ms(100); // blink_speed_ms

		LED1_OFF;
		LED2_ON;
		_delay_ms(100); // blink_speed_ms

		LED2_OFF;
		LED3_ON;
		_delay_ms(100); // blink_speed_ms
	}
}

