
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libaudio-defs
LOCAL_CATEGORY_PATH := libs
LOCAL_DESCRIPTION := Audio definitions library
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := -DADEF_API_EXPORTS -fvisibility=hidden -std=gnu11 -D_GNU_SOURCE
LOCAL_SRC_FILES := \
	src/adefs_formats.c \
	src/adefs_json.c \
	src/adefs.c

# Public API headers - top level headers first
# This header list is currently used to generate a python binding
LOCAL_EXPORT_CUSTOM_VARIABLES := LIBAUDIODEFS_HEADERS=$\
	$(LOCAL_PATH)/include/audio-defs/adefs.h;

LOCAL_PUBLIC_LIBRARIES :=

LOCAL_PRIVATE_LIBRARIES := \
	json \
	libulog

include $(BUILD_LIBRARY)


ifdef TARGET_TEST

include $(CLEAR_VARS)

LOCAL_MODULE := tst-libaudio-defs
LOCAL_LIBRARIES := \
	libcunit\
	libulog \
	libaudio-defs
LOCAL_CFLAGS := -std=gnu11
LOCAL_SRC_FILES := \
	tests/adefs_test.c \
	tests/adefs_test_format.c \
	tests/adefs_test_str.c

include $(BUILD_EXECUTABLE)

endif
