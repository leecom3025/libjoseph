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

$(info Joseph said... "Building for $(TARGET_PRODUCT)")

commonsrc := \
	src/joseph_utils.c \
	src/joseph_perf.c \
	src/joseph_net.c

#------------------------------------------------------------------------------
# executable
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Config.mk
#LOCAL_MULTILIB := 32
LOCAL_MODULE := torhmonitor

ifeq ($(TARGET_PRODUCT), aosp_hammerhead)
	LOCAL_CFLAGS += -DPRODUCT="hammerhead"
	LOCAL_CFLAGS += -D_PRODUCT=1
else ifeq ($(TARGET_PRODUCT), cm_hammerhead)
	LOCAL_CFLAGS += -DPRODUCT="hammerhead"
	LOCAL_CFLAGS += -D_PRODUCT=1
else ifeq ($(TARGET_PRODUCT), full_mako)
	LOCAL_CFLAGS += -DPRODUCT="mako"
	LOCAL_CFLAGS += -D_PRODUCT=2
else ifeq ($(TARGET_PRODUCT), cm_mako)
	LOCAL_CFLAGS += -DPRODUCT="mako"
	LOCAL_CFLAGS += -D_PRODUCT=2
else ifeq ($(TARGET_PRODUCT), full_togari)
	LOCAL_CFLAGS += -DPRODUCT="togari"
	LOCAL_CFLAGS += -D_PRODUCT=3
else ifeq ($(TARGET_PRODUCT), cm_togari)
	LOCAL_CFLAGS += -DPRODUCT="togari"
	LOCAL_CFLAGS += -D_PRODUCT=3
else ifeq ($(TARGET_PRODUCT), full_hima)
	LOCAL_CFLAGS += -DPRODUCT="hima"
	LOCAL_CFLAGS += -D_PRODUCT=4
else ifeq ($(TARGET_PRODUCT), cm_hima)
	LOCAL_CFLAGS += -DPRODUCT="hima"
	LOCAL_CFLAGS += -D_PRODUCT=4
else ifeq ($(TARGET_PRODUCT), cm_himaul)
	LOCAL_CFLAGS += -DPRODUCT="hima"
	LOCAL_CFLAGS += -D_PRODUCT=4
endif

LOCAL_SRC_FILES := \
	$(commonsrc) \
	src/monitor.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += \
	liblog

LOCAL_CFLAGS += \
	-DANDROID=1 \
	-Wno-format-contains-nul

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

ifeq ($(QUITE), true)
	LOCAL_CFLAGS += -DQUITE=1
endif

ifeq ($(WITH_JPERF), true)
	LOCAL_CFLAGS += -DJPERF_ENABLE=1
endif

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

