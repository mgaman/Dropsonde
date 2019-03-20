/*******************************************************************************/
/***                                                                         ***/
/*** d:\RTC\SpikeSR_Rida\Output\\icd_IMU.h                                   ***/
/***                                                                         ***/
/*** This file was created automatically by the RIDA IO application          ***/
/*** On: 04/01/2015 13:22:35                                                 ***/
/*** Rida IO HFileWriter Version: 1.17, last update: 26/03/2014 13:43:40     ***/
/*** Rida Database Version: 3.23                                             ***/
/***                                                                         ***/
/*** Header File Version marked as: 0.8                                      ***/
/*** ICD version marked as: 0.16                                             ***/
/*** Produced by: N9KL, On: L-3-N9KLTST                                      ***/
/***                                                                         ***/
/*** Enhancements & Maintenance is done by Software Infrastructure team,     ***/
/*** Missile Division.                                                       ***/
/*** ALL RIGHTS RESERVED RAFAEL (C) 20-10-99                                 ***/
/***                                                                         ***/
/*******************************************************************************/


#ifndef icd_IMU_h
#define icd_IMU_h

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


#include "commonDef.h"                                           /* MMC_ISU\icd_IMU.h */
#include "CommonConstDef.h"                                      /* MMC_ISU\icd_IMU.h */
#include "IMU_NAV.h"                                             /* MMC_ISU\icd_IMU.h */


/*---------------------- System Versions ----------------------*/

static const float h_ver_icd_IMU = 0.8f;                         /* Header File Version */
static const float icd_ver_icd_IMU_irrelevant = 0.16f;           /* ICD Version */
static const float ridaDB_ver_icd_IMU_irrelevant = 3.23f;        /* Rida Database Version */


/*---------------------- System Constants ----------------------*/

#define ISU_MISSILE_MA_MATRIX_LENGTH      9                      /* Constant 501 */
#define ISU_NUMBER_OF_CYCLES              4                      /* Constant 506 */
#define IMU_GYRO_OUT_SCALE                (0.02)                 /* Constant 526 - [deg/sec] */
#define IMU_GYRO_LOW_SCALE                (3.0517578125e-7)      /* Constant 531 - 0.01 * (1/2)^15  [deg/sec] */
#define IMU_ACC_OUT_SCALE                 (0.0008)               /* Constant 536 - [g] */
#define IMU_MAG_SCALE                     (0.0001)               /* Constant 541 - 0.0001 [gauss] */
#define IMU_BAROM_OUT_SCALE               (4e-5)                 /* Constant 546 - [bar] */
#define IMU_BAROM_LOW_SCALE               (6.103515625e-10)      /* Constant 551 - [bar] */
#define IMU_TEMPERATURE_SCALE             (5.65e-3)              /* Constant 556 - [Cel] */
#define IMU_TEMPERATURE_OFFSET            (25)                   /* Constant 561 - [Cel] */
#define IMU_ACC_LOW_SCALE                 (1.220703125e-8)       /* Constant 613 - Constant  0.0004 * (1/2)^15 [g] */
#define HIGH_G_ACC_VOLTAGE_SCALE          (0.0000625)            /* Constant 618 - 4.096 / 2 ^ 16 */
#define HIGH_G_VOLTAGE_SCALE              (0.000125)             /* Constant 623 - 4.096 / 2 ^ 15 */
#define HIGH_G_OFFSET_BEFORE              (-1.65)                /* Constant 628 - g = (Vout-1.65V)/2.2 * 1000[g] */
#define HIGH_G_SCALE_AFTER                (454.54545454545)      /* Constant 633 - 1000/2.2[g] */
#define HIGH_G_TEMPERATURE_SCALE          (0.0060562015503875968)     /* Constant 638 - Constant 638 - 0.0000625 * 25 / 0.258 [c] = 0.0000625* (96.8992248062) */
#define ISU_NAV_MSG_COMMUNICATION_TIME    (sizeof(ISU_MMC_NAV_MSG) * 10 / 4.5)     /* Constant 738 - The Nav message Communication time [us]; size of message [bytes] * byte size [# of bits] / freq ([bit/Sec] = size of message * 10 / 4.5 */
#define IMU_ACC_LOW_SCALE_WITH_G_TRANS    (1.21920166015625e-8)  /* Constant 1003 - (IMU_ACC_LOW_SCALE * 0.99877)     => (1.220703125e-8) * 0.99877 */
#define IMU_ACC_OUT_SCALE_WITH_G_TRANS    (7.99016e-4)           /* Constant 1008 - (IMU_ACC_OUT_SCALE * 0.99877)   => 0.0008 * 0.99877 */
#define IMU_ADIS_PROD_ID                  (16488)                /* Constant 1013 - IMU ADIS Prod ID = 16488 */
#define HIGH_G_ACC_SCALE                  (0.028409090909090909090909090909091)     /* Constant 1018 - Scale_Before * Scale_After = (4.096 / 2 ^ 16) * 1000/2.2 */
#define HIGH_G_ACC_OFFSET                 (-750)                 /* Constant 1023 - Offset_before * Scale_After = (-1.65) * 1000/2.2 */
#define ISU_PBIT_MAX_CYCLES_UNTIL_FAIL    (20)                   /* Constant 1238 */


/*-------------------- Basic Data Elements --------------------*/

typedef enum                 EIsuFom{                            /* Element 929 */
   ISU_FOM_BAD                 = 0,                              /* Enum value (0) */
   ISU_FOM_DEGRADED            = 1,                              /* Enum value (1) */
   ISU_FOM_GOOD                = 2                               /* Enum value (2) */
}EIsuFom;



/*---------------------- Fields Settings ----------------------*/
#define SIsuControlData_imuTime_scale 1E-06                      /* Scale factor for the SIsuControlData.imuTime field */

#define SImuMmcNavData_imuTime_scale 1E-06                       /* Scale factor for the SImuMmcNavData.imuTime field */

#define SIsuSoftwareData_isuTotalOperationalTime_scale 1E-06     /* Scale factor for the SIsuSoftwareData.isuTotalOperationalTime field */

#define SIsuSoftwareData_timeTag400HzInterrupt_scale 1E-06       /* Scale factor for the SIsuSoftwareData.timeTag400HzInterrupt field */

#define SIsuSoftwareData_timeTag400HzSync_scale 1E-06            /* Scale factor for the SIsuSoftwareData.timeTag400HzSync field */

#define SIsuSoftwareData_timeTag50Hz_scale 1E-06                 /* Scale factor for the SIsuSoftwareData.timeTag50Hz field */

#define SIsuSoftwareData_timeTagPreviousSync_scale 1E-06         /* Scale factor for the SIsuSoftwareData.timeTagPreviousSync field */

#define SIsuRawDataVoltagesAndTemperatures_P5VA_IN_ADC_scale 0.001     /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.P5VA_IN_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_P5VD_IN_ADC_scale 0.001     /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.P5VD_IN_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_P3V3_ADC_scale 0.001  /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.P3V3_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_P3V3A_ADC_scale 0.001 /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.P3V3A_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_P4V7A_ADC_scale 0.001 /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.P4V7A_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_DGND_ADC_scale 0.001  /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.DGND_ADC field */

#define SIsuRawDataVoltagesAndTemperatures_IMU_TEMP_scale 0.00565     /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.IMU_TEMP field */

