/*
 * Structure of data in EEPROM
 */
struct sRun {
    long ID;
	unsigned long LastPowerDownTime;       // epoch GMT
    unsigned long cumalativeRunTime;     // seconds
	unsigned long lastFatalDiskError;      // epoch GMT
    long fileNumber;   // for nnnnn in Lmmnnnnn.BIN
    long GPSrelative;   // for future use
    long reserve2;   // for future use
    long reserve3;   // for future use
};
struct sMS5611BA03 {
    long OSR;
    unsigned long rate;  // Hertz
    long Active; // 0 No, non zero YES
    long StateMachine;   // 0 No use polling, 1 YES
    long reserve2;   // for future use
    long reserve3;   // for future use
};
struct sCalibration {
    double Gain[27];
    double Bias[9];
};
struct sLSM9DS1 {
    long Gscale;    // deg/sec/sec
    long GODR;       // gyro sample rate
    long Ascale;    // accelerometer G at full scale
    long AODR;       // accelerometer sample rate
    long Mscale; // magnetometer at full scale
    long MODR;       // magnetometer sample rate
    struct sCalibration Calibration; // Calibration data 72 words
    long Active;   // for future use
    long reserve2;   // for future use
};
struct sMV340PDx {
    long rate;      // samples per sec
    long Active; // 0 No, non zero YES
    long Dead;     // timeout in millsecs for new data to arrive
    struct sCalibration Calibration; // Calibration data 72 words
    long reserve1;   // for future use
    long reserve2;   // for future use
};
struct sDS2745x {
    long MV;         // Powerdown voltage (millivolt)
    long Secs;        // Sample rate (seconds)
    long chargeMV;   // Voltage to go to low charge rate
    long reserve1;   // for future use
};

struct sMPU9250 {
	uint32_t Gscale;
	uint32_t Ascale;
	uint32_t Mscale;
	uint32_t lowpassfilter;
	uint32_t sampleRate;
	uint32_t Active;
	struct sCalibration Calibration; // Calibration data
	int32_t reserve2;
	int32_t reserve3;
};

struct sIMU3020 {
	int32_t Active; // 0 No, non zero YES
	int32_t Gscale;    // deg/sec/sec
	int32_t Ascale;    // accelerometer G at full scale
	int32_t BandWidthFilter;
	int32_t SampleRate;  // All sensors
	int32_t BaudRate;  //
	struct sCalibration Calibration; // Calibration data
	int32_t reserve1;   // for future use
	int32_t reserve2;   // for future use
};

struct sEEPROM
{
    struct sRun run;  // 8 dwords, offset 0
    struct sMS5611BA03 baro;  // 6 dwords, offset 32
    struct sLSM9DS1 accel;  // 80 dwords offset 56
    struct sMV340PDx Epson; // 77 dwords offset 376
    struct sDS2745x battery; // 4 dwords offset 684
	struct sIMU3020 IMU3020;
	struct sMPU9250 MPU9250;
};
