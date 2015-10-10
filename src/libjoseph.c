/*
 * Copyright (C) 2015 HyunJong Joseph Lee, Korvo, Georgia Tech
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined X86
  #include "../include/libjoseph.h"
#else
  #include "libjoseph.h"
#endif

void *threadFunc(void *arg)
{
	int *t;
  int n;
  //Joseph_readCPU_alltemps(&t);
  int c = 123456789;
  while (c > 0){
    c %= 3;
  }

  double k = 1234567890;
  while ( k > 0) {
    k /= 3.0;
  }
  return NULL;
}

void showThermal()
{
	int *temperature;
	int i, cpu = 4;
	Joseph_readCPU_alltemps(&temperature);
#if 0
	for ( i = 0; i < cpu; i++)
		printf("CPU %d temperature: %d ['C]\n", i, *(temperature + i));
#endif
	printf("%d\t%d\t%d\t%d\n", *(temperature), *(temperature+1),
		*(temperature+2), *(temperature+3));
	Joseph_readCPU_alltemps_free(&temperature);
	return;	
}

void showUtil()
{
	int *util;
	int i, cpu;
	Joseph_readCPU_allutils(&util, &cpu);
	for (i = 0; i < cpu; i++) 
		printf("\t%d", *(util+i));
	printf("\n");

	//printf("%d\t%d\t%d\t%d\n", *util, *(util+1), *(util+2), *(util+3));
	Joseph_readCPU_allutils_free(&util);
	return;
}

void show() {
	int *util, *freq, *temp;
	int i, mCpu, cpu = 4;
	char st[2048];
	Joseph_readCPU_alltemps(&temp);
	Joseph_readCPU_both(&util, &freq, &mCpu);

	sprintf(st, "%d, %d, %d, %d [ ", *temp, *(temp+1), *(temp+2), *(temp+3));

	for (i=0; i < mCpu; i++) {
		if (*(freq+i) < 2265600){ 
			char mBuff[64];

			sprintf(mBuff, "%d(%d) ", *(util+i), *(freq+i));
			strcat(st, mBuff);
		} else
			strcat(st, "*(*) ");
	}
	strcat(st, "]");
	
	ALOGD("%s",st);
	Joseph_readCPU_alltemps_free(&temp);
	Joseph_readCPU_both_free(&util, &freq);
	
	//showThermal();
	//showUtil();

	return;
}

int main (int argc, char* argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}

  while(1){
		int threads=0;
		int thread_num =256;
		pthread_t pth[thread_num];

		for(;threads<thread_num;threads++)
		{
			pth[threads] = (pthread_t*) malloc(sizeof(pthread_t));
			pthread_create(&pth[threads],NULL,threadFunc,"processing...");
		}

		printf("main waiting for thread to terminate...\n");
		for (threads = 0; threads < thread_num; threads++ )
			pthread_join(pth[threads],NULL);
  }

	struct jcpu **cpu;
	Joseph_CPU_ops(&cpu);

	while(1)
	{
		//sleep(1);
		usleep(10000);
		if (Joseph_CPU_read(cpu) != -1) {
			int i;
			char st[2048];
			char temp[512], util[512], freq[512];
			sprintf(st, "%d, %d, %d, %d [%d(%d) %d(%d) %d(%d) %d(%d)]\n",
				cpu[0]->temp, cpu[1]->temp, cpu[2]->temp, cpu[3]->temp, 
				cpu[0]->util, cpu[0]->freq, cpu[1]->util, cpu[1]->freq,
				cpu[2]->util, cpu[2]->freq, cpu[3]->util, cpu[3]->freq);
			ALOGD("%s", st);
		}
//		show();
		
		#if 0 
		int threads=0;
		int thread_num =1;
		pthread_t pth[thread_num];

		for(;threads<thread_num;threads++)
		{
			pth[threads] = (pthread_t*) malloc(sizeof(pthread_t));
			pthread_create(&pth[threads],NULL,threadFunc,"processing...");
		}

		printf("main waiting for thread to terminate...\n");
		for (threads = 0; threads < thread_num; threads++ )
			pthread_join(pth[threads],NULL);
		#endif
	}

#if 0
#if defined ANDROID && defined PRODUCT
	printf("Product is ");
	if (strcmp(PRODUCT, hammerhead) == 0)
		printf("Nexus 5 (%s)!\n", PRODUCT);
	else if (strcmp(PRODUCT, mako) == 0)
		printf("Nexus 4 (%s)!\n", PRODUCT);
	else
		printf("Unknown (%s)!\n", PRODUCT);
#endif

  JLT("======= joseph_utils test =======");
	int int_test, i;
	char *string_test, *path;
	double double_test;
	float float_test;

	Joseph_getInt("int_test", &int_test);
	printf("Int: %d\n", int_test);

	Joseph_getString("string_test", &string_test);
	printf("%s", string_test);

	Joseph_getDouble("double_test", &double_test);
	printf("Double: %f\n", double_test);

	Joseph_getFloat("float_test", &float_test);
	printf("Float: %lf\n", float_test);

	Joseph_getPath("jperf_test", &path);
	printf("Path: %s\n", path);
	JLT("JUtils passed!");

	JLT("======= joseph_perf test =======");
	jperf_usage();

	jperf_adjust();
	jperf_start();
		sleep(1);
	jperf_stop();
	jperf_write(path, "Job\tTaken", "Sleep:\t");
	printf("%ld\n", jperf_time());
	JLT("JPerf passed!");

#if defined WITH_ZMQ
	JLT("======= static_zmq test =======");
	void *context = zmq_init(1);
	assert(context != NULL);
	JLT("ZeroMQ passed");
#endif

#if defined WITH_CJSON
	JLT("======= static_cjson test =======");
	cJSON *root = cJSON_CreateObject();  
	assert(root != NULL);
	JLT("cJSON passed!");
#endif

	/* Thermal unit supported for Android only currently */
