/*
  Mstor.h - driver for Versalent Mstor Arduino Disk Shield
  Created by John Ursoleo 12/12/2022
  Released into the public domain.
  Allows Mstor to operate at low-speed using SoftwareSerial with Arduino Serial Monitor port active, or
  can use Arduino's hardware 'Serial' port at high speed for Mstor but with no Serial Monitor available.

  This file should not be edited.  All user-configurations are contained in mstorcfg.h
*/


#include "Arduino.h"

//mstor error codes
#define NO_ERROR						0
#define BAD_COMMAND 					1
#define FILE_NOT_FOUND 					2
#define DIRECTORY_NOT_FOUND 			3
#define FAILED_TO_OPEN_FILE 			4
#define FAILED_TO_CLOSE_FILE			5
#define INVALID_PARAMETER 				6
#define INVALID_COMMAND_LENGTH 			7
#define FILE_WRITE_ERROR 				8
#define DIR_PATH_ERROR 					9
#define UNKNOWN_COMMAND_STATE 			10
#define FAILED_TO_CREATE_DIRECTORY 		11
#define	FAILED_TO_DELETE 				12
#define INVALID_COMMAND_MODE 			13
#define TOO_MANY_CONSECUTIVE_RETRIES 	14
#define INVALID_8P3NAME 				15
#define WILDCARDS_NOT_ALLOWED 			16
#define COMMAND_CHECK_ERROR				17
#define FAILED_TO_RENAME_FILE 			18
#define FILE_READ_ERROR 				19
#define	INITIALIZATION_FAILED			20
#define COMMAND_TOO_LONG				21
#define INVALID_DECIMAL_POSITION 		22
#define INVALID_8P3_CHARACTER			23
#define FNAME_TOO_LONG 					24
#define DISK_NOT_READY 					25
#define INVALID_PACKET					26
#define GENERAL_ERROR					27
#define SOURCE_NOT_FOUND				28
#define USER_ABORT						29
#define COMMAND_TIMEOUT					30
#define INVALID_RETRY_REQUEST 			31
#define UNRECOVERABLE_PACKET_FAIL		32
#define MSTOR_NOT_FOUND					33
#define POWER_FAILURE					34
#define BLOCK_SIZES_DO_NOT_MATCH		35
#define INVALID_TIMEOUT					36
#define INVALID_FILE_MODE				37
#define FILEISZE_ERROR					38
#define BAD_BATTERY						39
#define END_OF_ERRORS					40

#define ACK	0x06
#define NAK	0x15
#define CARET	0x0d
#define NOTIFY 			true
#define NO_NOTIFY		false
#define PACKET_RETRY	true
#define NO_PACKET_RETRY false
#define DATA_SIZE 			32
#define MAX_CMD_LENGTH		46							//user command entries can be 45 characters (plus null = 46)
#define MIN_TIMEOUT			500
#define MAX_TIMEOUT			5000



//start Mstor class definition
class Mstor
{
  public:

  	byte data[DATA_SIZE];						// Arduino limited to 32 bytes to conserve data space
  	byte data_count = 0;						// count of DD..D  (data bytes only, up to DATA_SIZE=32 maximum)
	byte error_code = 0;
	byte mstor_initialized = false;				//if mstor has valid blocksize and timeout values (allow disk commands)
	byte mstor_connected = false;				//if mstor block size matches, and have retrieved mstor timeout
	char mstor_version[14];
	unsigned int timeout_ms;

//public methods
  	Mstor();											//this is the Mstor constructor
  	byte init_mstor();									//must be called before anything else .. to find mstor

	void hexit(unsigned char * data, unsigned char count);
	unsigned int get_elapsed_ms();
	void restart_elapsed_ms();							//timer for host application use
	void run_ms_timer();								//must be called by a timer ISR regularly every 2-25ms

//file and directory access methods
	unsigned char fileOpen(char mode, char * filename);		//filename including optional path = 45 chars maximum
	unsigned char fileSeek(char * filename, unsigned long ofst);
	unsigned char fileRead();
	unsigned char fileWrite();					//user has placed up to 32 bytes in Mstor.data .. and set Mstor.data_count
	unsigned char fileWrite(char * cmdstr);		//user can send a string of up to 45 chars maximum
	unsigned char listRead();
	unsigned char fileClose();
	unsigned char fileDelete(char * spathfile);		//spathfile is a string with a maximum of 45 characters
	unsigned char fileRename(char * oldname, char * newname);		//spathfile 45 chars max
	unsigned char fileCopy(char * fromfile, char * tofile);	//fromfile and tofile each 22 chars maximum including optional paths
	unsigned char fileConcat(char * f1, char * f2, char * ftarg);
	unsigned char fileList(char * scmd);			//overload that accepts a mask
	unsigned char fileList();						//overload that accepts no params
	unsigned char dirList(char * scmd);
	unsigned char makeDir(char * scmd);
	unsigned char deleteDir(char * scmd);
	unsigned char getCurrentDir(unsigned char offset);		//get up to 32 chars of current directory starting at offset
	unsigned char changeDir(char * dirstr);
	unsigned char getFileSize(char * pathfile);

//Mstor management methods
	unsigned char getVersion();
	unsigned char getTime();
	unsigned char setTime(char * timestr);
	unsigned char getDate();
	unsigned char setDate(char * datestr);
	unsigned char getPower();
	unsigned char setPower(char * pstr);
	unsigned char mstorReset();
	unsigned char getMode();
	unsigned char getCmdTimeout();
	unsigned char setCmdTimeout(char * timeout);
	unsigned char getClkCal();					//get clock calibration value
	unsigned char setClkCal(char val);			//set calibration -127 to +127
	unsigned char setBlocksize(char * bsize);		//value is sent as a decimal string  i.e. "32"
	unsigned char testBattery();
	unsigned char set_mstor_baudrate(unsigned char baud);
	int getMstorBlksize();					//this returns an integer, not a result-code




  private:
	byte _packet[DATA_SIZE + 5];
	unsigned int _elapsed_ms = 0;
	unsigned int _mstor_ms = 0;
	byte _ms_per_tick;
	byte _packet_count = 0;


//private methods
	unsigned int get_mstor_ms();
	void restart_mstor_ms();				//timer for internal driver use
	byte get_packet(unsigned int timeout, unsigned char allow_retry, char retry_cmd);
	void build_framed_retry_cmd(unsigned char * fcmd, char rcmd);
	byte check_for_ACK(unsigned int timeout);
	unsigned int compute_crc(unsigned char * blk, unsigned char blk_size);
	void build_cmd_block(unsigned char * blk, unsigned char * count);
	unsigned char validate_packet(unsigned char * buf, unsigned char count);
	unsigned char execute_command (char * mstor_cmd, unsigned char notify_host);		//execute a command string
	unsigned char execute_command(char cmd, unsigned char * cmdarray, unsigned char count, unsigned char notify_host);  //execute a command array
	unsigned char get_single_packet_response(unsigned int timeout, unsigned char notify_host);
	unsigned char get_packet(unsigned int timeout);
	unsigned char extract_error(unsigned char * nakstr);
	void build_data_block(unsigned char num_bytes, unsigned char blk_req);
	unsigned char check_connected();

	unsigned int get_mstor_timeout();
	byte send_packet(unsigned int timeout);

};			//Mstor class ends


// ****************** these functions are not part of the Mstor class
	byte get_recv_buf_count();
	unsigned char get_xmit_buf_available();
	byte get_serial_char();
	void flush_recv_buffer();
	void send_serial_char(unsigned char val);
	void send_serial_string(char * sval);
	void send_serial_array(unsigned char * sval, unsigned char length);




