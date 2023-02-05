

// **** To WRITE/DEBUG your application -- operate Mstor at low speed 38.4k baud with Arduino Serial Monitor active:  ***********
//	1) define DEBUG (as any value below)
//  2) communicate with Mstor using  MstorPort on pins  RX_PIN (8-12),  TX_PIN(8-12) below. Set Mstor jumpers to connect these signals
//  3) send debug messages to  Serial debug port using  Serial.println(string);

// **** If 38.4kbaud  (3k bytes/sec) is not fast enough for your application switch to high-speed mode after debugging complete:
//	1)  comment out  DEBUG  definition below
//	2)  Replace  "Serial."   in your application source file with  "//Serial."    to disable debug messages & use of the high-speed debug port
//  3)  Set Mstor jumpers to connect Arduino D0 and D1  to RX/TX,  and continue to communicate to Mstor  using MstorPort which can now be high-speed.
//      (Mstor will use the Serial port, so change  Serial.begin(baud)  to  high-baud


#define DEBUG			0				//comment out to operate Mstor at high speed using an RS232 shield connected to
										//an external terminal as the Serial Monitor


#define MS_PER_TICK  2
#define MSTOR_TIMEOUT 1000		//use 1000ms as the default command timeout period
#define MSTOR_TIMER  2			//use Timer 1 or Timer 2 for a 2ms timer (Arduino uses Timer 0 for millis() )

extern SoftwareSerial SSserial;	//and MstorPort is a SoftwareSerial Port

//DEBUG SECTION SETTINGS
#ifdef DEBUG			 		//if DEBUG is defined above then Mstor will use a (slow) SoftwareSerial port
  //Serial Monitor uses HardwareSerial port on D0 & D1
  #define MonitorPort Serial	//during debugging, Serial is the Serial Monitor port at 115k baud
  #define MONITOR_SPEED 115200	//use the high-speed serial port as Serial Monitor
  //Mstor uses SoftwareSerial port on designated pins
  #define MstorPort SSserial	// and SSserial talks to Mstor at 38.4k
  #define TX_PIN  9      		//SoftwareSerial out pin.
  #define RX_PIN  8     		//SoftwareSerial in pin
  #define RESET_PIN 10			//Arduino output pin used to RESET Mstor
  #define MSTOR_SPEED 38400

//HIGH_SPEED SECTION SETTINGS
#else
  //Mstor uses HardwareSerial port on D0 & D1
  #define MstorPort Serial			//if not debugging, MstorPort is the HIGH SPEED  port
  #define MSTOR_SPEED 250000		//250k max for reliable data transfers

  //Monitor uses SoftwareSerial port on designated pins
  #define MonitorPort SSserial	//and the Monitor port is a SoftwareSerial Port (which needs RS232 Shield to talk to ext terminal)
  #define TX_PIN  9      		//SoftwareSerial out pin.
  #define RX_PIN  8     		//SoftwareSerial in pin
  #define RESET_PIN 10			//Arduino output pin used to RESET Mstor
  #define MONITOR_SPEED 38400
#endif



//Advanced debugging .. Versalent personnel only
//#define INJECT_ERRORS 	0			//with this defined, errors are injected into received packets -- can see errors occur, and the corrections
//#define SHOW_ERRORS		0			//show any read errors that occur .. and their corrections