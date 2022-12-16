/********************************************************************************
* main.c: Demonstration av datastruktur för implementering av tryckknappar med
*         PCI-avbrott. I detta fall sker avläsning av en tryckknapp för
*         toggling av en lysdiod via en avbrottsrutin. För att göra motsvarande
*         objekt synliga i avbrottsrutinen så används globala datamedlemmar.
********************************************************************************/
#include "led.h"
#include "button.h"
#include "led_vector.h"

/* Globala datamedlemmar: */
static struct button b1;
static volatile bool leds_enabled = false;

ISR(PCINT0_vect)
{
	if(!button_is_pressed(&b1))
	{
		leds_enabled = !leds_enabled;
	}
}


/********************************************************************************
* main: Ansluter en lysdiod till pin 8-10 / PORTB0-2 samt en tryckknapp till pin 13
*       / PORTB5, med PCI-avbrott aktiverat för toggling av lysdioder.
********************************************************************************/
int main(void)
{
  struct led l1, l2, l3;
  struct led_vector v1;
  
  button_init(&b1, 13);
  button_enable_interrupt(&b1);
	
  led_init(&l1, 8);  // pin 8-10
  led_init(&l2, 9);
  led_init(&l3, 10);
  
  led_vector_init(&v1);
  led_vector_push(&v1, &l1);
  led_vector_push(&v1, &l2);
  led_vector_push(&v1, &l3);
   
  while (1)
   {
  if (leds_enabled)
  {
	 led_vector_blink_sequentially(&v1,100);
  }
  else 
  {
	 led_vector_off(&v1);
  }

   }

   return 0;
}

