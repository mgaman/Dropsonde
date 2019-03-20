
struct sLSM9SD0_XM {
  struct commonHeader header;
  short Accel[3];
  short Magnetometer[3];
};

struct sLSM9SD0_G {
  struct commonHeader header;
  short Gyro[3];
};

struct sLSM9SD0_M {
  struct commonHeader header;
  short Mag[3];
};

struct sLSM9SD0_All {
  struct commonHeader header;
  short Accel[3];
  short Magnetometer[3];
  short Gyro[3];
};

struct sLSM9SD0_Config {
  struct commonHeader header;
  char G[5];   // control registers
  char XM[8];
};

struct sLSM9SD1_Config {
	struct commonHeader header;
	unsigned short god;  // up to 2000dps
	unsigned char aod;  // up to 8g
	unsigned char mod;  // up to 16gauss
};

static const float LSM9DS0AccelFactors[] =   // report as XM
{
    2.0F/32767, // Range = +/- 2 g (16384 lsb/g)
    4.0F/32767, // Range = +/- 4 g (8192 lsb/g)
    4.0F/32767, // Range = +/- 6 g (8192 lsb/g)
    8.0F/32767, // Range = +/- 8 g (4096 lsb/g)
    16.0F/32767 // Range = +/- 16 g (2048 lsb/g)
};

static const float LSM9DS1AccelFactors[] =   // report as XM
{
	2.0F / 32767, // Range = +/- 2 g (16384 lsb/g)
	16.0F / 32767, // Range = +/- 4 g (8192 lsb/g)
	4.0F / 32767, // Range = +/- 6 g (8192 lsb/g)
	8.0F / 32767, // Range = +/- 8 g (4096 lsb/g)
};

static const float LSM9DS0GyroFactors[] =   // report as G
{
    245.0F/32767, // Range = +/- 245 deg/sec
    500.0F/32767, // Range = +/- 500 deg/sec
    2000.0F/32767, // Range = +/- 2000 deg/sec
    2000.0F/32767, // Range = +/- 2000 deg/sec
};

static const float LSM9DS1GyroFactors[] =   // report as G
{
	245.0F / 32767, // Range = +/- 245 deg/sec
	500.0F / 32767, // Range = +/- 500 deg/sec
	2000.0F / 32767, // Range = +/- 2000 deg/sec
	2000.0F / 32767, // Range = +/- 2000 deg/sec
};

static const float LSM9DS0MagnetometerFactors[] =   // report as G
{
    2.0F/32767, // Range = +/- 2 gauss
    4.0F/32767, // Range = +/- 4 gauss
    8.0F/32767, // Range = +/- 8 gauss
    12.0F/32767, // Range = +/- 12 gauss
};

static const float LSM9DS1MagnetometerFactors[] =   // report as G
{
	4.0F / 32767, // Range = +/- 2 gauss
	8.0F / 32767, // Range = +/- 4 gauss
	12.0F / 32767, // Range = +/- 8 gauss
	16.0F / 32767, // Range = +/- 12 gauss
};
