#pragma once
#pragma pack(1)
struct sNotificationX {
	struct commonHeader header;
	unsigned char note;
	struct mytm rtc;
};
enum eNotification { N_NONE, N_POWERUP, N_BUTTON_PRESS, N_1PPS };
