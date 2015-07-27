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

/* include */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "joseph_common.h"

#ifdef __cplusplus
extern "C" {
#endif

	int Joseph_getPath(char* arg, char** result);

	int Joseph_getInt(char *arg, int *data);
	int Joseph_getString(char *arg, char **result);
	int Joseph_getDouble(char *arg, double *data);
	int Joseph_getFloat(char *arg, float *data);

	int Joseph_setInt(char *arg, int value);
	int Joseph_setString(char *arg, char *value);
	int Joseph_setDouble(char *arg, double value);
	int Joseph_setFloat(char *arg, float data);

	int Joseph_appendString(char *arg, char **value);
	int Joseph_resetFile(char *arg);

	/* Thermal read/write */
	static const int CPU_NUM = 4;

	int Joseph_readCPU_temp(int *mTemp);
	int Joseph_readCPU_util(int cpu, int *mUtil);
	int Joseph_readCPU_allutils(int **mUtil, int *online);
	int Joseph_readCPU_freq(int cpu, int *mFreq);
	int Joseph_readCPU_allfreqs(int **mFreq, int *online);
	int Joseph_readCPU_both(int **mUtil, int **mFreq, int *online);

	int Joseph_readCPU_allutils_free(int **mUtil);
	int Joseph_readCPU_allfreqs_free(int **mFreq);
	int Joseph_readCPU_both_free(int **mUtil, int **mFreq);


#ifdef __cplusplus
}
#endif
