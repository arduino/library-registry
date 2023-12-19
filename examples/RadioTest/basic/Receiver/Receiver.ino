//
//
// waver 3.0
// Created 1 Jan 2024
// support@usblink.com
// www.USBLink.com
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
const int myled=20 ;

void setup()
{
  Waver.begin(12);  // channel=12
  pinMode(myled,OUTPUT);
 }

void loop()
{
  byte rc;  
  if (Waver.available())
  {
      rc=Waver.read();
      if (rc=='0') {
       digitalWrite(myled,HIGH);
    }
      else if (rc=='1') {
        digitalWrite(myled,LOW);    
    }      
  }
}
