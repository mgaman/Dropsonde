/*
    David Henry davidh@zickel.net
*/
struct sPoint {
  float degree;
  char hemisphere;
};


struct sExtLocation {
  unsigned short timestamp[7];  // yy:mm:dd:hh:mm:ss:msec
  struct sPoint latitude;
  struct sPoint longitude;
  float elevation;
};

struct sExtLocationFix {
	struct mytm utctime;
	long latitude;
	long longitude;
	long elevation;
	unsigned char fix;
};

struct sExtGGA {
  struct commonHeader header;
  struct sExtLocation location;
};

struct sExtGGAFix {
	struct commonHeader header;
	struct sExtLocationFix location;
};

struct sAbsLocation {
	int timestamp[7];  // yy:mm:dd:hh:mm:ss :ms
	int fix;
	double latitude;
	double longitude;
	double elevation;
};

struct sPositionDouble {
	struct commonHeader header;
	struct sAbsLocation location;
};

struct sNAVPVT {
	struct commonHeader header;
	struct mytm utctime;
	long lat, lon, height, hmsl;
	long veln, vele, veld;
	unsigned long hAcc, vAcc;
	unsigned char numSV, fixType;
	unsigned short pDOP;
};

/*
   Convert ddmm.mmm format to dd.dddd format
*/
double NMEAtoDecimal(double raw)
{
#if 1
	int ddmm = (int)raw;
	int deg = ddmm / 100;
	double min = raw - (deg*100);
	return deg + (min / 60.0);
#else
	return raw;
#endif
}
