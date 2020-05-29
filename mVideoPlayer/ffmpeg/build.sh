#!/bin/bash
if [ $# -lt 1 ];then
    echo "Usage:"
    echo "  ./build.sh ubuntu_x86_64"
    echo "  ./build.sh android_arm"
    echo "  ./build.sh android_arm64"
    echo "  ./build.sh android_x86"
    echo "  ./build.sh android_x86_x64"
    exit 0
fi
which make
if [ $? == 1 ];then
    sudo apt install make > /dev/null
fi

if [ ! -d ffmpeg-4.1.5 ];then
    tar xvf ffmpeg-4.1.5.tar.xz
fi
TARGET=$1
echo $TARGET
pushd ffmpeg-4.1.5/
ADDITIONAL_CONFIGURE_FLAG=
ADDI_LDFLAGS=
ADDI_CFLAGS=
if [ $TARGET == ubuntu_x86_64 ];then
arch=x86_64
TOOLCHAIN=
SYSROOT=
ADDI_CFLAGS+=""
ENABLE_CROSS_COMPILE=
ADDI_OPT=" --disable-ffplay --disable-programs"
elif [ $TARGET == android_x86 ];then
arch=x86
TOOLCHAIN=$HOME/Android/standalone-toolchains/android-toolchain-x86/bin/i686-linux-android-
SYSROOT=$HOME/Android/standalone-toolchains/android-toolchain-x86/sysroot/
ADDI_CFLAGS+=" -m32"
ENABLE_CROSS_COMPILE=
ADDI_OPT='--disable-ffplay --disable-programs'
elif [ $TARGET == android_x86_64 ];then
arch=x86_64
TOOLCHAIN=$HOME/Android/standalone-toolchains/android-toolchain-x86/bin/i686-linux-android-
SYSROOT=$HOME/Android/standalone-toolchains/android-toolchain-x86/sysroot/
ADDI_CFLAGS+="-m64"
ENABLE_CROSS_COMPILE=
ADDI_OPT='--disable-ffplay --disable-programs'
elif [ $TARGET == android_arm ];then
arch=arm
TOOLCHAIN=$HOME/Android/standalone-toolchains/android-toolchain-arm/bin/arm-linux-androideabi-
SYSROOT=$HOME/Android/standalone-toolchains/android-toolchain-arm/sysroot/
ADDI_CFLAGS+=" -marm"
ENABLE_CROSS_COMPILE=--enable-cross-compile
ADDI_OPT=" --disable-ffplay --disable-programs"
elif [ $TARGET == android_arm64 ];then
arch=arm64
TOOLCHAIN=$HOME/Android/standalone-toolchains/android-toolchain-arm64/bin/aarch64-linux-android-
SYSROOT=$HOME/Android/standalone-toolchains/android-toolchain-arm64/sysroot/
ADDI_CFLAGS+=" "
ENABLE_CROSS_COMPILE=--enable-cross-compile
ADDI_OPT=" --disable-ffplay --disable-programs"
else
    echo "arch($arch) not found"
    exit 0
fi
platform=$TARGET
make distclean
./configure \
 --cross-prefix=$TOOLCHAIN $ENABLE_CROSS_COMPILE --sysroot=$SYSROOT \
 --prefix=$(pwd)/../libffmpeg_$platform --target-path=~/build-ffmpeg-$platform/ --arch=$arch --target-os=linux --pkg-config= \
 --extra-cflags="-Os -fPIC $ADDI_CFLAGS" --extra-ldflags="$ADDI_LDFLAGS" --disable-x86asm --disable-everything \
 --enable-gpl --enable-version3 --disable-avdevice  \
 --enable-protocol=file --enable-protocol=rtp --enable-protocol=tcp --enable-protocol=udp --enable-demuxer=rtsp --enable-demuxer=rtp  \
 --disable-postproc --disable-avfilter \
 --enable-decoder=h264  --disable-ffprobe  --disable-doc --disable-devices \
 --disable-bsfs --disable-indevs --disable-outdevs --enable-parser=h264 --disable-zlib --disable-libxcb-shm $ADDI_OPT
 
make -j 8
make install
 popd
