/*
 * Copyright (C) 2015 HyunJong Joseph Lee
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

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#ifdef TERM 
	#define TEMRS_OF_POLICY \
	"/*\n"\
	" * Copyright (C) 2015 HyunJong Joseph Lee, CERCS,\n"\
	" *	\tGeorgia Institute of Technology\n"\
	" *\n"\
	" * Unless required by applicable law or agreed to in writing, \n"\
  " * software distributed under the License is distributed on an \n"\
  " * \"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY \n"\
  " * KIND, either express or implied. See the License for the \n"\
  " * specific language governing permissions and limitations \n"\
  " * under the License.\n"\
	" */\n\n"
#else
	#define TEMRS_OF_POLICY \
	""
#endif

#define ToP TEMRS_OF_POLICY
#define J_false   0
#define J_true    1

#ifdef ANDROID
  #include <cutils/properties.h>
  #include <android/log.h>
  #include <utils/Log.h>
  #include <errno.h>
#else
  #include <errno.h>
  #include <stdio.h>
  #include <stdint.h>
#endif

/* define  */
#ifdef ANDROID
 	#define DEFAULT_PATH "/data/joseph"
 	#define JLOG(x, ...) \
 	{\
 		(printf("%s: ", x)); \
 		(printf(__VA_ARGS__)); \
 		(printf("\n")); \
 	} //
	#define JLD(...) \
 	{ \
 		((void)ALOG(LOG_DEBUG, "libJoseph", __VA_ARGS__)); \
  		JLOG("Debug", __VA_ARGS__); \
  } //
#ifdef QUITE
	#define JLE(...){}
#else
	#define JLE(...) \
	{ \
  		((void)ALOG(LOG_ERROR, "libJoseph", __VA_ARGS__)); \
  		JLOG("Error", __VA_ARGS__); \
  } //
#endif
#ifdef QUITE
	#define JLW(...) {}
#else
	#define JLW(...) \
	{ \
  		((void)ALOG(LOG_WARN, "libJoseph", __VA_ARGS__)); \
  		JLOG("Warming", __VA_ARGS__); \
  } //
#endif
  #define JFD(...) \
  { \
 		((void)ALOG(LOG_DEBUG, "libjoseph", "(%s) %s\n", \
 			__FUNCTION__, __VA_ARGS__ )); \
 		(printf("FuncDebug(%s): ", __FUNCTION__); \
 		(printf(__VA_ARGS__)); \
 		(printf("\n")); \
 	} //
 	#define JLT(...) \
 	{ \
 		((void)ALOG(LOG_DEBUG, "libjoseph_test", __VA_ARGS__)); \
 		JLOG(">>> Test", __VA_ARGS__); \
 	} //

  /* _PRODUCT is internal model number, must be equal to one in Android.mk */
  #define _hammerhead 1
  #define _mako 2
  #define _togari 3
  #define _hima 4

#else
	#define DEFAULT_PATH "/tmp/joseph"
 	#define JLD(...) \
  { \
     (printf(__VA_ARGS__)); \
     (printf("\n")); \
  } //
 	#define JLE(...) \
  { \
     (printf(__VA_ARGS__)); \
     (printf("\n")); \
  } //
  #define JLW(...) \
  { \
     (printf(__VA_ARGS__)); \
     (printf("\n")); \
  } //
  #define JLD(...) \
  { \
     (printf(__VA_ARGS__)); \
     (printf("\n")); \
  } //
  #define JLT(...) \
  { \
     (printf(__VA_ARGS__)); \
     (printf("\n")); \
  } //
#endif
