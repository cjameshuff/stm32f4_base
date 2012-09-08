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

#include "delay.h"

volatile uint32_t systicks = 0;


void delay_us(uint32_t us)
{
    uint32_t tstart_ms = systicks;
    uint32_t tstart_clocks = SysTick->LOAD - (SysTick->VAL & 0x00FFFFFF);
    uint32_t del_clocks = us*(SysTick->LOAD/1000);// no rounding error at 72 MHz and millisecond systicks
    while((SysTick->LOAD - (SysTick->VAL & 0x00FFFFFF) - tstart_clocks) + (systicks - tstart_ms)*SysTick->LOAD < del_clocks)
        {;}
}

void delay_ms(uint32_t ms) {
    uint32_t tstart_ms = systicks;
    while((systicks - tstart_ms) < (ms + 1))
        {__WFI();}
}

// Maximum delay is 1000*(2^32 - 1)/72 MHz = 59652 seconds, 994 minutes or 16.5 hours
// void spin_ms(uint32_t ms) {
    // for(int j = 0; j < 1000; ++j)
    //     delay_us(ms);
// }
