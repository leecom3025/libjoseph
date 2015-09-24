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
  #include "../include/joseph_utils.h"
#else 
  #include "joseph_utils.h"
#endif

#if defined ANDROID
static const char* CPU_ONLINE
  = "/sys/devices/system/cpu/cpu%d/online";
static const char* CPU_UTIL
  = "/sys/devices/system/cpu/cpu%d/cpufreq/cpu_utilization";
static const char* CPU_FREQ
  = "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq";
#elif defined X86
  #warning TODO: finish x86 CPU monitor support
#endif 

#if defined ANDROID && defined PRODUCT
static const char *CPU_TEMP 
  = "/sys/class/thermal/thermal_zone%d/temp";
#elif defined ANDROID
static const char *CPU_TEMP
  = "/sys/class/thermal/thermal_zone%d/temp";
#elif defined X86
  #warning TODO:finish x86 thermal monitor support
#endif 


#if defined HOST_ANDROID
  #define TORH_ANDROID 1
#endif
/*
 * Param: 
 *  (filename, pointer to char)
 * Usage:
 *  char *path;
 *  if (Joseph_getPath("version", &path) < 0)
 *    perror(strerror(errno));
 */
int Joseph_getPath(char *arg, char **result) {
#if defined HOST_ANDROID
  return 0;
#endif
  if (arg == NULL) {
    JLE("ERROR: %s", "arg is NULL");
    return -1;
  }

  int len = strlen(DEFAULT_PATH);
  if ((len += strlen(arg)) > 255) {
    JLE("ERROR: %s%zu%s", "path is too long (",
     strlen(arg), ")");
    return -1;
  }

  *result = (char*) malloc(len);
  sprintf(*result, "%s/%s", DEFAULT_PATH, arg);
  return 0;
}

/*
 * Param: 
 * 	(filename, pointer to Int)
 * Usage:
 * 	int data;
 * 	if (Joseph_getInt("version", &data) < 0)
 *		perror(strerror(errno));
 */
int Joseph_getInt(char *arg, int *data) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "r");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  int size;
  size = fscanf(fd, "%d", data);
  fclose(fd);
  return 0;
}

int Joseph_getString(char *arg, char **result) {
#if defined HOST_ANDROID
  return 0;
#endif
  int fd;
  char *path;
  char mTemp[256];
  memset(mTemp, 0, sizeof(mTemp));

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = open(path, O_RDWR);
  if (fd < 0) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  read(fd, &mTemp, sizeof(mTemp));
  close(fd);

  *result = (char*) malloc(strlen(mTemp));

  strcpy(*result, mTemp);
  return 0;
}

int Joseph_getDouble(char *arg, double *data){
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "r");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }  

  int size;
  size = fscanf(fd, "%lf", data);
  fclose(fd);
  return 0;
}

int Joseph_getFloat(char *arg, float *data){
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "r");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }  

  int size;
  size = fscanf(fd, "%f", data);
  fclose(fd);
  return 0;
}

int Joseph_setInt(char *arg, int value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "w+");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fprintf(fd, "%d", value);
  fclose(fd);
  return 0;
}

int Joseph_setString(char *arg, char *value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "w+");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fprintf(fd, "%s", value);
  fclose(fd);
  return 0;
}

int Joseph_setDouble(char *arg, double value) {
#if defined HOST_ANDROID
  return 0;
#endif
	FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

	fd = fopen(path, "w+");
	if (fd == NULL) {
		JLE("ERROR: %s", strerror(errno));
		return -1;
	}   
	fprintf(fd, "%lf", value);
	fclose(fd);
	return 0;
}

int Joseph_setFloat(char *arg, float value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "w+");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }   
  fprintf(fd, "%f", value);
  fclose(fd);
  return 0;
}

int Joseph_appendString(char *arg, char **value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "a+");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fprintf(fd, "%s", *value);
  fclose(fd);
  return 0;
}

int Joseph_resetFile(char *arg) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (Joseph_getPath(arg, &path) < 0)
    return -1;

  fd = fopen(path, "w+");
  if (fd == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fprintf(fd, "\0");
  fclose(fd);
  return 0;
}

/* Thermal unit supported for Android only currently */
#if defined ANDROID 

int Joseph_CPU_init(struct jcpu **c, int id) {
	struct jcpu *cpu;
	cpu = (struct jcpu *) malloc(sizeof(jcpu));
	if (cpu == NULL) 
		return -1;

done:
	printf("init for %d: %08x\n", id, (unsigned int) cpu);
	cpu->id = id;
	cpu->temp = 0;
	cpu->util = 0;
	cpu->freq = 0;
	*c = cpu;
	return 0;
}

