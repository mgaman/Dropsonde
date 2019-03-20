


#ifndef CommonConstDef_h
#define CommonConstDef_h

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


/*---------------------- System Versions ----------------------*/

static const float h_ver_CommonConstDef = 0.3f;                  /* Header File Version */
static const float icd_ver_CommonConstDef = 0.11f;               /* ICD Version */
static const float ridaDB_ver_CommonConstDef = 3.23f;            /* Rida Database Version */


/*---------------------- System Constants ----------------------*/

#define CONST_2                       2                          /* Constant 6 */
#define CONST_1                       1                          /* Constant 11 */
#define CONST_3                       3                          /* Constant 16 */
#define CONST_12                      12                         /* Constant 21 */
#define CONST_7                       7                          /* Constant 26 */
#define CONST_9                       9                          /* Constant 31 */
#define CONST_4                       4                          /* Constant 36 */
#define CONST_5                       5                          /* Constant 41 */
#define CONST_11                      11                         /* Constant 46 */
#define CONST_15                      15                         /* Constant 51 */
#define CONST_6                       6                          /* Constant 56 */
#define CONST_10                      10                         /* Constant 61 */
#define CONST_14                      14                         /* Constant 66 */
#define CONST_13                      13                         /* Constant 71 */
#define CONST_8                       8                          /* Constant 76 */
#define CONST_500                     500                        /* Constant 81 */
#define CONST_24                      24                         /* Constant 286 */
#define CONST_50                      50                         /* Constant 316 */
#define CONST_60                      60                         /* Constant 321 */
#define CONST_48                      48                         /* Constant 326 */
#define CONST_21                      21                         /* Constant 331 */
#define CONST_16                      16                         /* Constant 336 */
#define CONST_20                      20                         /* Constant 341 */
#define CONST_352                     352                        /* Constant 346 */
#define CONST_620                     620                        /* Constant 351 */
#define CONST_256                     256                        /* Constant 461 */
#define CONST_27                      27                         /* Constant 466 */
#define CONST_22                      22                         /* Constant 471 */
#define CONST_19                      19                         /* Constant 476 */
#define CONST_40                      40                         /* Constant 496 */
#define const_1000                    1000                       /* Constant 503 */
#define SYNCHRO_CLOCK_FREQUENCY_HZ    (100000.0f)                /* Constant 521 - [Hz], equals 10 microsecond period */
#define CONST_31                      31                         /* Constant 581 */
#define CONST_32                      32                         /* Constant 586 */
#define SIZE_OF_BIG_BLOCKS            11000                      /* Constant 591 */
#define SIZE_OF_SMALL_BLOCKS          1100                       /* Constant 596 */
#define CONST_2000                    2000                       /* Constant 603 */
#define CONST_412                     412                        /* Constant 643 */
#define MICRO_TO_MILI                 100                        /* Constant 703 - time in 10 micro sec */
#define MICRO_TO_SEC                  100000                     /* Constant 708 */
#define CONST_288                     288                        /* Constant 723 */
#define CONST_34                      34                         /* Constant 743 */
#define CONST_356                     356                        /* Constant 833 */
#define CONST_320                     320                        /* Constant 998 */


#if defined WIN32 || defined __LINUX__
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif /* CommonConstDef_h */




