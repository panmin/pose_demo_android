// Copyright (c) 2019 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Native.h"
#include "Pipeline.h"
#include "postprocess.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_baidu_paddle_lite_demo_yolo_detection_Native
 * Method:    nativeInit
 * Signature:
 * (Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;II[F[FF)J
 */
JNIEXPORT jlong JNICALL
Java_com_baidu_paddle_lite_demo_yolo_1detection_Native_nativeInit(
    JNIEnv *env, jclass thiz, jstring jModelDir, jstring jLabelPath,jint modelType,
    jint cpuThreadNum, jstring jCPUPowerMode, jint inputWidth, jint inputHeight,
    jfloatArray jInputMean, jfloatArray jInputStd, jfloat scoreThreshold) {
  std::string modelDir = jstring_to_cpp_string(env, jModelDir);
  std::string labelPath = jstring_to_cpp_string(env, jLabelPath);
  std::string cpuPowerMode = jstring_to_cpp_string(env, jCPUPowerMode);
  std::vector<float> inputMean = jfloatarray_to_float_vector(env, jInputMean);
  std::vector<float> inputStd = jfloatarray_to_float_vector(env, jInputStd);
  return reinterpret_cast<jlong>(
      new Pipeline(modelDir, labelPath,modelType, cpuThreadNum, cpuPowerMode, inputWidth,
                   inputHeight, inputMean, inputStd, scoreThreshold));
}

/*
 * Class:     com_baidu_paddle_lite_demo_yolo_detection_Native
 * Method:    nativeRelease
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_baidu_paddle_lite_demo_yolo_1detection_Native_nativeRelease(
    JNIEnv *env, jclass thiz, jlong ctx) {
  if (ctx == 0) {
    return JNI_FALSE;
  }
  Pipeline *pipeline = reinterpret_cast<Pipeline *>(ctx);
  delete pipeline;
  return JNI_TRUE;
}

/*
 * Class:     com_baidu_paddle_lite_demo_yolo_detection_Native
 * Method:    nativeProcess
 * Signature: (JIIIILjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL
Java_com_baidu_paddle_lite_demo_yolo_1detection_Native_nativeProcess(
    JNIEnv *env, jclass thiz, jlong ctx, jint inTextureId, jint outTextureId,
    jint textureWidth, jint textureHeight, jstring jsavedImagePath, jint actionid, jboolean single) {
  if (ctx == 0) {
    return JNI_FALSE;
  }
  std::string savedImagePath = jstring_to_cpp_string(env, jsavedImagePath);
  Pipeline *pipeline = reinterpret_cast<Pipeline *>(ctx);
  pipeline->Process(inTextureId, outTextureId, textureWidth,
                           textureHeight, savedImagePath, actionid, single);
  return JNI_TRUE;
}

JNIEXPORT jintArray JNICALL
Java_com_baidu_paddle_lite_demo_yolo_1detection_Native_nativeGetActionCount(
    JNIEnv *env, jclass thiz, jlong ctx) {
  if (ctx == 0) {
    return JNI_FALSE;
  }
  Pipeline *pipeline = reinterpret_cast<Pipeline *>(ctx);
  std::vector<int> records = pipeline->GetCount();
  return intvector_to_jintarray(env, records);
}

JNIEXPORT jboolean JNICALL
Java_com_baidu_paddle_lite_demo_yolo_1detection_Native_nativeReset(
    JNIEnv *env, jclass thiz, jlong ctx) {
  if (ctx == 0) {
    return JNI_FALSE;
  }
  Pipeline *pipeline = reinterpret_cast<Pipeline *>(ctx);
  pipeline->ClearCount();
  return JNI_TRUE;
}

#ifdef __cplusplus
}
#endif
