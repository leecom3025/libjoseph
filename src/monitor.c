
#if defined X86
	#include "../include/libjoseph.h"
#else
	#include "libjoseph.h"
#endif

int main (int argc, char *argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}
	
	system("echo ondemand > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor");

	int period = 100000;
	char st[2048];
	struct jcpu **cpu;
	Joseph_CPU_ops(&cpu);

	while(1) {
		usleep(period);
		if (Joseph_CPU_read(cpu) != -1) {
			bzero(st, 2048);
			sprintf(st, "%d, %d, %d, %d [%d(%d) %d(%d) %d(%d) %d(%d)]\n",
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[0]->util, cpu[0]->freq, cpu[1]->util, cpu[1]->freq,
				cpu[2]->util, cpu[2]->freq, cpu[3]->util, cpu[3]->freq);
			ALOGD("%s", st);
		}
	}
	return 0;
}
