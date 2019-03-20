struct sRxmRaw {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  unsigned short recordlength;
  // char text []
};

#if 0
struct sRxmRawHeader {
	unsigned long TOW;
	unsigned short week;
	unsigned char numSV;
	unsigned char reserved;
};

struct sRxmSV {
	double cpMes;
	double prMes;
	float doMes;
	unsigned char sv;
	char mesQI;
	char cno;
	unsigned char lli;
};
#endif