#define SIsuRawDataVoltagesAndTemperatures_ADC_TEMP_scale 0.0060562015503876     /* Scale factor for the SIsuRawDataVoltagesAndTemperatures.ADC_TEMP field */



/*------------------------- Structures -------------------------*/

typedef struct SIsuAngularRatePhys {                             /* Struct 356 */
   T_REAL32 angularRateX;                                        /* X angular rate */
   T_REAL32 angularRateY;                                        /* Y angular rate */
   T_REAL32 angularRateZ;                                        /* Z angular rate */
} SIsuAngularRatePhys;

typedef struct SIsuAccelerationPhys {                            /* Struct 361 */
   T_REAL32 accX;                                                /* X linear acceleration */
   T_REAL32 accY;                                                /* Y linear acceleration */
   T_REAL32 accZ;                                                /* Z linear acceleration */
} SIsuAccelerationPhys;

typedef struct SIsuControlStatusBits {                           /* Struct 366 */

#ifdef LSB_BIT_FIELDS
   T_UINT16 isuCtrlNotValid         : 1;                         /* ISU sensors for flight control error – 'OR' of all bits */
   T_UINT16 isuCtrlAngularRateXError : 1;                        /* ISU gyro for flight control X error */
   T_UINT16 isuCtrlAngularRateYError : 1;                        /* ISU gyro for flight control Y error */
   T_UINT16 isuCtrlAngularRateZError : 1;                        /* ISU gyro for flight control Z error */
   T_UINT16 isuCtrlLinearAccXError  : 1;                         /* ISU accelerometer for flight control X error. When the IMU acc X is saturated & the High Acc sensor is ok => the bit is valid (=0) */
   T_UINT16 isuCtrlLinearAccYError  : 1;                         /* ISU accelerometer for flight control Y error */
   T_UINT16 isuCtrlLinearAccZError  : 1;                         /* ISU accelerometer for flight control Z error */
   T_UINT16 Spare9_15               : 9;                         /* Spare (1 Byte) */
#else
   T_UINT16 Spare9_15               : 9;                         /* Spare (1 Byte) */
   T_UINT16 isuCtrlLinearAccZError  : 1;                         /* ISU accelerometer for flight control Z error */
   T_UINT16 isuCtrlLinearAccYError  : 1;                         /* ISU accelerometer for flight control Y error */
   T_UINT16 isuCtrlLinearAccXError  : 1;                         /* ISU accelerometer for flight control X error. When the IMU acc X is saturated & the High Acc sensor is ok => the bit is valid (=0) */
   T_UINT16 isuCtrlAngularRateZError : 1;                        /* ISU gyro for flight control Z error */
   T_UINT16 isuCtrlAngularRateYError : 1;                        /* ISU gyro for flight control Y error */
   T_UINT16 isuCtrlAngularRateXError : 1;                        /* ISU gyro for flight control X error */
   T_UINT16 isuCtrlNotValid         : 1;                         /* ISU sensors for flight control error – 'OR' of all bits */
#endif

} SIsuControlStatusBits;

typedef union UIsuControlStatus {                                /* Struct 371 */
   T_UINT16 valueWord;
   SIsuControlStatusBits bits;
} UIsuControlStatus;

typedef struct SIsuSystemPbitStatusBits {                        /* Struct 381 */

#ifdef LSB_BIT_FIELDS
   T_UINT32 isuSwInitFail           : 1;                         /* Is the Software init process fail? the init process contains reading from the flash the following: configuration file, compensation table, MA matrix file. */
   T_UINT32 isConfigurationFileReadFail : 1;                     /* ISB_Configuration_File_BM */
   T_UINT32 isCompensationTablesReadFail : 1;                    /* ISB_Calibration_Matrix_Load_BM */
   T_UINT32 isuFlashFail            : 1;                         /* ISB_FLASH_BM */
   T_UINT32 isuNoExternalSync       : 1;
   T_UINT32 isImuInitFileReadFail   : 1;                         /* ISB_Init_File_Load_BM */
   T_UINT32 progEnable              : 1;
   T_UINT32 testEnable              : 1;
   T_UINT32 simEnable               : 1;
   T_UINT32 sampleSensorsRawDataError : 1;
   T_UINT32 progEnableLatch         : 1;
   T_UINT32 testEnableLatch         : 1;
   T_UINT32 simEnableLatch          : 1;
   T_UINT32 isDisableMainSecAlgo    : 1;
   T_UINT32 isDisableMisAlignmentAlgo : 1;
   T_UINT32 spareBit1               : 1;
   T_UINT32 isuPBitFail             : 1;
   T_UINT32 pBitHighGselfTestError  : 1;                         /* HighG_ACC_Self_Test_BM */
   T_UINT32 pBitPageIdError         : 1;
   T_UINT32 pBitDiagStatusError     : 1;
   T_UINT32 pBitDecRateError        : 1;                         /* IMU_Dec_Rate_BM */
   T_UINT32 pBitProdIdError         : 1;                         /* IMU_Prod_ID_BM */
   T_UINT32 pBitGlobCmdError        : 1;                         /* IMU_Glob_Cmd_BM */
   T_UINT32 pBitFunctionCtrlError   : 1;                         /* IMU_FNCTIO_CTRL_BM */
   T_UINT32 pBitConfigError         : 1;                         /* IMU_Config_BM */
   T_UINT32 pBitNullConfigError     : 1;                         /* IMU_NULL_CNFG_BM */
   T_UINT32 pBitFilterBank0Error    : 1;                         /* IMU_FILTER_BNK_0_BM */
   T_UINT32 pBitFilterBank1Error    : 1;                         /* IMU_FILTER_BNK_1_BM */
   T_UINT32 pBitAdisCalibrationTests : 1;                        /* Logic OR of all tha ADIS calibration pbit tests (18 registers), the registers data is multiplexed in UIsuMultiplexRawData. */
   T_UINT32 isCompensationUnitMatrixWarning : 1;
   T_UINT32 spare31                 : 1;
   T_UINT32 spare32                 : 1;
#else
   T_UINT32 spare32                 : 1;
   T_UINT32 spare31                 : 1;
   T_UINT32 isCompensationUnitMatrixWarning : 1;
   T_UINT32 pBitAdisCalibrationTests : 1;                        /* Logic OR of all tha ADIS calibration pbit tests (18 registers), the registers data is multiplexed in UIsuMultiplexRawData. */
   T_UINT32 pBitFilterBank1Error    : 1;                         /* IMU_FILTER_BNK_1_BM */
   T_UINT32 pBitFilterBank0Error    : 1;                         /* IMU_FILTER_BNK_0_BM */
   T_UINT32 pBitNullConfigError     : 1;                         /* IMU_NULL_CNFG_BM */
   T_UINT32 pBitConfigError         : 1;                         /* IMU_Config_BM */
   T_UINT32 pBitFunctionCtrlError   : 1;                         /* IMU_FNCTIO_CTRL_BM */
   T_UINT32 pBitGlobCmdError        : 1;                         /* IMU_Glob_Cmd_BM */
   T_UINT32 pBitProdIdError         : 1;                         /* IMU_Prod_ID_BM */
   T_UINT32 pBitDecRateError        : 1;                         /* IMU_Dec_Rate_BM */
   T_UINT32 pBitDiagStatusError     : 1;
   T_UINT32 pBitPageIdError         : 1;
   T_UINT32 pBitHighGselfTestError  : 1;                         /* HighG_ACC_Self_Test_BM */
   T_UINT32 isuPBitFail             : 1;
   T_UINT32 spareBit1               : 1;
   T_UINT32 isDisableMisAlignmentAlgo : 1;
   T_UINT32 isDisableMainSecAlgo    : 1;
   T_UINT32 simEnableLatch          : 1;
   T_UINT32 testEnableLatch         : 1;
   T_UINT32 progEnableLatch         : 1;
   T_UINT32 sampleSensorsRawDataError : 1;
   T_UINT32 simEnable               : 1;
   T_UINT32 testEnable              : 1;
   T_UINT32 progEnable              : 1;
   T_UINT32 isImuInitFileReadFail   : 1;                         /* ISB_Init_File_Load_BM */
   T_UINT32 isuNoExternalSync       : 1;
   T_UINT32 isuFlashFail            : 1;                         /* ISB_FLASH_BM */
   T_UINT32 isCompensationTablesReadFail : 1;                    /* ISB_Calibration_Matrix_Load_BM */
   T_UINT32 isConfigurationFileReadFail : 1;                     /* ISB_Configuration_File_BM */
   T_UINT32 isuSwInitFail           : 1;                         /* Is the Software init process fail? the init process contains reading from the flash the following: configuration file, compensation table, MA matrix file. */
#endif

} SIsuSystemPbitStatusBits;

