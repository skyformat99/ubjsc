rmdir /s /q build

mkdir build
cd build

curl -o ubjsc-0.4-deps.zip "http://dl.dropboxusercontent.com/s/23utlhfmo3afh35/ubjsc-0.4-deps.zip?dl=0#
7z x ubjsc-0.4-deps.zip

cmake -DJANSSON_EXPORT_DIR=.\jansson -DARGTABLE2_EXPORT_DIR=.\argtable2 ..
if %errorlevel% neq 0 exit /b 1

cmake --build .
if %errorlevel% neq 0 exit /b 1

ctest -VV .
if %errorlevel% neq 0 exit /b 1

cd ..
