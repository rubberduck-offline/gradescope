#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include <pthread.h>
#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

struct sigaction old_sa;
struct sigaction sa;
/*
block signals of type SIGVTALRM
REF doc: https://www.gnu.org/software/libc/manual/html_mono/libc.html#Blocking-Signals
*/
void preempt_disable(void)
{
    /* TODO Phase 4 */
    //struct sigaction sig_act_set;
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGVTALRM);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
}

/*
unblock signals of type SIGVTALRM
REF doc: https://www.gnu.org/software/libc/manual/html_mono/libc.html#Blocking-Signals
*/
void preempt_enable(void)
{
    /* TODO Phase 4 */
    //struct sigaction sig_act_set;
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGVTALRM);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}

/* The signal handler (catch_alarm) :
 acts as the timer interrupt handler,
 will force the currently running thread to yield, so that another thread can be scheduled instead
 then clears the flag and re-enables itself. */
 
void catch_alarm ()
{
    
    //int i=0;

    /* force the currently running thread to yield */
    
    //struct uthread_tcb* cur_thread=uthread_current();
    uthread_yield();
    /* just for debug
    for (i=0;i<10;i++)
        printf ("I have preempt successfully, %d! \n", i );
    */
    /*let main going */
    //keep_going = 0;
    /*  sigaction (sig, catch_alarm); */
}

void preempt_start(bool preempt)
{
    /* TODO Phase 4 */
    if(!preempt)return ;
    
    
    
    /*     struct itimerval {
    structtimevalit_interval;  // timer interval
    struct timeval it_value;   // current value
    };    */
    struct itimerval value2,ovalue;
    
    
    /*1 Install a signal handler for SIGVTALRM(Standard Signals: signal virtual time alarm )*/
    sa.sa_handler=catch_alarm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sigaction (SIGVTALRM, &sa, &old_sa);
    
    
        
    /*2 Configure a timer 100 Hz*/
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 10000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 10000;
    
    
    /* setitimer() set a timer. If itimerval.it_interval is not 0, the timer will persist be valid(1 signal every interval)*/
    setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
    //preempt = true;
    //return preempt;
}

void preempt_stop(void)
{
    /* TODO Phase 4 */

    struct itimerval value2,ovalue;
    //struct sigaction sa;
    //struct sigaction old_sa;
    
    sigaction (SIGVTALRM, &old_sa, NULL);
    /* restore the previous signal action, */

    /*
    TODO !!!
    */
    
    /*and restore the previous timer configuration.*/
    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 0;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 0;
     
    /*estitimer provide a timer. If itimerval.it_interval is not zero, then this timer will be persistently valid*/
    setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
    
    
    
}