int Joseph_CPU_ops(struct jcpu ***cpu) {
	int i;
	struct jcpu **tCpu;
	size_t len = sizeof(struct jcpu*);

	tCpu = (struct jcpu *) malloc(len * CPU_NUM);
	
	for (i = 0; i < CPU_NUM; i++) {
		struct jcpu *holder;
		holder = tCpu[i];
		Joseph_CPU_init(&holder, i);
		tCpu[i] = holder;
	}
	
	*cpu = tCpu;
	return 0;
}

int Joseph_CPU_read(struct jcpu **cpu) {
	int i;	
	size_t len = sizeof(struct jcpu*);

	for (i = 0; i < CPU_NUM; i++){
		struct jcpu *holder;
		holder = cpu[i]; 
		Joseph_All_read(holder); 
	}

	return 0;
}

int Joseph_CPU_online(struct jcpu *cpu) {
	FILE *pFile;
	char *mFileName;
	int mOnline = 0;
	
	mFileName = (char*) malloc(strlen(CPU_FREQ) + sizeof(int));
	sprintf(mFileName, CPU_ONLINE, cpu->id);
	if ((pFile = fopen(mFileName, "r")) == NULL) {
		JLE("ERROR: %s", strerror(errno));
		return -1;
	}
	fscanf(pFile, "%d", &mOnline);
	fclose(pFile);

	if (mOnline != 1) {
		JLW("CPU %d is offline", cpu->id);
		goto done;
	}

done:
	cpu->online = mOnline;
	free(mFileName);
	return 0;
}

int Joseph_Thermal_read(struct jcpu *cpu) {
	FILE *pFile;
	char *mFileName;
	int cnum = CPU_OFFSET + cpu->id;

	mFileName = (char*) malloc(strlen(CPU_TEMP) + sizeof(int32_t));
	sprintf(mFileName, CPU_TEMP, cnum);

	setpriority(PRIO_PROCESS, 0, -20);
	if ((pFile = fopen(mFileName, "r")) == NULL) {
		JLE("ERROR: %s", strerror(errno));
		return -1;
	}
	
	fscanf(pFile, "%d", &(cpu->temp));
	setpriority(PRIO_PROCESS, 0, 0);
	fclose(pFile);
	free(mFileName);
	
	return 0;
}

int Joseph_Util_read(struct jcpu *cpu) {
	FILE *pFile = NULL;
	char *mFileName = NULL;
	int mUtil = 0;

	if (cpu->online != 1) {
		goto done;
	} else {
		mFileName = (char*) malloc(strlen(CPU_UTIL)+ sizeof(int));
		sprintf(mFileName, CPU_UTIL, cpu->id);

		setpriority(PRIO_PROCESS, 0, -20);
		if ((pFile = fopen(mFileName, "r")) == NULL) {
			JLE("ERROR: %s", strerror(errno));
			free(mFileName);
			return -1; 
		}
		fscanf(pFile, "%d", &mUtil);
		setpriority(PRIO_PROCESS, 0, 0);

		fclose(pFile);
		free(mFileName);
	}

done:
	cpu->util = mUtil;
	return 0;
}

int Joseph_Freq_read(struct jcpu *cpu) {
	FILE *pFile = NULL;
	char *mFileName = NULL;
	int mFreq = 0;

	if (cpu->online != 1) {
		goto done;
	} else {
		mFileName = (char*) malloc(strlen(CPU_FREQ)+ sizeof(int));
		sprintf(mFileName, CPU_FREQ, cpu->id);

		setpriority(PRIO_PROCESS, 0, -20);
		if ((pFile = fopen(mFileName, "r")) == NULL) {
			JLE("ERROR: %s", strerror(errno));
			free(mFileName);
			return -1; 
		}
		fscanf(pFile, "%d", &mFreq);
		setpriority(PRIO_PROCESS, 0, 0);
		
		fclose(pFile);
		free(mFileName);
	}

done:
	cpu->freq = mFreq;
	return 0;
}

int Joseph_UtilFreq_read(struct jcpu *cpu) {
	if (Joseph_CPU_online(cpu) == -1) {
		cpu->online = -1;
		return -1;
	}

	if (Joseph_Util_read(cpu) == -1) {
		cpu->util = -1;
		return -1;
	}

	if (Joseph_Freq_read(cpu) == -1) {
		cpu->freq = -1;
		return -1;
	}

	return 0;
}

int Joseph_All_read(struct jcpu *cpu) {
	int result = 0;
	result = Joseph_Thermal_read(cpu);
	result = Joseph_UtilFreq_read(cpu);

	return result == 0 ? 0 : -1;
}

#endif // ANDROID
