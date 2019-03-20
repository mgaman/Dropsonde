struct sMID41_Data {
  struct commonHeader header;
  unsigned short NavValid;		// 0
  unsigned short NavType;			// 2
  unsigned short ExtendedWeekNumber;	// 4
  unsigned long TOW;				// 6
  unsigned short UTCYear;			// 10
  unsigned char  UTCMonth;		// 12
  unsigned char  UTCDay;			// 13
  unsigned char  UTCHour;			// 14
  unsigned char  UTCMinute;		// 15
  unsigned short  UTCSecond;		// 16
  unsigned long  SatelliteList;	// 18
  long  Latitude;					// 22
  long  Longitude;				// 26
  long  AltitudeFromEllipsoid;	// 30
  long  AltitudeFromMSL;			// 34
  unsigned char Datum;			// 38
  unsigned short  SOG;			// 39
  unsigned short  COG;			// 41
  short MagVar;					// 43
  short ClimbRate;				// 45
  short HeadingRate;				// 47
  unsigned long EHPE;				// 49
  unsigned long EVPE;				// 53
  unsigned long EstimatedTimeError; // 57
  unsigned short EHVE;			// 61
  long ClockBias;					// 65
  unsigned long ClockBiasError;	// 67
  long ClockDrift;				// 71
  unsigned long ClockDriftError;	// 75
  long Distance;					// 79
  unsigned short DistanceError;	// 83
  unsigned short HeadingError;	// 85
  unsigned char NumSVinFix;		// 87
  unsigned char HDOP;				// 88
  unsigned char AdditionalModeInfo; // 89
};

// macros for endian swap
unsigned long BELE4(unsigned long s)
{
  return ((s&0xff000000)>>24)+(((s&0xff0000)>>16)<<8)+(((s&0xff00)>>8)<<16)+(((s&0xff))<<24);
}
unsigned short BELE2(unsigned short s)
{
  return ((s&0xff00)>>8) + ((s&0xff)<<8);
}
