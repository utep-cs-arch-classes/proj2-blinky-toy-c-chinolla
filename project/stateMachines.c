#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char toggle_red()		
{
  static char state = 0;
  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  static char state = 0;
  switch(state)
    {
    case 0:
      green_on = 1;
      state = 1;
      break;
    case 1:
      green_on = 0;
      state = 0;
      break;
    }
  return 1;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  

  static enum {R=0, G=1} color = G;
  switch (s)
    {
    case 0:
      red_on = 1;
      green_on = 1;
      changed = 1;
      break;
    case 1:
      testdimLights();
      changed = 1;
      break;
    case 2:
      changed = toggle_both();
      makeSound();
      break;
    case 3:
      changed = turn_off();
      buzzer_set_period(0);
      break;
    }
     

  led_changed = changed;
  led_update();
}


char toggle_both()
{
  static char state = 0;

  switch(state)
    {
    case 0:
      red_on = 1;
      green_on = 0;
      state = 1;
      break;
    case 1:
      red_on = 0;
      green_on = 1;
      state = 0;
      break;
    }
  return 1;
}

void dimone()
{
  char changed_led = 0;
  static char dimS = 0;
  switch(dimS)
    {
    case 0:
      red_on = 1;
      dimS = 1;
      break;
    case 1:
      red_on = 0;
      dimS = 2;
      break;
    case 2:
      red_on = 0;
      dimS = 3;
      break;
    case 3:
      red_on = 0;
      dimS = 0;
      break;
    }
  changed_led = 1;
  led_update();
}


void dimtwo()
{
  char changed_led = 0;
  static char dimS = 0;
  switch(dimS)
    {
    case 0:
      red_on = 1;
      dimS = 1;
      break;
    case 1:
      red_on = 0;
      dimS = 2:
      break;
    case 2:
      red_on = 1:
      dimS = 3;
      break;
    case 3:
      red_on = 0;
      dimS = 0;
      break;
    }
  changed_led = 1;
  led_update();
}

void dimthree()
{
  char changed_led = 0;
  static char dimS = 0;
  switch(dimS)
    {
    case 0:
      red_on = 1:
      dimS = 1;
      break;
    case 1:
      red_on = 0;
      dimS = 2;
      break;
    case 2:
      red_on = 1;
      dimS = 3;
      break;
    case 3:
      red_on = 1;
      dimS = 0;
      break;
    }
  changed_led = 1;
  led_update();
}

void dimLights()
{
  static char dimS = 0;
  switch(dimS)
    {
      dimone();
      dimS = 1;
      break;
    case 1:
      dimtwo();
      dimS = 2;
      break;
    case 2:
      dimthree();
      dimS = 3;
      break;
    }
}

void testdimLights()
{
  static char state = 0;
  switch(state)
    {
    case 0:
      red_on = 1;
      green_on = 1:
      state = 1;
      break;
    case 1:
      red_on = 0;
      green_on = 0;
      state = 0;
      break;
    }
  led_changed = 1;
  led_update();
}
