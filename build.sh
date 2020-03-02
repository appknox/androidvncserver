#!/usr/bin/env bash

mkdir -p builds/arm64-v8a
mkdir -p builds/armeabi-v7a
NDK_ROOT=$ANDROID_NDK_ROOT;
CURRENT_DIR=$PWD;
SDK_LEVEL=26

if [[ -z "${NDK_ROOT}" ]]; then
    echo "Error: ANDROID_NDK_ROOT env not set"
    exit 12
else
    echo "NDK Root at ${NDK_ROOT}"
    echo "SDK ${SDK_LEVEL}"
fi

cd builds/arm64-v8a && cmake \
-DCMAKE_TOOLCHAIN_FILE=${NDK_ROOT}/build/cmake/android.toolchain.cmake \
-DANDROID_ABI=arm64-v8a \
-DANDROID_NATIVE_API_LEVEL=${SDK_LEVEL} \
-DENABLE_SHARED=0 \
-DENABLE_STATIC=1 \
-DPNG_SHARED=0 \
-DPNG_STATIC=1 \
-DPNG_TESTS=0 \
-DWITH_TURBOJPEG=0 \
${CURRENT_DIR} && make && cd ${CURRENT_DIR}

cd builds/armeabi-v7a && cmake \
-DCMAKE_TOOLCHAIN_FILE=${NDK_ROOT}/build/cmake/android.toolchain.cmake \
-DANDROID_ABI=armeabi-v7a \
-DANDROID_NATIVE_API_LEVEL=${SDK_LEVEL} \
-DENABLE_SHARED=0 \
-DENABLE_STATIC=1 \
-DPNG_SHARED=0 \
-DPNG_STATIC=1 \
-DPNG_TESTS=0 \
-DWITH_TURBOJPEG=0 \
${CURRENT_DIR} && make && cd ${CURRENT_DIR}

cp -f builds/arm64-v8a/androidvncserver builds/androidvncserver_arm64
cp -f builds/armeabi-v7a/androidvncserver builds/androidvncserver_armeabi
