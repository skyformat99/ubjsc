echo '***** BUILD *****'

rmdir /s /q build2

mkdir build2
cd build2
mkdir logs

"C:\Program Files\CMake\bin\cmake" ..
"C:\Program Files\CMake\bin\cmake" --build .

cd ..
