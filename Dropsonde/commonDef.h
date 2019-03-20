


#ifndef commonDef_h
#define commonDef_h

#include "cmnBasicTypes.h"

//#ifdef __cplusplus
//using namespace CommonServices;
//#endif

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


#include "CommonConstDef.h"                                      /* COMMON_DEF\commonDef.h */


/*---------------------- System Versions ----------------------*/

static const float h_ver_commonDef = 0.7f;                       /* Header File Version */
static const float icd_ver_commonDef = 0.11f;                    /* ICD Version */
static const float ridaDB_ver_commonDef = 3.23f;                 /* Rida Database Version */


/*-------------------- Basic Data Elements --------------------*/

typedef enum                 EMsgOpcodes{                        /* Element 557 */
   OP_MMC_HW                        = 26,                        /* 0x1A */
   OP_HW_MMC                        = 27,                        /* 0x1B */
   OP_MMC_SCB_PBIT_VER_REQ          = 42,                        /* 0x2A */
   OP_SCB_MMC_PBIT_VER              = 43,                        /* 0x2B */
   OP_MMC_SCB_CONTROL               = 44,                        /* 0x2C */
   OP_SCB_MMC_STATUS                = 45,                        /* 0x2D */
   OP_MMC_ICM_PBIT_VER_REQ          = 58,                        /* 0x3A */
   OP_ICM_MMC_PBIT_VER              = 59,                        /* 0x3B */
   OP_MMC_ICM_CONTROL               = 60,                        /* 0x3C */
   OP_ICM_MMC_STATUS                = 61,                        /* 0x3D */
   OP_ICM_MMC_READY                 = 62,                        /* 0x3E */
   OP_ICM_MMC_TELEMETRY             = 63,                        /* 0x3F */
   OP_MMC_PIB_CONTROL               = 76,                        /* 0x4C */
   OP_PIB_MMC_STATUS                = 77,                        /* 0x4D */
   OP_MMC_TELEM                     = 154,                       /* 0x9A */
   OP_ICM_SSB_PBIT_VER_REQ          = 170,                       /* 0xAA */
   OP_SSB_MCU_PBIT_VER              = 171,                       /* 0xAB */
   OP_ICM_SSB_CONTROL               = 172,                       /* 0xAC */
   OP_SSB_MCU_STATUS                = 173,                       /* 0xAD */
   OP_ISU_MMC_CONTROL               = 6763,                      /* 0x1A6B */
   OP_ISU_MMC_NAV                   = 6989,                      /* 0x1B4D */
   OP_ATE_ISU_SIM_SENSORS           = 7258,                      /* 0x1C5A */
   OP_ISU_METRY                     = 7310,                      /* 0x1C8E */
   OP_ATE_MMC_PIB_TRANSPARENT       = 20753,                     /* 0x5111 */
   OP_ATE_MMC_SCB_TRANSPARENT       = 21026,                     /* 0x5222 */
   OP_ATE_MMC_ICM_TRANSPARENT       = 21299,                     /* 0x5333 */
   OP_ATE_MMC_CIB_TRANSPARENT       = 21845,                     /* 0x5555 */
   OP_MMC_CIB_CONTROL               = 21930,                     /* 0x55AA */
   OP_ATE_MMC_SAB_TRANSPARENT       = 22118,                     /* 0x5666 */
   OP_ATE_MMC_MAINTENANCE_COMMAND   = 31314,                     /* 0x7A52 */
   OP_CIB_MMC_STATUS                = 43605                      /* 0xAA55 */
}EMsgOpcodes;

typedef enum                 EMllStatus{                         /* Element 674 */
   MISSILE_IN_LAUNCHER         = 0,                              /* Enum value (0) */
   MISSILE_LEFT_LAUNCHER       = 1                               /* Enum value (1) */
}EMllStatus;

typedef enum                 EAteMmcMaintTestCode{               /* Element 919 */
   ATE_MMC_COMMAND_ISU_POWER_D   = 5,
   ATE_MMC_COMMAND_PIB_POWER_D   = 10,
   ATE_MMC_COMMAND_TEL_TX_ON     = 15,
   ATE_MMC_COMMAND_TEL_BAT_ON    = 16                            /* Enum value (16) */
}EAteMmcMaintTestCode;

typedef enum                 EAteMmcMaintTestParam{              /* Element 924 */
   ATE_MMC_TEST_COMMAND_PARAM_0   = 1,                           /* 1 */
   ATE_MMC_TEST_COMMAND_PARAM_1   = 2                            /* 2 */
}EAteMmcMaintTestParam;

typedef enum                 EBitDataStatus{                     /* Element 1239 */
   BIT_DATA_IN_PROGRESS        = 0,                              /* Enum value (0) */
   BIT_DATA_IS_READY           = 1                               /* Enum value (1) */
}EBitDataStatus;

typedef enum                 EProgEnStatus{                      /* Element 1429 */
   DISCRETE_PROGRAM_ENABLED    = 0,
   DISCRETE_PROGRAM_DISABLED   = 1
}EProgEnStatus;

typedef enum                 ETestEnStatus{                      /* Element 1434 */
   DISCRETE_TEST_ENABLE        = 0,
   DISCRETE_TEST_DISABLE       = 1
}ETestEnStatus;

typedef enum                 EPibAndCibButtonTrackCmd{           /* Element 1684 */
   TRACK_NO_PUSH               = 0,                              /* Enum value (0) */
   TRACK_PUSH                  = 235                             /* 0xEB */
}EPibAndCibButtonTrackCmd;

typedef enum                 EDiscreteIsuPowerDown{              /* Element 1689 */
   ISU_POWER_ON                = 0,                              /* Enum value (0) */
   ISU_POWER_OFF               = 1                               /* Enum value (1) */
}EDiscreteIsuPowerDown;