typedef union UIsuSystemPbit {                                   /* Struct 386 */
   T_UINT32 valueDword;
   SIsuSystemPbitStatusBits bits;
} UIsuSystemPbit;

typedef union UIsuMultiplexSwSystemData {                        /* Struct 391 */
   SDssCompVerDetails isuPreLoaderSwVer;                         /* Dependency Element Value = 1 */
   SDssCompVerDetails isuProtectedVxWorksRescue;                 /* Dependency Element Value = 2 */
   SDssCompVerDetails isuProtectedDssSwVer;                      /* Dependency Element Value = 3 */
   SDssCompVerDetails isuProtectedFirmwareVer;                   /* Dependency Element Value = 4 */
   SDssCompVerDetails isuVxWorksBootline;                        /* Dependency Element Value = 5 */
   SDssCompVerDetails isuDssSwVer;                               /* Dependency Element Value = 6 */
   SDssCompVerDetails isuFirmwareVer;                            /* Dependency Element Value = 7 */
   SDssCompVerDetails isuOperSwVer;                              /* Dependency Element Value = 8 */
   SDssCompVerDetails isuConfigurationFileVer;                   /* Dependency Element Value = 9 */
   SDssCompVerDetails isuInitParamsFileVer;                      /* Dependency Element Value = 10 */
   SDssCompVerDetails isuCalibrationMatrixVer;                   /* Dependency Element Value = 11 */
   SDssCompVerDetails isuMissileCalibrationMatVer;               /* Dependency Element Value = 12 */
   SDssCompVerDetails adis16488ImuVer;                           /* Dependency Element Value = 13 */
   SDssCompVerDetails imu_h_icd_ver;                             /* Dependency Element Value = 14 */
   SDssCompVerDetails fw_h_icd_ver;                              /* Dependency Element Value = 15 */
   SDssCompVerDetails telemetry_h_icd_ver;                       /* Dependency Element Value = 16 */
   SDssCompVerDetails icd_ver;                                   /* Dependency Element Value = 17 */
   SDssCompVerDetails ridaDB_ver;                                /* Dependency Element Value = 18 */
} UIsuMultiplexSwSystemData;

typedef struct SIsuAcceleration {                                /* Struct 446 */
   T_SINT32 accX;                                                /* X Raw linear acceleration */
   T_SINT32 accY;                                                /* Y Raw linear acceleration */
   T_SINT32 accZ;                                                /* Z Raw linear acceleration */
} SIsuAcceleration;

typedef struct SIsuMagnometer {                                  /* Struct 456 */
   T_SINT32 magX;                                                /* Raw Magnometer X */
   T_SINT32 magY;                                                /* Raw Magnometer Y */
   T_SINT32 magZ;                                                /* Raw Magnometer Z */
} SIsuMagnometer;

typedef union UIsuMultiplexRawData {                             /* Struct 461 */
   T_SINT16 DIAG_STS;                                            /* Dependency Element Value = 0 */
   T_SINT16 DEC_RATE;                                            /* Dependency Element Value = 1 */
   T_SINT16 PAGE_ID;                                             /* Dependency Element Value = 2 */
   T_SINT16 PROD_ID;                                             /* Dependency Element Value = 3 */
   T_SINT16 GLOB_CMD;                                            /* Dependency Element Value = 4 */
   T_SINT16 FIRM_REV_R;                                          /* Dependency Element Value = 5 */
   T_SINT16 CONFIG;                                              /* Dependency Element Value = 6 */
   T_SINT16 NULL_CNFG;                                           /* Dependency Element Value = 7 */
   T_SINT16 FILTR_BNK_0;                                         /* Dependency Element Value = 8 */
   T_SINT16 FILTR_BNK_1;                                         /* Dependency Element Value = 9 */
   T_REAL32 missileMA_matrix1;                                   /* Dependency Element Value = 10 */
   T_REAL32 missileMA_matrix2;                                   /* Dependency Element Value = 11 */
   T_REAL32 missileMA_matrix3;                                   /* Dependency Element Value = 12 */
   T_REAL32 missileMA_matrix4;                                   /* Dependency Element Value = 13 */
   T_REAL32 missileMA_matrix5;                                   /* Dependency Element Value = 14 */
   T_REAL32 missileMA_matrix6;                                   /* Dependency Element Value = 15 */
   T_REAL32 missileMA_matrix7;                                   /* Dependency Element Value = 16 */
   T_REAL32 missileMA_matrix8;                                   /* Dependency Element Value = 17 */
   T_REAL32 missileMA_matrix9;                                   /* Dependency Element Value = 18 */
   T_REAL32 highAccSelfTest1;                                    /* Dependency Element Value = 19 */
   T_REAL32 highAccSelfTest2;                                    /* Dependency Element Value = 20 */
   T_REAL32 highAccSelfTest3;                                    /* Dependency Element Value = 21 */
   T_REAL32 highAccSelfTest4;                                    /* Dependency Element Value = 22 */
   T_REAL32 highAccSelfTest5;                                    /* Dependency Element Value = 23 */
   T_REAL32 highAccSelfTest6;                                    /* Dependency Element Value = 24 */
   T_REAL32 highAccSelfTest7;                                    /* Dependency Element Value = 25 */
   T_REAL32 highAccSelfTest8;                                    /* Dependency Element Value = 26 */
   T_REAL32 highAccSelfTest9;                                    /* Dependency Element Value = 27 */
   T_REAL32 highAccSelfTest10;                                   /* Dependency Element Value = 28 */
   T_SINT16 FNCTIO_CTRL;                                         /* Dependency Element Value = 29 */
   T_SINT16 pbitFirstCycle;                                      /* Dependency Element Value = 30 */
   T_SINT16 pbitNumberOfCycles;                                  /* Dependency Element Value = 31 */
   T_SINT16 X_GYRO_SCALE;                                        /* Dependency Element Value = 32 */
   T_SINT16 Y_GYRO_SCALE;                                        /* Dependency Element Value = 33 */
   T_SINT16 Z_GYRO_SCALE;                                        /* Dependency Element Value = 34 */
   T_SINT16 X_ACCL_SCALE;                                        /* Dependency Element Value = 35 */
   T_SINT16 Y_ACCL_SCALE;                                        /* Dependency Element Value = 36 */
   T_SINT16 Z_ACCL_SCALE;                                        /* Dependency Element Value = 37 */
   T_SINT16 XG_BIAS_LOW;                                         /* Dependency Element Value = 38 */
   T_SINT16 XG_BIAS_HIGH;                                        /* Dependency Element Value = 39 */
   T_SINT16 YG_BIAS_LOW;                                         /* Dependency Element Value = 40 */
   T_SINT16 YG_BIAS_HIGH;                                        /* Dependency Element Value = 41 */
   T_SINT16 ZG_BIAS_LOW;                                         /* Dependency Element Value = 42 */
   T_SINT16 ZG_BIAS_HIGH;                                        /* Dependency Element Value = 43 */
   T_SINT16 XA_BIAS_LOW;                                         /* Dependency Element Value = 44 */
   T_SINT16 XA_BIAS_HIGH;                                        /* Dependency Element Value = 45 */
   T_SINT16 YA_BIAS_LOW;                                         /* Dependency Element Value = 46 */
   T_SINT16 YA_BIAS_HIGH;                                        /* Dependency Element Value = 47 */
   T_SINT16 ZA_BIAS_LOW;                                         /* Dependency Element Value = 48 */
   T_SINT16 ZA_BIAS_HIGH;                                        /* Dependency Element Value = 49 */
   T_SINT16 spare1;                                              /* Dependency Element Value = 50 */
   T_SINT16 spare2;                                              /* Dependency Element Value = 51 */
   T_SINT16 spare3;                                              /* Dependency Element Value = 52 */
} UIsuMultiplexRawData;

