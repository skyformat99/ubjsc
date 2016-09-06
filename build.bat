echo '***** BUILD *****'

rmdir /s /q build

mkdir build
cd build
mkdir logs

"C:\Program Files\CMake\bin\cmake" ..
if %errorlevel% neq 0 exit /b 1

"C:\Program Files\CMake\bin\cmake" --build .
if %errorlevel% neq 0 exit /b 1

"C:\Program Files\CMake\bin\ctest" -VV .
if %errorlevel% neq 0 exit /b 1

cd ..
