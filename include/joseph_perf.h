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

#include <linux/ioctl.h>
#define __force
#define __bitwise
#define __user
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "joseph_common.h"

// #define libj_perf_PRECISION 100 /* adjust time to write */

typedef struct timeMeasure {
	unsigned long time_start;
	unsigned long time_end;
	unsigned long time_took;
} timeMeasure;

static struct timeMeasure *jperf;
static double drift;

#ifdef __cplusplus
extern "C" {
#endif
	void libj_perf_usage();

	unsigned long libj_perf_getmicro();
	void libj_perf_start();
	void libj_perf_stop();
	unsigned long libj_perf_time_raw();
	char* libj_perf_time();

	int libj_perf_record_init(char *filename, char *header);
	int libj_perf_record_delete(char *filename);
	int libj_perf_write(char *filename, char *header, char *pattern);
	int libj_perf_record(char *filename, char *at);

	int libj_perf_adjust();

#ifdef __cplusplus
}
#endif

