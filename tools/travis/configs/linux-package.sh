#!/bin/sh

$CMAKE_BIN -GNinja -DCMAKE_PREFIX_PATH="/usr/local/jamoma/share/cmake/Jamoma;/opt/qt5-static/lib/cmake/Qt5" -DISCORE_CONFIGURATION=staticqt-release ..
$CMAKE_BIN --build . --target package --config StaticRelease