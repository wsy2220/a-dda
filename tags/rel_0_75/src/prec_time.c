/* FILE: prec_time.c
 * AUTH: Maxim Yurkin
 * DESCR: precision timing routines (OS dependent)
 *        definitions and inlines are in prec_time.h
 *
 * Copyright (C) 2006 University of Amsterdam
 * This code is covered by the GNU General Public License.
 */
#include "prec_time.h"
#include "const.h"

/* this is to eliminate warnings about empty source file */
void void_function(void) ATT_UNUSED;
void void_function(void) {}

#ifdef PRECISE_TIMING /* following is only for precise timing */

/* LOCAL VARIABLES */

#ifdef WINDOWS
static double inv_freq;
#elif defined(POSIX)
# define MICRO 1E-6
#endif

/*============================================================*/

void InitTime(SYSTEM_TIME *t)
     /* set time to zero */
{
#ifdef WINDOWS
  t->QuadPart=0;
#elif defined(POSIX)
  t->tv_sec=t->tv_usec=0;
#endif
}

/*============================================================*/

void SetTimerFreq(void)
   /* set frequency of windows timer;
   should be called once before running TimerToSec or DiffSec*/
{
#ifdef WINDOWS
  LARGE_INTEGER freq;

  QueryPerformanceFrequency(&freq);
  inv_freq=1/(double)freq.QuadPart;
#endif
}

/*============================================================*/

double TimerToSec(const SYSTEM_TIME *t)
   /* timer to seconds */
{
#ifdef WINDOWS
  return (inv_freq*t->QuadPart);
#elif defined(POSIX)
  return (t->tv_sec+MICRO*t->tv_usec);
#endif
}

/*============================================================*/

double DiffSec(const SYSTEM_TIME *t1,const SYSTEM_TIME *t2)
   /* difference between two times in seconds */
{
  SYSTEM_TIME res;

  elapsed(t1,t2,&res);
  return TimerToSec(&res);
}

#endif /* PRECISE_TIMING */
