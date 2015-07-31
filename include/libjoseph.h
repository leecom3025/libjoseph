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
#include "joseph_perf.h"
#include "joseph_net.h"

#include <jni.h>

/* Code names */
#define hammerhead "hammerhead"
#define mako "mako"

#ifdef WITH_ZMQ
	#include <zmq.h>
#endif

#ifdef WITH_PERF
 	#include <linux/perf_event.h>
#endif

#ifdef WITH_CJSON
 	#include <cJSON.h>
#endif

#ifdef WITH_CURL
	#include <curl/curl.h>
#endif 
