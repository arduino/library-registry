//
// chat 
// waver 3.0
// Created 1 Jan 2024
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
uint8_t tog;
const int led=20;

void setup()
{
  tog=0;
  pinMode(led,OUTPUT);
  Waver.begin(11);// ch=11~15, if ch=0 broadcast 
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    Waver.beginTransmission();
    
    while(Serial.available())
    {
      char c = Serial.read();
      Waver.write(c);
    }
        
    Waver.endTransmission();
  }
  
  if (Waver.available())
  {
    tog=1-tog;
    while(Waver.available())
     Serial.write(Waver.read());
    digitalWrite(led,tog);
    
  }
  
  delay(10);
}


