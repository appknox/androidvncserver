# androidvncserver

This is a standalone VNC Server for Android

### Build using the following

```
cd .. && mkdir -p androidvncserverbuild && cd androidvncserverbuild && cmake \
-DCMAKE_TOOLCHAIN_FILE=$(ANDROID_NDK_ROOT)/build/cmake/android.toolchain.cmake \
-DANDROID_ABI=arm64-v8a \
-DANDROID_NATIVE_API_LEVEL=25 \
-DENABLE_SHARED=0 \
-DENABLE_STATIC=1 \
-DPNG_SHARED=0 \
-DPNG_STATIC=1 \
-DPNG_TESTS=0 \
-DWITH_TURBOJPEG=0 \
../androidvncserverbuild && make
```

## For flinger Please check the repo https://github.com/appknox/libdvnc_flinger
