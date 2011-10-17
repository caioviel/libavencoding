/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class br_ufscar_lince_streaming_RTPStream */

#ifndef _Included_br_ufscar_lince_streaming_RTPStream
#define _Included_br_ufscar_lince_streaming_RTPStream
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    create
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_br_ufscar_lince_streaming_RTPStream_create
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_RTPStream_destroy
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    addStream
 * Signature: (Lbr/ufscar/lince/streaming/AVEncoder;)V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_RTPStream_addStream
  (JNIEnv *, jobject, jobject);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_RTPStream_stop
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_RTPStream_start
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    waitFinishing
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_RTPStream_waitFinishing
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_RTPStream
 * Method:    isFinished
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_br_ufscar_lince_streaming_RTPStream_isFinished
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
