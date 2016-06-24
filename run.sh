#!/bin/bash

astyle -q --recursive '*.h' '*.c'

./build.sh && ./test.sh && ./misc.sh && ./dist.sh
