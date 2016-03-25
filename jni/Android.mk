LOCAL_PATH:= $(call my-dir)
#===================================================
#Build libnativehelper section
include $(CLEAR_VARS)
LIB_NATIVEHELPER_PATH:= $(LOCAL_PATH)/libnativehelper
LOCAL_MODULE_TAGS := user
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := libnativehelper/JNIHelp.c		
LOCAL_C_INCLUDES := $(LIB_NATIVEHELPER_PATH)/include/nativehelper/ 
LOCAL_LDLIBS := -llog
LOCAL_MODULE := libnativehelper

include $(BUILD_STATIC_LIBRARY)

#===================================================
#Build libpapa section
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := user
LOCAL_ARM_MODE := arm

# This is the target being built.
LOCAL_MODULE := libdes3

# All of the source files that we will compile.
LOCAL_SRC_FILES := \
    main.cpp    \
    papa.cpp

LOCAL_SRC_FILES += \
    des3/des.cpp

# All of the shared libraries we link against.
LOCAL_SHARED_LIBRARIES := \
	libnativehelper

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/libnativehelper/include/ \
	$(LOCAL_PATH)/libnativehelper/include/nativehelper/ \
	$(LOCAL_PATH)/utils/ \
	$(LOCAL_PATH)/des3/ 

LOCAL_LDLIBS := -lz -llog
#LOCAL_LDLIBS := -lz -llog -L$(APP_PROJECT_PATH)/libs/$(TARGET_ARCH_ABI)/ -lnativehelper

#support android_support iconv.h
#LOCAL_WHOLE_STATIC_LIBRARIES += android_support

# Compiler flags.
LOCAL_CFLAGS += -O3 -fvisibility=hidden
#LOCAL_CFLAGS += -g

# Don't prelink this library.  For more efficient code, you may want
# to add this library to the prelink map and set this to true. However,
# it's difficult to do this for applications that are not supplied as
# part of a system image.

LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)


#$(call import-module, android/support)
