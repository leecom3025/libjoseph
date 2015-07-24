LOCAL_PATH:= $(call my-dir)

#####################################################
# shared library
#####################################################
include $(CLEAR_VARS)
LOCAL_MODULE := libjoseph

WITH_ZMQ := true
# WITH_PERF := true
WITH_CJSON := true

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
	-lz \
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

#####################################################
# executable
#####################################################
include $(CLEAR_VARS)
LOCAL_MODULE := joseph

WITH_JPERF := true
WITH_ZMQ := true
# WITH_PERF := true
WITH_CJSON := true

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
	-lz \
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
