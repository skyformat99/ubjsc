#!/bin/bash

test -d docs && rm -rf docs
mkdir docs
doxygen
