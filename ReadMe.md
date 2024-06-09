In order to use protobuf on android your toolchain (which is ndk: ~/Android/Sdk/ndk/25.1.8937393/toolchains/llvm/prebuilt/linux-x86_64/bin) must see it.
By default it is not installed so you have to install it from source.


###Prerequisites

1. install dependency: abseil
git clone git@github.com:abseil/abseil-cpp.git  
git checkout 20240116.rc2
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/zby/Android/Sdk/ndk/25.1.8937393/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI="armeabi-v7a" \
        -DANDROID_PLATFORM=android-23 \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$HOME/Android/abseil
sudo make install


git@github.com:google/googletest.git
git checkout v1.14.0-pre
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/home/zby/Android/Sdk/ndk/25.1.8937393/build/cmake/android.toolchain.cmake \
         -DANDROID_ABI="armeabi-v7a" \
         -DANDROID_PLATFORM=android-23 \
         -DCMAKE_INSTALL_PREFIX=$HOME/Android/gtest1.14 \
         -DCMAKE_BUILD_TYPE=Release
sudo make install


2. build protobuf.
remember you have to use your toolchain. Notice that form some version (at least 25.1) ndk provides cmake toolchain file android.toolchain.cmake, so you can use it
for cross compilation DCMAKE_TOOLCHAIN_FILE= ...android.toolchain.cmake

git clone git@github.com:protocolbuffers/protobuf.git
git checkout v5.27.0-rc3
mkdir build
cd build
cmake .. \
-DCMAKE_TOOLCHAIN_FILE=/home/zby/Android/Sdk/ndk/25.1.8937393/build/cmake/android.toolchain.cmake \
-DANDROID_ABI="armeabi-v7a" \
-DANDROID_PLATFORM=android-23 \
-DCMAKE_INSTALL_PREFIX=$HOME/Android/protobuf-v5.27.0-rc3 \
-DCMAKE_BUILD_TYPE=Release \
-Dprotobuf_BUILD_TESTS=OFF \
-Dprotobuf_ABSL_PROVIDER=package \
-Dabsl_DIR=$HOME/Android/abseil/lib/cmake/absl

sudo make install

###Build & deploy

building 
- for android
```
/opt/Qt/Tools/CMake/bin/cmake -S /home/zby/repos/Gomoku2/frontend/GUI -B /home/zby/repos/Gomoku2/frontend/buildxxx -DCMAKE_GENERATOR:STRING="Unix Makefiles" -DCMAKE_BUILD_TYPE:STRING=Release  -DQT_QMAKE_EXECUTABLE:FILEPATH=/opt/Qt/6.6.1/android_armv7/bin/qmake -DCMAKE_PREFIX_PATH:PATH=/opt/Qt/6.6.1/android_armv7 -DCMAKE_C_COMPILER:FILEPATH=/home/zby/Android/Sdk/ndk/25.1.8937393/toolchains/llvm/prebuilt/linux-x86_64/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/home/zby/Android/Sdk/ndk/25.1.8937393/toolchains/llvm/prebuilt/linux-x86_64/bin/clang++ -DANDROID_PLATFORM:STRING=android-23 -DANDROID_NDK:PATH=/home/zby/Android/Sdk/ndk/25.1.8937393 -DCMAKE_TOOLCHAIN_FILE:FILEPATH=/home/zby/Android/Sdk/ndk/25.1.8937393/build/cmake/android.toolchain.cmake -DANDROID_USE_LEGACY_TOOLCHAIN_FILE:BOOL=OFF -DANDROID_ABI:STRING=armeabi-v7a -DANDROID_STL:STRING=c++_shared -DCMAKE_FIND_ROOT_PATH:PATH=/opt/Qt/6.6.1/android_armv7 -DQT_NO_GLOBAL_APK_TARGET_PART_OF_ALL:BOOL=ON -DQT_HOST_PATH:PATH=/opt/Qt/6.6.1/gcc_64 -DANDROID_SDK_ROOT:PATH=/home/zby/Android/Sdk -DProtobuf_DIR:STRING=/home/zby/Android/protobuf-v5.27.0-rc3/lib/cmake/protobuf -Dutf8_range_DIR:STRING=/home/zby/Android/protobuf-v5.27.0-rc3/lib/cmake/utf8_range -Dabsl_DIR:STRING=/home/zby/Android/abseil/lib/cmake/absl -DGTest_DIR:STRING=/home/zby/Android/gtest1.14/lib/cmake/GTest

cd /home/zby/repos/Gomoku2/frontend/buildxxx
make VERBOSE=1

"/opt/Qt/6.6.1/gcc_64/bin/androiddeployqt" --input /home/zby/repos/Gomoku2/frontend/buildxxx/android-appGomokuGui-deployment-settings.json --output /home/zby/repos/Gomoku2/frontend/buildxxx/android-build --android-platform android-34 --jdk /usr/lib/jvm/java-11-openjdk-amd64 --gradle --release
```

before you upload app you must sign it:

* generate key (password 'strit44')
```
keytool -genkey -v -keystore my-release-key.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000
```
* asign app
```
apksigner sign --ks my-release-key.keystore --ks-key-alias alias_name /home/zby/Desktop/shared/build-GUI-Android_kit_oppo-Release/android-build/build/outputs/apk/release/android-build-release-unsigned.apk
```
* upload to oppo
```
adb -s RQ3002M8LG install /home/zby/Desktop/shared/build-GUI-Android_kit_oppo-Release/android-build/build/outputs/apk/release/android-build-release-unsigned.apk
```
* upload to sony
```
adb -s 4815ed70 install /home/zby/Desktop/shared/build-GUI-Android_kit_oppo-Release/android-build/build/outputs/apk/release/android-build-release-unsigned.apk
```

* usefull cmd
```
adb devices #lists phone devices attached to usb
adb catlog  #shows online logs
```