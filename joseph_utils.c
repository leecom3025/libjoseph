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

#include "joseph_utils.h"

#define DEFAULT_PATH "/data/joseph"

// This is for CPU temp, util, freq.
// /sys/class/thermal/thermal_zone5/temp
// /sys/devices/system/cpu/cpu0/cpufreq/cpu_utilization
// /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq

#ifdef PRODUCT
 static const char* CPU_TEMP     = "/sys/class/thermal/thermal_zone5/temp";
#else 
 static const char* CPU_TEMP     = "/sys/class/thermal/thermal_zone5/temp";
#endif 
static const char* CPU_ONLINE   = "/sys/devices/system/cpu/cpu%d/online";
static const char* CPU_UTIL     = "/sys/devices/system/cpu/cpu%d/cpufreq/cpu_utilization";
static const char* CPU_FREQ     = "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq";
static const int CPU_NUM = 4;


/*
 * Param: 
 *  (filename, pointer to char)
 * Usage:
 *  char *path;
 *  if (Joseph_getPath("version", &path) < 0)
 *    perror(strerror(errno));
 */
int Joseph_getPath(char *arg, char **result) {
  if (arg == NULL) {
    JLE("ERROR: %s", "arg is NULL");
    return -1;
  }

  int len = strlen(DEFAULT_PATH);
  if ((len += strlen(arg)) > 255) {
    JLE("ERROR: %s%d%s", "path is too long (",
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

/* Thermal read/write */
/*
 * Param: 
 *  (pointer to Int)
 * Usage:
 *  int temp;
 *  if (Joseph_readCPUTemp(&temp) < 0)
 *    perror(strerror(errno));
 */
int Joseph_readCPU_temp(int *mTemp) {
  FILE *pFile;

  setpriority(PRIO_PROCESS, 0, -20);
  if ((pFile = fopen(CPU_TEMP, "r")) == NULL) { 
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }

  fscanf(pFile, "%d", mTemp);
  fclose(pFile);
  return 0;
}

int Joseph_readCPU_util(int cpu, int *mUtil) {
  return 0;
}

int Joseph_readCPU_freq(int cpu, int *mFreq) {
  return 0;
}