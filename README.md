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
  - libj_perf_[pause,resume]
  - libj_perf_record_[init,delete]
  - libj_perf_[write,record]
  - libj_perf_adjust
  - libj_perf_usage
* joseph_net
  - libj_net_[init, prep, done]
  - libj_net_[send, recv]
  - libj_net_zmq_[...] not supported yet

## Examples
libj_utils:
```C++
char *model;
struct jcpu *cpu;
if (libj_getString("model", &model) < 0) //read "/data/joseph/model"
	perror(strerror(errno));
if (libj_CPU_ops(&cpu) < 0)
  perror (strerror(errno));
if (libj_CPU_read(&cpu) < 0) 
  perror (strerror(errno));
for (i = 0; i < CPU_NUM; i++) 
  printf("CPU %d temperature: %d ['C] frequency: %d\n", i, cpu[i]->temp, cpu[i]->freq);
```
libj_perf: 
```C++
libj_perf_adjust(); // adjust drift for high precision
libj_perf_start();
	// ... do some work
libj_perf_stop();
libj_perf_write("/tmp/joseph/jperf_data", "Job\tTime", "work:\t");
char *msg = libj_perf_time();
unsigned long msg_raw = libj_perf_time_raw();
JLD("%s [%ld]\n", msg, msg_raw); //print 
```
libj_net:
```C++
struct Jsocket *sck;
int i, role, port, msg_len;
role= JNET_SERVER;
port = 12345;
msg_len = 255;
if (libj_net_init(&sck, JNET_TCP) < 0) 
  JLE("libj_net_init error");
if (libj_net_prep(&sck, role, &port, NULL) < 0)
  JLE("libj_net_prep error");
char *msg;
if (libj_net_recv(&sck, &msg, msg_len) < 0) // blocking call
  JLE("libj_net_recv error");
for(i = 0; i < msg_len; i++) 
  *(msg+i) = (*msg) + 1; // shift
if (libj_net_send(&sck, &msg) < 0) // msg len detected by ending null
  JLE("libj_net_send error");
// do more works 
if (libj_net_done(&sck) < 0) // free mem and net associates 
  JLE("libj_net_done error"); 
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
