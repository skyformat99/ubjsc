
echo '***** BUILD *****'

rmdir /s /q build

mkdir build
cd build
mkdir logs

cmake ..
if %errorlevel% neq 0 exit /b 1

cmake --build .
if %errorlevel% neq 0 exit /b 1

ctest -VV .
if %errorlevel% neq 0 exit /b 1

cd ..
