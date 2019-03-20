// miznack
struct sBattery {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  unsigned short battery;
};

// pisa
struct sBatTest {
#if 0
  enum eRecTypes type;
  char myid;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  unsigned short data[3];
};

struct sDS2745 {
	struct commonHeader header;
	short temperature;
	short voltage;
	short current;
};

#define DS2745_TEMPERATURE_FACTOR 0.125   // to deg centigrade
#define DS2745_VOLTAGE_FACTOR 4.88     // to millivolt
#define DS2745_CURRENT_FACTOR 0.00156  // to milliamp
