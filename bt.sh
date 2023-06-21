#!/bin/bash

cd ${0%/*}

cmake --build build

cd build

ctest

cd ..
