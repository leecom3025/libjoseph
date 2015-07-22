LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
	libjoseph.c \
	joseph_utils.c \
	joseph_perf.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)
	# external/curl/include \
	# external/zmq/zmq4.x/include \
	# external/libcjson

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	libc \
	liblog

LOCAL_CFLAGS += \
	-DJPERF_ENABLE=1 \
	-Wno-format-contains-nul

LOCAL_EXPORT_CFLAGS += \
	-DJPERF_ENABLE=1

LOCAL_MODULE := libjoseph
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := \
	libjoseph.c \
	joseph_utils.c \
	joseph_perf.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)
	# external/curl/include \
	# external/zmq/zmq4.x/include \
	# external/libcjson

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	libc \
	liblog
	# libzmq \
	# libcjson

LOCAL_CFLAGS += \
	-DJPERF_ENABLE=1 \
	-Wno-format-contains-nul

LOCAL_EXPORT_CFLAGS += \
	-DJPERF_ENABLE=1

LOCAL_MODULE := joseph
LOCAL_PRELINK_MODULE := false
include $(BUILD_EXECUTABLE)
