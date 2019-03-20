struct sSensors {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  float euler[3];
  signed short ITG3200[3];
  signed short BMA180[3];
  signed long  BMP085[2];
  signed short HMC5843[3];
	char oss;
};
