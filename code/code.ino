#include "U8glib.h"

// Only use this if you're using an i2c OLED.
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

// This is for SPI OLEDs
U8GLIB_SH1106_128X64 u8g(13, 11, 9, 10); // SCK = 13, MOSI = 11, CS = 10, A0 = 9
#define OLED_RESET 12

uint16_t dist = 0; //between 0 and 1023
float refresh = 1000/60; //60 Hz


void draw(void) {
 // graphic commands to redraw the complete screen should be placed here
 u8g.setFont(u8g_font_unifont);
 //u8g.setFont(u8g_font_osb21);
 u8g.drawStr( 0, 18, "Digital Ruler");
 u8g.drawBox( 0, 50, dist >> 3 , 14 );

}
void setup(void) {
 u8g.setColorIndex(1);
 Serial.begin(9600);

 //Reset the OLED
 pinMode(OLED_RESET, OUTPUT);
 digitalWrite(OLED_RESET, LOW);
 delay(100);
 digitalWrite(OLED_RESET, HIGH);
}

void loop(void) {
  //Serial.println("helloworld");
  dist = analogRead(A3);
 // picture loop
 u8g.firstPage();
 do {
 draw();
 } while( u8g.nextPage() );
 
 delay(refresh);
}