typedef struct SIsuBitMagBits {                                  /* Struct 601 */

#ifdef LSB_BIT_FIELDS
   T_UINT8 X_MAGN_INRANGE           : 1;
   T_UINT8 Y_MAGN_INRANGE           : 1;
   T_UINT8 Z_MAGN_INRANGE           : 1;
   T_UINT8 BAROM_INRANGE            : 1;
   T_UINT8 MAGN_BAROM_GROUP         : 1;
   T_UINT8 MAGN_BAROM_LATCH         : 1;
   T_UINT8 spare1                   : 1;
   T_UINT8 spare2                   : 1;
#else
   T_UINT8 spare2                   : 1;
   T_UINT8 spare1                   : 1;
   T_UINT8 MAGN_BAROM_LATCH         : 1;
   T_UINT8 MAGN_BAROM_GROUP         : 1;
   T_UINT8 BAROM_INRANGE            : 1;
   T_UINT8 Z_MAGN_INRANGE           : 1;
   T_UINT8 Y_MAGN_INRANGE           : 1;
   T_UINT8 X_MAGN_INRANGE           : 1;
#endif

} SIsuBitMagBits;

typedef struct SIsuBitVoltagesAndTemperaturesBits {              /* Struct 606 */

#ifdef LSB_BIT_FIELDS
   T_UINT16 P5VA_IN_ADC             : 1;
   T_UINT16 P5VD_IN_ADC             : 1;
   T_UINT16 P3V3_ADC                : 1;
   T_UINT16 P3V3A_ADC               : 1;
   T_UINT16 P4V7A_ADC               : 1;
   T_UINT16 DGND_ADC                : 1;
   T_UINT16 P1V1_PGD                : 1;
   T_UINT16 P1V5_PGD                : 1;
   T_UINT16 P2V5_PGD                : 1;
   T_UINT16 P3V3_PGD                : 1;
   T_UINT16 DDR_VTT_PGD             : 1;
   T_UINT16 POWER_GOOD_INFORMATION  : 1;                         /* Group of the all the _PGD bits - POWER_GOOD_information */
   T_UINT16 IMU_TEMP_INRANGE        : 1;
   T_UINT16 ADC_TEMP_INRANGE        : 1;
   T_UINT16 IMU_TEMP_DEVIATION      : 1;
   T_UINT16 spare1                  : 1;
#else
   T_UINT16 spare1                  : 1;
   T_UINT16 IMU_TEMP_DEVIATION      : 1;
   T_UINT16 ADC_TEMP_INRANGE        : 1;
   T_UINT16 IMU_TEMP_INRANGE        : 1;
   T_UINT16 POWER_GOOD_INFORMATION  : 1;                         /* Group of the all the _PGD bits - POWER_GOOD_information */
   T_UINT16 DDR_VTT_PGD             : 1;
   T_UINT16 P3V3_PGD                : 1;
   T_UINT16 P2V5_PGD                : 1;
   T_UINT16 P1V5_PGD                : 1;
   T_UINT16 P1V1_PGD                : 1;
   T_UINT16 DGND_ADC                : 1;
   T_UINT16 P4V7A_ADC               : 1;
   T_UINT16 P3V3A_ADC               : 1;
   T_UINT16 P3V3_ADC                : 1;
   T_UINT16 P5VD_IN_ADC             : 1;
   T_UINT16 P5VA_IN_ADC             : 1;
#endif

} SIsuBitVoltagesAndTemperaturesBits;

typedef struct SIsuBitSensorsBits {                              /* Struct 621 */

#ifdef LSB_BIT_FIELDS
   T_UINT32 MAIN_GYRO_X_SAT         : 1;
   T_UINT32 MAIN_GYRO_Y_SAT         : 1;
   T_UINT32 MAIN_GYRO_Z_SAT         : 1;
   T_UINT32 MAIN_GYRO_X_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_Y_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_Z_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_X_CONTINUITY  : 1;
   T_UINT32 MAIN_GYRO_Y_CONTINUITY  : 1;
   T_UINT32 MAIN_GYRO_Z_CONTINUITY  : 1;
   T_UINT32 MAIN_ACC_X_SAT          : 1;
   T_UINT32 MAIN_ACC_Y_SAT          : 1;
   T_UINT32 MAIN_ACC_Z_SAT          : 1;
   T_UINT32 MAIN_ACC_X_VITALITY     : 1;
   T_UINT32 MAIN_ACC_Y_VITALITY     : 1;
   T_UINT32 MAIN_ACC_Z_VITALITY     : 1;
   T_UINT32 MAIN_ACC_X_CONTINUITY   : 1;
   T_UINT32 MAIN_ACC_Y_CONTINUITY   : 1;
   T_UINT32 MAIN_ACC_Z_CONTINUITY   : 1;
   T_UINT32 HIGH_G_ACC_SAT          : 1;
   T_UINT32 HIGH_G_ACC_VITALITY     : 1;
   T_UINT32 HIGH_G_ACC_CONTINUITY   : 1;
   T_UINT32 HIGH_G_ACC_FAIL_LATCH   : 1;
   T_UINT32 OUT_ACC_X_HIGH_G        : 1;
   T_UINT32 VOLTAGE_GROUP           : 1;
   T_UINT32 TEMPERATURE_LATCH       : 1;
   T_UINT32 VOLTAGE_LATCH           : 1;
   T_UINT32 MAIN_ACC_FAIL_LATCH     : 1;
   T_UINT32 MAIN_GYRO_FAIL_LATCH    : 1;
   T_UINT32 IMU_BIT_LATCH           : 1;
   T_UINT32 spare1                  : 1;
   T_UINT32 SYS_E_FLAG_ERROR        : 1;
   T_UINT32 ALM_STS_ERROR           : 1;
#else
   T_UINT32 ALM_STS_ERROR           : 1;
   T_UINT32 SYS_E_FLAG_ERROR        : 1;
   T_UINT32 spare1                  : 1;
   T_UINT32 IMU_BIT_LATCH           : 1;
   T_UINT32 MAIN_GYRO_FAIL_LATCH    : 1;
   T_UINT32 MAIN_ACC_FAIL_LATCH     : 1;
   T_UINT32 VOLTAGE_LATCH           : 1;
   T_UINT32 TEMPERATURE_LATCH       : 1;
   T_UINT32 VOLTAGE_GROUP           : 1;
   T_UINT32 OUT_ACC_X_HIGH_G        : 1;
   T_UINT32 HIGH_G_ACC_FAIL_LATCH   : 1;
   T_UINT32 HIGH_G_ACC_CONTINUITY   : 1;
   T_UINT32 HIGH_G_ACC_VITALITY     : 1;
   T_UINT32 HIGH_G_ACC_SAT          : 1;
   T_UINT32 MAIN_ACC_Z_CONTINUITY   : 1;
   T_UINT32 MAIN_ACC_Y_CONTINUITY   : 1;
   T_UINT32 MAIN_ACC_X_CONTINUITY   : 1;
   T_UINT32 MAIN_ACC_Z_VITALITY     : 1;
   T_UINT32 MAIN_ACC_Y_VITALITY     : 1;
   T_UINT32 MAIN_ACC_X_VITALITY     : 1;
   T_UINT32 MAIN_ACC_Z_SAT          : 1;
   T_UINT32 MAIN_ACC_Y_SAT          : 1;
   T_UINT32 MAIN_ACC_X_SAT          : 1;
   T_UINT32 MAIN_GYRO_Z_CONTINUITY  : 1;
   T_UINT32 MAIN_GYRO_Y_CONTINUITY  : 1;
   T_UINT32 MAIN_GYRO_X_CONTINUITY  : 1;
   T_UINT32 MAIN_GYRO_Z_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_Y_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_X_VITALITY    : 1;
   T_UINT32 MAIN_GYRO_Z_SAT         : 1;
   T_UINT32 MAIN_GYRO_Y_SAT         : 1;
   T_UINT32 MAIN_GYRO_X_SAT         : 1;
#endif

} SIsuBitSensorsBits;

