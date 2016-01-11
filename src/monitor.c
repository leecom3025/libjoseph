
#if defined X86
	#include "../include/libjoseph.h"
#else
	#include "libjoseph.h"
#endif

#ifdef LOG_TAG
  #undef LOG_TAG 
#endif

#define LOG_TAG "libj"

int main(int argc, char *argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}
  return monitor(argc, arvg);
}

int monitor(int argc, char *argv[]) {
  int c, i; 
	int period = 100000; // 100 mili == 0.1 sec
  int verbose = J_false;
  double avg_tmp = 0.0;

  while ((c = getopt(argc, argv, "t:")) != -1) {
    switch(c) {
      case 't':
        period =  atoi(optarg);
        break;
      default:
        printf("help not supported\n");
    }
  }
	
  char st[2048];
	struct jcpu **cpu;
#ifdef ANDROID
	libj_CPU_ops(&cpu);
#endif

	while(1) {
		usleep(period);
#ifdef ANDROID
		if (libj_CPU_read(cpu) != -1) {
      avg_tmp = 0.0;
      for (i = 0; i < CPU_NUM; i++) {
        avg_tmp += cpu[i]->temp;
      }
      avg_tmp /= CPU_NUM;
      libj_setString("avg_temp", avg_tmp);

      if (verbose) {
        bzero(st, 2048);
#if _PRODUCT == _hima
        sprintf(st, "%s, %d,%d,%d,%d,%d,%d,%d,%d, \
            %d,%d,%d,%d,%d,%d,%d,%d\n",
          libj_perf_getmicro(),
          cpu[0]->temp, cpu[1]->temp, 
          cpu[2]->temp, cpu[3]->temp,
          cpu[4]->temp, cpu[5]->temp, 
          cpu[6]->temp, cpu[7]->temp,
          cpu[0]->freq, cpu[1]->freq, 
          cpu[2]->freq, cpu[3]->freq,
          cpu[4]->freq, cpu[5]->freq, 
          cpu[6]->freq, cpu[7]->freq);
#else
        sprintf(st, "%ls, %d,%d,%d,%d, %d,%d,%d,%d\n",
          libj_perf_getmicro(),
          cpu[0]->temp, cpu[1]->temp, 
          cpu[2]->temp, cpu[3]->temp,
          cpu[0]->freq, cpu[1]->freq, 
          cpu[2]->freq, cpu[3]->freq);
#endif // PRODUCT
        ALOGD("%s", st);
      }
		}
#endif // ANDROID
	}
	return 0;
}

