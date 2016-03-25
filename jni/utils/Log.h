#ifndef MY_LOG_MACRO_H 
#define MY_LOG_MACRO_H 
#include <android/log.h>
#include <stdio.h>

//#define DEBUG
#define TAG "PAPA"

#ifdef DEBUG
//redefinition des macros 
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, \
TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , \
TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , \
TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , \
TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , \
TAG, __VA_ARGS__)
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif


#endif  // MY_LOG_MACRO_H