typedef union UIsuBitMag {                                       /* Struct 626 */
   SIsuBitMagBits bits;
   T_UINT8 valueByte;
} UIsuBitMag;

typedef union UIsuBitVoltagesAndTemperatures {                   /* Struct 631 */
   SIsuBitVoltagesAndTemperaturesBits bits;
   T_UINT16 valueWord;
} UIsuBitVoltagesAndTemperatures;

typedef union UIsuBitSensors {                                   /* Struct 646 */
   SIsuBitSensorsBits bits;
   T_UINT32 valueDword;
} UIsuBitSensors;

typedef struct SImuRawData {                                     /* Struct 776 */
   T_SINT32 qt_x;
   T_SINT32 qt_y;
   T_SINT32 qt_z;
   T_SINT32 qv_x;
   T_SINT32 qv_y;
   T_SINT32 qv_z;
} SImuRawData;

typedef struct SIsuBitTimeStampsBits {                           /* Struct 1421 */

#ifdef LSB_BIT_FIELDS
   T_UINT8 TS_1_2400HZ              : 1;
   T_UINT8 TS_2_400HZ_DATA_READY    : 1;
   T_UINT8 TS_3_400HZ_SYNC          : 1;
   T_UINT8 TS_4_50HZ                : 1;
   T_UINT8 TS_1_2400HZ_LATCH        : 1;
   T_UINT8 TS_2_400HZ_DATA_READY_LATCH : 1;
   T_UINT8 TS_3_400HZ_SYNC_LATCH    : 1;
   T_UINT8 TS_4_50HZ_LATCH          : 1;
#else
   T_UINT8 TS_4_50HZ_LATCH          : 1;
   T_UINT8 TS_3_400HZ_SYNC_LATCH    : 1;
   T_UINT8 TS_2_400HZ_DATA_READY_LATCH : 1;
   T_UINT8 TS_1_2400HZ_LATCH        : 1;
   T_UINT8 TS_4_50HZ                : 1;
   T_UINT8 TS_3_400HZ_SYNC          : 1;
   T_UINT8 TS_2_400HZ_DATA_READY    : 1;
   T_UINT8 TS_1_2400HZ              : 1;
#endif

} SIsuBitTimeStampsBits;

typedef union UIsuBitTimeStamps {                                /* Struct 1426 */
   SIsuBitTimeStampsBits bits;
   T_UINT8 valueByte;
} UIsuBitTimeStamps;

typedef struct SIsuRawSensorsDataAfterMS {                       /* Struct 1431 */
   T_REAL32 highG_Acc;                                           /* X, Y, Z  Raw linear acceleration */
   T_REAL32 msBias;
} SIsuRawSensorsDataAfterMS;

typedef struct SIsuMultiplexSwSystemData {                       /* Struct 1576 */
   SDssCompVerDetails isuPreLoaderSwVer;
   SDssCompVerDetails isuProtectedVxWorksRescue;
   SDssCompVerDetails isuProtectedDssSwVer;
   SDssCompVerDetails isuProtectedFirmwareVer;
   SDssCompVerDetails isuVxWorksBootline;
   SDssCompVerDetails isuDssSwVer;
   SDssCompVerDetails isuFirmwareVer;
   SDssCompVerDetails isuOperSwVer;
   SDssCompVerDetails isuConfigurationFileVer;
   SDssCompVerDetails isuInitParamsFileVer;
   SDssCompVerDetails isuCalibrationMatrixVer;
   SDssCompVerDetails isuMissileCalibrationMatVer;
   SDssCompVerDetails adis16488ImuVer;
   SDssCompVerDetails imu_h_icd_ver;
   SDssCompVerDetails fw_h_icd_ver;
   SDssCompVerDetails telemetry_h_icd_ver;
   SDssCompVerDetails icd_ver;
   SDssCompVerDetails ridaDB_ver;
} SIsuMultiplexSwSystemData;

