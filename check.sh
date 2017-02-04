#!/bin/bash
set -x

./check-leaks.sh
./check-coverage.sh
./check-static.sh
./check-profile.sh

