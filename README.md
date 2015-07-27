Joseph Library
===============================================================================
Joseph Library is a lightweight library to easily call system calls. 


## APIs
* joseph_utils
	- Joseph_getPath
		Usage:
		
		```
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