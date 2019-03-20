/*
  Convert 16 bit raw data to float values
  Convert accelerometer from m/s^2 to G
  Convert Magnetometer from tesla to microtesla
*/
struct sMPU9150 {
  struct commonHeader header;
  char accelselect;		// for scaling accelerometer data
  char gyroselect;		// for scaling gyro data
  //short data[8];   // why this ??
  short data[9];   // or is it 9 float ?
 // float data[9];   // or is it 9 float ?
};

struct sMPU9150_Calib {
  struct commonHeader header;
  unsigned char configregs[4];		// 28,27,26,25
};

//*****************************************************************************
//
// The factors used to convert the acceleration readings from the MPU9150 into
// floating point values in meters per second squared.
//
// Values are obtained by taking the g conversion factors from the data sheet
// and multiplying by 9.81 (1 g = 9.81 m/s^2).
//
//*****************************************************************************
static const float g_fMPU9150AccelFactors[] =   // report as G
{
    2.0F/32767, //0.0005985482F/9.81,                           // Range = +/- 2 g (16384 lsb/g)
    4.0F/32767, //0.0011970964F/9.81,                           // Range = +/- 4 g (8192 lsb/g)
    8.0F/32767, //0.0023941928F/9.81,                           // Range = +/- 8 g (4096 lsb/g)
    16.0F/32767  //0.0047883855F/9.81                            // Range = +/- 16 g (2048 lsb/g)
};

//*****************************************************************************
//
// The factors used to convert the acceleration readings from the MPU9150 into
// floating point values in radians per second.
//
// Values are obtained by taking the degree per second conversion factors
// from the data sheet and then converting to radians per sec (1 degree =
// 0.0174532925 radians).
//
//*****************************************************************************
static const float g_fMPU9150GyroFactors[] =
{
    250.0F/32767, // 1.3323124e-4F,                           // Range = +/- 250 dps (131.0)
    500.0F/32767, //2.6646248e-4F,                           // Range = +/- 500 dps (65.5)
    1000.0F/32767, //5.3211258e-4F,                           // Range = +/- 1000 dps (32.8)
    2000.0F/32767 //0.0010642252F                            // Range = +/- 2000 dps (16.4)
};

//*****************************************************************************
//
// Converting sensor data to tesla (0.3 uT per LSB)
//
//*****************************************************************************
#define CONVERT_TO_TESLA        0.0000003F
#define TESLA_TO_GAUSS		10000