typedef struct SIsuSystemCbitStatusBits {                        /* Struct 1956 */

#ifdef LSB_BIT_FIELDS
   T_UINT32 isuCtrlCBitFail         : 1;
   T_UINT32 isuNavCBitFail          : 1;
   T_UINT32 imuSysErrorFlagError    : 1;
   T_UINT32 imuAlarmStatusError     : 1;
   T_UINT32 CTRL_GYRO_X_FAIL_GROUP  : 1;
   T_UINT32 CTRL_GYRO_Y_FAIL_GROUP  : 1;
   T_UINT32 CTRL_GYRO_Z_FAIL_GROUP  : 1;
   T_UINT32 CTRL_ACC_X_FAIL_GROUP   : 1;
   T_UINT32 CTRL_ACC_Y_FAIL_GROUP   : 1;
   T_UINT32 CTRL_ACC_Z_FAIL_GROUP   : 1;
   T_UINT32 CTRL_HIGH_G_ACC_FAIL_GROUP : 1;
   T_UINT32 isuInterruptError       : 1;
   T_UINT32 NAV_GYRO_X_FAIL_GROUP   : 1;
   T_UINT32 NAV_GYRO_Y_FAIL_GROUP   : 1;
   T_UINT32 NAV_GYRO_Z_FAIL_GROUP   : 1;
   T_UINT32 NAV_ACC_X_FAIL_GROUP    : 1;
   T_UINT32 NAV_ACC_Y_FAIL_GROUP    : 1;
   T_UINT32 NAV_ACC_Z_FAIL_GROUP    : 1;
   T_UINT32 NAV_HIGH_G_ACC_FAIL_GROUP : 1;
   T_UINT32 VOLTAGE_GROUP           : 1;
   T_UINT32 spareBit2               : 1;
   T_UINT32 GYRO_X_FAIL_LATCH       : 1;
   T_UINT32 GYRO_Y_FAIL_LATCH       : 1;
   T_UINT32 GYRO_Z_FAIL_LATCH       : 1;
   T_UINT32 ACC_X_FAIL_LATCH        : 1;
   T_UINT32 ACC_Y_FAIL_LATCH        : 1;
   T_UINT32 ACC_Z_FAIL_LATCH        : 1;
   T_UINT32 HIGH_G_ACC_FAIL_LATCH   : 1;
   T_UINT32 VOLTAGE_LATCH           : 1;
   T_UINT32 TEMPERATURE_LATCH       : 1;
   T_UINT32 IMU_BIT_LATCH           : 1;
   T_UINT32 isuInterruptErrorLatch  : 1;
#else
   T_UINT32 isuInterruptErrorLatch  : 1;
   T_UINT32 IMU_BIT_LATCH           : 1;
   T_UINT32 TEMPERATURE_LATCH       : 1;
   T_UINT32 VOLTAGE_LATCH           : 1;
   T_UINT32 HIGH_G_ACC_FAIL_LATCH   : 1;
   T_UINT32 ACC_Z_FAIL_LATCH        : 1;
   T_UINT32 ACC_Y_FAIL_LATCH        : 1;
   T_UINT32 ACC_X_FAIL_LATCH        : 1;
   T_UINT32 GYRO_Z_FAIL_LATCH       : 1;
   T_UINT32 GYRO_Y_FAIL_LATCH       : 1;
   T_UINT32 GYRO_X_FAIL_LATCH       : 1;
   T_UINT32 spareBit2               : 1;
   T_UINT32 VOLTAGE_GROUP           : 1;
   T_UINT32 NAV_HIGH_G_ACC_FAIL_GROUP : 1;
   T_UINT32 NAV_ACC_Z_FAIL_GROUP    : 1;
   T_UINT32 NAV_ACC_Y_FAIL_GROUP    : 1;
   T_UINT32 NAV_ACC_X_FAIL_GROUP    : 1;
   T_UINT32 NAV_GYRO_Z_FAIL_GROUP   : 1;
   T_UINT32 NAV_GYRO_Y_FAIL_GROUP   : 1;
   T_UINT32 NAV_GYRO_X_FAIL_GROUP   : 1;
   T_UINT32 isuInterruptError       : 1;
   T_UINT32 CTRL_HIGH_G_ACC_FAIL_GROUP : 1;
   T_UINT32 CTRL_ACC_Z_FAIL_GROUP   : 1;
   T_UINT32 CTRL_ACC_Y_FAIL_GROUP   : 1;
   T_UINT32 CTRL_ACC_X_FAIL_GROUP   : 1;
   T_UINT32 CTRL_GYRO_Z_FAIL_GROUP  : 1;
   T_UINT32 CTRL_GYRO_Y_FAIL_GROUP  : 1;
   T_UINT32 CTRL_GYRO_X_FAIL_GROUP  : 1;
   T_UINT32 imuAlarmStatusError     : 1;
   T_UINT32 imuSysErrorFlagError    : 1;
   T_UINT32 isuNavCBitFail          : 1;
   T_UINT32 isuCtrlCBitFail         : 1;
#endif

} SIsuSystemCbitStatusBits;

typedef struct SIsuRawDataVoltagesAndTemperatures {              /* Struct 1961 */
   T_SINT16 P5VA_IN_ADC;                                         /* Scaling Factor = 0.001 */
   T_SINT16 P5VD_IN_ADC;                                         /* Scaling Factor = 0.001 */
   T_SINT16 P3V3_ADC;                                            /* Scaling Factor = 0.001 */
   T_SINT16 P3V3A_ADC;                                           /* Scaling Factor = 0.001 */
   T_SINT16 P4V7A_ADC;                                           /* Scaling Factor = 0.001 */
   T_SINT16 DGND_ADC;                                            /* Scaling Factor = 0.001 */
   T_SINT16 IMU_TEMP;                                            /* Scaling Factor = 0.00565, Offset = 25 */
   T_SINT16 ADC_TEMP;                                            /* Scaling Factor = 0.00605620155038759689922480620155 */
} SIsuRawDataVoltagesAndTemperatures;

typedef struct SIsuInternalSwSystemBits {                        /* Struct 1971 */

#ifdef LSB_BIT_FIELDS
   T_UINT16 ctrlMsgSendingTimeWarning1 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning2 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning3 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning4 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 navMsgSendingTimeWarning : 1;                        /* When the Nav message sending time -  sync time less than XXX us (define in FW register NAV_DELAY_FROM_LAST_SYNC) */
   T_UINT16 ctrlMsgSendingTimeError1 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError2 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError3 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError4 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 navMsgSendingTimeError  : 1;                         /* When the Nav message sending time is after the last opportunity time to send. (cycle sending time + communication time > 2.5 us) => (sending time - sync time + ISU_NAV_MSG_COMMUNICATION_TIME > 2500) */
   T_UINT16 spare                   : 6;                         /* Spare */
#else
   T_UINT16 spare                   : 6;                         /* Spare */
   T_UINT16 navMsgSendingTimeError  : 1;                         /* When the Nav message sending time is after the last opportunity time to send. (cycle sending time + communication time > 2.5 us) => (sending time - sync time + ISU_NAV_MSG_COMMUNICATION_TIME > 2500) */
   T_UINT16 ctrlMsgSendingTimeError4 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError3 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError2 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 ctrlMsgSendingTimeError1 : 1;                        /* When the Control message sending time is after the sync. */
   T_UINT16 navMsgSendingTimeWarning : 1;                        /* When the Nav message sending time -  sync time less than XXX us (define in FW register NAV_DELAY_FROM_LAST_SYNC) */
   T_UINT16 ctrlMsgSendingTimeWarning4 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning3 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning2 : 1;                      /* When the sync time - interrupt time is less than 30 us */
   T_UINT16 ctrlMsgSendingTimeWarning1 : 1;                      /* When the sync time - interrupt time is less than 30 us */
#endif

} SIsuInternalSwSystemBits;

typedef union UIsuSystemCbit {                                   /* Struct 1976 */
   T_UINT32 valueDword;
   SIsuSystemCbitStatusBits bits;
} UIsuSystemCbit;

typedef struct SIsuAngularRatePhysDeg {                          /* Struct 2263 */
   T_REAL32 angularRateX;                                        /* X angular rate, Scaling Unit = Deg/sec, Alarm [-450, 450] */
   T_REAL32 angularRateY;                                        /* Y angular rate, Scaling Unit = Deg/sec, Alarm [-450, 450] */
   T_REAL32 angularRateZ;                                        /* Z angular rate, Scaling Unit = Deg/sec, Alarm [-450, 450] */
} SIsuAngularRatePhysDeg;

