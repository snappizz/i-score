#!/bin/sh
source "$CONFIG_FOLDER/linux-source-qt.sh"

$CMAKE_BIN -DBOOST_ROOT="$BOOST_ROOT" -DISCORE_CONFIGURATION=debug ..
$CMAKE_BIN --build . --target all_unity -- -j2
