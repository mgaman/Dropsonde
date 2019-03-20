/*
	ITG3200 data
*/
struct sGyro {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed short ITG3200[3];
};

