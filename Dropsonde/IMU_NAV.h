


#ifndef IMU_NAV_h
#define IMU_NAV_h

 #if defined WIN32 || defined __LINUX__
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif

/* Create compilation error when a message have an unexpected size: */
#ifndef ASSERT_MESSAGE_SIZE
#define ASSERT_MESSAGE_SIZE(macMessageName,macExpectedMessageSize) \
    const int RIDASizeOf##macMessageName = macExpectedMessageSize / (int)(sizeof(macMessageName)==macExpectedMessageSize);
#endif


#include "commonDef.h"                                           /* MMC_ISU\IMU_NAV.h */


/*---------------------- System Versions ----------------------*/

static const float h_ver_IMU_NAV = 0.1f;                         /* Header File Version */
static const float icd_ver_IMU_NAV = 0.12f;                      /* ICD Version */
static const float ridaDB_ver_IMU_NAV = 3.23f;                   /* Rida Database Version */


/*---------------------- Fields Settings ----------------------*/


/*------------------------- Structures -------------------------*/

typedef struct SIsuMagnometerPhys {                              /* Struct 406 */
   T_REAL32 magX;                                                /* Magnometer X */
   T_REAL32 magY;                                                /* Magnometer Y */
   T_REAL32 magZ;                                                /* Magnometer Z */
} SIsuMagnometerPhys;

typedef struct SIsuNavSensorsStatusBits {                        /* Struct 416 */

#ifdef LSB_BIT_FIELDS
   T_UINT16 gyroXInvalid            : 1;                         /* Status invalid for Gyro X - True / False */
   T_UINT16 gyroYInvalid            : 1;                         /* Status invalid for Gyro Y - True / False */
   T_UINT16 gyroZInvalid            : 1;                         /* Status invalid for Gyro Z - True / False */
   T_UINT16 accXInvalid             : 1;                         /* Status  invalid for Accelerometer X - True / False. When the IMU acc X is saturated & the High Acc sensor is ok => the bit is valid (=0) */
   T_UINT16 accYInvalid             : 1;                         /* Status  invalid for Accelerometer Y - True / False */
   T_UINT16 accZInvalid             : 1;                         /* Status  invalid for Accelerometer Z - True / False */
   T_UINT16 highG_X_Invalid         : 1;                         /* Status  invalid for High G Accelerometer X - True / False */
   T_UINT16 spare6Bits              : 6;
   T_UINT16 spare1                  : 1;
   T_UINT16 spare2                  : 1;
   T_UINT16 spare3                  : 1;
#else
   T_UINT16 spare3                  : 1;
   T_UINT16 spare2                  : 1;
   T_UINT16 spare1                  : 1;
   T_UINT16 spare6Bits              : 6;
   T_UINT16 highG_X_Invalid         : 1;                         /* Status  invalid for High G Accelerometer X - True / False */
   T_UINT16 accZInvalid             : 1;                         /* Status  invalid for Accelerometer Z - True / False */
   T_UINT16 accYInvalid             : 1;                         /* Status  invalid for Accelerometer Y - True / False */
   T_UINT16 accXInvalid             : 1;                         /* Status  invalid for Accelerometer X - True / False. When the IMU acc X is saturated & the High Acc sensor is ok => the bit is valid (=0) */
   T_UINT16 gyroZInvalid            : 1;                         /* Status invalid for Gyro Z - True / False */
   T_UINT16 gyroYInvalid            : 1;                         /* Status invalid for Gyro Y - True / False */
   T_UINT16 gyroXInvalid            : 1;                         /* Status invalid for Gyro X - True / False */
#endif

} SIsuNavSensorsStatusBits;

typedef union UIsuNavSensorsStatus {                             /* Struct 421 */
   T_UINT16 valueWord;
   SIsuNavSensorsStatusBits bits;
} UIsuNavSensorsStatus;

typedef struct SIsuGyroIncrements {                              /* Struct 576 */
   T_REAL32 gyroIncrementX;                                      /* QtX  increment [rad] */
   T_REAL32 gyroIncrementY;                                      /* QtY  increment [rad] */
   T_REAL32 gyroIncrementZ;                                      /* QtZ  increment [rad] */
} SIsuGyroIncrements;

typedef struct SIsuAccIncrements {                               /* Struct 581 */
   T_REAL32 accIncrementX;                                       /* QVX  increments [m/sec] */
   T_REAL32 accIncrementY;                                       /* QVY  increments [m/sec] */
   T_REAL32 accIncrementZ;                                       /* QVZ  increments [m/sec] */
} SIsuAccIncrements;

typedef struct SIsuNavSensorsProcessBits {                       /* Struct 2056 */

#ifdef LSB_BIT_FIELDS
   T_UINT16 isuSensorsReady         : 1;                         /* 1 - ISU Sensors Ready, 0 - ISU Sensors not ready */
   T_UINT16 HighG_on                : 1;                         /* Flag indicates which accelerometer is used - Main Acc_X (0) or High_G_Acc_X (1) */
   T_UINT16 spare1Byte              : 8;
   T_UINT16 spare1                  : 1;
   T_UINT16 spare2                  : 1;
   T_UINT16 spare3                  : 1;
   T_UINT16 spare4                  : 1;
   T_UINT16 spare5                  : 1;
   T_UINT16 spare6                  : 1;
#else
   T_UINT16 spare6                  : 1;
   T_UINT16 spare5                  : 1;
   T_UINT16 spare4                  : 1;
   T_UINT16 spare3                  : 1;
   T_UINT16 spare2                  : 1;
   T_UINT16 spare1                  : 1;
   T_UINT16 spare1Byte              : 8;
   T_UINT16 HighG_on                : 1;                         /* Flag indicates which accelerometer is used - Main Acc_X (0) or High_G_Acc_X (1) */
   T_UINT16 isuSensorsReady         : 1;                         /* 1 - ISU Sensors Ready, 0 - ISU Sensors not ready */
#endif

} SIsuNavSensorsProcessBits;

typedef union UIsuNavSensorsProcess {                            /* Struct 2061 */
   T_UINT16 valueWord;
   SIsuNavSensorsProcessBits bits;
} UIsuNavSensorsProcess;

typedef struct SIsuNavData {                                     /* Struct 411 */
   SIsuGyroIncrements imuGyro;                                   /* QtX, QtY, QtZ increments [rad] */
   SIsuAccIncrements imuAcc;                                     /* QVX, QVY, QVZ  increments [m/sec] */
   T_REAL32 barom;
   SIsuMagnometerPhys mag;                                       /* X, Y, Z magnometer */
   UIsuNavSensorsStatus navSensorsStatus;
   UIsuNavSensorsProcess navSensorsProcess;
} SIsuNavData;



#if defined WIN32 || defined __LINUX__
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif /* IMU_NAV_h */




