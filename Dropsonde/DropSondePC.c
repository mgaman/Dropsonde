// DropSondePC.cpp : Defines the entry point for the console application.
//
// IMPORTANT set TZ=UTC in IDE Propertie/Configuration Properties/Debigging/Environment to force mktime/localtime to work properly

// Ubuntu 64 bit port
// add -m32 flag for compiler AND linker so that long is 32 bit, not 64
// swap all windows heap stuff my malloc
// replace int64_t by int64_t
// include <stdint.h> plus other libs covered by windows.h
// _localtime32_s by localtime and struct tm by my version without timezone

#include <stdint.h>
#include <stdbool.h>
#ifdef WIN32
#include "stdafx.h"
#include <windows.h>
#else
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <byteswap.h>
#define _byteswap_ulong(x) bswap_32(x)
#endif
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>


#pragma pack(1)  -- set /Zp flag instead of using pragma
// make common header for all structures
struct commonHeader
{
  unsigned char id;  // actually char
  char myID;
  unsigned long timestamp;
};

struct mytm
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/
};
#pragma pack(1)
#include "Loadcell.h"
#include "bmp085.h"
#include "bma180.h"
#include "HMC5843.h"
#include "ITG3200.h"
#include "UBX.h"
#include "ADS8556.h"
#include "Battery.h"
#include "GPSlocation.h"
#include "Sensors.h"
#include "MPU9150.h"
#include "ErrorRecord.h"
#include "Critical.h"
#include "MS561011BA3.h"
#include "LSM9DS0.h"
#include "MMC_INU.h"
#include "Sirf.h"
#include "Notification.h"
#include "MV340PD.h"
#include "PisaEEPROM.h"
#include "IMU3020.h"
#include "Calibration.h"
#include "MPU9250.h"
#include "getopt.h"

//#define SW_VERSION 0x101	// UBX data, single sensor per file
//#define SW_VERSION 0x102	// critical error expanded
//#define SW_VERSION 0x103	// fixed bug in printing barometer
//#define SW_VERSION 0x104	// added HMC5883L
//#define SW_VERSION 0x105	// added SENSOR_HMC5843,SENSOR_HMC5883L
//#define SW_VERSION 0x106	// added ACCELEROMETERCALIBRATE
//#define SW_VERSION 0x107	// added MSDCLOSE critical error, critical file name function of card number
//#define SW_VERSION 0x108	// added MPU9150
//#define SW_VERSION 0x109	// fixed basename overflow bug
//#define SW_VERSION 0x10A	// add -s -d options and multiple file input. also handle timestamp > 4G and rollovers
//#define SW_VERSION 0x10B	// add pisa MS56, LSM9DS0 stuff
//#define SW_VERSION 0x10C	// add -t -m flags, stop repeating calibration lines, bug fix in LARGE_CARD where timestamp > 4G ignored
//#define SW_VERSION 0x10D	// add MMC_INU stuff
//#define SW_VERSION 0x10E	// add MID41 stuff
//#define SW_VERSION 0x10F	// bugfix in MPU9150, extracted incorrect XM[2] scaling factor
//#define SW_VERSION 0x110	// modified MID41 to entire structure
//#define SW_VERSION 0x111	// added MPU9150_CONFIG, renamed LSM9DS0_CALIB to LSM9DS0_CONFIG
//#define SW_VERSION 0x112	// added -r for MPU9150 and LSM6DS0 raw data
//#define SW_VERSION 0x113	// added POSITION_DOUBLE LSM9DS1_CONFIG NOTIFICATION_EVENT UBXLOCATIONFIX MV340PDBURST
                            // redo FormatAltimeter bugfix
//#define SW_VERSION 0x114	// changed sExtLocationFix format, bugfix on notification epoch calculation
//#define SW_VERSION 0x115	// add UBXPVT
//#define SW_VERSION 0x116	// add MV340PDSINGLE
//#define SW_VERSION 0x117	// apply -r flag to all sensors, fix factors for LSM9DS1
//#define SW_VERSION 0x118	// Add recovery from bad data
							// bug fix when no number after -r option
//#define SW_VERSION 0x119    // bug fix in file recovery
//#define SW_VERSION 0x120    // Changed separator size to 90
//#define SW_VERSION 0x121    // added sanity check that myID is OK and command line structure
							// added backward compatibility for -r with no values
//#define SW_VERSION 0x122     // peak for good header after separator
//#define SW_VERSION 0x123     // -m flag increments first character of filename i.e A99000001.bin to B9900001.bin
//#define SW_VERSION 0x124     // -m flag increments 2nd part of name from BIN to B00,B01
                             // handle mmEEPROM.BIN file
                             // replace pragma pack by /Zp flag (because of problems)
                             // set TZ=UTC in properties/cong properties/debug/environment
//#define SW_VERSION 0x125		// added IMU3020
//#define SW_VERSION 0x125		// added general calibration (epson,imu3020,lsm9ds1)
//#define SW_VERSION 0x126		// added mpu9250_config
//#define SW_VERSION 0x127		// added NULL_REC padding
//#define SW_VERSION 0x128		// Update eeprom structure, output all contents of eeprom as SYSTEMnn.TXT
                               // typo error in extended error
#define SW_VERSION 0x129     // bugfix, lsm9ds1 is little-endian, not big
                             // bugfix in use of rawdata
//   0          1      2          3           4            5         6     7
enum eRecTypes { SENSOR_HMC5843, GPS, APP_ERROR, DEBUG_MSG, TXT_MESSAGE, LARGE_CARD, GYRO, BATTERY,
		//   8         9       10      11         12      13
		LOCATION, EXTLOCATION,UTM , UBXLOCATION, UBXRAW, BAROMETER,
//     14             15                         16                 17                  18
	  ACCELEROMETER, MAGNETOMETER_HMC5843, BAROMETERCALIBRATE, MAGNETOMETER_HMC5883L, SENSOR_HMC5883L, 
//   19                20       21            22        23        24           25             26           27                  28
    ACCELEROMETERCALIB,MPU9150,MPU9150_CONFIG,LSM9DS0_XM,LSM9DS0_G,LSM9DS0_ALL,LSM9DS0_CONFIG,MS561101BA03,MS561101BA03_CALIB,BATTERY_TEST,
//  29         30             31          32           33          34		35             36                 37
	LSM9DS0_M,MMC_INU_CONTROL,MMC_INU_NAV,MMC_INU_1PPS,MMC_INU_MLL,MID41,POSITION_DOUBLE, LSM9DS1_CONFIG, NOTIFICATION_EVENT,
//    38            39          40		41        42         43         44           45            46            47             48
	UBXLOCATIONFIX,MV340PDBURST,DS2745,UBXPVT,MV340PDSINGLE,IMU3020RAW,IMU3020CONFIG,LSM9DS1_CALIB,MV340PD_CALIB,IMU3020_CALIB, MPU9250_CONFIG,
//      49            50
	APP_ERR_XTND, NULL_REC,NUM_TYPES};
#pragma pack(1)

struct sSensors Sensors;
struct sError ErrorSt;
struct sErrorExt ErrorStExt;
//struct sGGA GGAData;
struct sExtGGA ExtGGAData;
struct sExtGGAFix ExtGGADataFix;
struct sADS8556 ADS8556;
struct sBattery Battery;
struct sGyro Gyros;
struct sRxmRaw RXMRaw;
struct sBarometer Barometer;
struct sAccelerometer Accelerometer;
struct sAccelerometerCalibrate AccelerometerCalibrate;
struct sMagnetometer Magnetometer;
struct critRecord CriticalRecord;
struct sBarometerCalibrate BarometerCalibrate;
struct sMPU9150 MPU9150data; 
struct sMPU9150_Calib MPU9150Calib;
struct sMS56_CALIBRATION MS56Calibrate;
struct sMS56_TP MS56TP;
struct sLSM9SD0_XM  LSM9SD0XMdata;
struct sLSM9SD0_G  LSM9SD0Gdata;
struct sLSM9SD0_M  LSM9SD0Mdata;
struct sLSM9SD0_All LSM9SD0AllData;
struct sLSM9SD0_Config LSM9SD0Config;
struct sBatTest BatteryData;
struct sMMC_CONTROL MMC_ControlData;
struct sMMC_NAV MMC_NavData;
struct sMID41_Data MID41Data;
struct sPositionDouble PositionDouble;
struct sLSM9SD1_Config LSM9DS1Config;
struct sNotificationX Notification;
struct sMV340PD MV340PD;
struct sMV340PDSingle MV340PDSingle;
struct sDS2745 DS2745data;
struct sNAVPVT NavPVTdata;
struct sEEPROM pisa2EEPROM;
struct sIMU3020Raw IMU3020data;
struct sIMU3020Calib IMU3020Calib;
struct sGeneralCalib GeneralCalib;
struct sMPU9250_Config MPU9250Config;