typedef struct SIsuAccelerationPhysG {                           /* Struct 2268 */
   T_REAL32 accX;                                                /* X linear acceleration, Scaling Unit = g, Alarm [-18, 18] */
   T_REAL32 accY;                                                /* Y linear acceleration, Scaling Unit = g, Alarm [-18, 18] */
   T_REAL32 accZ;                                                /* Z linear acceleration, Scaling Unit = g, Alarm [-18, 18] */
} SIsuAccelerationPhysG;

typedef struct SIsuHighAccelerationPhysG {                       /* Struct 2273 */
   T_REAL32 highAccX;                                            /* X linear acceleration, Scaling Unit = g, Alarm [-500, 500] */
   T_REAL32 highAccY;                                            /* Y linear acceleration, Scaling Unit = g, Alarm [-500, 500] */
   T_REAL32 highAccZ;                                            /* Z linear acceleration, Scaling Unit = g, Alarm [-500, 500] */
} SIsuHighAccelerationPhysG;

typedef struct SIsuCbitForBitManagerBits {                       /* Struct 2595 - CIB BIT Details on CBIT - By MMC */

#ifdef LSB_BIT_FIELDS
   T_UINT32 IMU_GYRO_X_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
   T_UINT32 IMU_GYRO_Y_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
   T_UINT32 IMU_GYRO_Z_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
   T_UINT32 IMU_GYRO_X_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_GYRO_Y_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_GYRO_Z_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_ACC_X_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_Y_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_Z_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_X_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 IMU_ACC_Y_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 IMU_ACC_Z_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 HIGH_G_ACC_VITALITY     : 1;                         /* ISB_HighG_Acc_Vitality_BM */
   T_UINT32 HIGH_G_ACC_CONTINUITY   : 1;                         /* ISB_HighG_Acc_Continuity_BM */
   T_UINT32 SYS_E_FLAG              : 1;                         /* IMU_Sys_E_Flag_BM */
   T_UINT32 ALM_STS                 : 1;                         /* IMU_ALM_BM */
   T_UINT32 P5VA_IN_ADC             : 1;                         /* Input_P5VA_ADC_BIT_MGR */
   T_UINT32 P5VD_IN_ADC             : 1;                         /* Internal_P5VD_ADC_BIT_MGR */
   T_UINT32 P3V3_ADC                : 1;                         /* Internal_P3V3_ADC_BIT_MGR */
   T_UINT32 P3V3A_ADC               : 1;                         /* Internal_P3V3A_ADC_BIT_MGR */
   T_UINT32 P4V7A_ADC               : 1;                         /* Input_P4V7A_ADC_BIT_MGR */
   T_UINT32 DGND_ADC                : 1;                         /* Internal_DGND_ADC_BIT_MGR */
   T_UINT32 POWER_GOOD              : 1;                         /* ISB_Power_Good_BM */
   T_UINT32 IMU_TEMP_INRANGE        : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 ADC_TEMP_INRANGE        : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 TEMP_DEVIATION          : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 NO_EXTERNAL_SYNC        : 1;                         /* MMC_SYNC_BIT_MGR */
   T_UINT32 IMU_DATA_READY_ERROR    : 1;                         /* isb_rs485_spi_comm_timeout */
   T_UINT32 IMU_FATAL_ERROR         : 1;
   T_UINT32 spare30                 : 1;
   T_UINT32 spare31                 : 1;
   T_UINT32 spare32                 : 1;
#else
   T_UINT32 spare32                 : 1;
   T_UINT32 spare31                 : 1;
   T_UINT32 spare30                 : 1;
   T_UINT32 IMU_FATAL_ERROR         : 1;
   T_UINT32 IMU_DATA_READY_ERROR    : 1;                         /* isb_rs485_spi_comm_timeout */
   T_UINT32 NO_EXTERNAL_SYNC        : 1;                         /* MMC_SYNC_BIT_MGR */
   T_UINT32 TEMP_DEVIATION          : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 ADC_TEMP_INRANGE        : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 IMU_TEMP_INRANGE        : 1;                         /* ISB_temp_BIT_MGR */
   T_UINT32 POWER_GOOD              : 1;                         /* ISB_Power_Good_BM */
   T_UINT32 DGND_ADC                : 1;                         /* Internal_DGND_ADC_BIT_MGR */
   T_UINT32 P4V7A_ADC               : 1;                         /* Input_P4V7A_ADC_BIT_MGR */
   T_UINT32 P3V3A_ADC               : 1;                         /* Internal_P3V3A_ADC_BIT_MGR */
   T_UINT32 P3V3_ADC                : 1;                         /* Internal_P3V3_ADC_BIT_MGR */
   T_UINT32 P5VD_IN_ADC             : 1;                         /* Internal_P5VD_ADC_BIT_MGR */
   T_UINT32 P5VA_IN_ADC             : 1;                         /* Input_P5VA_ADC_BIT_MGR */
   T_UINT32 ALM_STS                 : 1;                         /* IMU_ALM_BM */
   T_UINT32 SYS_E_FLAG              : 1;                         /* IMU_Sys_E_Flag_BM */
   T_UINT32 HIGH_G_ACC_CONTINUITY   : 1;                         /* ISB_HighG_Acc_Continuity_BM */
   T_UINT32 HIGH_G_ACC_VITALITY     : 1;                         /* ISB_HighG_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_Z_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 IMU_ACC_Y_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 IMU_ACC_X_CONTINUITY    : 1;                         /* IMU_Main_Acc_Continuity_BM */
   T_UINT32 IMU_ACC_Z_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_Y_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_ACC_X_VITALITY      : 1;                         /* IMU_Main_Acc_Vitality_BM */
   T_UINT32 IMU_GYRO_Z_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_GYRO_Y_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_GYRO_X_CONTINUITY   : 1;                         /* IMU_Main_Gyros_Continuity_BM */
   T_UINT32 IMU_GYRO_Z_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
   T_UINT32 IMU_GYRO_Y_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
   T_UINT32 IMU_GYRO_X_VITALITY     : 1;                         /* IMU_Main_Gyros_Vitality_BM */
#endif

} SIsuCbitForBitManagerBits;

typedef union UIsuCbitForBitManager {                            /* Struct 2600 */
   SIsuCbitForBitManagerBits bits;
   T_UINT32 valueDword;
} UIsuCbitForBitManager;

typedef struct SIsuCbitGroups {                                  /* Struct 2605 */
   UIsuCbitForBitManager isuCbitMomentary;
   UIsuCbitForBitManager isuCbitFilter;
   UIsuCbitForBitManager isuCbitLatch;
} SIsuCbitGroups;

typedef struct SIsuControlData {                                 /* Struct 351 */
   T_UINT32 isuIndex;
   T_UINT32 imuTime;                                             /* Should be filled by the ISU, Scaling Factor = 1E-06 */
   SIsuAngularRatePhys gyro;                                     /* X, Y, Z angular rate */
   SIsuAccelerationPhys acc;                                     /* X, Y, Z linear acceleration */
} SIsuControlData;

typedef struct SImuMmcCtrlData {                                 /* Struct 376 */
   SIsuControlData controlData;
   UIsuControlStatus status;
   T_UINT16 spare;
} SImuMmcCtrlData;

typedef struct SIsuBitStatus {                                   /* Struct 431 */
   UIsuBitSensors sensorsBit;
   UIsuBitVoltagesAndTemperatures voltagesAndTemperaturesBit;
   UIsuBitMag magBit;
   UIsuBitTimeStamps timeStampsBit;
} SIsuBitStatus;

