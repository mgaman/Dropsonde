#pragma once
struct sGeneralCalib {
	struct commonHeader header;
	double calib[36]; // 27 gain, 9 bias
};
