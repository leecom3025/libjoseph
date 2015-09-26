
#include <jni.h>
#include "libjoseph.h"

#ifndef _Included_joseph_Torh
#define _Included_joseph_Torh

#ifdef __cplusplus
extern "C" {
#endif 

JNIEXPORT void JNICALL joseph_Torh_check(JNIEnv *, jclass);
JNIEXPORT jdouble JNICALL joseph_Torh_getTemp(JNIEnv *, jclass);
JNIEXPORT jdouble JNICALL joseph_Torh_getUtil(JNIEnv *, jclass);
JNIEXPORT jdouble JNICALL joseph_Torh_getFreq(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif 

#endif 
