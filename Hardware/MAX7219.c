#include "MAX7219.h"
#include "gpio.h"
unsigned int column[8]={0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01};
unsigned int line[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
void CLK_0(void)
{  
  HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_RESET);
}
void CLK_1(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin,GPIO_PIN_SET);
}
void DIN_0(void)
{
    HAL_GPIO_WritePin(DIN_GPIO_Port,DIN_Pin,GPIO_PIN_RESET);

}
void DIN_1(void)
{
    HAL_GPIO_WritePin(DIN_GPIO_Port,DIN_Pin,GPIO_PIN_SET);
}

void MAX7219_WriteByte(uint8_t addr, uint8_t data)
{
    uint16_t packet = 0;  // 16位数据包
    uint8_t i;
    
    // 构建16位数据包
    // 格式：无关位(4) + 地址(4) + 数据(8)
    // 通常将无关位设为0
    packet = ((uint16_t)addr << 8) | data;
    
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
    
    // 发送16位，从最高位D15开始
    for(i = 16; i >= 1; i--)
    {
        CLK_0();
        
        if(packet & 0x8000)  // 检查最高位
        {
            DIN_1();
        }
        else
        {
            DIN_0();
        }
        
        packet = packet << 1;  // 左移，准备下一位
        CLK_1();
    }
    
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}
void MAX7219_Init(void)
{
   

    MAX7219_WriteByte(MAX7219_SHUTDOWN, 0x01);    // 正常工作模式（退出关机）
    MAX7219_WriteByte(MAX7219_DECODE, 0x00);      // 不使用BCD码
    MAX7219_WriteByte(MAX7219_SCAN_LIMIT, 0x07);  // 扫描 8 行（0x07=行 0~7）
    MAX7219_WriteByte(MAX7219_INTENSITY, 0x03);   // 亮度调节（0~15 可调）
    MAX7219_WriteByte(MAX7219_DISPLAY_TEST, 0x00);  // 关闭显示测试
        
     MAX7219_WriteByte(0x08, 0x00);
     MAX7219_WriteByte(0x01, 0x00);
     MAX7219_WriteByte(0x02, 0x00);
     MAX7219_WriteByte(0x03, 0x00);
     MAX7219_WriteByte(0x04, 0x00);
     MAX7219_WriteByte(0x05, 0x00);
     MAX7219_WriteByte(0x06, 0x00);
     MAX7219_WriteByte(0x07, 0x00);
}
void MAX7219_LightLED(uint8_t Column,uint8_t Line)
{
    
MAX7219_WriteByte(0x08, 0x00);
     MAX7219_WriteByte(0x01, 0x00);
     MAX7219_WriteByte(0x02, 0x00);
     MAX7219_WriteByte(0x03, 0x00);
     MAX7219_WriteByte(0x04, 0x00);
     MAX7219_WriteByte(0x05, 0x00);
     MAX7219_WriteByte(0x06, 0x00);
     MAX7219_WriteByte(0x07, 0x00);
    MAX7219_WriteByte(column[Column-1], line[Line-1]);
 
    
} 


