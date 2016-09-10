rmdir /s /q build

mkdir build
cd build

curl -o ubjsc-0.4-deps.7z "http://dl.dropboxusercontent.com/s/6l849mulq4vzv08/ubjsc-0.4-deps.7z"
7z x ubjsc-0.4-deps.7z

cmake -DJANSSON_EXPORT_DIR=.\jansson -DARGTABLE2_EXPORT_DIR=.\argtable2 ..
if %errorlevel% neq 0 exit /b 1

cmake --build .
if %errorlevel% neq 0 exit /b 1

ctest -VV .
if %errorlevel% neq 0 exit /b 1

cd ..
