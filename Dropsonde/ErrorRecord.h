struct sError {
  struct commonHeader header;
  unsigned short version;
  unsigned short linenumber;
  unsigned short linelength;
  // char text []
};

struct sErrorExt {
	struct commonHeader header;
	unsigned short version;
	uint32_t cumalativeRunTime;
	uint32_t tbd1;
	uint32_t tbd2;
	uint32_t tbd3;
	unsigned short linenumber;
	unsigned short linelength;
	// char text []
};
