/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class br_ufscar_lince_streaming_UDPMpegTS */

#ifndef _Included_br_ufscar_lince_streaming_UDPMpegTS
#define _Included_br_ufscar_lince_streaming_UDPMpegTS
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    waitFinishing
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_waitFinishing
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    isFinished
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_isFinished
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_stop
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_start
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    addStream
 * Signature: (Lbr/ufscar/lince/streaming/AVEncoder;)V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_addStream
  (JNIEnv *, jobject, jobject);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    create
 * Signature: (Ljava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_create
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     br_ufscar_lince_streaming_UDPMpegTS
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_UDPMpegTS_destroy
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif