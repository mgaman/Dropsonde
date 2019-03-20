
struct sMS56_CALIBRATION {
  struct commonHeader header;
  unsigned short C[6];  // calibration C[1] to C[6] in Pisa code, change to C[0] to C[5] here
};

struct sMS56_TP {
  struct commonHeader header;
  unsigned long data[2];
};

void FormatAltimeter(unsigned long D1,unsigned long D2,unsigned short *C,double *Temp,double *Press)
{
	// orignal code in C example refers to C[4] in an array of 8
	// we have an array of 6 starting from 2nd item in original array so C[n] becomes C[n-1]
	//double P; // compensated pressure value
	//double T; // compensated temperature value
	double dT; // difference between actual and measured temperature
	double OFF; // offset at actual temperature
	double SENS; // sensitivity at actual temperature
    dT=D2-C[4]*pow(2.0,8.0);
    OFF=C[1]*pow(2.0,16.0)+dT*C[3]/pow(2.0,7.0);
    SENS=C[0]*pow(2.0,15.0)+dT*C[2]/pow(2.0,8.0);
    
    *Temp=(2000+(dT*C[5])/pow(2.0,23.0))/100;   // temperature * 100
    *Press=(((D1*SENS)/pow(2.0,21.0)-OFF)/pow(2.0,15.0))/100; // millibar

}
