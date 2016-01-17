#!/bin/sh
source "$CONFIG_FOLDER/osx-source-qt.sh"

$CMAKE_BIN $CMAKE_COMMON_FLAGS -DISCORE_CONFIGURATION=static-release ..
$CMAKE_BIN --build . --target all_unity -- -j2
$CMAKE_BIN --build . --target install/fast --config StaticRelease