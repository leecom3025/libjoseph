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
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>

#include "joseph_common.h"
#include "joseph_struct.h"

#ifdef __cplusplus
extern "C" {
#endif
  
	int libj_getPath(char* arg, char** result);

	int libj_getInt(char *arg, int *data);
	int libj_getString(char *arg, char **result);
	int libj_getDouble(char *arg, double *data);
	int libj_getFloat(char *arg, float *data);

	int libj_setInt(char *arg, int value);
	int libj_setString(char *arg, char *value);
	int libj_setDouble(char *arg, double value);
	int libj_setFloat(char *arg, float data);

	int libj_appendString(char *arg, char **value);
	int libj_resetFile(char *arg);
  static int bool_DPath = J_false;
  static char *char_DPath;

	/* 
	(CPU_OFFSET | CPU)
	
	Nexus 5: (6 | cpu) 
		thermal_zone6 	- cpu0 
		thermal_zone7 	- cpu1
		thermal_zone8 	- cpu2
		thermal_zone9 	- cpu3
	Nexus 4: (7 | cpu)
		thermal_zone7 	- cpu0
		thermal_zone8 	- cpu1
		thermal_zone9 	- cpu2
		thermal_zone10 	- cpu3
	Togari: (5 | cpu)
		thermal_zone5 	- cpu0 
		thermal_zone6 	- cpu1
		thermal_zone7 	- cpu2
		thermal_zone8 	- cpu3
	*/
	#ifdef ANDROID /* Thermal unit supported for Android only currently */
		#if _PRODUCT == _hammerhead
			#define CPU_OFFSET 5
			#define _CPU_NUM 4
		#elif _PRODUCT == _mako
			#define CPU_OFFSET 7
			#define _CPU_NUM 4
		#elif _PRODUCT == _togari
			#define CPU_OFFSET 5
			#define _CPU_NUM 4
		#elif _PRODUCT == _hima
    /* zone 12-13 --> sth else 
     * 0, 1, 2, 3,  4,  5,  6,  7
     * 7, 8, 9, 10, 11, 14, 15, 16 
     */
			#define CPU_OFFSET 7
			#define _CPU_NUM 8
		#else
			#define CPU_OFFSET 0
			#define _CPU_NUM 1
		#endif 
	
	/* Thermal read/write */
	static const ssize_t CPU_NUM = _CPU_NUM;

//	int libj_CPU_init(struct jcpu *, int);
	extern int libj_CPU_ops(struct jcpu ***);
	extern int libj_CPU_read(struct jcpu **);
	int libj_CPU_online(struct jcpu *);
	extern int libj_Thermal_read(struct jcpu *);
	extern int libj_Util_read(struct jcpu *);
	extern int libj_Freq_read(struct jcpu *);
  extern int libj_Freq_stat(struct jcpu *);
	extern int libj_UtilFreq_read(struct jcpu *);
	extern int libj_All_read(struct jcpu *);

	#endif // ANDROID

#ifdef __cplusplus
}
#endif

