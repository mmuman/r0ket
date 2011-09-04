#ifdef SIMULATOR
#define _POSIX_C_SOURCE 199309
#include <time.h>
#endif

#include <sysdefs.h>
#include "lpc134x.h"

#ifdef SIMULATOR
void delayms(uint32_t ms)
{
  struct timespec t;
  t.tv_sec = ms / 1000;
  t.tv_nsec = (ms % 1000) * 1000000;

  nanosleep (&t, NULL);
}
#else
/**************************************************************************/
/*! 
    Approximates a 1 millisecond delay using "nop".  This is less
    accurate than a dedicated timer, but is useful in certain situations.

    The number of ticks to delay depends on the optimisation level set
    when compiling (-O).  Depending on the compiler settings, one of the
    two defined values for 'delay' should be used.
*/
/**************************************************************************/
void delayms(uint32_t ms)
{
  uint32_t delay = ms * ((CFG_CPU_CCLK / 100) / 45);      // Release Mode (-Os)
  // uint32_t delay = ms * ((CFG_CPU_CCLK / 100) / 120);  // Debug Mode (No optimisations)

  while (delay > 0)
  {
    __asm volatile ("nop");
    delay--;
  }
}
#endif
