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

#define JPERF_ENABLE 1
// #define TERM
// #define JPERF_PRECISION 100 /* adjust time to write */

#ifdef TERM 
	#define TEMRS_OF_POLICY \
	"/*\n"\
	" * Copyright (C) 2015 HyunJong Joseph Lee, Korvo, CERCS,\n"\
	" *	\tGeorgia Institute of Technology\n"\
	" *\n"\
	" * Unless required by applicable law or agreed to in writing, software\n"\
	" * distributed under the License is distributed on an \"AS IS\" BASIS,\n"\
	" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"\
	" * See the License for the specific language governing permissions and\n"\
	" * limitations under the License.\n"\
	" */\n\n"
#else
	#define TEMRS_OF_POLICY \
	""
#endif

// usage 
// jperf_start() 
// 		... do some work
// jperf_stop()
// jperf_write(path, header, pattern)
// jperf_time() 	

typedef struct timeMeasure {
	unsigned long time_start;
	unsigned long time_end;
	unsigned long time_took;
} timeMeasure;

static struct timeMeasure *jperf;

#ifdef __cplusplus
extern "C" {
#endif
	void jperf_usage();

	unsigned long getmicro();
	void jperf_start();
	void jperf_stop();
	unsigned long jperf_time();

	int jperf_record_init(char *filename, char *header);
	int jperf_record_delete(char *filename);
	int jperf_write(char *filename, char *header, char *pattern);
	int jperf_record(char *filename, char *at);

	int jperf_adjust();

#ifdef __cplusplus
}
#endif

