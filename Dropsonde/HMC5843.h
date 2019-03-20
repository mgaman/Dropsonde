/*
	HMC5843 data
*/
struct sMagnetometer {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed short HMC5843[3];
};
