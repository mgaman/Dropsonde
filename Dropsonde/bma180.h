/*
   accelerometer structures
*/
  struct sAccelerometer {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed short BMA180[3];
};

  struct sAccelerometerCalibrate {
#if 0
  char id;  // actually char
  char myID;
  unsigned long timestamp;
#else
  struct commonHeader header;
#endif
  signed short Offset[3];
};