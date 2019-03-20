#pragma once
struct sMPU9250_Config {
	struct commonHeader header;
	unsigned short god;  // up to 2000dps
	unsigned char aod;  // up to 8g
	unsigned char mod;  // up to 16gauss
	short sensitivity[3];
};
