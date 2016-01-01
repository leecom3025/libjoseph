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

#if 0
void *threadFunc(void *arg)
{
	int *t;
  int n;
  //libj_readCPU_alltemps(&t);
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

void whileFunc(int thrds)
{
  while(1)
  {
    int threads, thread_num = thrds;
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
}
#endif

int main (int argc, char* argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}
  
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
  
  libj_perf_start();
	libj_getInt("int_test", &int_test);
	printf("Int: %d\n", int_test);
  libj_perf_stop();
  printf("%s\n", libj_perf_time());


	libj_getString("string_test", &string_test);
	printf("%s", string_test);

	libj_getDouble("double_test", &double_test);
	printf("Double: %f\n", double_test);

	libj_getFloat("float_test", &float_test);
	printf("Float: %lf\n", float_test);

	libj_getPath("libj_perf_test", &path);
	printf("Path: %s\n", path);
	JLT("JUtils passed!");

	JLT("======= joseph_perf test =======");
	libj_perf_usage();

	libj_perf_adjust();
	libj_perf_start();
		sleep(1);
	libj_perf_stop();
	libj_perf_write(path, "Job\tTaken", "Sleep:\t");
	printf("%ld\n", libj_perf_time_raw());
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

	libj_readCPU_alltemps(&temperature);
	for (i = 0; i < CPU_NUM; i++) {
		printf("CPU %d temperature: %d ['C]\n", i, *(temperature + i));
	}
	libj_readCPU_alltemps_free(&temperature);

	libj_readCPU_allutils(&utils, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d util: %d%%\n", i, *(utils + i));
	}
	libj_readCPU_allutils_free(&utils);

	libj_readCPU_allfreqs(&freqs, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d freq: %dHz\n", i, *(freqs + i));
	}
	libj_readCPU_allfreqs_free(&freqs);

	libj_readCPU_both(&utils, &freqs, &online);
	for (i = 0; i < online; i++) {
		printf("CPU %d: (%d%%, %dHz)\n", i, *(utils + i), *(freqs + i));
	}
	libj_readCPU_both_free(&utils, &freqs);
	JLT("JTherm passed!");
#endif

	JLT("====== joseph_net test ======");
	struct Jsocket *sck;
	int port = 30331;
	int pid = fork();
	if (pid > 0) { // parent
		if (libj_net_init(&sck, JNET_TCP) < 0) 
			JLE("libj_net_init");
		if (libj_net_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("libj_net_prep");
		char *msg;
		if (libj_net_recv(&sck, &msg, 255) < 0)
			JLE("libj_net_recv");
		if (libj_net_send(&sck, &msg) < 0)
			JLE("libj_net_send");
		if (libj_net_done(&sck) < 0)
			JLE("libj_net_done");
		JLT("libj_net_TCP passed!");
	} else if (pid == 0) { // child 
		if (libj_net_init(&sck, JNET_TCP) < 0) 
			JLE("libj_net_init");
		if (libj_net_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("libj_net_prep");
		char *msg = "TEST SUCCESS";
		if (libj_net_send(&sck, &msg) < 0) 
			JLE("libj_net_send");
		if (libj_net_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("libj_net_recv");
		if (libj_net_done(&sck) < 0)
			JLE("libj_net_done");
		return 0; // kill child
	} else {
		JLE("fork() failed");
		return -1;
	}

	sleep(1);
	pid = fork();
	if (pid > 0) { // parent
		if (libj_net_init(&sck, JNET_UDP) < 0) 
			JLE("libj_net_init");
		if (libj_net_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("libj_net_prep");
		char *msg;
		if (libj_net_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("libj_net_recv");
		if (libj_net_send(&sck, &msg) < 0)
			JLE("libj_net_send");
		if (libj_net_done(&sck) < 0)
			JLE("libj_net_done");
		JLT("libj_net_UDP passed!");
	} else if (pid == 0) { // child 
		if (libj_net_init(&sck, JNET_UDP) < 0) 
			JLE("libj_net_init");
		if (libj_net_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("libj_net_prep");
		char *msg = "TEST SUCCESS";
		if (libj_net_send(&sck, &msg) < 0) 
			JLE("libj_net_send");
		if (libj_net_done(&sck) < 0)
			JLE("libj_net_done");
		return 0; // kill child
	} else {
		JLE("fork() failed");
	}
	return 0;
}

