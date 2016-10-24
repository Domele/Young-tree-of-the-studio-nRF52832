#include "nrf52.h"
#include "nrf_gpio.h"
#include "led.h"
#include "time.h"
#include <stdbool.h>
#include <stdint.h>



/**
 * @brief Function for timer initialization.
 */
static volatile NRF_TIMER_Type * timer_init(timer_t timer)
{
    volatile NRF_TIMER_Type * p_timer;

    // 开始16 MHz晶振.
    NRF_CLOCK->EVENTS_HFCLKSTARTED  = 0;
    NRF_CLOCK->TASKS_HFCLKSTART     = 1;

    // 等待外部振荡器启动
    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) 
    {
        // Do nothing.
    }

    switch (timer)
    {
        case TIMER0:
            p_timer = NRF_TIMER0;
            break;

        case TIMER1:
            p_timer = NRF_TIMER1;
            break;

        case TIMER2:
            p_timer = NRF_TIMER2;
            break;

        default:
            p_timer = 0;
            break;
    }
    return p_timer;
}


/** @brief Function for using the peripheral hardware timers to generate an event after requested number of milliseconds.
 *
 * @param[in] timer Timer to be used for delay, values from @ref p_timer
 * @param[in] number_of_ms Number of milliseconds the timer will count.
 * @note This function will power ON the requested timer, wait until the delay, and then power OFF that timer.
 */

void nrf_timer_delay_ms(timer_t timer, uint_fast16_t volatile number_of_ms)
{
    volatile NRF_TIMER_Type * p_timer = timer_init(timer);

    if (p_timer == 0) 
    {
        while(true) 
        {
            // Do nothing.
        }
    }

    p_timer->MODE           = TIMER_MODE_MODE_Timer;        // 设置为定时器模式
    p_timer->PRESCALER      = 9;                            // Prescaler 9 produces 31250 Hz timer frequency => 1 tick = 32 us.
    p_timer->BITMODE        = TIMER_BITMODE_BITMODE_16Bit;  // 16 bit 模式.
    p_timer->TASKS_CLEAR    = 1;                            // 清定时器.
    
    // With 32 us ticks, we need to multiply by 31.25 to get milliseconds.
    p_timer->CC[0]          = number_of_ms * 31;
    p_timer->CC[0]         += number_of_ms / 4; 
    p_timer->TASKS_START    = 1;                    // Start timer.

    while (p_timer->EVENTS_COMPARE[0] == 0)
    {
        // Do nothing.
    }

    p_timer->EVENTS_COMPARE[0]  = 0;
    p_timer->TASKS_STOP         = 1;                // Stop timer.
}
/** @} */



/** @brief 初始化TIME0, 通过time1和time2来启动和停止定时器计数.
*/
 void timer0_init(void)
{
    NRF_TIMER0->MODE    = TIMER_MODE_MODE_Counter;      // 设置定时器位计数模式.
    NRF_TIMER0->BITMODE = TIMER_BITMODE_BITMODE_24Bit;  // 24-bit 模式.
}


/** @brief 定时器1初始化.
 *  @details初始化定时器1外设,   每2s创建一个事件与中断
 *           by configuring CC[0] to timer overflow value, we create events at even number of seconds
 *           for example, events are created at 2,4,6 ... seconds. This event can be used to stop Timer 0
 *           with Timer1->Event_Compare[0] triggering Timer 0 TASK_STOP through PPI.
*/
 void timer1_init(void)
{
    // 配置定时器每2 seconds溢出.
    // SysClk = 16 Mhz
    // BITMODE = 16 bit
    // PRESCALER = 9
    // The overflow occurs every 0xFFFF/(SysClk/2^PRESCALER).
    // = 65535/31250 = 2.097 sec
    NRF_TIMER1->BITMODE     = (TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER1->PRESCALER   = 9;
    NRF_TIMER1->SHORTS      = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);

    // Trigger interrupt for compare[0] event.
    NRF_TIMER1->MODE        = TIMER_MODE_MODE_Timer;
    NRF_TIMER1->CC[0]       = 0xFFFFUL;  // Match at even number of seconds
}


/** @brief Function for Timer 2 initialization.
 *  @details Initializes Timer 2 peripheral, creates event and interrupt every 2 seconds
 *           by configuring CC[0] to half of timer overflow value. Events are created at odd number of seconds.
 *           For example, events are created at 1,3,5,... seconds. This event can be used to start Timer 0
 *           with Timer2->Event_Compare[0] triggering Timer 0 TASK_START through PPI.
*/
 void timer2_init(void)
{
    // Generate interrupt/event when half of time before the timer overflows has past, that is at 1,3,5,7... seconds from start.
    // SysClk = 16Mhz
    // BITMODE = 16 bit
    // PRESCALER = 9
    // now the overflow occurs every 0xFFFF/(SysClk/2^PRESCALER)
    // = 65535/31250 = 2.097 sec */
    NRF_TIMER2->BITMODE     = (TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos);
    NRF_TIMER2->PRESCALER   = 9;
    NRF_TIMER2->SHORTS      = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);

    // Trigger interrupt for compare[0] event.
    NRF_TIMER2->MODE        = TIMER_MODE_MODE_Timer;
    NRF_TIMER2->CC[0]       = 0x7FFFUL;  // Match at odd number of seconds.
}


