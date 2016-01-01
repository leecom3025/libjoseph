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
static const char* CPU_TIME
  = "/sys/devices/system/cpu/cpufreq/stats/cpu%d/time_in_state";
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
 *  if (libj_getPath("version", &path) < 0)
 *    perror(strerror(errno));
 *  print("path is %s", path); // path is /tmp/joseph/version
 */
int libj_getPath(char *arg, char **result) {
#if defined HOST_ANDROID
  return 0;
#endif
  if (arg == NULL) {
    JLE("ERROR: %s", "arg is NULL");
    return -1;
  }

  int len = strlen(DEFAULT_PATH);
  if ((len += strlen(arg)) > 255) {
    JLE("ERROR: %s%zu%s", "path is too long (", strlen(arg), ")");
    return -1;
  }

  *result = (char*) malloc(len);
  sprintf(*result, "%s/%s", DEFAULT_PATH, arg);
  return 0;
}


// set default path
int libj_setDPath(char *arg){
  return 0;
}

/*
 * Param: 
 * 	(filename, pointer to Int)
 * Usage:
 * 	int data;
 * 	if (libj_getInt("version", &data) < 0)
 *		perror(strerror(errno));
 */
int libj_getInt(char *arg, int *data) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_getString(char *arg, char **result) {
#if defined HOST_ANDROID
  return 0;
#endif
  int fd;
  char *path;
  char mTemp[256];
  memset(mTemp, 0, sizeof(mTemp));

  if (libj_getPath(arg, &path) < 0)
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

int libj_getDouble(char *arg, double *data){
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_getFloat(char *arg, float *data){
#if defined HOST_ANDROID
  return 0;
#endif
  FILE *fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_setInt(char *arg, int value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_setString(char *arg, char *value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_setDouble(char *arg, double value) {
#if defined HOST_ANDROID
  return 0;
#endif
	FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_setFloat(char *arg, float value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_appendString(char *arg, char **value) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_resetFile(char *arg) {
#if defined HOST_ANDROID
  return 0;
#endif
  FILE* fd;
  char *path;

  if (libj_getPath(arg, &path) < 0)
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

int libj_CPU_init(struct jcpu **c, int id) {
  char *fileName;
  struct jcpu *cpu;
	cpu = (struct jcpu *) malloc(sizeof(jcpu));
	if (cpu == NULL) 
		return -1;

done:
	printf("init for %d at %08x\n", id, cpu);
	cpu->id = id;
	cpu->temp = 0;
	cpu->util = 0;
	cpu->freq = 0;
#if _PRODUCT == _hima
  int i;
  for (i = 0; i < FREQ_LEVEL; i++) {
    cpu->freq_a[i].seq = i;
//    printf ("assigned %d\n", cpu->freq_a[i].seq);
  }
  fileName = (char*) malloc(strlen(CPU_TIME) + sizeof(int32_t));
  if (fileName == NULL)
    return -1;
  sprintf(fileName, CPU_TIME, cpu->id);
  cpu->stat_path = fileName;
  libj_Freq_stat_init(cpu);
#endif
  *c = cpu;
	return 0;
}

int libj_CPU_ops(struct jcpu ***cpu) {
  int i;
	struct jcpu **tCpu;
	ssize_t len = sizeof(struct jcpu*);

	tCpu = (struct jcpu **) malloc(len * CPU_NUM);
	
	for (i = 0; i < CPU_NUM; i++) {
		struct jcpu *holder;
    holder = tCpu[i];
		libj_CPU_init(&holder, i);
		tCpu[i] = holder;
	}
	*cpu = tCpu;
	return 0;
}

int libj_CPU_read(struct jcpu **cpu) {
	int i;
  size_t len = sizeof(struct jcpu*);

	for (i = 0; i < CPU_NUM; i++){
		struct jcpu *holder;
		holder = cpu[i];
		libj_All_read(holder);
	}

	return 0;
}

int libj_CPU_online(struct jcpu *cpu) {
	FILE *pFile;
	char *mFileName;
	ssize_t mOnline = 0;
	
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

int libj_Thermal_read(struct jcpu *cpu) {
	FILE *pFile;
	char *mFileName;
	ssize_t cnum = CPU_OFFSET + cpu->id;

#if _PRODUCT == _hima
  if (cpu->id > 4) 
    cnum += 2;
#endif

	mFileName = (char*) malloc(strlen(CPU_TEMP) + sizeof(uint32_t));
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

int libj_Util_read(struct jcpu *cpu) {
#if _PRODUCT == _hima
  int result = 0;

  setpriority(PRIO_PROCESS, 0, -20);
  result = libj_Freq_stat(cpu);
  setpriority(PRIO_PROCESS, 0, 0);

  return result;
#endif
	FILE *pFile = NULL;
	char *mFileName = NULL;
	int32_t mUtil = 0;

	if (cpu->online != 1) {
		goto done;
	} else {
		mFileName = (char*) malloc(strlen(CPU_UTIL)+ sizeof(uint32_t));
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

int libj_Freq_read(struct jcpu *cpu) {
	FILE *pFile = NULL;
	char *mFileName = NULL;
	int32_t mFreq = 0;

	if (cpu->online != 1) {
		goto done;
	} else {
		mFileName = (char*) malloc(strlen(CPU_FREQ)+ sizeof(uint32_t));
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

int libj_Freq_stat_get(struct freq_str *freq){
  return 0;
}

int libj_Freq_stat_init(struct jcpu *cpu){
  FILE *fp;
  char *fileName, *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0 ;

  fp = fopen(cpu->stat_path, "r");
  while ((read = getline(&line, &len, fp)) != -1) {
    int id, time;
    ssize_t last;
    sscanf(line, "%d %d\n", &id, &time);
    cpu->freq_a[i].id = id;
    cpu->freq_a[i].last = time;
    cpu->freq_a[i].time = time;
    i++;
  }

  cpu->max_freq = cpu->freq_a[i-1].id;

  fclose(fp);
  return 0; 
}

int libj_Freq_stat_read(struct jcpu *cpu){
  FILE *fp;
  char *fileName, *line = NULL;
  size_t len = 0;
  ssize_t read;
  int i = 0;
  double total_time = 0;
  double total_freq = 0;

  fp = fopen(cpu->stat_path, "r");

  while ((read = getline(&line, &len, fp)) != -1) {
    int32_t id, time, diff;
    ssize_t last;

    sscanf(line, "%d %d\n", &id, &time);
    last = cpu->freq_a[i].last;
    
    if (last != time) { 
      diff = time - last;
      total_time += diff;
      total_freq += (id * diff);
//      printf("%f: %f [max: %d]\n", id, diff, cpu->max_freq);
    }

    cpu->freq_a[i].last = cpu->freq_a[i].time;
    cpu->freq_a[i].time = time;
    i++;
  }

  double potential = (((double)cpu->max_freq) * total_time);
  double d_util = (total_freq / potential) * 100;
  cpu->util = (int32_t)d_util;
//  printf ("%d util: %d\n", cpu->id, cpu->util);

  fclose(fp);
  return 0; 
}

int libj_Freq_stat(struct jcpu *cpu) 
{
#if _PRODUCT != _hima
  return -1;
#endif
//  printf("Reading cpu %d:\n", cpu->id); 
  libj_Freq_stat_read(cpu);

  return 0; 
}

int libj_UtilFreq_read(struct jcpu *cpu) {
	if (libj_CPU_online(cpu) == -1) {
		cpu->online = -1;
		return -1;
	}

/*	if (libj_Util_read(cpu) == -1) {
		cpu->util = -1;
	}
*/
	if (libj_Freq_read(cpu) == -1) {
		cpu->freq = -1;
	}

	return 0;
}

int libj_All_read(struct jcpu *cpu) {
	ssize_t result = 0;
	result = libj_Thermal_read(cpu);
	result = libj_UtilFreq_read(cpu);

	return result == 0 ? 0 : -1;
}

#endif // ANDROID
