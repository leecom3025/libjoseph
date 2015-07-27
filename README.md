Joseph Library
===============================================================================
Joseph Library is a lightweight library to easily call system calls. 


## APIs
* joseph_utils
	- Joseph_get[Path,Int,String,Double,Float]
	- Joseph_set[Int,String,Double,Float]
	- Joseph_appendString
	- Joseph_resetFile
	- Joseph_readCPU_temp
	- Joseph_readCPU_util
	- Joseph_readCPU_freq
* joseph_perf
	- jperf_[start,stop,time]
	- jperf_record_[init,delete]
	- jperf_[write,record]
	- jperf_adjust
	- jperf_usage

## Examples
Joseph_getString:
```C++
char *model;
if (Joseph_getString("model", &model) < 0) //read "/data/joseph/model"
	perror(strerror(errno));
```
jperf: 
```C++
jperf_adjust(); // adjust drift for high precision
jperf_start();
	// ... do some work
jperf_stop();
jperf_write("/data/joseph/jperf_data", "Job\tTime", "work");
JLD("%ld\n", jperf_time()); // print
```


## Supported models
- Nexus 4 (mako)
- Nexus 5 (hammerhead)

## Disclaimer
You are welcome to use library as long as license is denoted. 

License is in LICENSE file. 