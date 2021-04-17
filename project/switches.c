#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed, s1, s2, s3, s4;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  s1 = (SW1 & p2val) ? 0 : 1;
  s2 = (SW2 & p2val) ? 0 : 1;
  s3 = (SW3 & p2val) ? 0 : 1;
  s4 = (SW4 & p2val) ? 0 : 1;

  if(s1)
    {
      switch_state_down = 1;
    }
  else if (s2)
    {
      switch_state_down = 2;
    }
  else if (s3)
    {
      switch_state_down = 3;
    }
  else if (s4)
    {
      switch_state_down = 4;
    }
  state_advance();
  
}
