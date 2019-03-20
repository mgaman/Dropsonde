#pragma once
#pragma pack(1)
union uDWF {
	uint32_t dw;
	float df;
};

struct sTelem {
	union uDWF Accel[3]; // accel[3], gyro[3], mag[3], temperature all bigendian float
	union uDWF Gyro[3];
	union uDWF Mag[3];
	union uDWF temp;
};

struct sIMU3020Raw {
	struct commonHeader header;
	struct sTelem telem;
};

struct sIMU3020Calib {
	struct commonHeader header;
	uint32_t filter;
	uint32_t sampleRate;
	uint32_t Arange;
	uint32_t Grange;
};

uint32_t Filters[] = { 0,25,50,75,100,10,200 };
uint32_t Aranges[] = { 0,2,4,8,10,15,20,40 };
uint32_t Granges[] = { 0,120,240,480,960,1920 };
