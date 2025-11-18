@echo off
cd /d D:\Desktop\Recording
"C:\Program Files\JetBrains\CLion 2025.2\bin\cmake\win\x64\bin\cmake.exe" -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_MAKE_PROGRAM=C:/Program Files/JetBrains/CLion 2025.2/bin/ninja/win/x64/ninja.exe" -G Ninja -S D:\Desktop\Recording -B D:\Desktop\Recording\cmake-build-debug
pause

