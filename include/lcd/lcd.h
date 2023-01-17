#ifndef __LCD_H
#define __LCD_H

#include <stdint.h>
#include <stdio.h>

#include "gd32vf103_gpio.h"
#include "stdlib.h"
#include "systick.h"

#define USE_HORIZONTAL 2  // Set horizontal or vertical screen display 0 or 1 for vertical screen 2 or 3 for horizontal screen
#define HAS_BLK_CNTL 0

#define LCD_A 240
#define LCD_B 135

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W LCD_B
#define LCD_H LCD_A
#else
#define LCD_W LCD_A
#define LCD_H LCD_B
#endif

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

// -------------------------------Transcription---------------------------
#define UBYTE uint8_t
#define UWORD uint16_t
#define UDOUBLE uint32_t
#define DEV_CS_PIN GPIO_PIN_2
#define DEV_RST_PIN GPIO_PIN_1
#define DEV_DC_PIN GPIO_PIN_0

#define DEV_SPI_WRITE(_dat) LCD_Writ_Bus(_dat)
#define DEV_Delay_ms(__xms) delay_1ms(__xms)
#define DEV_Digital_Write(_pin, _value) (_value ? gpio_bit_set(GPIOB, _pin) : gpio_bit_reset(GPIOB, _pin))
#define DEV_Digital_Read(_pin) gpio_input_bit_get(GPIO_B, _pin)
void LCD_WriteData_Byte(UBYTE da);
void LCD_WriteData_Word(UWORD da);
void LCD_WriteReg(UBYTE da);

void LCD_SetCursor(UWORD x1, UWORD y1, UWORD x2, UWORD y2);
void LCD_SetUWORD(UWORD x, UWORD y, UWORD Color);
void LCD_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD UWORD);

// -------------------------------End transcription---------------------------

// #define LED_ON gpio_bit_reset(GPIOC,GPIO_PIN_13)
// #define LED_OFF gpio_bit_set(GPIOC,GPIO_PIN_13)

#define LED_ON
#define LED_OFF

#define SPI0_CFG 1  // hardware spi
// #define SPI0_CFG 2  //hardware spi dma
// #define SPI0_CFG 3  //software spi

#define FRAME_SIZE 25600

//-----------------OLED端口定义----------------
#if SPI0_CFG == 1
#define OLED_SCLK_Clr()
#define OLED_SCLK_Set()

#define OLED_SDIN_Clr()
#define OLED_SDIN_Set()

#define OLED_CS_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_2)  // CS PB2
#define OLED_CS_Set() gpio_bit_set(GPIOB, GPIO_PIN_2)
#elif SPI0_CFG == 2
#define OLED_SCLK_Clr()
#define OLED_SCLK_Set()

#define OLED_SDIN_Clr()
#define OLED_SDIN_Set()

#define OLED_CS_Clr()
#define OLED_CS_Set()
#else                                                      /* SPI0_CFG */
#define OLED_SCLK_Clr() gpio_bit_reset(GPIOA, GPIO_PIN_5)  // CLK PA5
#define OLED_SCLK_Set() gpio_bit_set(GPIOA, GPIO_PIN_5)

#define OLED_SDIN_Clr() gpio_bit_reset(GPIOA, GPIO_PIN_7)  // DIN PA7
#define OLED_SDIN_Set() gpio_bit_set(GPIOA, GPIO_PIN_7)

#define OLED_CS_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_2)  // CS PB2
#define OLED_CS_Set() gpio_bit_set(GPIOB, GPIO_PIN_2)
#endif /* SPI0_CFG */

#define OLED_RST_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_1)  // RES PB1
#define OLED_RST_Set() gpio_bit_set(GPIOB, GPIO_PIN_1)

#define OLED_DC_Clr() gpio_bit_reset(GPIOB, GPIO_PIN_0)  // DC PB0
#define OLED_DC_Set() gpio_bit_set(GPIOB, GPIO_PIN_0)

#if HAS_BLK_CNTL
#define OLED_BLK_Clr() gpio_bit_reset(GPIOA, GPIO_PIN_5)  // BLK
#define OLED_BLK_Set() gpio_bit_set(GPIOA, GPIO_PIN_5)
#else
#define OLED_BLK_Clr()
#define OLED_BLK_Set()
#endif

#define OLED_CMD 0   // Write command
#define OLED_DATA 1  // Write data

extern u16 BACK_COLOR;  // Background color
extern unsigned char image[12800];

void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);
void Lcd_Init(void);
void LCD_Clear(u16 Color);
void LCD_ShowChinese(u16 x, u16 y, u8 index, u8 size, u16 color);
void LCD_DrawPoint(u16 x, u16 y, u16 color);
void LCD_DrawPoint_big(u16 x, u16 y, u16 color);
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2, u16 color);
void Draw_Circle(u16 x0, u16 y0, u8 r, u16 color);
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 mode, u16 color);
void LCD_ShowString(u16 x, u16 y, const u8 *p, u16 color);
u32 mypow(u8 m, u8 n);
void LCD_ShowNum(u16 x, u16 y, u16 num, u8 len, u16 color);
void LCD_ShowNum1(u16 x, u16 y, float num, u8 len, u16 color);
void LCD_ShowPicture(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_ShowLogo(void);

// Brush color
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40  // brown
#define BRRED 0XFC07  // maroon
#define GRAY 0X8430   // gray

// GUI color

#define DARKBLUE 0X01CF   // navy blue
#define LIGHTBLUE 0X7D7C  // light blue
#define GRAYBLUE 0X5458   // gray blue
// The above three colors are the colors of PANEL

#define LIGHTGREEN 0X841F  // light green
#define LGRAY 0XC618       // Light gray (PANNEL), form background color

#define LGRAYBLUE 0XA651  // Light gray blue (middle layer color)
#define LBBLUE 0X2B12     // Light brown blue (inverted color of selected item)

#endif