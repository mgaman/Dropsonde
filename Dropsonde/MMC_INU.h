/*
	Based upon header files from Rafael
*/
#include "icd_IMU.h"

struct sMMC_CONTROL {
  struct commonHeader header;
  //unsigned char body[MMC_CONTROL_LENGTH];
  SIsuMmcControlMsg MMC_IMU_Control_Message;
};
struct sMMC_NAV {
  struct commonHeader header;
  //unsigned char body[MMC_NAV_LENGTH];
  SIsuMmcNavMsg MMC_IMU_Nav_Message;
};
struct sMMC_1PPS {
  struct commonHeader header;
  // no body, just need the time
};
struct sMMC_MLL {
  struct commonHeader header;
  // no body, just need the time
};

