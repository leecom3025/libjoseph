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
```C++
char *path;
if (Joseph_getPath("version", &path) < 0)
	perror(strerror(errno));
```

## Supported models
- Nexus 4 (mako)
- Nexus 5 (hammerhead)

## Disclaimer
You are welcome to use library as long as license is denoted. 

License is in LICENSE file. 