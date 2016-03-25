//
// Created by xiet on 2016/2/29.
//

#include "utils/Log.h"
#include <nativehelper/JNIHelp.h>
#include <nativehelper/jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#include "des.h"

#define APP_PKG_NAME    "com/rhodes/a3des"

//密钥
#define SECRET_KEY      "BRkYiusbJQx7g4ZpL5iFKKgm"

int checkPadding(int *src,int len) {
	int ret_len;

	ret_len = 0;
	for (int i = 0; i < len; i++) {
		int dec = src[i];
		if (dec > 0 && dec <= 8) {
			int is_padding = 0;
			LOGI("padding=%d", dec);
			for (int j = 0; j < dec; j++) {
				is_padding = (dec == src[i + j]);
				if (is_padding == 0) {
					break;
				}
			}

			if (is_padding == 1) {
				ret_len = i;
				break;
			}
		}
	}
	LOGI("ret_len=%d", ret_len);

	return ret_len;
}

static jbyteArray PapaCore_decrypt(JNIEnv *env, jclass thiz, jbyteArray jmsg) {
	const char *src;
	const char *dst;
	const char *key;
	int op = -1;
	int len;

	key = SECRET_KEY;
	jbyte *srcByte = env->GetByteArrayElements(jmsg, 0);
	jsize srcSize = env->GetArrayLength(jmsg);
	len = srcSize;
	src = (char*)malloc(sizeof(char)*len);
	memcpy((void *)src, srcByte, len);
	if (src == NULL) {
		return NULL;
	}
	LOGI("key=%s, plain=%s, len=%d", key, src, len);

	LOGI("len=%d", len);
	len = (len % 8 == 0) ? len : ((len / 8 + 1) * 8);
	int round = len / 8;
	LOGI("outsize=%d, block size=%d", len, round);
	dst = (const char *) malloc(len);
	memset((char*) dst, 0, len);

	for (int i = 0; i < round; i++) {
		TripleDES((unsigned char*) (src + 8 * i),
				(unsigned char*) (dst + 8 * i), (unsigned char*) key, op);
	}
	env->ReleaseByteArrayElements(jmsg, (jbyte*) src, 0);

	int *dsta;
	dsta = (int*)malloc(len*sizeof(int));
	for(int i=0;i<len;i++){dsta[i]=dst[i];}
	char *dstc;
	len = checkPadding(dsta, len);
	dstc = (char*) malloc(len);
	memcpy(dstc, dst, len);

	LOGI("cipher=%s", dst);
	//	ret = env->NewStringUTF(dst);//dst is not valid utf-8 string.

	int outSize = len;
	jbyte *dstByte = (jbyte*) dstc;
	jbyteArray jarray = env->NewByteArray(outSize);
	env->SetByteArrayRegion(jarray, 0, outSize, dstByte);

	delete[] dst,dstc;

	return jarray;
}

static jbyteArray PapaCore_encrypt(JNIEnv *env, jclass thiz, jbyteArray jmsg) {
	const char *src;
	const char *dst;
	const char *key;
	int op = 1;
	jstring ret;
	int len_o;
	int len;

	key = SECRET_KEY;
	jbyte *srcByte = env->GetByteArrayElements(jmsg, 0);
	jsize srcSize = env->GetArrayLength(jmsg);
	len = len_o = srcSize;
	src = (char*)malloc(sizeof(char)*len);
	memcpy((void *)src, srcByte, len);
//	src = (const char *) env->GetByteArrayElements(jmsg, 0);
	if (src == NULL) {
		return NULL;
	}
//	len = len_o = strlen((char*) src);
	LOGI("key=%s, plain=%s, plain_len=%d", key, src, len);

	int mod = len % 8;
	int nopadding = (len % 8 == 0);
	len = nopadding ? len + 8 : ((len / 8 + 1) * 8);
	int round = len / 8;
	LOGI("outsize=%d, block size=%d", len, round);

	unsigned char* in;
	in = (unsigned char*) malloc(len);
	memset(in, 0, len);
	memset(in, 8 - mod, len);
	memcpy(in, src, len_o);

	LOGV("nopadding=%d", nopadding);

	dst = (const char *) malloc(len);
	memset((char*) dst, 0, len);
	for (int i = 0; i < round; i++) {
		TripleDES(in + 8 * i, (unsigned char*) (dst + 8 * i),
				(unsigned char*) key, op);
	}
	env->ReleaseByteArrayElements(jmsg, (jbyte*) src, 0);
	LOGI("cipher=%s", dst);
//	ret = env->NewStringUTF(dst);//dst is not valid utf-8 string.

	int outSize = len;
	LOGI("outSize=%d", outSize);
	jbyte *dstByte = (jbyte*) dst;
	jbyteArray jarray = env->NewByteArray(outSize);
	env->SetByteArrayRegion(jarray, 0, outSize, dstByte);

	delete[] dst, in;

	return jarray;
}

//native ---------------------------------------


/*static jbyteArray PapaCore_nativeDecrypt1(JNIEnv *env, jclass thiz, jintArray jmsg) {
	const char *src;
	const char *dst;
	const char *key;
	int op = -1;
	jstring ret;
	int len;
	jint *arr;

	arr = env->GetIntArrayElements(jmsg, false);
	len = (int)env->GetArrayLength(jmsg);

	key = SECRET_KEY;
//	src = (const char *) env->GetByteArrayElements(jmsg, 0);
	src = (const char *)malloc(len);
	for(int i=0;i<len;i++)
	{
		int ch = (int)arr[i];
		memset((char*)&src[i], ch, 1);
	}
	if (src == NULL) {
		return NULL;
	}

	LOGI("key=%s, plain=%s", key, src);
//	len = strlen((char*) src);

	LOGI("len=%d", len);
	len = (len % 8 == 0) ? len : ((len / 8 + 1) * 8);
	int round = len / 8;
	LOGI("outsize=%d, block size=%d", len, round);
	dst = (const char *) malloc(len);
	memset((char*) dst, 0, len);

	for (int i = 0; i < round; i++) {
		TripleDES((unsigned char*) (src + 8 * i),
				(unsigned char*) (dst + 8 * i), (unsigned char*) key, op);
	}
//	env->ReleaseByteArrayElements(jmsg, (jbyte*) src, 0);
	env->ReleaseIntArrayElements(jmsg, arr, 0);

	int *dsta;
	dsta = (int*)malloc(len*sizeof(int));
	for(int i=0;i<len;i++){dsta[i]=dst[i];}
	char *dstc;
	len = checkPadding(dsta, len);
	dstc = (char*) malloc(len);
	memcpy(dstc, dst, len);

	LOGI("cipher=%s", dstc);
	//	ret = env->NewStringUTF(dst);//dst is not valid utf-8 string.

	int outSize = len;
	jbyte *dstByte = (jbyte*) dstc;
	jbyteArray jarray = env->NewByteArray(outSize);
	env->SetByteArrayRegion(jarray, 0, outSize, dstByte);

	delete[] dst, dstc;

	return jarray;
}*/




int register_PapaCore(JNIEnv *env) {

	static const JNINativeMethod methods[] = {
//			{ "decrypt", "([I)[B", (void *) PapaCore_nativeDecrypt1 },
			{ "decrypt", "([B)[B", (void *) PapaCore_decrypt },
			{ "encrypt", "([B)[B", (void *) PapaCore_encrypt },
	};

	return jniRegisterNativeMethods(env, APP_PKG_NAME "/Des3", methods,	NELEM(methods));
}
