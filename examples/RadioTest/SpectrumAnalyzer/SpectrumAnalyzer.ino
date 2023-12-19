/*

Run this sketch using a Zigduino and monitor the serial output
it will output comma separated data values when
you trigger it by sending something to the serial port

The comma separated format looks like
channel #, frequency, ED Level, RSSI

dump the data into a spreadsheet program and plot it out

try turning on other 2.4 GHz devices and see if the data changes

note that the valid channels for the PLL are from 11 to 26

*/

//
// Spectrum Analyzer
//
// waver 3.0
// Created 1 Jan 2014
// By support@usblink.com
// www.usblink.com
//
//
//    Pin.NO   NAME     PORT            Etc           
//
//	 0	PWM1	PB7
//	 1	PWM2	PG5		PCINT7
//	 2	PWM3	PB5		PCINT5
//	 3	PWM4	PB6		PCINT6
//	 4	PWM5	PB4		PCINT4
//	 5	PWM6	PE3
//	 6	PWM7	PE4
//	 7	PWM8	PE5
//       8      SS	PB0		PCINT0
//	 9	TX1	PD3
//	10	RX1	PD2
//	11	SCL	PD0
//	12	SDA	PD1
//	13	A0	PF0
//	14	A1	PF1
//	15	SCK	PB1		PCINT1
//	16	MOSI	PB2		PCINT2
//	17	MISO	PB3		PCINT3
//	18	RX0	PE0		PCINT8	
//      19	TX0	PE1
//      20	LED	PE5             built_in Led 

#include <waver.h>

void setup()
{
  Waver.begin(11);
  Serial.begin(9600);
  
  Waver.attachError(errHandle);
  
  Serial.println(); // signal the start with a new line
}

void loop()
{
  if (Waver.available()) {
     while(Waver.available())
     Serial.write(Waver.read());

      Waver.setChannel(11);
      Serial.print("\t");
      Serial.print(((int16_t)(11*5))+2350, 10);// Current Channel
      Serial.print(",");
      Serial.print(Waver.getEdNow(), 10); // Energe Detect Level
      Serial.print(",");
      Serial.print(Waver.getRssiNow(), 10);// RSSI (Received Signal Strength Indicatior) dBM
      Serial.println("");
}
  
}

void errHandle(radio_error_t err)
{
  Serial.println();
  Serial.print("Error: ");
  Serial.print((uint8_t)err, 10);
  Serial.println();
}

