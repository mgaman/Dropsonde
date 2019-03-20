struct sADS8556 {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed short ADS8556data[6];
};
