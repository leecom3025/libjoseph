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

//APQ8064 - Nexus 4
//MSM8974 - Nexus 5

int main (int argc, char* argv[]) {
	if (argc != 2 && argv[0] != NULL) {
		int a = 1;
	}
/*
	if (argc != 2) {
	    fprintf(stderr, "Usage: %s <flush-frequency-in-seconds>\n", argv[0]);
	    exit(2);
	} else {
        int frequency = atoi(argv[1]);
	}
*/

#ifdef PRODUCT
	printf("Product is ");
	if (strcmp(PRODUCT, hammerhead) == 0)
		printf("Nexus 5 (%s)!\n", PRODUCT);
	else if (strcmp(PRODUCT, mako) == 0)
		printf("Nexus 4 (%s)!\n", PRODUCT);
	else
		printf("Unknown (%s)!\n", PRODUCT);
#endif

	printf("======= joseph_utils test =======\n");

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

	printf("======= joseph_perf test =======\n");
	jperf_usage();

	jperf_adjust();
	jperf_start();
		sleep(1);
	jperf_stop();
	jperf_write(path, "Job\tTaken", "Sleep:\t");
	printf("%ld\n", jperf_time());

#ifdef WITH_ZMQ
	printf("======= static_zmq test =======\n");
	void *context = zmq_init(1);
	assert(context != NULL);
	printf("passed!\n");
#endif

#ifdef WITH_CJSON
	printf("======= static_cjson test =======\n");
	cJSON *root = cJSON_CreateObject();  
	assert(root != NULL);
	printf("passed!\n");
#endif

	printf("====== joseph_thermal test ======\n");

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

	return 0;
}