unsigned counter = 0;
unsigned allcounters[NUM_TYPES];
int lbc;
char linebuf[1000];	// should be plenty
#include <stdio.h>
FILE *infile;
FILE *outfile[NUM_TYPES] = {0};
unsigned recordCount[NUM_TYPES] = {0};
int rcFlag = 0;
//struct tm gpstime;
time_t epoch;
struct tm *temprtc;
long temperature,pressure;
double Temp,Press;
unsigned long mv340errors;
#define SEPARATOR_SIZE 90  // same as in Pisa code
//#define LARGEST_STRUCTURE_SIZE 90
unsigned char recoveryBuffer[(SEPARATOR_SIZE * 2)+2];  // add 2 bytes for peak at next header
unsigned char separator[SEPARATOR_SIZE] = { 0xff };

char *commentlines[] = {
 "%Sensors\n%counter,type,id,timestamp,gyrox,gyroy,gyroz,accelx,accely,accelz,rawpress,rawtemp,magx,magy,magz,oss,press,temp\n", // 0
 "\n", // 1
 "%AppError\n%counter,type,id,timestamp,version,linenumber,file\n", // 2
 "\n", // 3
 "\n", // 4
 "%Large\n%counter,type,id,timestamp,A0-ExtX,A1-ExtY,B0-ExtZ,B1-LC,C0-IntX,C1-IntT\n", // 5
 "%Gyro\n%counter,type,id,timestamp,X,Y,Z\n", // 6
 "%Battery\n%counter,type,id,timestamp,mVolt\n", // 7
 "\n", // 8
 "%Location\n%counter,type,id,timestamp,year,month,day,hour,min,sec,msec,lat,,long,,elev\n", // 9
 "\n", // 10
 "%Location\n%counter,type,id,timestamp,year,month,day,hour,minute,second,millsec,lat,N,long,E,alt\n", // 11
 "",	// 12
 "%Barometer\n%counter,type,id,timestamp,rawT,rawP,oss,temp,pascals\n", // 13
 "%Accelerometer\n%counter,type,id,timestamp,X,Y,Z\n", // 14
 "%Magnetometer\n%counter,type,id,timestamp,X,Y,Z\n", // 15
 "%BMP085Calibrate\n%counter,type,id,timestamp,AC1,AC2,AC3,AC4,AC5,AC6,B1,B2,MB,MC,MD\n", // 16
 "%Magnetometer\n%counter,type,id,timestamp,X,Y,Z\n", // 17
 "%Sensors\n%counter,type,id,timestamp,gyrox,gyroy,gyroz,accelx,accely,accelz,rawpress,rawtemp,magx,magy,magz,oss,press,temp\n",  // 18
 "%BMA180 Calibrate\n%counter,type,id,timestamp,X,Y,Z\n",  // 19
 "%MPU9150\n%counter,type,id,timestamp,AccelX,AccelY,AccelZ,MagX,MagY,MagZ,GyroX,GyroY,GyroZ\n",  // 20
 "%MPU9150_CONFIG\n%counter,type,id,timestamp,Accel,Gyro,Config,SampleRate\n", // 21
 "%LSM9DS0_XM\n%counter,type,id,timestamp,AccelX,AccelY,AccelZ,MagZ,MagY,MagZ\n", // 22
 "%LSM9DS0_G\n%counter,type,id,timestamp,GyroX,GyroY,GyroZ\n", // 23
 "%LSM9DS0_all\n%counter,type,id,timestamp,AccelX,AccelY,AccelZ,MagX,MagY,MagZ,GyroX,GyroY,GyroZ\n", // 24
 "%LSM9DS0_CONFIG\n%counter,type,id,timestamp,G1,G2,G3,G4,G5,X0,X1,X2,X3,X4,X5,X6,X7\n", // 25
 "%MS561101BA03\n%counter,type,id,timestamp,Temp,mBar\n", // 26
 "%MS561101BA03_CALIB\n%counter,type,id,timestamp,C1,C2,C3,C4,C5,C6\n", // 27
 "%ADC\n%counter,type,id,timestamp,RTC,MAIN,CURRENT\n", // 28
 "", // 29
 "%MMC_INU_CONTROL\ncounter,type,id,timestamp\n", // 30
 "%MMC_INU_NAV\ncounter,type,id,timestamp,opcode,counter\n", // 31
 "%MMC_INU_IPPS\ncounter,type,id,timestamp\n", // 32
 "%MMC_INU_MLL\ncounter,type,id,timestamp\n", // 33
 "%MID41\ncounter,type,id,timestamp,NavValis,Longitude,Latitude,Altitude,HDOP,Year,Month,Day,Hour,Minute,Second\n", // 34
 "%Position\ncounter,type,id,timestamp,Fix,Latitude,Longitude,Altitude,Year,Month,Day,Hour,Minute,Second\n", // 35
 "%LSM9DS1Config\ncounter,type,id,timestamp,Gscale,Ascale,Mscale\n", // 36
 "&Event\ncounter,type,id,timestamp,event,year,month,day,hour,min,sec,msec,epoch\n", // 37
 "%Location\n%counter,type,id,timestamp,year,month,day,hour,minute,second,millsec,lat,long,alt,fix\n", // 38
 "%Epson\n%counter,type,id,timestamp,temperature,gyrox,gyroy,gyroz,accelx,accely,accelz,count,ND,EA\n", // 39
 "%DS2745\n%counter,type,id,timestamp,temperature,mV,mA\n", // 40
 "%UBXPVT\n%counter,type,id,timestamp,lat,long,height,hmsl,velN,velE,velD,hAcc,vAcc,pDOP,numSV,fix,Year,Month,Day,Hour,Minute,Second,mSec\n", // 41
 "%Epson\n%counter,type,id,timestamp,temperature,gyrox,gyroy,gyroz,accelx,accely,accelz,ND,EA\n", // 42
 "%IMU3020\n%counter,type,id,timestamp,ACC C,ACC Y,ACC Z,GYRO X,GYRO Y,GYRO Z,MAG X,MAG Y,MAG Z,Temp\n", // 43
 "%IMU3020 Config\n%counter,type,id,filter Hz,SampleRate Hz,AScale g,GScale deg/sec\n", // 44
 "%LSM9DS1 Calib\n%counter,type,id\n", // 45
 "%MV340PD Calib\n%counter,type,id\n", // 46
 "%IMU3020 Calib\n%counter,type,id\n", // 47
 "%MPU9250 Config\n%counter,type,id,Acc fsr,Mag fsr,Gyro fsr,sensX,sensY,sensZ\n", // 48
 "%Trace\n%counter,type,id,timestamp,Hours,VERSION,tbd1,tbd2,tbd3,linenumber,file\n", // 49
 "", // 50
};

char *Rawcommentlines[] = {
	NULL, // 0
	NULL, // 1
	NULL, // 2
	NULL, // 3
	NULL, // 4
	NULL, // 5
	NULL, // 6
	NULL, // 7
	NULL, // 8
	NULL, // 9
	NULL, // 10
	NULL, // 11
	NULL, // 12
	NULL, // 13
	NULL, // 14
	NULL, // 15
	NULL, // 16
	NULL, // 17
	NULL, // 18
	NULL, // 19
	"%MPU9150 RAW\n%counter,type,id,timestamp,AccelX,AccelY,AccelZ,MagX,MagY,MagZ,GyroX,GyroY,GyroZ\n", // 20
	NULL, // 21
	NULL, // 22
	NULL, // 23
	"%LSM9DS0_all RAW\n%counter,type,id,timestamp,AccelX,AccelY,AccelZ,MagX,MagY,MagZ,GyroX,GyroY,GyroZ\n", // 24
	NULL, // 25
	"%MS561101BA03 RAW\n%counter,type,id,timestamp,data-0,data-1\n", // 26
	NULL, // 27
	NULL, // 28
	NULL, // 29
	NULL, // 30
	NULL, // 31
	NULL, // 32
	NULL, // 33
	NULL, // 34
	NULL, // 35
	NULL, // 36
	NULL, // 37
	NULL, // 38
	"%Epson RAW\n%counter,type,id,timestamp,temperature,gyrox,gyroy,gyroz,accelx,accely,accelz,count,ND,EA\n", // 39
	NULL, // 40
	NULL, // 41
	"%Epson RAW\n%counter,type,id,timestamp,temperature,gyrox,gyroy,gyroz,accelx,accely,accelz,ND,EA\n", // 42
	NULL, // 43
	NULL, // 44
	NULL, // 45
	NULL, // 46
	NULL, // 47
	NULL, // 48
	NULL, // 49
	NULL, // 50
};
// see dropsonde.h for this

char *sourcefilenames[] = {
"",
"CriticalError.c",
"DropSonde.c",
"RecordToFlash.c"
};
char *criticaltypes[] = {
	"MSDINIT",
	"GPSLOST",
	"BATLOW",
	"MSDERROR",
	"FAULTISR",
	"MSDCLOSE"
};

unsigned fileoffset,goodoffset;
bool rawdata[NUM_TYPES] = { false };