typedef enum                 EDiscretePibPowerDown{              /* Element 1694 */
   PIB_POWER_ON                = 0,                              /* Enum value (0) */
   PIB_POWER_OFF               = 1                               /* Enum value (1) */
}EDiscretePibPowerDown;



/*---------------------- Fields Settings ----------------------*/


/*------------------------- Structures -------------------------*/

typedef struct SSizeXY {                                         /* Struct 166 */
   T_REAL32 x;
   T_REAL32 y;
} SSizeXY;

typedef struct SOpcodeHeaderMsgData {                            /* Struct 266 */
   T_UINT16 opcode;
   T_UINT16 counter;
} SOpcodeHeaderMsgData;

typedef struct SCrcFooterMsgData {                               /* Struct 271 */
   T_UINT32 crc;
} SCrcFooterMsgData;

typedef struct SDssCompVerDetails {                              /* Struct 276 */
   T_UINT16 version;
   T_UINT16 revision;
   T_UINT8 date_Day;
   T_UINT8 date_Month;
   T_UINT8 date_Year;
   T_UINT8 component_ID;
   T_UINT32 checksum;
} SDssCompVerDetails;

typedef struct SAlgCompVerDetails {                              /* Struct 866 */
   T_UINT8 algorithm_ID;
   T_UINT8 version;
   T_UINT8 revision;
   T_UINT8 spare;
} SAlgCompVerDetails;

typedef struct SMasterCommFailStatus {                           /* Struct 943 */

#ifdef LSB_BIT_FIELDS
   T_UINT32 commErrorCounter        : 16;
   T_UINT32 crcFail                 : 1;
   T_UINT32 opcodeFail              : 1;
   T_UINT32 sizeFail                : 1;
   T_UINT32 frameCounterFail        : 1;
   T_UINT32 missedMsg               : 1;
   T_UINT32 echoCounterFail         : 1;
   T_UINT32 spare                   : 9;
   T_UINT32 correctMsg              : 1;
#else
   T_UINT32 correctMsg              : 1;
   T_UINT32 spare                   : 9;
   T_UINT32 echoCounterFail         : 1;
   T_UINT32 missedMsg               : 1;
   T_UINT32 frameCounterFail        : 1;
   T_UINT32 sizeFail                : 1;
   T_UINT32 opcodeFail              : 1;
   T_UINT32 crcFail                 : 1;
   T_UINT32 commErrorCounter        : 16;
#endif

} SMasterCommFailStatus;

typedef struct SAteMaintenanceData {                             /* Struct 1306 */
   T_UINT32 test_code;                                           /* Using EAteMmcMaintTestCode enum */
   T_UINT8 test_param_1;                                         /* Using EAteMmcMaintTestParam enum */
   T_UINT8 test_param_2;                                         /* Using EAteMmcMaintTestParam enum */
   T_UINT8 test_param_3;                                         /* Using EAteMmcMaintTestParam enum */
   T_UINT8 test_param_4;                                         /* Using EAteMmcMaintTestParam enum */
} SAteMaintenanceData;

typedef struct SDssFileDescriptor {                              /* Struct 1656 */
   T_UINT32 verification_code;                                   /* Verification code */
   T_UINT16 component_sub_version;                               /* component (CSCI) sub version */
   T_UINT16 component_main_version;                              /* component (CSCI) main version */
   T_UINT8 component_id;                                         /* component (CSCI) ID */
   T_UINT8 date_day;                                             /* Autofilled: Saved space for date - day */
   T_UINT8 date_month;                                           /* Autofilled: Saved space for date - month */
   T_UINT8 date_year;                                            /* Autofilled: Saved space for date - year */
   T_UINT8 date_hour;                                            /* Autofilled: Saved space for date - hour */
   T_UINT8 date_minute;                                          /* Autofilled: Saved space for date - minute */
   T_UINT8 spare1;                                               /* Spare */
   T_UINT8 Board_ID;                                             /* Board ID */
   T_UINT32 item_number;                                         /* Item number - Barad Plada */
   T_UINT32 component_checksum;                                  /* Autofilled: Saved for file checksum (Excluding this descriptor) */
   T_UINT32 component_length;                                    /* Autofilled: Saved for file length (Excluding this descriptor) */
   T_UINT8 DoCompress;                                           /* Spare */
   T_UINT8 spare2[CONST_31];                                     /* Autofilled: Saved for file length (Excluding this descriptor) */
   T_UINT32 descriptor_checksum;
} SDssFileDescriptor;

typedef struct SSlaveCommStatus {                                /* Struct 1786 */

#ifdef LSB_BIT_FIELDS
   T_UINT32 commErrorCounter        : 16;                        /* Increment by one when recognize one of the errors */
   T_UINT32 crcFail                 : 1;
   T_UINT32 opcodeFail              : 1;
   T_UINT32 sizeError               : 1;
   T_UINT32 frameCounterFail        : 1;
   T_UINT32 spare                   : 12;
#else
   T_UINT32 spare                   : 12;
   T_UINT32 frameCounterFail        : 1;
   T_UINT32 sizeError               : 1;
   T_UINT32 opcodeFail              : 1;
   T_UINT32 crcFail                 : 1;
   T_UINT32 commErrorCounter        : 16;                        /* Increment by one when recognize one of the errors */
#endif

} SSlaveCommStatus;

typedef struct SLengthHeaderMsgData {                            /* Struct 2248 */
   T_UINT16 length;
   T_UINT16 frameCounter;
} SLengthHeaderMsgData;

typedef struct SCheckSumFooterMsgData {                          /* Struct 2253 */
   T_UINT32 checkSum;
} SCheckSumFooterMsgData;



#if defined WIN32 || defined __LINUX__
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif /* commonDef_h */

