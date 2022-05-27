package com.baidu.paddle.lite.demo.yolo_detection;

import android.content.Context;

public class Native {
    static {
        System.loadLibrary("Native");
    }

    public static int MODEL_NAME_TYPE = 1;
    private long ctx = 0;

    public boolean init(String modelDir,
                        String labelPath,
                        int modelType,
                        int cpuThreadNum,
                        String cpuPowerMode,
                        int inputWidth,
                        int inputHeight,
                        float[] inputMean,
                        float[] inputStd,
                        float scoreThreshold) {
        ctx = nativeInit(
                modelDir,
                labelPath,
                modelType,
                cpuThreadNum,
                cpuPowerMode,
                inputWidth,
                inputHeight,
                inputMean,
                inputStd,
                scoreThreshold);
        return ctx == 0;
    }

    public boolean release() {
        if (ctx == 0) {
            return false;
        }
        return nativeRelease(ctx);
    }

    public boolean process(int inTextureId, int outTextureId, int textureWidth, int textureHeight, String savedImagePath,int actionid,boolean single) {
        if (ctx == 0) {
            return false;
        }
        return nativeProcess(ctx, inTextureId, outTextureId, textureWidth, textureHeight, savedImagePath, actionid, single);
    }

    public int[] getActionCount() {
        return nativeGetActionCount(ctx);
    }

    public boolean reset() {
        return nativeReset(ctx);
    }

    public static native long nativeInit(String modelDir,
                                         String labelPath,
                                         int modelType,
                                         int cpuThreadNum,
                                         String cpuPowerMode,
                                         int inputWidth,
                                         int inputHeight,
                                         float[] inputMean,
                                         float[] inputStd,
                                         float scoreThreshold);

    public static native boolean nativeRelease(long ctx);

    public static native boolean nativeProcess(long ctx, int inTextureId, int outTextureId, int textureWidth, int textureHeight, String savedImagePath, int actionid, boolean single);

    public static native boolean nativeReset(long ctx);

    public static native int[] nativeGetActionCount(long ctx);
}