bool SingleWrite[NUM_TYPES];   // some files whould only be written once
unsigned usernumber, entrynumber;  // e.g for L0700818.bin usernumber is 7, entrynumber is 818

// MPU9150 conversions
float MPU9150Final[9],LSM9DS0Xfactor,LSM9DS0Gfactor,LSM9DS0Mfactor;
// to make _TCHAR same as char in regular C, go to properties/configuration/character set and change 
// Use  Unicode to Use Multibyte
// int tmain(int argc, char* argv[])

unsigned short bswap(unsigned short s)
{
	unsigned char *c = (unsigned char *)&s;
	unsigned short ss = (c[0] << 8) + c[1];
	return ss;
}

void usage()
{
	printf("Usage: dropsondePC [-s n] [-d n] [-t] [-m] [-r nn[,nn]] filename\n");
	exit(10);
}

bool validHeader(struct commonHeader *pH)
{
	return pH->id <= NUM_TYPES && pH->id != NULL_REC && pH->myID == usernumber;
}
// records may not be in order of timestamp because recording not necessarily in order of occurence of interrupt
// this allowance is an attempt to still be able to judge whether we are rolling over the 4G limit
#define OUT_OF_ORDER_ALLOWANCE 0   
#ifdef WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	char /*type,*/*fname;
	int Flush, skipData;
	int lengthread,boardid,i,j,c,fileindex,allDone;
	// sflag & dflag must handle numbers > 4G
	// records not in order of timestamp so track each independently
	unsigned /*int64_t*/ long long sflag,dflag,rdata,tincrement[NUM_TYPES] = {0},prevTimestamp[NUM_TYPES] = {0};
//	unsigned long sflag,dflag,tincrement;
	unsigned long PreviousAdsTimestamp = 0;
	//unsigned offset = 0;
	char *pBasename,*pFilepart,tempc,*pPathname,*rargs;
#if WIN32
	LPVOID  basename,newname;
#else
	void *  basename;
	void *newname;
#endif
	int filenamelength;
	struct commonHeader header,prevHeader;
	printf("Dropsonde Unpacker Version %04X\n",SW_VERSION);
	sflag = 0;
	dflag = 0;  // max possible in usecs
	allDone = 0;
	Flush = 0;
	bool titleFlag = false;
	bool multifileFlag = false;
	int numFiles = 1;  // default without -m flag, update to actual number present if -m set
	struct stat filestat;
	bool missingR = false;
	bool mpuLittleEndian = false;

//	struct sMMC_INU_Header *pMMCINUHeader;
	if (argc < 2)
		usage();
	while ((c = getopt(argc, argv, "s:d:tmr:")) != -1)
	{
		if (argc < 3)
			usage();
		switch (c)
		{
		case 's':   // -s nnn    skip nnn seconds   
			sflag = atoi(optarg);
			sflag *= 1000000;
			break;
		case 'd':   // -d nnn   stop at nnn seconds
			dflag = atoi(optarg);
			dflag *= 1000000;
			break;
		case 't':    // -t add titles
			titleFlag = true;
			break;
		case 'm':   // multiple files  // search for consecutive files after 1st file
			multifileFlag = true;
			break;
		case 'r':
			// scan next field for which files to convert
			if (isdigit((int)(*optarg)))
			{
				rargs = optarg;
				while (rargs)
				{
					rdata = atoi(rargs);
					rawdata[rdata] = true;
					if (strchr(rargs, ',') == NULL)
						rargs = NULL;
					else
						rargs = strchr(rargs, ',') + 1;
				}
			}
			else
			{
				missingR = true;  // Missing -r parameters
				printf("Backward compatibilty - default -r\r\n");
				for (i = 0; i < NUM_TYPES; i++)
					rawdata[i] = true;
//				rawdata[MPU9150] = true;
	//			rawdata[LSM9DS0_ALL] = true;
			}
			break;
		case '?':
			usage();
			break;
		}
	}
	if (dflag == 0)
	  dflag = LLONG_MAX; //_UI64_MAX;
	else
	  dflag += sflag;
	if (missingR)
		optind--;
	fileindex = optind;  // first non-option is first file name 
	// handle CRITICAL.BIN, if present
	// get boardid from filename argument and construct critical file name
	// find Lnn part, note that file name may or may not be preceded by path name, just go
	 // backwards from end of file name which is always LnnMMMMM.bin
	fname = (char *)argv[fileindex] + strlen(argv[fileindex]) - 11;  // point to 2nd character
	sscanf(fname,"%02d",&boardid);
	sprintf(linebuf,"CRIT%04d.BIN",boardid);
	printf("Opening %s\n",linebuf);
	if ((infile = fopen(linebuf/*"CRITICAL.BIN"*/,"rb")))
	{
		while (fread(&CriticalRecord,sizeof(struct critRecord),1,infile) == 1)
		{
			printf("%s %u %s %u %f %f %d/%d/%d %d:%d:%d\n",criticaltypes[CriticalRecord.error],CriticalRecord.systick,
				sourcefilenames[CriticalRecord.filenumber],CriticalRecord.linenumber,
				CriticalRecord.location.latitude.degree,CriticalRecord.location.longitude.degree,
				CriticalRecord.location.timestamp[0],CriticalRecord.location.timestamp[1],CriticalRecord.location.timestamp[2],
				CriticalRecord.location.timestamp[3],CriticalRecord.location.timestamp[4],CriticalRecord.location.timestamp[5]);
		}
		fclose(infile);
	}
	/*
	*   Handle nnEEPROM.BIN
	*/
	sprintf(linebuf, "%02uEEPROM.BIN", boardid);
	printf("Opening %s\n", linebuf);
	infile = fopen(linebuf, "rb");
	if (infile != NULL)
	{
		size_t length;
		length = fread(&pisa2EEPROM, 1, sizeof(struct sEEPROM), infile);
		//		printf("Read %u bytes\n", length);
				// report of total run time and last shutdown time
		//		if (SetEnvironmentVariable("TZ", "UTC") == 0)
		//			printf("Error %u\n", GetLastError());
#ifdef WIN32
		_localtime32_s(&temprtc, (const __time32_t *)&pisa2EEPROM.run.LastPowerDownTime);
#else
		temprtc = localtime((const time_t *)&pisa2EEPROM.run.LastPowerDownTime);
#endif
		printf("Board %u\n"
			"Last powerdown at %u/%u/%u %02u:%02u:%02u TZ %s\n"
			"Runtime %f hours\n",
			boardid, temprtc->tm_year + 1900, temprtc->tm_mon + 1, temprtc->tm_mday, temprtc->tm_hour, temprtc->tm_min, temprtc->tm_sec, getenv("TZ"), pisa2EEPROM.run.cumalativeRunTime / 3600.0);
#ifdef WIN32
		_localtime32_s(&temprtc, (const __time32_t *)&pisa2EEPROM.run.lastFatalDiskError);
#else
		temprtc = localtime((const time_t *)&pisa2EEPROM.run.lastFatalDiskError);
#endif
		printf("Last fatal disk error at %u/%u/%u %02u:%02u:%02u TZ %s\n",
			temprtc->tm_year + 1900, temprtc->tm_mon + 1, temprtc->tm_mday, temprtc->tm_hour, temprtc->tm_min, temprtc->tm_sec, getenv("TZ"));
		fclose(infile);
		// echo all eeprom contents to a system.ini file
		sprintf(linebuf, "SYSTEM%02u.INI", boardid);
		outfile[0] = fopen(linebuf, "w");
		if (outfile[0] != NULL)
		{
			fprintf(outfile[0], "# eeprom contents\n[RUN]\nID=%u\nFN=%u\nRELATIVE=%u\n",
				pisa2EEPROM.run.ID, pisa2EEPROM.run.fileNumber, pisa2EEPROM.run.GPSrelative);
			fprintf(outfile[0], "[MS561101BA03]\nOSR=%u\nRATE=%u\nACTIVE=%uSM=%u\n\n",
				pisa2EEPROM.baro.OSR, pisa2EEPROM.baro.rate, pisa2EEPROM.baro.Active, pisa2EEPROM.baro.StateMachine);
			fprintf(outfile[0], "[LSM9DS1]\nACTIVE=%u\nGSCALE=%u\nGODR=%u\nMSCALE=%u\nMODR=%u\nASCALE=%u\nAODR=%u\n",
				pisa2EEPROM.accel.Active, pisa2EEPROM.accel.Gscale, pisa2EEPROM.accel.GODR,
				pisa2EEPROM.accel.Mscale, pisa2EEPROM.accel.MODR, pisa2EEPROM.accel.Ascale, pisa2EEPROM.accel.AODR);
			fprintf(outfile[0], "[DS2745]\nMV=%u\nSECS=%u\n",
				pisa2EEPROM.battery.MV, pisa2EEPROM.battery.Secs);
			fprintf(outfile[0], "[MV340PD]\nRATE=%u\nACTIVE=%u\nDEAD=%u\n",
				pisa2EEPROM.Epson.rate, pisa2EEPROM.Epson.Active, pisa2EEPROM.Epson.Dead);
			fprintf(outfile[0], "[IMU3020]\nBAUD=%u\nFBW=%u\nACCRANGE=%u\nGYRORANGE=%u\nRATE=%u\nACTIVE=%u\n",
				pisa2EEPROM.IMU3020.BaudRate, pisa2EEPROM.IMU3020.BandWidthFilter, pisa2EEPROM.IMU3020.Ascale,
				pisa2EEPROM.IMU3020.Gscale, pisa2EEPROM.IMU3020.SampleRate, pisa2EEPROM.IMU3020.Active);
			fprintf(outfile[0], "[MPU9250]\nACTIVE=%u\nGSCALE=%u\nMSCALE=%u\nASCALE=%u\nGODR=%u\nLPF=%u\n",
				pisa2EEPROM.MPU9250.Active, pisa2EEPROM.MPU9250.Gscale, pisa2EEPROM.MPU9250.Mscale,
				pisa2EEPROM.MPU9250.Ascale, pisa2EEPROM.MPU9250.sampleRate, pisa2EEPROM.MPU9250.lowpassfilter);
		}
	}
	else
		perror(linebuf);

	// mutlti input file support, loop on all file names
	// Policy - all output CSV files are based upon 1st file names e.g. if arguments are L0700100.BIN L0700101.BIN
	// output files are L0700100-NN.CSV even when processing L0700101.BIN
	//
	//for (i=optind;i<argc;i++)
	//	printf("%s\n",argv[i]);
	//
	// calculate basename just once
	// generate name from input file
	// fix bug where basename too short
	filenamelength = strlen((char*)argv[optind]);
	// version 109 bugfix
