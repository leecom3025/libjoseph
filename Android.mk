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

$(info Joseph said... \"Building for $(TARGET_PRODUCT)\")

#------------------------------------------------------------------------------
# control variables
#------------------------------------------------------------------------------
#WITH_JPERF := true
#WITH_ZMQ := true
# WITH_PERF := true
#WITH_CJSON := true

#------------------------------------------------------------------------------
# shared library
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := libjoseph

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
endif

LOCAL_SRC_FILES := \
	joseph_utils.c \
	joseph_perf.c \
	joseph_net.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \
	system/core/include 
	# external/curl/include \

LOCAL_SHARED_LIBRARIES += \
	libcutils \
	libutils \
	libc \
	liblog

LOCAL_CFLAGS += \
	-DANDROID=1 \
	-Wno-format-contains-nul \
	-DDEVICE_ANDROID=1

$(info $(TARGET_ARCH) == $(HOST_ARCH) for device?)

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

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

include $(BUILD_SHARED_LIBRARY)

#------------------------------------------------------------------------------
# shared library
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := libjoseph

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
endif

LOCAL_SRC_FILES := \
	joseph_utils.c \
	joseph_perf.c \
	joseph_net.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include
	# external/curl/include \

LOCAL_STATIC_LIBRARIES += \
	libcutils \
	libutils \
	liblog

LOCAL_CFLAGS += \
	-DANDROID=1 \
	-Wno-format-contains-nul \
	-DHOST_ANDROID=1

$(info $(TARGET_ARCH) == $(HOST_ARCH))

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

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

include $(BUILD_HOST_SHARED_LIBRARY)

#------------------------------------------------------------------------------
# static library
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := stljoseph

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
endif

LOCAL_SRC_FILES := \
	joseph_utils.c \
	joseph_perf.c \
	joseph_net.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += \
	libcutils

LOCAL_STATIC_LIBRARIES += \
	libutils \
	libc \
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

include $(BUILD_STATIC_LIBRARY)

#------------------------------------------------------------------------------
# host-static library
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := stljoseph

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
endif

LOCAL_SRC_FILES := \
	joseph_utils.c \
	joseph_perf.c \
	joseph_net.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \
	system/core/include

LOCAL_SHARED_LIBRARIES += \
	libcutils \
	libutils \
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

include $(BUILD_HOST_STATIC_LIBRARY)


#------------------------------------------------------------------------------
# executable
#------------------------------------------------------------------------------
include $(CLEAR_VARS)
LOCAL_MODULE := joseph

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
endif

LOCAL_SRC_FILES := \
	libjoseph.c \
	joseph_utils.c \
	joseph_perf.c \
	joseph_net.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES += \
	libcutils \
	libutils \
	liblog

LOCAL_CFLAGS += \
	-DANDROID=1 \
	-Wno-format-contains-nul

LOCAL_LDLIBS += \
	-llog \
	-ldl \
	-lstdc++ \
	-lpthread

LOCAL_MODULE_TAGS := optional
LOCAL_PRELINK_MODULE := false

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
