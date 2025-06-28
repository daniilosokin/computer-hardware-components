rmdir /s /q build
cmake -G Ninja -B build
cd build
ninja
cd ..