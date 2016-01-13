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

#ifdef X86
  #include "../include/joseph_perf.h"
#else
  #include "joseph_perf.h"
#endif

const char *puts_model = "Time taken: %lu micro-seconds";

void libj_perf_usage() {
#if !defined JPERF_ENABLE
	JLW("%s", "make sure to -DJPERF_ENABLE=1 in cmake_config\n");
	JLW("%s", "	or #define libj_perf_NEABLE 1 in jperf.h\n");

	printf("%s", "make sure to -DJPERF_ENABLE=1 in cmake_config\n");
	printf("%s", " or #define libj_perf_NEABLE 1 in jperf.h\n");
#endif
	JLW("%s", "libj_perf_start()\n\t... do some work\njperf_stop()\n");
	JLW("%s", "libj_perf_write(path, header, pattern)\n");
	JLW("%s", "libj_perf_record_initme() // if you want to check the time\n");
}

unsigned long libj_perf_getmicro() {
  struct timeval curTime;
  gettimeofday(&curTime, NULL);
  return curTime.tv_sec * (uint64_t) 1000000 + curTime.tv_usec;
}

void libj_perf_start() {
#ifdef JPERF_ENABLE
	unsigned long curr = libj_perf_getmicro();
	jperf = (struct timeMeasure*) malloc(sizeof(struct timeMeasure));
  NULL_CHECK(jperf);

	jperf->time_start = curr;
  jperf->time_end = curr;
  jperf->time_took = 0;
  jperf->state = RUNNING;
#endif
}

void libj_perf_stop() {
#ifdef JPERF_ENABLE
	unsigned long curr = libj_perf_getmicro();
  NULL_CHECK(jperf);
  if (jperf->state == RUNNING) {
    jperf->time_end = curr;
    jperf->time_took += jperf->time_end - jperf->time_start;
    jperf->state = STOP;
  }
#endif
}

void libj_perf_pause() {
#ifdef JPERF_ENABLE
  unsigned long curr = libj_perf_getmicro();
  NULL_CHECK(jperf);

  if (jperf->state == RUNNING) {
    jperf->time_end = curr;
    jperf->time_took += jperf->time_end - jperf->time_start;
    jperf->state = PAUSED; 
  }
#endif
}

void libj_perf_resume() {
#ifdef JPERF_ENABLE
  NULL_CHECK(jperf);
  if (jperf->state == PAUSED) {
    unsigned long curr = libj_perf_getmicro();
    jperf->time_start = curr;
    jperf->state = RUNNING;
    /* JLW("libj_perf paused"); */
  }
#endif
}

unsigned long libj_perf_time_raw() {
	unsigned long ret = 0;

#ifdef JPERF_ENABLE
	if (!jperf || jperf->time_start > jperf->time_end) {
		JLE("ERROR");
	}

#ifdef libj_perf_PUTS
	char* p = (char*)malloc(strlen(puts_model));
	sprintf(p, puts_model, jperf->time_took);
	puts (p);
	free(p);
#endif
	
	ret = jperf->time_took - drift;
  if (jperf->state == STOP || jperf->state == INVALID)
    free(jperf);
#endif

	return ret;
}

/*
 *  this one returns pointer to str 
 *  use libj_perf_time_raw() for ulong
 */
char *libj_perf_time() {
  char *ret;
  ret = (char*)malloc(sizeof(unsigned long));
  sprintf(ret, "%ld", libj_perf_time_raw());
  return ret;
}

/*
 * this one does not have to be called by dev 
 * called from *libj_perf_record_write* if not initialized
 */
int libj_perf_record_init(char* filename, char* header) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (header == NULL) {
		JLW("header in libj_perf_record_init is NULL");
		header = "";
	}

#ifdef JPERF_ENABLE
	if (!jperf) {
		JLE("libj_perf_record_init() failed [jperf is NULL]");
		return -1;
	}
  
  char *template, *buff;
#if defined TERM
  template = "%s%s\n====================\n";
#else 
  template = "%s\n===================\n";
#endif
  buff = (char*) malloc(strlen(header) + 
#if defined TERM
      strlen(ToP) +
#endif 
      strlen(template));

  sprintf(buff, template, 
#if defined TERM
      ToP, 
#endif 
      header);
  if (libj_appendString(filename, &buff) < -1) {
    JLE("%s failed [appendString failed]", __FUNCTION__);
    return -1;
  }
#endif
	return 0;
}

int libj_perf_record_delete(char* filename) {
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

int libj_perf_write(char *filename, char *header, char *pattern) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (header == NULL) {
		JLW("header in libj_perf_write is NULL");
		header = "";
	}

	if (pattern == NULL) {
		JLW("pattern in libj_perf_write is NULL");
		header = "";
	}

#ifdef JPERF_ENABLE
	if (!jperf) {
		JLE("perf_write() failed");
		return -1;
	}

  char *path, *template;
  if (libj_getPath(filename, &path) < 0) {
    JLE("libj_getPath errorrrrr");
    return -1;
  }
  
  if (access(path, F_OK) < 0) 
    libj_perf_record_init(filename, header);
  jperf->time_took -= drift;
  template = (char*) malloc(strlen(pattern) 
      + sizeof(jperf->time_took));
  sprintf(template, "%s%lu\n", pattern, jperf->time_took);

  if (libj_appendString(filename, &template) < 0) {
    JLE("appendString errorrrr");
    return -1;
  }
#endif
	return 0;
}

int libj_perf_record(char* filename, char* at) {
	if (filename == NULL) {
		JLE("filename is NULL");
		return -1;
	}

	if (at == NULL) {
		JLW("at in libj_perf_record is NULL");
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

int libj_perf_adjust() {

#if defined JPERF_ENABLE && defined ANDROID
	int i, j, k, iterate = 20;
	unsigned long shift = 0;
	double _shift = 0;
	char *path = "/data/joseph/libj_perf_adjust";
	const char *precision_path = "/data/joseph/libj_perf_precision";
	const int size = 3*1024*1024; // Allocate 3M. Set much larger then L2

	if (access(precision_path, F_OK) != -1) {
		FILE *out = fopen(precision_path, "r");
		fscanf(out, "%lf", &_shift);
		fclose(out);
	} else {
		printf(">> adjusting time drift... (takes ~4 mins)\n");

		for (i = 0; i < iterate; i++) {
			libj_perf_start();
				sleep(1);
			libj_perf_stop();
			libj_perf_write(path, "Job\tTaken", "Sleep:\t");
			shift += (libj_perf_time_raw() - 1000000);

			char *c = (char *) malloc(size); //cache flush
			for (k = 0; k < 0xff; k++)
				for (j = 0; j < size; j++)
					c[j] = k*j;
			free(c);

		}

		libj_perf_record_delete(path);
		_shift = (((double)shift) / iterate);

		FILE *out = fopen(precision_path, "w");
		fprintf(out, "%lf", _shift);
		fclose(out);
	}

	printf("shift: %ld\n", shift);
	printf("avg shift: %lf\n", _shift);
	drift = _shift;
#endif

	return 0;
}
