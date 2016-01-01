libJoseph
===============================================================================
libJoseph is a lightweight library to provide high-level abstraction of POSIX system calls. 
```git
git clone https://github.com/forkjoseph/libjoseph external/libjoseph
make
sudo make install
```

## APIs
The convention is "libj_[prefix]" expect util is "libj_[operation]"
* joseph_utils
	- libj_get[Path,Int,String,Double,Float]
	- libj_set[Int,String,Double,Float]
	- libj_appendString
	- libj_resetFile
	- libj_readCPU_temp
	- libj_readCPU_util
	- libj_readCPU_freq
* joseph_perf
	- libj_perf_[start,stop,time]
	- libj_perf_record_[init,delete]
	- libj_perf_[write,record]
	- libj_perf_adjust
	- libj_perf_usage

## Examples
libj_getString:
```C++
char *model;
if (libj_getString("model", &model) < 0) //read "/data/joseph/model"
	perror(strerror(errno));
```
jperf: 
```C++
libj_perf_adjust(); // adjust drift for high precision
libj_perf_start();
	// ... do some work
libj_perf_stop();
libj_perf_write("/data/joseph/jperf_data", "Job\tTime", "work:\t");
JLD("%ld\n", libj_perf_time()); // print
```
libj_readCPU_alltemps:
```C++
int *temperature;
if (libj_readCPU_alltemps(&temperature) < 0) 
  perror(strerror(errno));
for (i = 0; i < CPU_NUM; i++) 
  printf("CPU %d temperature: %d ['C]\n", i, *(temperature + i));
if (libj_readCPU_alltemps_free(&temperature) < 0) 
  perror(strerror(errno));
```

## Supported models
- Nexus 4 (mako)
- Nexus 5 (hammerhead)
- Ultra Z (togari)
- Galaxy S4 (i9500)
- One M9 (hami)
- TBD: Nexus 6, Nexus 5(2015), G4, G Flex2, Galaxy S3, x86 Generic

## Dependency
libJoseph depends on [ZeroMQ (v4.x)](https://github.com/zeromq/libzmq), [cJSON](https://github.com/kbranigan/cJSON).

If you want to fetch them with *Android porting*, do:
```shell
cd external/libjoseph
cd scripts
./fetch.sh [zmq, cjson]
```

## Disclaimer
You are welcome to use library as long as license is denoted. 

License is in LICENSE file. 
