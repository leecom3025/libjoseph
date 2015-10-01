
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
	/*system("stop mdprecision");
	
	int i;
	char cmd[strlen(GOVERN)];
	FILE* fd;
	for (i=0; i<4; i++) {
		char cmd[strlen(GOVERN)];
		sprintf(cmd, GOVERN, i);
		ALOGD("%s", cmd);
		fd = fopen(cmd, "w");
		if (fd == NULL)
			return -1;
		fscanf(fd, "%s", "ondemand");
		fclose(fd);
	}
	system("echo ondemand > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor");
	system("echo ondemand > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor");
	system("echo ondemand > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor");
	system("echo ondemand > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor");*/

	int period = 100000; // 100 mili == 0.1 sec
	char st[2048];
	struct jcpu **cpu;
	Joseph_CPU_ops(&cpu);

	while(1) {
		usleep(period);
		if (Joseph_CPU_read(cpu) != -1) {
			bzero(st, 2048);
			sprintf(st, "%lu, %d, %d, %d, %d, %d,%d, %d,%d, %d,%d, %d,%d,\n",
				getmicro(),
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[0]->util, cpu[0]->freq, cpu[1]->util, cpu[1]->freq,
				cpu[2]->util, cpu[2]->freq, cpu[3]->util, cpu[3]->freq);
			ALOGD("%s", st);
		}
	}
	return 0;
}
