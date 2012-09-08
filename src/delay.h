/*******************************************************************************
# Copyright (c) 2011 Christopher James Huff
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#******************************************************************************/

#ifndef DELAY_H
#define DELAY_H
//******************************************************************************

#include "common.h"

void Delays_Init(void);

extern volatile uint32_t systicks;// milliseconds since startup (increment in SysTick handler)

// Microsecond delay. Accuracy depends on the SysTick clock.
// Maximum delay is (2^32 - 1)/SystemCoreClock
// 72 MHz: 59 seconds
// 168 MHz: 25 seconds
void delay_us(uint32_t us);

// Approximate delay, exits on first systick following expiry of delay and may be
// as much as 1 ms longer than specified.
// Sleeps the processor with __WFI() until an interrupt occurs.
// Maximum delay is 1000*(2^32 - 1)/SystemCoreClock
// 72 MHz: 59652 seconds/994 minutes/16.5 hours
// 168 MHz: 25565 seconds/426 minutes/7 hours
void delay_ms(uint32_t ms);


// Microsecond spinloop delay
// Does not sleep the processor until an interrupt occurs, and can be used with interrupts
// disabled.
// void spin_us(uint32_t us);

// Millisecond spinloop delay.
// Does not sleep the processor until an interrupt occurs, and can be used with interrupts
// disabled.
// Maximum delay is 1000*(2^32 - 1)/72 MHz = 59652 seconds, 994 minutes or 16.5 hours
// void spin_ms(uint32_t ms);


// An extremely basic timer based on the systicks count, to be used in a conditional
// statement. Resets timer and returns true if expired, otherwise returns false.
// Reset time is from time of expiry, not from time of call, and a very stale timer
// may remain expired after a call, and thus trigger immediately on next poll.
static inline bool checktimer(uint32_t * timer, uint32_t period)
{
    if(systicks > *timer) {
        *timer += period;
        return true;
    }
    return false;
}


// Minimum-delay version of checktimer() guarantees a minimum delay until next trigger.
// If processing is delayed for multiple periods, timer will trigger at minDly intervals
// until it catches up.
static inline bool checktimer_mindly(uint32_t * timer, uint32_t period, uint32_t minDly)
{
    if(systicks > *timer) {
        *timer += period;
        if(systicks + minDly > *timer)
            *timer = systicks + minDly;
        return true;
    }
    return false;
}

//******************************************************************************
#endif //  DELAY_H
