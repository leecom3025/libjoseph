#------------------------------------------------------------------------------
# Copyright (C) 2015 HyunJong Joseph Lee, Korvo, Georgia Tech
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#------------------------------------------------------------------------------
#==============================================================================
# Author(s): = "HyunJong Joseph Lee"
#==============================================================================

LOCAL_PATH:= $(call my-dir)

#------------------------------------------------------------------------------
# shared library
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := libjoseph

WITH_ZMQ := true
# WITH_PERF := true
WITH_CJSON := true

ifeq ($(TARGET_PRODUCT), aosp_hammerhead)
	LOCAL_CFLAGS += -DPRODUCT="hammerhead"
else ifeq ($(TARGET_PRODUCT), full_mako)
	LOCAL_CFLAGS += -DPRODUCT="mako"
endif

LOCAL_SRC_FILES := \
	libjoseph.c \
	joseph_utils.c \
	joseph_perf.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)
	# external/curl/include \

LOCAL_SHARED_LIBRARIES += \
	libcutils \
	libutils \
	libc \
	liblog

LOCAL_CFLAGS += \
	-DJPERF_ENABLE=1 \
	-Wno-format-contains-nul

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++

# LOCAL_EXPORT_CFLAGS += \
# 	-DJPERF_ENABLE=1

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

ifeq ($(WITH_ZMQ),true)
	LOCAL_CFLAGS += -DWITH_ZMQ
	LOCAL_C_INCLUDES += \
		external/zmq/zmq4.x/include
	LOCAL_STATIC_LIBRARIES += \
		stlzmq
	include external/stlport/libstlport.mk
endif

ifeq ($(WITH_PERF),true)
	LOCAL_CFLAGS += -DWITH_PERF
	LOCAL_C_INCLUDES += \
		external/linux-tools-perf/perf-3.12.0/include
	LOCAL_STATIC_LIBRARIES += \
		libperf
endif

ifeq ($(WITH_CJSON), true)
	LOCAL_CFLAGS += -DWITH_CJSON
	LOCAL_C_INCLUDES += \
		external/libcjson
	LOCAL_STATIC_LIBRARIES += \
		stlcjson
endif

include $(BUILD_SHARED_LIBRARY)

#------------------------------------------------------------------------------
# executable
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := joseph

WITH_JPERF := true
WITH_ZMQ := true
# WITH_PERF := true
WITH_CJSON := true

ifeq ($(TARGET_PRODUCT), aosp_hammerhead)
	LOCAL_CFLAGS += -DPRODUCT="hammerhead"
else ifeq ($(TARGET_PRODUCT), full_mako)
	LOCAL_CFLAGS += -DPRODUCT="mako"
endif

LOCAL_SRC_FILES := \
	libjoseph.c \
	joseph_utils.c \
	joseph_perf.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)
	# external/curl/include \

LOCAL_SHARED_LIBRARIES += \
	libcutils \
	libutils \
	libc \
	liblog

LOCAL_CFLAGS += \
	-DJPERF_ENABLE=1 \
	-Wno-format-contains-nul

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++

# LOCAL_EXPORT_CFLAGS += \
# 	-DJPERF_ENABLE=1

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

ifeq ($(WITH_ZMQ),true)
	LOCAL_CFLAGS += -DWITH_ZMQ
	LOCAL_C_INCLUDES += \
		external/zmq/zmq4.x/include
	LOCAL_STATIC_LIBRARIES += \
		stlzmq
	include external/stlport/libstlport.mk
endif

ifeq ($(WITH_PERF),true)
	LOCAL_CFLAGS += -DWITH_PERF
	LOCAL_C_INCLUDES += \
		external/linux-tools-perf/perf-3.12.0/include
	LOCAL_STATIC_LIBRARIES += \
		libperf
endif

ifeq ($(WITH_CJSON), true)
	LOCAL_CFLAGS += -DWITH_CJSON
	LOCAL_C_INCLUDES += \
		external/libcjson
	LOCAL_STATIC_LIBRARIES += \
		stlcjson
endif

include $(BUILD_EXECUTABLE)
