#ifndef __MAX7219_H__
#define __MAX7219_H__

#include <stdint.h>
#include "gpio.h"


//#define MAX7219_NO_OP      0x00    // 无操作
//#define MAX7219_DIGIT0     0x01    // 第 0 列（顶部）
//#define MAX7219_DIGIT1     0x02    // 第 1 列
//#define MAX7219_DIGIT2     0x03    // 第 2 列
//#define MAX7219_DIGIT3     0x04    // 第 3 列
//#define MAX7219_DIGIT4     0x05    // 第 4 列
//#define MAX7219_DIGIT5     0x06    // 第 5 列
//#define MAX7219_DIGIT6     0x07    // 第 6 列
//#define MAX7219_DIGIT7     0x08    // 第 7 列（底部）
#define MAX7219_DECODE     0x09    // 解码模式寄存器
#define MAX7219_INTENSITY  0x0A    // 亮度寄存器
#define MAX7219_SCAN_LIMIT 0x0B    // 扫描限制寄存器
#define MAX7219_SHUTDOWN   0x0C    // 关机模式寄存器
#define MAX7219_DISPLAY_TEST 0x0F  // 显示测试寄存器
//测试



void CLK_1(void);
void CLK_0(void);

void MAX7219_WriteByte(uint8_t addr,uint8_t Data);
void MAX7219_Init(void);
void MAX7219_LightLED(uint8_t Column,uint8_t Line);
#endif
