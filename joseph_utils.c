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
  #include "include/joseph_utils.h"
#else 
  #include "joseph_utils.h"
#endif

// This is for CPU temp, util, freq.
// /sys/class/thermal/thermal_zone5/temp
// /sys/devices/system/cpu/cpu0/cpufreq/cpu_utilization
// /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq

#if defined ANDROID && defined PRODUCT
 static const char* CPU_TEMP     = "/sys/class/thermal/thermal_zone5/temp";
#elif defined ANDROID
static const char* CPU_TEMP     = "/sys/class/thermal/thermal_zone5/temp";
static const char* CPU_ONLINE   = "/sys/devices/system/cpu/cpu%d/online";
static const char* CPU_UTIL     = "/sys/devices/system/cpu/cpu%d/cpufreq/cpu_utilization";
static const char* CPU_FREQ     = "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq";
#elif defined X86
  #warning TODO:finish x86 thermal monitor support
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

#ifdef ANDROID /* Thermal unit supported for Android only currently */
/* Thermal read/write */
/*
 * Param: 
 *  (pointer to Int)
 * Usage:
 *  int temp;
 *  if (Joseph_readCPU_temp(&temp) < 0)
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
  FILE *pFile;
  char *mFileName;
  int mOnline = 0;

  mFileName = (char*) malloc(strlen(CPU_FREQ) + sizeof(int));
  sprintf(mFileName, CPU_ONLINE, cpu);
  if ((pFile = fopen(mFileName, "r")) == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fscanf(pFile, "%d", &mOnline);
  fclose(pFile);

  if (mOnline != 1) {
    JLW("CPU %d is offline", cpu);
    return -1;
  }

  sprintf(mFileName, CPU_UTIL, cpu);
  if ((pFile = fopen(mFileName, "r")) == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }
  fscanf(pFile, "%d", mUtil);
  fclose(pFile);
  free(mFileName);

  return 0;
}

int Joseph_readCPU_freq(int cpu, int *mFreq) {
  FILE *pFile;
  char *mFileName;
  int mOnline = 0;

  mFileName = (char*) malloc(strlen(CPU_FREQ) + sizeof(int));
  sprintf(mFileName, CPU_ONLINE, cpu);
  if ((pFile = fopen(mFileName, "r")) == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }

  fscanf(pFile, "%d", &mOnline);
  fclose(pFile);

  if (mOnline != 1) {
    JLW("CPU %d is offline", cpu);
    return -1;
  }

  sprintf(mFileName, CPU_FREQ, cpu);
  if ((pFile = fopen(mFileName, "r")) == NULL) {
    JLE("ERROR: %s", strerror(errno));
    return -1;
  }

  fscanf(pFile, "%d", mFreq);
  fclose(pFile);
  free(mFileName);

  return 0;
}

/*
 * Param: 
 *  (pointer to pointer to Int arr, pointer to Int)
 * Usage:
 *  int *utils;
 *  int online;
 *  Joseph_readCPU_allutils(&utils, &online);
 *  for (int i = 0; i < online; i++) 
 *    printf("%d ", *(utils + i));
 *  Joseph_readCPU_allutils_free(&utils); // make sure to free
 */
int Joseph_readCPU_allutils(int **mUtil, int *online) {
  int (*tUtil)[CPU_NUM];
  int i;

  *online = 0;
  tUtil = malloc(sizeof(int32_t) * CPU_NUM);

  for (i = 0; i < CPU_NUM; i++) {
    if (Joseph_readCPU_util(i, &((*tUtil)[i])) > - 1) {
      (*(online))++;
      // printf("CPU %d: %d\n", i, (*tUtil)[i]);
    }
  } 

  *mUtil = *tUtil;
  return 0;
}

int Joseph_readCPU_allutils_free(int **mUtil) {
  free(*mUtil);
  return 0;
}

int Joseph_readCPU_allfreqs(int **mFreq, int *online) {
  int (*tFreq)[CPU_NUM];
  int i;

  *online = 0;
  tFreq = malloc(sizeof(int32_t) * CPU_NUM);

  for (i = 0; i < CPU_NUM; i++) {
    // #if DONTREAD
    //   Joseph_readCPU_freq(i, &((*tFreq)[i]));
    // #else
      if(Joseph_readCPU_freq(i, &((*tFreq)[i])) > -1) {
          (*(online))++;
      }
    // #endif
  }
  *mFreq = *tFreq;
  return 0;
}

int Joseph_readCPU_allfreqs_free(int **mFreq) {
  free(mFreq);
  return 0;
}

int Joseph_readCPU_both(int **mUtil, int **mFreq, int *online) {
  Joseph_readCPU_allutils(mUtil, online);
  Joseph_readCPU_allfreqs(mFreq, online);

  return 0;
}

int Joseph_readCPU_both_free(int **mUtil, int **mFreq) {
  Joseph_readCPU_allutils_free(mUtil);
  Joseph_readCPU_allfreqs_free(mFreq);
  return 0;
}
#endif // ANDROID
