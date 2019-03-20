//BMP085 1,7913,-1298,-14498,33949,24872,16347,5498,71,-32768,-11075,2432
//BMP085 2,7827,-1247,-14404,35142,24792,18484,5498,68,-32768,-11075,2432 
//BMP085 3,9192,-1224,-14501,33019,25100,17647,5498,66,-32768,-11075,2432
//BMP085 4,8188,-1341,-14418,35419,25054,18332,5498,74,-32768,-11075,2432
//BMP085 5,9413,-1272,-14385,35270,24771,16801,5498,70,-32768,-11075,2432
//BMP085 6,8416,-1272,-14443,34435,24863,16565,5498,70,-32768,-11075,2432
//BMP085 7,6972,-1296,-14332,35062,25051,17171,5498,71,-32768,-11075,2432
        

/*
	Calibration data for BMP085
	Indexed by card ID
*/
#if 0
struct sCalibData {
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2,MB,MC,MD;
};

struct sCalibData BMP085Calib[] = {
	{0}, //0
	{7913,-1298,-14498,33949,24872,16347,5498,71,-32768,-11075,2432}, //1
	{7827,-1247,-14404,35142,24792,18484,5498,68,-32768,-11075,2432}, //2
	{9192,-1224,-14501,33019,25100,17647,5498,66,-32768,-11075,2432}, //3
	{8188,-1341,-14418,35419,25054,18332,5498,74,-32768,-11075,2432}, //4
	{9413,-1272,-14385,35270,24771,16801,5498,70,-32768,-11075,2432}, //5
	{8416,-1272,-14443,34435,24863,16565,5498,70,-32768,-11075,2432},	//6
	{6972,-1296,-14332,35062,25051,17171,5498,71,-32768,-11075,2432}	//7
};
#else
	short AC1,AC2,AC3;
	unsigned short AC4,AC5,AC6;
	short B1,B2,MB,MC,MD;
#endif

struct sBarometer {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed long bmp085values[2];
	char oss;
	};

struct sBarometerCalibrate {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  short data[11];
};

// useful macros
#define TWOP2 4
#define TWOP4 16
#define TWOP8 256
#define TWOP11 2048
#define TWOP12 4096
#define TWOP13 8192
#define TWOP15 32768
#define TWOP16 65536
//#define oss 0

long UT,X1,X2,X3,B5,B6,B3,UP,p;
unsigned long B4,B7;

void FormatBMP085(long tdata, long pdata, char oss,long *T, long *P )
{
	UT = tdata;
	X1 = (UT-AC6) * AC5 / TWOP15;
	X2 = (MC * TWOP11) / (X1+MD);
	B5 = X1 + X2;
	*T = (B5+8)/TWOP4;
    UP = pdata;
    B6 = B5 - 4000;
    X1 = (B2 * (B6 * B6 / TWOP12)) / TWOP11;
    X2 = AC2 * B6 / TWOP11;
    X3 = X1 + X2;
    B3 = (((AC1*4+X3)<<oss) + 2)/4;
    X1 = AC3 * B6 / TWOP13;
    X2 = (B1 * (B6*B6/TWOP12))/TWOP16;
    X3 = ((X1+X2)+2)/TWOP2;
    B4 = AC4 * (unsigned long)(X3 + 32768)/TWOP15;
    B7=((unsigned long)UP-B3)*(50000>>oss);
    if (B7<0X80000000)
      p = (B7 * 2) / B4;
    else
      p = (B7/B4) * 2;
    X1 = (p/TWOP8) * (p/TWOP8);
    X1 = (X1 * 3038) / TWOP16;
    X2 = (-7357 * p ) / TWOP16;
    *P = p + (X1 + X2 + 3791)/TWOP4;
}

void CalibrateBMP085(struct sBarometerCalibrate *bc)
{
	AC1 = (short)bc->data[0];
	AC2 = (short)bc->data[1];
	AC3 = (short)bc->data[2];
	AC4 = (unsigned short)bc->data[3];
	AC5 = (unsigned short)bc->data[4];
	AC6 = (unsigned short)bc->data[5];
	B1 = (short)bc->data[6];
	B2 = (short)bc->data[7];
	MB = (short)bc->data[8];
	MC = (short)bc->data[9];
	MD = (short)bc->data[10];
}
