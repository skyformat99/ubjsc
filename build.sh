#!/bin/bash
test -d build && rm -r build

mkdir build
cd build
cmake -DJANSSON_WITHOUT_TESTS=ON .. || exit 1
cmake --build . || exit 1
ctest -VV . || exit 1

rm -r *
cmake -DJANSSON_WITHOUT_TESTS=ON -DCMAKE_BUILD_TYPE=Debug . || exit 1
cmake --build .. || exit 1

test/unittests &> /dev/null
gcovr -x -r . -e 'test' -o coverage.xml

valgrind --leak-check=full --xml=yes --xml-file=valgrind.xml test/unittests

# @todo
# cppcheck --xml --enable=all --language=c --suppress=missingIncludeSystem ptrie/src/*.c src/*.c test/*.c test/*.cpp tools/*.c python/*.h python/*.c 2> cppcheck.xml

# @todo
# wget https://github.com/SonarOpenCommunity/sonar-cxx/blob/master/sonar-cxx-plugin/src/tools/vera%2B%2BReport2checkstyleReport.perl
# vera++ -s -c vera.xml include/*.h src/*.h src/*.c test/*.h test/*.c tools/*.c python/*.h python/*.c

# @todo sonar scanner
cd ..

