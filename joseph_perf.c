/*
 * Copyright (C) 2015 HyunJong Joseph Lee, Korvo, CERCS, Georgia Tech
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

#include "joseph_perf.h"

const char *puts_model = "Time taken: %lu micro-seconds";

void jperf_usage() {
#ifndef JPERF_ENABLE
	JLW("%s", "make sure to -DJPERF_ENABLE=1 in cmake_config\n");
	JLW("%s", "	or #define JPERF_NEABLE 1 in jperf.h\n");

	printf("%s", "make sure to -DJPERF_ENABLE=1 in cmake_config\n");
	printf("%s", " or #define JPERF_NEABLE 1 in jperf.h\n");
#endif
	JLW("%s", "jperf_start()\n\t... do some work\njperf_stop()\n");
	JLW("%s", "jperf_write(path, header, pattern)\n");
	JLW("%s", "jperf_record_initme() // if you want to check the time\n");
}

unsigned long getmicro() {
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    return curTime.tv_sec * (uint64_t) 1000000 + curTime.tv_usec;
}

void jperf_start() {
#ifdef JPERF_ENABLE
	unsigned long curr = getmicro();
	jperf = (struct timeMeasure*) malloc(sizeof(struct timeMeasure));
	jperf->time_start = curr;
#endif
}

void jperf_stop() {
#ifdef JPERF_ENABLE
	unsigned long curr = getmicro();
	if(!jperf) {
		JLE("You didn't call jperf_start()!\n\t(a.k.a. YOU ARE STUPID LOL)");
	}
	jperf->time_end = curr;
	jperf->time_took = jperf->time_end - jperf->time_start;
#endif
}

unsigned long jperf_time() {
	unsigned long ret = 0;

#ifdef JPERF_ENABLE
	if (!jperf || jperf->time_start > jperf->time_end) {
		JLE("ERROR");
	}

#ifdef JPERF_PUTS
	char* p = (char*)malloc(strlen(puts_model));
	sprintf(p, puts_model, jperf->time_took);
	puts (p);
	free(p);
#endif
	
	ret = jperf->time_took;
	free(jperf);
#endif

	return ret;
}

int jperf_record_init(char* filename, char* header) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (header == NULL) {
		JLW("header in jperf_record_init is NULL");
		header = "";
	}

#ifdef JPERF_ENABLE
	if (!jperf) {
		JLE("jperf_record_init() failed");
		return -1;
	}

	FILE *out = fopen(filename, "w");
	fprintf(out, "%s", TEMRS_OF_POLICY);
	fprintf(out, "%s\n", header);
	fprintf(out, "=======================================================\n");
	fclose(out);
#endif

	return 0;
}

int jperf_record_delete(char* filename) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	int ret;
#ifdef JPERF_ENABLE
	if (access(filename, F_OK) == -1) {
		JLE("%s does not exist", filename);
		return -1;
	} 
	ret = remove(filename);
#endif
	return ret;
}

int jperf_write(char* filename, char* header, char* pattern) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (header == NULL) {
		JLW("header in jperf_write is NULL");
		header = "";
	}

	if (pattern == NULL) {
		JLW("pattern in jperf_write is NULL");
		header = "";
	}

#ifdef JPERF_ENABLE
	if (!jperf) {
		JLE("perf_write() failed");
		return -1;
	}

	if (access(filename, F_OK) == -1)
		jperf_record_init(filename, header);
	FILE *out = fopen(filename, "a");

#ifdef JPERF_PRECISION
	jperf->time_took -= JPERF_PRECISION;
#endif

	fprintf(out, "%s%lu\n", pattern, jperf->time_took);
	fclose(out);
#endif

	return 0;
}

int jperf_record(char* filename, char* at) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (at == NULL) {
		JLW("at in jperf_record is NULL");
		at = "";
	}

#ifdef JPERF_ENABLE
	if (!jperf) {
		JLE("perf_record() failed");
		return -1;
	}
	// if (access(filename, F_OK) == -1)
	// 	perf_record_init(filename, header);
	FILE *out = fopen(filename, "a");
	fprintf(out, "%s %lu\n", at, jperf->time_start);
	fclose(out);
#endif

	return 0;
}

int jperf_adjust() {
	int i;
	unsigned long shift = 0;
	char *path = "/data/joseph/jperf_adjust";

#ifdef JPERF_ENABLE
	printf(">> adjusting time drift... (takes ~2 mins)\n");

	for (i = 0; i < 100; i++) {
		jperf_start();
			sleep(1);
		jperf_stop();
		jperf_write(path, "Job\tTaken", "Sleep:\t");
		shift += (jperf_time() - 1000000);
	}

	jperf_record_delete(path);
	printf("shift: %ld\n", shift);
	printf("avg shift: %ld\n", shift/100);

	FILE *out = fopen("/data/joseph/jperf_precision", "w");
	fprintf(out, "%ld", (shift/100));
	fclose(out);
#endif

	return 0;
}