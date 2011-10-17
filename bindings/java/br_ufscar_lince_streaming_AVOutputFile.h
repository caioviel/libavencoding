/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class br_ufscar_lince_streaming_AVOutputFile */

#ifndef _Included_br_ufscar_lince_streaming_AVOutputFile
#define _Included_br_ufscar_lince_streaming_AVOutputFile
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    getFilename
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_getFilename
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_stop
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_start
  (JNIEnv *, jobject);

/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    addStream
 * Signature: (Lbr/ufscar/lince/streaming/AVEncoder;)V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_addStream
  (JNIEnv *, jobject, jobject);

/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    create
 * Signature: (Ljava/lang/String;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_create
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     br_ufscar_lince_streaming_AVOutputFile
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_br_ufscar_lince_streaming_AVOutputFile_destroy
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
