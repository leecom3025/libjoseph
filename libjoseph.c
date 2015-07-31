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

#include "libjoseph.h"

int main (int argc, char* argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}

	JLT("Default path is %s", DEFAULT_PATH);
#ifdef PRODUCT
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

#ifdef WITH_ZMQ
	JLT("======= static_zmq test =======");
	void *context = zmq_init(1);
	assert(context != NULL);
	JLT("ZeroMQ passed");
#endif

#ifdef WITH_CJSON
	JLT("======= static_cjson test =======");
	cJSON *root = cJSON_CreateObject();  
	assert(root != NULL);
	JLT("cJSON passed!");
#endif

	/* Thermal unit supported for Android only currently */
#ifdef ANDROID
	JLT("====== joseph_thermal test ======");

	int temperature, online;
	int *utils, *freqs;

	Joseph_readCPU_temp(&temperature);
	printf("Temperature: %d\n", temperature);

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
	struct jsocket *sck;
	int port = 30331;
	int pid = fork();
	if (pid > 0) { // parent
		if (jnet_init(&sck, JNET_TCP) < 0) 
			JLE("jnet_init");
		if (jnet_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("jnet_prep");
		char *msg;
		if (jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("jnet_recv");
		if (jnet_send(&sck, &msg) < 0)
			JLE("jnet_send");
		if (jnet_done(&sck) < 0)
			JLE("jnet_done");
		JLT("JNET_TCP passed!");
	} else if (pid == 0) { // child 
		if (jnet_init(&sck, JNET_TCP) < 0) 
			JLE("jnet_init");
		if (jnet_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("jnet_prep");
		char *msg = "TEST SUCCESS";
		if (jnet_send(&sck, &msg) < 0) 
			JLE("jnet_send");
		if (jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("jnet_recv");
		if (jnet_done(&sck) < 0)
			JLE("jnet_done");

		return 0; // kill child
	} else {
		JLE("fork() failed");
		return -1;
	}

	sleep(2);
	port = 30332;
	pid = fork();
	if (pid > 0) { // parent
		if (jnet_init(&sck, JNET_UDP) < 0) 
			JLE("jnet_init");
		if (jnet_prep(&sck, JNET_SERVER, &port, NULL) < 0) 
			JLE("jnet_prep");
		char *msg;
		if (jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("jnet_recv");
		if (jnet_send(&sck, &msg) < 0)
			JLE("jnet_send");
		if (jnet_done(&sck) < 0)
			JLE("jnet_done");
		JLT("JNET_UDP passed!");
	} else if (pid == 0) { // child 
		if (jnet_init(&sck, JNET_UDP) < 0) 
			JLE("jnet_init");
		if (jnet_prep(&sck, JNET_CLIENT, &port, "127.0.0.1") < 0) 
			JLE("jnet_prep");
		char *msg = "TEST SUCCESS";
		if (jnet_send(&sck, &msg) < 0) 
			JLE("jnet_send");
		if (jnet_recv(&sck, &msg, strlen(msg)) < 0)
			JLE("jnet_recv");
		if (jnet_done(&sck) < 0)
			JLE("jnet_done");
		return 0; // kill child
	} else {
		JLE("fork() failed");
	}

	return 0;
}