#ifdef WIN32
	basename = HeapAlloc(GetProcessHeap(),0,2 * filenamelength);
#else
	basename = malloc(2 * filenamelength);
#endif
	if (basename == NULL)
	{
		perror("Memory allocation failed\r\n");
		return 1;
	}
	strcpy((char *)basename,(char*)argv[optind]);
	pBasename = (char *)basename + strlen((char *)basename) - 1; // point to the end
	while (*pBasename != '.')
		pBasename--;
	*pBasename = 0;
	//  at this point basename includes path (if specified). We need to separate path from file name so that we can
	// regenerate complete name when necessary
//	printf("entire %s\n",basename);
	pFilepart = pBasename - 8;  // file names always in 8.3 format
//	printf("item %s\n",pFilepart);
	sscanf(pFilepart,"%c%02d%05d",&tempc,&usernumber,&entrynumber);
	// if multiple defined, check for presence of consecutive file names
	pPathname = (char *)basename;
	*(pPathname + strlen(pPathname) -8) = 0;
//	printf("path %s\n",pPathname);
	if (multifileFlag)
	{
		char filename[256];
		sprintf(filename,"%s%c%02d%05d.BIN",pPathname,tempc,usernumber,entrynumber);
		numFiles = 0;
		while (stat(filename,&filestat) == 0)
		{
			numFiles++;
		//	entrynumber++;
			tempc++;   // increment 1st character
			sprintf(filename,"%s%c%02d%05d.BIN",pPathname,tempc,usernumber,entrynumber);
		}
	//	entrynumber -= numFiles;  // back to original number
		tempc -= numFiles;  // back to original initial
	}
