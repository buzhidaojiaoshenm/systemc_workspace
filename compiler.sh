#!/bin/bash
target=$1

export SYSTEMC_HOME=/home/sjh/work/systemc-3.0.0
export LD_LIBRARY_PATH=/home/sjh/work/systemc-3.0.0/lib-linux64:$LD_LIBRARY_PATH

g++ -o $target $target.cpp -I/home/sjh/work/systemc-3.0.0/include -L/home/sjh/work/systemc-3.0.0/lib-linux64 -lsystemc
./$target