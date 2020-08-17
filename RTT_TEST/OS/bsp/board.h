#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"
#include "rtdef.h"

#ifdef __ICCARM__
// Use *.icf ram symbal, to avoid hardcode.
extern char __ICFEDIT_region_IRAM1_end__;
#define STM32_SRAM_END          &__ICFEDIT_region_IRAM1_end__
#else
/* 根据自己MCU 内部SRAM大小不同修改 */
#define STM32_SRAM_SIZE          64
#define STM32_SRAM_END          (0x20000000 + STM32_SRAM_SIZE * 1024)
#endif

#ifdef __CC_ARM
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN    (&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="HEAP"
#define HEAP_BEGIN    (__segment_end("HEAP"))
#else
extern int __bss_end;
#define HEAP_BEGIN    (&__bss_end)
#endif

#define HEAP_END                STM32_SRAM_END

void rt_hw_us_delay(rt_uint32_t us);
void rt_hw_board_init(void);

#endif





