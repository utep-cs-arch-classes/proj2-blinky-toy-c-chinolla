#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"


static short D1 = 27;
static short A1 = 18;
static short G1 = 21;
static short F1 = 23;



void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

void makeSound()
{
  char sound[] = "sans";
  static int i = 0;
  char length = sound[i];
  switch(length)
    {
    case'D':
      buzzer_set_period(D1);
      break;
    case'A':
      buzzer_set_period(A1);
      break;
    case'G':
      buzzer_set_period(G1);
      break;
    case'F':
      buzzer_set_period(F1);
      break;
    }
  if (i == sizeof(sound) - 1)
    {
      i = 0;
    }
  else
    {
      i++;
    }
}


    
    
  