//	for (fileindex=optind;fileindex<argc;fileindex++)
	for (j=0;j<numFiles;j++)
	{
		char filename[256];
		sprintf(filename,"%s%c%02d%05d.BIN",pPathname,tempc+j,usernumber,entrynumber);
		printf("Opening %s\n",filename);
//		if (!(infile = fopen((char*)argv[fileindex],"rb")))
		if (!(infile = fopen(filename,"rb")))
		{
			perror(filename);
			return 1;
		}
		// read the header, same for all sensors
		while (fread(&header,sizeof(struct commonHeader),1,infile) && !allDone)
		{
			goodoffset = fileoffset;
			fileoffset = ftell(infile);
			if (!validHeader(&header))
			{
				bool recovered = false;
				// check if this is a padding buffer
				if (header.id == NULL_REC)
				{
					// back up to beginning of header
					fseek(infile, fileoffset - sizeof(header), SEEK_SET);
					int bToRead = 512 - ((ftell(infile) + 512) % 512);
					while (bToRead)
					{
						uint8_t c;
						fread(&c, 1, 1, infile);
						if (c == NULL_REC)
							bToRead--;
						else
							break;
					}
					recovered = bToRead == 0;
				}
				if (recovered)
					continue;
				printf("Corrupted file at %04x, good record at %04x, near timestamp %d\r\n", fileoffset -sizeof(header), goodoffset - sizeof(header), prevHeader.timestamp);
				/*
				start recovery at goodoffset - sizeof(header)
				read a large block and search for separator pattern, calculate offset and skip past it
				*/
				fseek(infile, goodoffset - sizeof(header), SEEK_SET);
				fread(recoveryBuffer, sizeof(recoveryBuffer)+2, 1, infile);   // read 2 more bytes to check for valid header after separator
				memset(separator, 0xff, SEPARATOR_SIZE);
				for (skipData = 0; skipData < SEPARATOR_SIZE; skipData++)
				{
					if (memcmp(&recoveryBuffer[skipData], separator, SEPARATOR_SIZE) == 0 && validHeader((struct commonHeader *)&recoveryBuffer[skipData+ SEPARATOR_SIZE]))
					{
							// found it!
						fseek(infile, goodoffset - sizeof(header) + skipData + SEPARATOR_SIZE, SEEK_SET);
						recovered = true;
						break;
					}
				}
				if (recovered)
					continue;
				else
				{
					printf("Could not recover from corruption at %x", goodoffset - sizeof(header) + skipData);
					return 2;
				}
			}
			prevHeader = header;
		//	offset+= sizeof(struct commonHeader);
			counter++;
			if (header.id == MAGNETOMETER_HMC5843)
			{
				int j = 1;
			}
			// create output file if doesnt already exist
			if (outfile[header.id] == 0)
			{
#if WIN32
				newname = HeapAlloc(GetProcessHeap(),0,2 * filenamelength);
#else
				newname = malloc(2 * filenamelength);
#endif
				if (newname == NULL)
				{
					perror("Memory allocation failed\r\n");
					return 1;
				}
				sprintf((char *)newname,"%s%c%02d%05d-%02d.CSV",pPathname,tempc,usernumber,entrynumber,header.id);
				if (header.id == UBXRAW)
					outfile[header.id] = fopen((char *)newname,"wb");
				else
				{
					outfile[header.id] = fopen((char *)newname,"w");
					if (titleFlag)
					{
						if (rawdata[header.id] && (Rawcommentlines[header.id] != NULL))
							fputs(Rawcommentlines[header.id], outfile[header.id]);
						else
							fputs(commentlines[header.id], outfile[header.id]);
					}
				}
 				printf("Opening: %s\n",(char *)newname);
				// free up memory
			//	HeapFree(GetProcessHeap(),0,basename);
#if WIN32
 				HeapFree(GetProcessHeap(),0,newname);
#else
 				free(newname);
#endif

			}
			allcounters[header.id]++;
			Flush = 0;	// some sensors have variable length packet so need to delay flush
			//
			//  check if we are too early or too later to process data. timestamp only goes to 4G so may need to add base
	//		if (header.timestamp + tincrement[header.id] > dflag)
	//			break;	// we're all done
			if ((header.timestamp +  tincrement[header.id]) < prevTimestamp[header.id])  // indicates wrap around
			{
				//if (header.id == LARGE_CARD)
				//	printf("large card\n");
	          tincrement[header.id] += UINT_MAX;
			}
			prevTimestamp[header.id] = header.timestamp + tincrement[header.id];
			skipData =  (header.timestamp + tincrement[header.id] < sflag) || (header.timestamp + tincrement[header.id] > dflag);  // if too early, read data but ignore it
			// count records
			recordCount[header.id]++;
			switch(header.id)
			{
#if 0  // obsolete
			case SENSOR_HMC5843:
				case SENSOR_HMC5883L:
					Sensors.id = type;
					lengthread = fread(&Sensors.myID,sizeof(struct sSensors)-1,1,infile);
					if (Sensors.timestamp < sflag || Sensors.timestamp > dflag)
						break;
					offset += sizeof(struct sSensors)-1;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (AC1 != 0)	// already got the BMPCALIBRATE line
						FormatBMP085(Sensors.BMP085[0],Sensors.BMP085[1],Sensors.oss,&temperature,&pressure);
					fprintf(outfile[type],"%u,%d,%d,%u,"
						"%d,%d,%d,%d,%d,%d,%d,%d,",       
					  counter,type,Sensors.myID,Sensors.timestamp,
						Sensors.ITG3200[0],Sensors.ITG3200[1],Sensors.ITG3200[2],
						Sensors.BMA180[0],Sensors.BMA180[1],Sensors.BMA180[2],
						Sensors.BMP085[0],Sensors.BMP085[1]);
						// SWAP XYZ to XYZ for HMC8533L
					if (type == SENSOR_HMC5883L) 
						fprintf(outfile[type],"%d,%d,%d,%d,%d,%d\n",
							Sensors.HMC5843[0],Sensors.HMC5843[2],Sensors.HMC5843[1],
							Sensors.oss,temperature,pressure);
					else
						fprintf(outfile[type],"%d,%d,%d,%d,%d,%d\n",
							Sensors.HMC5843[0],Sensors.HMC5843[1],Sensors.HMC5843[2],
							Sensors.oss,temperature,pressure);
					break;
#endif
				case BATTERY:
					Battery.header = header;
					lengthread = fread(&Battery.battery,sizeof(struct sBattery)-sizeof(header),1,infile);
					if (skipData)
						break;
					//offset += sizeof(struct sBattery)-sizeof(header);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%hu\n",
					  counter,header.id,header.myID,header.timestamp+tincrement[header.id],Battery.battery);
					break;
				case ACCELEROMETER:
					Accelerometer.header = header;
					lengthread = fread(&Accelerometer.BMA180,sizeof(struct sAccelerometer)-sizeof(header),1,infile);
					// actually dint need to check every sensor, 1 enough
					if (skipData)
					{
						break;
					}
					//offset += sizeof(struct sAccelerometer)-sizeof(header);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%d,%d,%d\n",
					  counter,header.id,header.myID,header.timestamp+tincrement[header.id],Accelerometer.BMA180[0],Accelerometer.BMA180[1],Accelerometer.BMA180[2]);
					break;
				case MAGNETOMETER_HMC5843:	// reports XYZ
				case MAGNETOMETER_HMC5883L:	// reports XZY
					Magnetometer.header = header;
					lengthread = fread(&Magnetometer.HMC5843,sizeof(struct sMagnetometer)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (header.id == MAGNETOMETER_HMC5883L)
					{
						// swap ZY to YZ
						short temp = Magnetometer.HMC5843[1];
						Magnetometer.HMC5843[1] = Magnetometer.HMC5843[2];
						Magnetometer.HMC5843[2] = temp;
					}
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%d,%d,%d\n",
					  counter,header.id,header.myID,header.timestamp+tincrement[header.id],Magnetometer.HMC5843[0],Magnetometer.HMC5843[1],Magnetometer.HMC5843[2]);
					break;
				case BAROMETER:
					Barometer.header = header;
					lengthread = fread(&Barometer.bmp085values,sizeof(struct sBarometer)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%d,%d,%d,",
					  counter,header.id,header.myID,header.timestamp+tincrement[header.id],Barometer.bmp085values[0],Barometer.bmp085values[1],Barometer.oss);
					if (Barometer.bmp085values[0] == 0 || Barometer.bmp085values[0] == 0xffff || Barometer.bmp085values[1] == 0 || Barometer.bmp085values[1] == 0xffff)
						// bad data
						fprintf(outfile[header.id],"0,0\n");
					else
					{
						// translate to real data
						FormatBMP085(Barometer.bmp085values[0],Barometer.bmp085values[1],Barometer.oss,&temperature,&pressure);
						fprintf(outfile[header.id],"%d,%d\n",temperature,pressure);
					}
					break;
				case BAROMETERCALIBRATE:
					// never drop this message
					BarometerCalibrate.header = header;
					lengthread = fread(&BarometerCalibrate.data,sizeof(struct sBarometerCalibrate)-sizeof(header),1,infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (!SingleWrite[BAROMETERCALIBRATE])
					{
						CalibrateBMP085(&BarometerCalibrate);
						fprintf(outfile[header.id],"%u,%d,%d,%llu,%hd,%hd,%hd,%hu,%hu,%hu,%hd,%hd,%hd,%hd,%hd\n",
						  counter,header.id,header.myID,header.timestamp+tincrement[header.id],AC1,AC2,AC3,AC4,AC5,AC6,B1,B2,MB,MC,MD);
						SingleWrite[BAROMETERCALIBRATE] = true;
					}
					break;
				case GYRO:
					Gyros.header = header;
					lengthread = fread(&Gyros.ITG3200,sizeof(struct sGyro)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%hd,%hd,%hd\n",
					  counter,header.id,header.myID,header.timestamp+tincrement[header.id],Gyros.ITG3200[0],Gyros.ITG3200[1],Gyros.ITG3200[2]);
					break;
				case LARGE_CARD:
					ADS8556.header = header;
					lengthread = fread(&ADS8556.ADS8556data,sizeof(struct sADS8556)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (ADS8556.header.timestamp != 0x05050505)	// ignore padding records
					{
						// ignore records where timestamp goes down
						if (true /*ADS8556.header.timestamp >= PreviousAdsTimestamp*/)
						{
							PreviousAdsTimestamp = ADS8556.header.timestamp;
						//	if (tincrement[header.id] != 0)
							//	printf("%llu",header.timestamp+tincrement[header.id]);
							fprintf(outfile[header.id],"%u,%d,%d,%llu"
								",%hd,%hd,%hd,%hd,%hd,%hd"
								"\n",
								counter,header.id,header.myID,header.timestamp+tincrement[header.id],
								ADS8556.ADS8556data[0],ADS8556.ADS8556data[1],ADS8556.ADS8556data[2],
								ADS8556.ADS8556data[3],ADS8556.ADS8556data[4],ADS8556.ADS8556data[5]);
						}
					}
					break;
				case APP_ERROR:
					// never drop this message
					ErrorSt.header = header;
					lengthread = fread(&ErrorSt.version,sizeof(struct sError)-sizeof(header),1,infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,%hu,%hu,\"",
						counter,header.id,header.myID,header.timestamp + tincrement[header.id],ErrorSt.version,ErrorSt.linenumber);
					lengthread = fread(linebuf,ErrorSt.linelength,1,infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (Flush)
						break;
					linebuf[ErrorSt.linelength] = 0;
					fputs(linebuf,outfile[header.id]);
					fputs("\"\n",outfile[header.id]);
					break;
				case APP_ERR_XTND:
					// never drop this message
					ErrorStExt.header = header;
					lengthread = fread(&ErrorStExt.version, sizeof(struct sErrorExt) - sizeof(header), 1, infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id], "%u,%d,%d,%llu,%f,%hu,%d,%d,%d,%hu,\"",
						counter, header.id, header.myID, header.timestamp + tincrement[header.id], ErrorStExt.cumalativeRunTime/3600.0f,ErrorStExt.version,
						ErrorStExt.tbd1, ErrorStExt.tbd2, ErrorStExt.tbd3,ErrorStExt.linenumber);
					lengthread = fread(linebuf, ErrorStExt.linelength, 1, infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (Flush)
						break;
					linebuf[ErrorStExt.linelength] = 0;
					fputs(linebuf, outfile[header.id]);
					fputs("\"\n", outfile[header.id]);
					break;
#if 0
				case GPS:
					// read up until newline
					fread(&c,1,1,infile);
					bp = linebuf;
					while (c != 0x0d)
					{
						*bp++ = c;
						fread(&c,1,1,infile);
					}
					*bp = 0;
					printf("%u,%d,,,,,,,,,,,,,,,,\"%s\"\n",counter,type,linebuf);
					break;
	#endif
	#if 0
				case LOCATION:
					GGAData.id = type;
					lengthread = fread(&GGAData.myID,sizeof(struct sGGA)-1,1,infile);
					if (lengthread != 1)
						perror(argv[1]);
					fprintf(outfile[type],"%u,%d,%d,%u,"
								 "%d,%d,%d,"
								 "%f,%c,"
								 "%f,%c,"
							 "%f\n",
						counter,type,GGAData.myID,GGAData.timestamp,
						GGAData.location.timestamp[0],GGAData.location.timestamp[1],GGAData.location.timestamp[2],
						GGAData.location.latitude.degree,GGAData.location.latitude.hemisphere,
						GGAData.location.longitude.degree,GGAData.location.longitude.hemisphere,
						GGAData.location.elevation);
					break;
	#endif
				case EXTLOCATION:
				case UBXLOCATION:
					ExtGGAData.header = header;
					lengthread = fread(&ExtGGAData.location,sizeof(struct sExtGGA)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id],"%u,%d,%d,%llu,"
								 "%d,%d,%d,%d,%d,%d,%d,"
								 "%f,%c,"
								 "%f,%c,"
							 "%f\n",
						counter,header.id,header.myID,header.timestamp + tincrement[header.id],
						ExtGGAData.location.timestamp[0],ExtGGAData.location.timestamp[1],ExtGGAData.location.timestamp[2],ExtGGAData.location.timestamp[3],ExtGGAData.location.timestamp[4],ExtGGAData.location.timestamp[5],ExtGGAData.location.timestamp[6],
						ExtGGAData.location.latitude.degree,ExtGGAData.location.latitude.hemisphere,
						ExtGGAData.location.longitude.degree,ExtGGAData.location.longitude.hemisphere,
						ExtGGAData.location.elevation);
					break;
				case UBXLOCATIONFIX:
					ExtGGADataFix.header = header;
					lengthread = fread(&ExtGGADataFix.location, sizeof(struct sExtGGAFix) - sizeof(header), 1, infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					fprintf(outfile[header.id], "%u,%d,%d,%llu,"
						"%d,%d,%d,%d,%d,%d,%d,"
						"%f,%f,%f,%u\n",
						counter, header.id, header.myID, header.timestamp + tincrement[header.id],
						ExtGGADataFix.location.utctime.tm_year+1900, ExtGGADataFix.location.utctime.tm_mon+1, ExtGGADataFix.location.utctime.tm_mday, // y m d
						ExtGGADataFix.location.utctime.tm_hour, ExtGGADataFix.location.utctime.tm_min, ExtGGADataFix.location.utctime.tm_sec, // h m s
						ExtGGADataFix.location.utctime.tm_wday/1000000L, // msec
						(float)ExtGGADataFix.location.latitude/10E6, (float)ExtGGADataFix.location.longitude/10e6, (float)ExtGGADataFix.location.elevation/1000,
						ExtGGADataFix.location.fix);
					break;
				case DEBUG_MSG:
					// no data so already read
					// skip until cr/lf
	//				fprintf(outfile[type],"%u,%d,0,",counter,type); // no timestamp
					lbc = 0;
					while (1)
					{
						fread(&linebuf[lbc],1,1,infile);
						if (linebuf[lbc] == 0x0a)
						{
							linebuf[lbc] = 0;
		//					fprintf(outfile[type],"\"%s\"",linebuf);
							break;
						}
						else
							lbc++;
					}
					break;
				case UBXRAW:
					RXMRaw.header = header;
					lengthread = fread(&RXMRaw.recordlength,sizeof(struct sRxmRaw)-sizeof(header),1,infile);
					if (skipData)
						Flush = 1;
					lengthread = fread(linebuf,RXMRaw.recordlength,1,infile);
					if (Flush)
						break;
					fwrite(linebuf,RXMRaw.recordlength,1,outfile[header.id]);
					break;
				case ACCELEROMETERCALIB:
					// never drop this message
					AccelerometerCalibrate.header = header;
					lengthread = fread(&AccelerometerCalibrate.Offset,sizeof(struct sAccelerometerCalibrate)-sizeof(header),1,infile);
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					if (!SingleWrite[ACCELEROMETERCALIB])
					{
						fprintf(outfile[header.id],"%u,%d,%d,%llu,"
									 "%d,%d,%d\n",
							counter,header.id,header.myID,header.timestamp + tincrement[header.id],
							AccelerometerCalibrate.Offset[0],AccelerometerCalibrate.Offset[1],AccelerometerCalibrate.Offset[2]);
						SingleWrite[ACCELEROMETERCALIB] = true;
					}
					break;
				case MPU9150:
					MPU9150data.header = header;
					lengthread = fread(&MPU9150data.accelselect,sizeof(struct sMPU9150)-sizeof(header),1,infile);
					if (skipData)
						break;
					if (lengthread != 1)
						perror((char*)argv[fileindex]);
					// convert 16 bits to floating point
					for (i=0;i<3;i++)
						MPU9150Final[i] = MPU9150data.data[i] * (rawdata[MPU9150] ? 1.0f : g_fMPU9150AccelFactors[MPU9150data.accelselect]);
					for (i=3;i<6;i++)
						MPU9150Final[i] = MPU9150data.data[i] * (rawdata[MPU9150] ? 1.0f : (CONVERT_TO_TESLA * 1000000.0F / TESLA_TO_GAUSS));  // convert to microtesla
					for (i=6;i<9;i++)
						MPU9150Final[i] = MPU9150data.data[i] * (rawdata[MPU9150] ? 1.0f : (g_fMPU9150GyroFactors[MPU9150data.gyroselect]));
					fprintf(outfile[header.id],"%u,%u,%u,%llu,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
						counter,header.id,header.myID,header.timestamp + tincrement[header.id],
						MPU9150Final[0],MPU9150Final[1],MPU9150Final[2],MPU9150Final[3],MPU9150Final[4],
						MPU9150Final[5],MPU9150Final[6],MPU9150Final[7],MPU9150Final[8]);
					break;
				case MPU9150_CONFIG:
					MPU9150Calib.header = header;
					lengthread = fread(&MPU9150Calib.configregs,sizeof(struct sMPU9150_Calib)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp,
						MPU9150Calib.configregs[0],MPU9150Calib.configregs[1],MPU9150Calib.configregs[2],MPU9150Calib.configregs[3]);
					break;
				case MS561101BA03_CALIB:
					MS56Calibrate.header = header;
					lengthread = fread(&MS56Calibrate.C,sizeof(struct sMS56_CALIBRATION)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp,MS56Calibrate.C[0],
						MS56Calibrate.C[1],MS56Calibrate.C[2],MS56Calibrate.C[3],MS56Calibrate.C[4],MS56Calibrate.C[5]);
					break;
				case MS561101BA03:
					MS56TP.header = header;
					lengthread = fread(&MS56TP.data,sizeof(struct sMS56_TP)-sizeof(header),1,infile);
					if (rawdata[MS561101BA03])
						fprintf(outfile[header.id],"%u,%u,%u,%u,%u,%u\n",
							counter,header.id,header.myID,header.timestamp,MS56TP.data[0],MS56TP.data[1]);
					else
					{
						// convert to temperature/pressure
						FormatAltimeter(MS56TP.data[0], MS56TP.data[1], MS56Calibrate.C, &Temp, &Press);
						fprintf(outfile[header.id], "%u,%u,%u,%u,%f,%f\n",
							counter, header.id, header.myID, header.timestamp, Temp, Press);
					}
					break;
				case LSM9DS0_CONFIG:
					LSM9SD0Config.header = header;
					lengthread = fread(&LSM9SD0Config.G,sizeof(struct sLSM9SD0_Config)-sizeof(header),1,infile);
					LSM9DS0Xfactor = LSM9DS0AccelFactors[(LSM9SD0Config.XM[2]>>3)&0x7];  // REG2_XM
					LSM9DS0Gfactor = LSM9DS0GyroFactors[(LSM9SD0Config.G[3]>>4)&0x3];  // REG4_G
					LSM9DS0Mfactor = LSM9DS0MagnetometerFactors[(LSM9SD0Config.XM[6]>>0x1f) & 0x03]; // REG6_XM
					// now calculate conversion factors Accel in XM[2] bits 1-4
					fprintf(outfile[header.id],"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp,
							LSM9SD0Config.G[0],LSM9SD0Config.G[1],LSM9SD0Config.G[2],LSM9SD0Config.G[3],LSM9SD0Config.G[4],
							LSM9SD0Config.XM[0],LSM9SD0Config.XM[1],LSM9SD0Config.XM[2],LSM9SD0Config.XM[4],LSM9SD0Config.XM[4],
						    LSM9SD0Config.XM[5],LSM9SD0Config.XM[6],LSM9SD0Config.XM[7]);
					if (rawdata[LSM9DS0_CONFIG])
						LSM9DS0Xfactor = LSM9DS0Gfactor = LSM9DS0Mfactor = 1.0f;
					break;
				case LSM9DS1_CONFIG:
		//			mpuLittleEndian = true;    // bug, should be false
					LSM9DS1Config.header = header;
					lengthread = fread(&LSM9DS1Config.god, sizeof(struct sLSM9SD1_Config) - sizeof(header), 1, infile);																									  // now calculate conversion factors Accel in XM[2] bits 1-4
					fprintf(outfile[header.id], "%u,%u,%u,%u,%u,%u,%u\n",
						counter, header.id, header.myID, header.timestamp,
						LSM9DS1Config.god, LSM9DS1Config.aod, LSM9DS1Config.mod);
					LSM9DS0Xfactor = rawdata[LSM9DS1_CONFIG] ? 1.0f : LSM9DS1Config.aod / 32767.0F;
					LSM9DS0Gfactor = rawdata[LSM9DS1_CONFIG] ? 1.0f : LSM9DS1Config.god / 32767.0F;
					LSM9DS0Mfactor = rawdata[LSM9DS1_CONFIG] ? 1.0f : LSM9DS1Config.mod / 32767.0F;
					break;
				case MPU9250_CONFIG:
					mpuLittleEndian = true;
					MPU9250Config.header = header;
					lengthread = fread(&MPU9250Config.god, sizeof(struct sMPU9250_Config) - sizeof(header), 1, infile);																									  // now calculate conversion factors Accel in XM[2] bits 1-4
					fprintf(outfile[header.id], "%u,%u,%u,%u,%u,%u,%u,%d,%d,%d\n",
						counter, header.id, header.myID, header.timestamp,
						MPU9250Config.god, MPU9250Config.aod, MPU9250Config.mod,
						MPU9250Config.sensitivity[0], MPU9250Config.sensitivity[1], MPU9250Config.sensitivity[2]);
					LSM9DS0Xfactor = rawdata[MPU9250_CONFIG] ? 1.0f : MPU9250Config.aod / 32767.0F;
					LSM9DS0Gfactor = rawdata[MPU9250_CONFIG] ? 1.0f : MPU9250Config.god / 32767.0F;
					LSM9DS0Mfactor = rawdata[MPU9250_CONFIG] ? 1.0f : MPU9250Config.mod / 32767.0F;
					break;
				case LSM9DS0_XM:
					LSM9SD0XMdata.header = header;
					lengthread = fread(&LSM9SD0XMdata.Accel,sizeof(struct sLSM9SD0_XM)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%d,%d,%d,%d,%d,%d\n",
						counter,header.id,header.myID,header.timestamp,
						LSM9SD0XMdata.Accel[0],LSM9SD0XMdata.Accel[1],LSM9SD0XMdata.Accel[2],
						LSM9SD0XMdata.Magnetometer[0],LSM9SD0XMdata.Magnetometer[1],LSM9SD0XMdata.Magnetometer[2]);
					break;
				case LSM9DS0_G:
					LSM9SD0Gdata.header = header;
					lengthread = fread(&LSM9SD0Gdata.Gyro,sizeof(struct sLSM9SD0_G)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%d,%d,%d\n",
						counter,header.id,header.myID,header.timestamp,
						LSM9SD0Gdata.Gyro[0],LSM9SD0Gdata.Gyro[1],LSM9SD0Gdata.Gyro[2]);
					break;
				case LSM9DS0_M:
					LSM9SD0Mdata.header = header;
					lengthread = fread(&LSM9SD0Mdata.Mag,sizeof(struct sLSM9SD0_M)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%d,%d,%d\n",
						counter,header.id,header.myID,header.timestamp,
						LSM9SD0Mdata.Mag[0],LSM9SD0Mdata.Mag[1],LSM9SD0Mdata.Mag[2]);
					break;
				case LSM9DS0_ALL:
					LSM9SD0AllData.header = header;
					lengthread = fread(&LSM9SD0AllData.Accel,sizeof(struct sLSM9SD0_All)-sizeof(header),1,infile);
					if (mpuLittleEndian)
					{
						int i;
						for (i = 0; i < 3; i++)
						{
							LSM9SD0AllData.Accel[i] = (short)bswap(LSM9SD0AllData.Accel[i]);
						//	LSM9SD0AllData.Magnetometer[i] = (short)bswap(LSM9SD0AllData.Magnetometer[i]); // magnetometer already littleendian
							LSM9SD0AllData.Gyro[i] = (short)bswap(LSM9SD0AllData.Gyro[i]);
						}
					}
					if (rawdata[LSM9DS0_ALL])
						fprintf(outfile[header.id], "%u,%u,%u,%u,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
							counter, header.id, header.myID, header.timestamp,
							LSM9SD0AllData.Accel[0], LSM9SD0AllData.Accel[1], LSM9SD0AllData.Accel[2],
							LSM9SD0AllData.Magnetometer[0], LSM9SD0AllData.Magnetometer[1], LSM9SD0AllData.Magnetometer[2],
							LSM9SD0AllData.Gyro[0], LSM9SD0AllData.Gyro[1], LSM9SD0AllData.Gyro[2]);
					else
						fprintf(outfile[header.id],"%u,%u,%u,%u,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
							counter,header.id,header.myID,header.timestamp,
						LSM9SD0AllData.Accel[0]*LSM9DS0Xfactor,LSM9SD0AllData.Accel[1]*LSM9DS0Xfactor,LSM9SD0AllData.Accel[2]*LSM9DS0Xfactor,
						LSM9SD0AllData.Magnetometer[0]*LSM9DS0Mfactor,LSM9SD0AllData.Magnetometer[1]*LSM9DS0Mfactor,LSM9SD0AllData.Magnetometer[2]*LSM9DS0Mfactor,
						LSM9SD0AllData.Gyro[0]*LSM9DS0Gfactor,LSM9SD0AllData.Gyro[1]*LSM9DS0Gfactor,LSM9SD0AllData.Gyro[2]*LSM9DS0Gfactor);
					break;
				case BATTERY_TEST:
					BatteryData.header = header;
					lengthread = fread(&BatteryData.data,sizeof(struct sBatTest)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp,
						BatteryData.data[0],BatteryData.data[1],BatteryData.data[2]);
					break;
/*
				case MMC_INU_CONTROL:
					MMC_ControlData.header = header;
					lengthread = fread(&MMC_ControlData.MMC_IMU_Control_Message,sizeof(struct sMMC_CONTROL)-sizeof(header),1,infile);
				//	pMMCINUHeader = &MMC_ControlData.MMC_IMU_Control_Message.header;
					fprintf(outfile[header.id],"%u,%u,%u,%u,%4X,%u\n",
						counter,header.id,header.myID,header.timestamp,
						MMC_ControlData.MMC_IMU_Control_Message.header.opcode,MMC_ControlData.MMC_IMU_Control_Message.header.counter);
					break;
				case MMC_INU_NAV:
					MMC_NavData.header = header;
					lengthread = fread(&MMC_NavData.MMC_IMU_Nav_Message,sizeof(struct sMMC_NAV)-sizeof(header),1,infile);
				//	pMMCINUHeader = (struct sMMC_INU_Header *)&MMC_NavData.body;
					fprintf(outfile[header.id],"%u,%u,%u,%u,%4X,%u\n",
						counter,header.id,header.myID,header.timestamp,
						MMC_NavData.MMC_IMU_Nav_Message.header.opcode,MMC_NavData.MMC_IMU_Nav_Message.header.counter);
					break;
*/
				case MMC_INU_1PPS:
				case MMC_INU_MLL:
					// no data body so just print out the header
					fprintf(outfile[header.id],"%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp);
					break;
				case MID41:
					MID41Data.header = header;
					lengthread = fread(&MID41Data.NavValid,sizeof(struct sMID41_Data)-sizeof(header),1,infile);
					fprintf(outfile[header.id],"%u,%u,%u,%u,%hd,%f,%f,%f,%d,%u,%u,%u,%u,%u,%u\n",
						counter,header.id,header.myID,header.timestamp,
						MID41Data.NavValid,BELE4(MID41Data.Longitude)/10000000.0,BELE4(MID41Data.Latitude)/10000000.0,BELE4(MID41Data.AltitudeFromMSL)/100.0,MID41Data.HDOP,
						(unsigned)BELE2(MID41Data.UTCYear),MID41Data.UTCMonth,MID41Data.UTCDay,MID41Data.UTCHour,MID41Data.UTCMinute,(unsigned)BELE2(MID41Data.UTCSecond));
					break;
				case POSITION_DOUBLE:
					PositionDouble.header = header;
					lengthread = fread(&PositionDouble.location.timestamp, sizeof(struct sPositionDouble) - sizeof(header), 1, infile);
					fprintf(outfile[header.id], "%u,%u,%u,%u,%d,%f,%f,%f,%u,%u,%u,%u,%u,%u\n",
						counter, header.id, header.myID, header.timestamp,
						// lat/long are in NMEA format ddmm.mmm, convert to decimal
						PositionDouble.location.fix, NMEAtoDecimal(PositionDouble.location.latitude),
						NMEAtoDecimal(PositionDouble.location.longitude), PositionDouble.location.elevation,
						//                        year based on 1900,   month from 0
						PositionDouble.location.timestamp[0]+1900, PositionDouble.location.timestamp[1]+1, PositionDouble.location.timestamp[2],
						PositionDouble.location.timestamp[3], PositionDouble.location.timestamp[4], PositionDouble.location.timestamp[5]);
					break;
				case NOTIFICATION_EVENT:
					Notification.header = header;
					lengthread = fread(&Notification.note, sizeof(struct sNotificationX) - sizeof(header), 1, infile);
					// NOTE mktime changes isdst and tm_hour fields, so do mktime from a copy;
//					temprtc = Notification.rtc;
//					epoch = mktime(&temprtc);
					struct tm temptm;
					temptm = *(struct tm *)&Notification.rtc;
					temptm.tm_zone = 0;
					temptm.tm_gmtoff = 0;
					epoch = mktime(&temptm);
					fprintf(outfile[header.id], "%u,%u,%u,%u,%d,%u,%u,%u,%u,%u,%u,%u,%u\n",
						counter, header.id, header.myID, header.timestamp, Notification.note,
						Notification.rtc.tm_year+1900, Notification.rtc.tm_mon+1, Notification.rtc.tm_mday,
						Notification.rtc.tm_hour, Notification.rtc.tm_min, Notification.rtc.tm_sec, Notification.rtc.tm_wday/1000000L,epoch);
					break;
				case MV340PDBURST:
					MV340PD.header = header;
					lengthread = fread(&MV340PD.burst, sizeof(struct sMV340PD) - sizeof(header), 1, infile);
					if (MV340PD.burst.address == 0x20 && MV340PD.burst.cr == 0x0d && MV340PD.burst.ea == 0 && MV340PD.burst.nd == 0xFE)
					{
						if (rawdata[MV340PDBURST])
							fprintf(outfile[header.id], "%u,%u,%u,%u,%d,%d,%d,%d,%d,%d,%d,%hu,%u,%u\n",
								counter, header.id, header.myID, header.timestamp,
								(short)bswap(MV340PD.burst.temp_out),
								(short)bswap(MV340PD.burst.gyro_out[0]), (short)bswap(MV340PD.burst.gyro_out[1]), (short)bswap(MV340PD.burst.gyro_out[2]),
								(short)bswap(MV340PD.burst.accel_out[0]), (short)bswap(MV340PD.burst.accel_out[1]), (short)bswap(MV340PD.burst.accel_out[2]),
								bswap(MV340PD.burst.count_out),
								MV340PD.burst.nd, MV340PD.burst.ea);
						else
							fprintf(outfile[header.id], "%u,%u,%u,%u,%f,%f,%f,%f,%f,%f,%f,%hu,%u,%u\n",
								counter, header.id, header.myID, header.timestamp,
								V340_Temperature(bswap(MV340PD.burst.temp_out)),
								V340_Gyro(bswap(MV340PD.burst.gyro_out[0])), V340_Gyro(bswap(MV340PD.burst.gyro_out[1])), V340_Gyro(bswap(MV340PD.burst.gyro_out[2])),
								V340_Accelerometer(bswap(MV340PD.burst.accel_out[0])), V340_Accelerometer(bswap(MV340PD.burst.accel_out[1])), V340_Accelerometer(bswap(MV340PD.burst.accel_out[2])), bswap(MV340PD.burst.count_out),
								MV340PD.burst.nd, MV340PD.burst.ea);
					}
					else
					{
						printf("MV340PD error sequence %u error count %u\n", counter, mv340errors++);
					}
					break;
				case MV340PDSINGLE:
					MV340PDSingle.header = header;
					lengthread = fread(&MV340PDSingle.burst, sizeof(struct sMV340PDSingle) - sizeof(header), 1, infile);
					if (MV340PDSingle.burst.address == 0x20 && MV340PDSingle.burst.cr == 0x0d && MV340PDSingle.burst.ea == 0 && MV340PDSingle.burst.nd == 0xFE)
					{
						if (rawdata[MV340PDSINGLE])
							fprintf(outfile[header.id], "%u,%u,%u,%u,%d,%d,%d,%d,%d,%d,%d,%u,%u\n",
								counter, header.id, header.myID, header.timestamp,
								(short)bswap(MV340PDSingle.burst.temp_out),
								(short)bswap(MV340PDSingle.burst.gyro_out[0]), (short)bswap(MV340PDSingle.burst.gyro_out[1]), (short)bswap(MV340PDSingle.burst.gyro_out[2]),
								(short)bswap(MV340PDSingle.burst.accel_out[0]), (short)bswap(MV340PDSingle.burst.accel_out[1]), (short)bswap(MV340PDSingle.burst.accel_out[2]),
								MV340PDSingle.burst.nd, MV340PDSingle.burst.ea);
						else
							fprintf(outfile[header.id], "%u,%u,%u,%u,%f,%f,%f,%f,%f,%f,%f,%u,%u\n",
								counter, header.id, header.myID, header.timestamp,
								V340_Temperature(bswap(MV340PDSingle.burst.temp_out)),
								V340_Gyro(bswap(MV340PDSingle.burst.gyro_out[0])), V340_Gyro(bswap(MV340PDSingle.burst.gyro_out[1])), V340_Gyro(bswap(MV340PDSingle.burst.gyro_out[2])),
								V340_Accelerometer(bswap(MV340PDSingle.burst.accel_out[0])), V340_Accelerometer(bswap(MV340PDSingle.burst.accel_out[1])), V340_Accelerometer(bswap(MV340PDSingle.burst.accel_out[2])),
								MV340PDSingle.burst.nd, MV340PDSingle.burst.ea);
					}
					else
					{
						printf("MV340PD error sequence %u error count %u\n", counter, mv340errors++);
					}
					break;
				case DS2745:
					DS2745data.header = header;
					lengthread = fread(&DS2745data.temperature, sizeof(struct sDS2745) - sizeof(header), 1, infile);
					fprintf(outfile[header.id], "%u,%u,%u,%u,%f,%f,%f\n",
						counter, header.id, header.myID, header.timestamp,
						DS2745data.temperature * DS2745_TEMPERATURE_FACTOR, DS2745data.voltage * DS2745_VOLTAGE_FACTOR, DS2745data.current * DS2745_CURRENT_FACTOR);
						break;
				case UBXPVT:
					NavPVTdata.header = header;
					lengthread = fread(&NavPVTdata.utctime, sizeof(struct sNAVPVT) - sizeof(header), 1, infile);
					fprintf(outfile[header.id], "%u,%u,%u,%u,"
						"%.7f,%.7f,%.7f,%.7f,"
						"%d,%d,%d,%u,%u,%u,%u,%u,"
						"%d,%d,%d,%d,%d,%d,%d\n",
						counter, header.id, header.myID, header.timestamp,
						(double)NavPVTdata.lat / 10E6, (double)NavPVTdata.lon / 10E6, (double)NavPVTdata.height / 1000, (double)NavPVTdata.hmsl/1000,
						NavPVTdata.veln, NavPVTdata.vele, NavPVTdata.veld, NavPVTdata.hAcc, NavPVTdata.vAcc, NavPVTdata.pDOP, NavPVTdata.numSV, NavPVTdata.fixType,
						NavPVTdata.utctime.tm_year+1900, NavPVTdata.utctime.tm_mon+1, NavPVTdata.utctime.tm_mday, NavPVTdata.utctime.tm_hour,
						NavPVTdata.utctime.tm_min, NavPVTdata.utctime.tm_sec, NavPVTdata.utctime.tm_wday/ 1000000L);
						break;
				case IMU3020RAW:
					IMU3020data.header = header;
					lengthread = fread(IMU3020data.telem.Accel, sizeof(struct sIMU3020Raw) - sizeof(header), 1, infile);
					for (i = 0; i < 3; i++)
					{
						IMU3020data.telem.Accel[i].dw = _byteswap_ulong(IMU3020data.telem.Accel[i].dw);
						IMU3020data.telem.Gyro[i].dw = _byteswap_ulong(IMU3020data.telem.Gyro[i].dw);
						IMU3020data.telem.Mag[i].dw = _byteswap_ulong(IMU3020data.telem.Mag[i].dw);
					}
					IMU3020data.telem.temp.dw = _byteswap_ulong(IMU3020data.telem.temp.dw);
					fprintf(outfile[header.id], "%u,%u,%u,%u,"
						"%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f\n",
						counter, header.id, header.myID, header.timestamp,
						IMU3020data.telem.Accel[0].df, IMU3020data.telem.Accel[1].df, IMU3020data.telem.Accel[2].df,
						IMU3020data.telem.Gyro[0].df, IMU3020data.telem.Gyro[1].df, IMU3020data.telem.Gyro[2].df,
						IMU3020data.telem.Mag[0].df, IMU3020data.telem.Mag[1].df, IMU3020data.telem.Mag[2].df,
						IMU3020data.telem.temp.df);
						break;
				case IMU3020CONFIG:
					IMU3020Calib.header = header;
					lengthread = fread(&IMU3020Calib.filter, sizeof(struct sIMU3020Calib) - sizeof(header), 1, infile);
					fprintf(outfile[header.id], "%u,%u,%u,%u,%u, %u, %u, %u\n",
						counter, header.id, header.myID, header.timestamp,
						Filters[IMU3020Calib.filter], 800/IMU3020Calib.sampleRate, Aranges[IMU3020Calib.Arange], Granges[IMU3020Calib.Grange]);
						break;
				case LSM9DS1_CALIB:
				case MV340PD_CALIB:
				case IMU3020_CALIB:
					GeneralCalib.header = header;
					lengthread = fread(&GeneralCalib.calib, sizeof(struct sGeneralCalib) - sizeof(header), 1, infile);
					fprintf(outfile[header.id], "%u,%u,%u,%u,",
						counter, header.id, header.myID, header.timestamp);
					for (j = 0; j < 36; j++)
						fprintf(outfile[header.id],"%.10f,", GeneralCalib.calib[j]);
					fprintf(outfile[header.id], "\n");
					break;
				default:
					printf("Out of sync at %u\n", fileoffset);
					return 1;
			}
		} 
	}
	counter++;
	for (i=0;i<NUM_TYPES;i++)
	  if (recordCount[i] != 0)
		printf("Type %d Count %u\n",i,recordCount[i]);
	return 0;
}

