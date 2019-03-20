#pragma once
#pragma pack(1)
struct sBurst {
	unsigned char address;  // must be 0x20
	unsigned char nd;
	unsigned char ea;
	// All raw uint18_t values are in little-endian
	short temp_out;
	short gyro_out[3];  // X,Y,Z
	short accel_out[3];
	short gpio_out;
	short count_out;
	unsigned char cr; // must be 0x0d
};

struct sBurstSingle {
	unsigned char address;  // must be 0x20
	unsigned char nd;
	unsigned char ea;
	// All raw uint18_t values are in little-endian
	short temp_out;
	short gyro_out[3];  // X,Y,Z
	short accel_out[3];
	short gpio_out;
	unsigned char cr; // must be 0x0d
};
struct sMV340PD {
	struct commonHeader header;
	struct sBurst burst;
};
struct sMV340PDSingle {
	struct commonHeader header;
	struct sBurstSingle burst;
};
#pragma pack()
/*
    Data conversion
	(see datasheet)

	Temperature
	T (centigrade) = SF * (A-1469) + 25 where Scale Factor is -0.0053964
*/
double V340_Temperature(short a)
{
	return -0.0053964 *(a - 1469) + 25;
}
/*
     scale factor 0.18 mG per LSB
*/
double V340_Accelerometer(short a)
{
	return a * 0.18;
}
/*
scale factor 0.015deg/sec per LSB
*/
double V340_Gyro(short a)
{
	return a * 0.015;
}