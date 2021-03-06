#!/bin/bash -eux

cd /image

NPROC=$(nproc)

yum -y install perl-version libxcb libxcb-devel xcb-util xcb-util-devel fontconfig-devel libX11-devel libXrender-devel libXi-devel git openssl-devel dbus-devel glib2-devel mesa-libGL-devel

git clone https://code.qt.io/qt/qt5.git

(
  cd qt5
  git checkout 5.7
  perl init-repository --module-subset=qtbase,qtimageformats,qtsvg,qtwebsockets,qttranslations,qtrepotools,qtdeclarative,qttools,qtdoc
)

export CC=/usr/local/bin/gcc
export CXX=/usr/local/bin/g++

mkdir qt5-build
(
  cd qt5-build
  ../qt5/configure -release \
                   -opensource \
                   -confirm-license \
                   -nomake examples \
                   -nomake tests \
                   -no-qml-debug \
                   -qt-zlib \
                   -no-mtdev \
                   -no-journald \
                   -no-syslog \
                   -no-gif \
                   -qt-libpng \
                   -qt-libjpeg \
                   -qt-freetype \
                   -qt-harfbuzz \
                   -openssl \
                   -qt-pcre \
                   -qt-xcb \
                   -qt-xkbcommon-x11 \
                   -no-xinput2 \
                   -glib \
                   -no-pulseaudio \
                   -no-alsa \
                   -no-compile-examples \
                   -no-cups \
                   -no-iconv \
                   -no-tslib \
                   -no-icu \
                   -no-pch \
                   -ltcg \
                   -dbus-linked \
                   -no-gstreamer \
                   -no-system-proxies

  make -j$NPROC
  make install -j$NPROC
)
