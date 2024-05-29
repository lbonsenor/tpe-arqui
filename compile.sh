#!/bin/bash
make clean
cd Toolchain
make clean
make all
cd ..
make all