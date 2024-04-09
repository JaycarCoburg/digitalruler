# Digital Ruler
An Arduino-Based Digital Ruler using OLED and a IR-Distance Sensor.

## Components Needed
- Arduino Uno *or* Arduino Compatable Board \([XC9202](https://www.jaycar.com.au/arduino-uno-rev3-arduino-development-board/p/XC9202) *or* [XC4410](https://www.jaycar.com.au/duinotech-uno-r3-main-board/p/XC4410)\) *or* an alternative microcontroller.
- SHARP IR Distance Sensor \([XC3735](https://www.jaycar.com.au/duinotech-arduino-compatible-ir-distance-sensor/p/XC3735)\)
- 128x64 OLED Display \([XC3735](https://www.jaycar.com.au/duinotech-arduino-compatible-1-3-inch-monochrome-oled-display/p/XC3728)\)
- Jumper Leads Mixed Pack \([WC6027](https://www.jaycar.com.au/jumper-lead-mixed-pack-100-pieces/p/WC6027)\)
## Optional Components and Tools
These components are optional. Their use is discussed in the next section.
- Mini Breadboard \([PB8817](https://www.jaycar.com.au/arduino-compatible-mini-breadboard-with-170-tie-points/p/PB8817)\)
- Solder-Splices, 6 Pack \([WH5669](https://www.jaycar.com.au/1-7mm-solder-splice-heatshrink-pack-of-6/p/WH5669)\)
- Wire Stripper  \([TH1841](https://www.jaycar.com.au/stainless-steel-wire-stripper-cutter-pliers/p/TH1841) *or* [TH1827](https://www.jaycar.com.au/heavy-duty-wire-stripper-cutter-crimper-with-wire-guide/p/TH1827) *or* [TH1824](https://www.jaycar.com.au/wire-stripper/p/TH1824)\)
- Pocket Blowtorch \([TH1610](https://www.jaycar.com.au/pocket-gas-torch/p/TH1610)\)

## Wiring and Assembly
The wiring diagram is provided below:

![Wiring Diagram](img/arduino_circuit.png)

Please note that you may require a breadboard to connect more that 1 wire to the 5V pin on the arduino.
You will also need to connect the bare-wires from the Distance Sensor to Dupont wires in order to connect to the Arduino.
This can be completed using the solder-splice and the wire-strippers.

## Libraries
The following libraries must be installed. This can be through the Arduino IDE directly, or through the links provided.
- [U8glib](https://github.com/olikraus/u8glib) by Oli Kraus.

## Code
The following code should be compiled and uploaded to the microcontroller VIA the Arduino IDE.
Make sure that when uploading, you select the correct board and the correct port.

```cpp
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
```
