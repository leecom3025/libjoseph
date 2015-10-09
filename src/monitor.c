
#if defined X86
	#include "../include/libjoseph.h"
#else
	#include "libjoseph.h"
#endif

#ifdef LOG_TAG
#undef LOG_TAG
#endif 

#define LOG_TAG "TORH"

#define GOVERN "/sys/device/system/cpu/cpu%d/cpufreq/scaling_governor"

int main (int argc, char *argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}
	int period = 100000; // 100 mili == 0.1 sec
	char st[2048];
	struct jcpu **cpu;
	Joseph_CPU_ops(&cpu);

	while(1) {
		usleep(period);
		if (Joseph_CPU_read(cpu) != -1) {
			bzero(st, 2048);
#if _PRODUCT == _hima
      sprintf(st, "%lu, %d,%d,%d,%d,%d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d\n", getmicro(),
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[4]->temp, cpu[5]->temp, cpu[6]->temp, cpu[7]->temp, 
				cpu[0]->freq, cpu[1]->freq, cpu[2]->freq, cpu[3]->freq,
				cpu[4]->freq, cpu[5]->freq, cpu[6]->freq, cpu[7]->freq);
          
/*			sprintf(st, "%lu, %d, %d, %d, %d, %d, %d, %d, %d, %d,%d, %d,%d, %d,%d, %d,%d, %d,%d, %d,%d, %d,%d, %d,%d\n",
				getmicro(),
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[4]->temp, cpu[5]->temp, cpu[6]->temp, cpu[7]->temp, 
				cpu[0]->util, cpu[0]->freq, cpu[1]->util, cpu[1]->freq,
				cpu[2]->util, cpu[2]->freq, cpu[3]->util, cpu[3]->freq,
				cpu[4]->util, cpu[4]->freq, cpu[5]->util, cpu[5]->freq,
				cpu[6]->util, cpu[6]->freq, cpu[7]->util, cpu[7]->freq);
*/
#else
      sprintf(st, "%lu, %d,%d,%d,%d, %d,%d,%d,%d\n",
				getmicro(),
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[0]->freq, cpu[1]->freq, cpu[2]->freq, cpu[3]->freq);
#endif
      ALOGD("%s", st);
		}
	}
	return 0;
}