typedef struct SIsuStatus {                                      /* Struct 656 - ISU Status: system and software */
   UIsuSystemPbit isuBit;
   UIsuSystemCbit isuSensorsBit;
} SIsuStatus;

typedef struct SIsuMmcControlMsg {                               /* Struct 976 */
   SOpcodeHeaderMsgData header;
   SImuMmcCtrlData data;
   SCrcFooterMsgData footer;
} SIsuMmcControlMsg;

typedef struct SIsuRawSensorsDataBeforeCompensation {            /* Struct 1406 */
   SIsuAngularRatePhysDeg imuRawGyro;                            /* X, Y, Z Raw angular rate */
   SIsuAccelerationPhysG imuRawAcc;                              /* X, Y, Z  Raw linear acceleration */
   T_REAL32 highG_AccRaw;
} SIsuRawSensorsDataBeforeCompensation;

typedef struct SIsuRawSensorsDataAfterCompensation {             /* Struct 1946 */
   SIsuAngularRatePhysDeg imuGyro;                               /* X, Y, Z Raw angular rate */
   SIsuAccelerationPhysG imuAcc;                                 /* X, Y, Z  Raw linear acceleration */
   SIsuHighAccelerationPhysG highG_Acc;
} SIsuRawSensorsDataAfterCompensation;

typedef struct SIsuRawSensorsData {                              /* Struct 1951 */
   SIsuRawSensorsDataBeforeCompensation beforeCompensation;
   SIsuRawSensorsDataAfterCompensation afterCompensation;
   SIsuRawSensorsDataAfterMS afterMS;
} SIsuRawSensorsData;

typedef union UIsuInternalSwSystemStatus {                       /* Struct 1966 */
   SIsuInternalSwSystemBits bits;
   T_UINT16 valueWord;
} UIsuInternalSwSystemStatus;

typedef struct SIsuSoftwareData {                                /* Struct 396 */
   T_UINT32 isuTotalOperationalTime;                             /* Scaling Factor = 1E-06 */
   T_UINT32 timeTag400HzInterrupt;                               /* Scaling Factor = 1E-06 */
   T_UINT32 timeTag400HzSync;                                    /* Scaling Factor = 1E-06 */
   T_UINT32 timeTag50Hz;                                         /* Scaling Factor = 1E-06 */
   T_UINT32 timeTagPreviousSync;                                 /* The sync time tag of the previous cycle, Scaling Factor = 1E-06 */
   T_UINT16 isuControlTimeBeforeSync[ISU_NUMBER_OF_CYCLES];      /* microseconds */
   T_UINT16 timeDiffFromSyncToSensorsData;                       /* To MMC - Time Diff From Sync To Sensors Data time. [us] (default 833 us) */
   T_UINT16 isuNavTimeFromInterrupt;                             /* microseconds */
   T_UINT16 isuTotalDurationCycle;
   T_UINT8 imuErrorFlag;
   T_UINT8 sliceIndex;
   T_UINT16 stackSize;
   T_UINT8 cpuUsage;
   T_UINT8 isuTs50HzErrorCounter;                                /* Counter the error of 50 Hz, the bit is in isuSensorsData->navBitStatus->timeStampBit */
   UIsuInternalSwSystemStatus isuSwSystemStatus;
   T_UINT16 isuSwSystemControlWarningsCounter;                   /* The counter increment on each (Control) warning bit == 1 in  isuSwSystemStatus */
   T_UINT16 isuSwSystemControlErrorsCounter;                     /* The counter increment on each (Control) error bit == 1 in  isuSwSystemStatus */
   T_UINT16 isuSwSystemNavWarningsCounter;                       /* The counter increment on each (Nav) warning bit == 1 in  isuSwSystemStatus */
   T_UINT16 isuSwSystemNavErrorsCounter;                         /* The counter increment on each (Nav) error bit == 1 in  isuSwSystemStatus */
   T_UINT16 isuTsDataReadyErrorCounter;                          /* Counter the error of Data Ready (interrupt) 400 Hz, the bit is in isuSensorsData->navBitStatus->timeStampBit */
   T_UINT16 isuInterruptErrorCounter;                            /* Counter the error of the Interrupt (400 Hz,) the bit is in isuStatus->isuSensorsBit */
   T_UINT16 imuMultiplexIndex;
   UIsuMultiplexSwSystemData imuMultiplexData;
} SIsuSoftwareData;

typedef struct SIsuRawData {                                     /* Struct 1436 */
   SIsuRawSensorsData ctrlRawSensors1;
   UIsuBitSensors ctrlSensorsBit1;
   SIsuRawSensorsData ctrlRawSensors2;
   UIsuBitSensors ctrlSensorsBit2;
   SIsuRawSensorsData ctrlRawSensors3;
   UIsuBitSensors ctrlSensorsBit3;
   SIsuRawSensorsData ctrlRawSensors4;
   UIsuBitSensors ctrlSensorsBit4;
   SIsuRawSensorsData navRawSensors;
   SIsuBitStatus navBitStatus;
   SIsuRawDataVoltagesAndTemperatures voltagesAndTemperaturesRawData;
   T_UINT16 POWER_GOOD_INFO_DATA;                                /* Power Good Data, The required value is 31 (0x1f) => 11111b, all the PGD are ok. (5 of them) */
   T_UINT16 isuMultiplexIndex;
   UIsuMultiplexRawData isuMultiplexData;
   T_UINT16 imuSysErrorFlagData;
   T_UINT16 imuAlarmStatusData;
} SIsuRawData;

typedef struct SImuMmcNavData {                                  /* Struct 436 */
   T_UINT32 imuTime;                                             /* Should be filled by the ISU, Scaling Factor = 1E-06 */
   SIsuStatus isuStatus;                                         /* ISU Status: Pbit and Cbit */
   SIsuNavData isuNavData;
   SIsuSoftwareData isuSwData;
   SIsuRawData isuSensorsData;
   SIsuCbitGroups isuCbit;
} SImuMmcNavData;

typedef struct SIsuMmcNavMsg {                                   /* Struct 981 */
   SOpcodeHeaderMsgData header;
   SImuMmcNavData data;
   SCrcFooterMsgData footer;
} SIsuMmcNavMsg;



/*-------------------------- Messages --------------------------*/

typedef struct ISU_MMC_CONTROL_MSG {                             /* (Opcode 0x1A6B) Message 261 - OPCODE = OP_ISU_MMC_CONTROL */
   SIsuMmcControlMsg msg;
} ISU_MMC_CONTROL_MSG;

/*ASSERT_MESSAGE_SIZE(ISU_MMC_CONTROL_MSG, 44)*/                     /* Divide by zero means compiled size does not match RIDA's size */

typedef struct ISU_MMC_NAV_MSG {                                 /* (Opcode 0x1B4D) Message 266 - OPCODE = OP_ISU_MMC_NAV */
   SIsuMmcNavMsg msg;
} ISU_MMC_NAV_MSG;

/*ASSERT_MESSAGE_SIZE(ISU_MMC_NAV_MSG, 556)*/                        /* Divide by zero means compiled size does not match RIDA's size */



#if defined WIN32 || defined __LINUX__
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif /* icd_IMU_h */

/*******************************************************************************/
/*** d:\RTC\SpikeSR_Rida\Output\\icd_IMU.h                                   ***/
/*** End of generated code.                                                  ***/
/*******************************************************************************/