#if defined ANDROID
	JLT("====== joseph_thermal test ======");

	int online, kk;
	int *temperature, *utils, *freqs;

	Joseph_readCPU_alltemps(&temperature);
	for (i = 0; i < CPU_NUM; i++) {
		printf("CPU %d temperature: %d ['C]\n", i, *(temperature + i));
	}
	Joseph_readCPU_alltemps_free(&temperature);

	Joseph_readCPU_allutils(&utils, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d util: %d%%\n", i, *(utils + i));
	}
	Joseph_readCPU_allutils_free(&utils);

	Joseph_readCPU_allfreqs(&freqs, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d freq: %dHz\n", i, *(freqs + i));
	}
	Joseph_readCPU_allfreqs_free(&freqs);

	Joseph_readCPU_both(&utils, &freqs, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d: (%d%%, %dHz)\n", i, *(utils + i), *(freqs + i));
	}
	Joseph_readCPU_both_free(&utils, &freqs);
	JLT("JTherm passed!");
#endif

	JLT("====== joseph_net test ======");
	struct Jsocket *sck;
	int port = 30331;
	int pid = fork();
	if (pid > 0) { // parent
		if (Jnet_init(&sck, JNET_TCP) < 0) 
			JLE("Jnet_init");
		if (Jnet_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("Jnet_prep");
		char *msg;
		if (Jnet_recv(&sck, &msg, 255) < 0)
			JLE("Jnet_recv");
		if (Jnet_send(&sck, &msg) < 0)
			JLE("Jnet_send");
		if (Jnet_done(&sck) < 0)
			JLE("Jnet_done");
		JLT("Jnet_TCP passed!");
	} else if (pid == 0) { // child 
		if (Jnet_init(&sck, JNET_TCP) < 0) 
			JLE("Jnet_init");
		if (Jnet_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("Jnet_prep");
		char *msg = "TEST SUCCESS";
		if (Jnet_send(&sck, &msg) < 0) 
			JLE("Jnet_send");
		if (Jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("Jnet_recv");
		if (Jnet_done(&sck) < 0)
			JLE("Jnet_done");
		return 0; // kill child
	} else {
		JLE("fork() failed");
		return -1;
	}

	sleep(1);
	pid = fork();
	if (pid > 0) { // parent
		if (Jnet_init(&sck, JNET_UDP) < 0) 
			JLE("Jnet_init");
		if (Jnet_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("Jnet_prep");
		char *msg;
		if (Jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("Jnet_recv");
		if (Jnet_send(&sck, &msg) < 0)
			JLE("Jnet_send");
		if (Jnet_done(&sck) < 0)
			JLE("Jnet_done");
		JLT("Jnet_UDP passed!");
	} else if (pid == 0) { // child 
		if (Jnet_init(&sck, JNET_UDP) < 0) 
			JLE("Jnet_init");
		if (Jnet_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("Jnet_prep");
		char *msg = "TEST SUCCESS";
		if (Jnet_send(&sck, &msg) < 0) 
			JLE("Jnet_send");
		if (Jnet_done(&sck) < 0)
			JLE("Jnet_done");
		return 0; // kill child
	} else {
		JLE("fork() failed");
	}
#endif
	return 0;
}
