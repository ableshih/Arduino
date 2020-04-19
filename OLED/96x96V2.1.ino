/*
Rotation/Mirror  Description
U8G2_R0 No rotation, landscape
U8G2_R1 90 degree clockwise rotation
U8G2_R2 180 degree clockwise rotation
U8G2_R3 270 degree clockwise rotation
U8G2_MIRROR No rotation, landscape, display content is mirrored (v2.6.x)

FONT https://github.com/olikraus/u8g2/wiki/fntlistall#42-pixel-height

u8g2 wiki https://github.com/olikraus/u8g2/wiki/u8g2reference

UNO OLED
A4  SDA
A5  SCL
3V3 VCC
GND GND
*/
#include <Arduino.h>
#include <U8g2lib.h>
//#include <SPI.h>
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>

U8G2_SSD1327_SEEED_96X96_1_HW_I2C u8g2(U8G2_R3, /* reset=*/ U8X8_PIN_NONE);

void setup(void)
{
  u8g2.begin();u8g2.clear(); u8g2.clearBuffer();
}

void loop()
{
  u8g2.firstPage();
  do {
        draw();
  } while ( u8g2.nextPage() );
}

void draw() {
  //u8g2.clear();
  u8g2.setFont(u8g2_font_unifont_t_greek);
  u8g2.setCursor(0, 16);
  u8g2.print("HC-S Sensor PS");
  u8g2.drawStr(00,50,"123");//左右,上下,str

u8g2.setFontMode(1);
//u8g2.setDrawColor(1);
//u8g2.drawStr(3, 40, "Color");
//u8g2.setDrawColor(0);
//u8g2.drawStr(3, 50, "Color00");
//u8g2.setFontMode(1);

//u8g2.setDrawColor(1);
//u8g2.drawStr(3, 60, "Col11");
u8g2.setDrawColor(1);
//u8g2.drawStr(3, 80, "Colo01");
//u8g2.clearBuffer();
  
  if (0) {u8g2.drawRFrame(40, 17, 30, 22, 7);}
  else {u8g2.drawRBox(40, 25, 20, 25, 5);}
}
