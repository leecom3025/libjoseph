
#include "joseph_Torh.h"

static struct jcpu **cpu;

JNIEXPORT void JNICALL Java_joseph_Torh_check(JNIEnv *env, jclass clazz) {
	int i = 0;
	return;
}

JNIEXPORT void JNICALL Java_joseph_Torh_init(JNIEnv *env, jclass clazz) {
	Joseph_CPU_ops(&cpu);
	return;
}

JNIEXPORT jdouble JNICALL Java_joseph_Torh_getTemp(JNIEnv *env, jclass clazz) {
	if (Joseph_CPU_read(cpu) != -1) {
		int temp = cpu[0]->temp + cpu[1]->temp + cpu[2]->temp + cpu[3]->temp;
		jdouble jtemp = (jdouble) temp/4;
		return jtemp;
	} 
	double i = -1;
	return (jdouble)i;
}

JNIEXPORT jdouble JNICALL Java_joseph_Torh_getUtil(JNIEnv *env, jclass clazz) {
	if (Joseph_CPU_read(cpu) != -1) {
		int temp = cpu[0]->util + cpu[1]->util + cpu[2]->util + cpu[3]->util;
		jdouble jutil = (jdouble) temp/4;
		return jutil;
	} 
	double i = -1;
	return (jdouble)i;
}

JNIEXPORT jdouble JNICALL Java_joseph_Torh_getFreq(JNIEnv *env, jclass clazz) {
	if (Joseph_CPU_read(cpu) != -1) {
		int temp = cpu[0]->freq + cpu[1]->freq + cpu[2]->freq + cpu[3]->freq;
		jdouble jfreq = (jdouble) temp/4;
		return jfreq;
	} 
	double i = -1;
	return (jdouble)i;
}

