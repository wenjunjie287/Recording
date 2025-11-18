# OpenCV 配置修复说明

## 问题原因
CMakeLists.txt 中的 OpenCV_DIR 设置为 `C:/opencv/build/x64/vc16`，但实际上 OpenCVConfig.cmake 文件位于 `C:/opencv/build/x64/vc16/lib` 目录。

## 已完成的修复
已将 CMakeLists.txt 第 18 行的 OpenCV_DIR 从：
```cmake
set(OpenCV_DIR "C:/opencv/build/x64/vc16")
```
修改为：
```cmake
set(OpenCV_DIR "C:/opencv/build/x64/vc16/lib")
```

## 下一步操作（请在 CLion 中执行）
1. 在 CLion 中，点击菜单：**Tools** -> **CMake** -> **Reset Cache and Reload Project**
   或者
2. 删除 `cmake-build-debug` 目录，然后在 CLion 中点击 **Reload CMake Project** 按钮

## 注意事项
- 你使用的是 Visual Studio 2022 (vc17)，而 OpenCV 是用 Visual Studio 2019 (vc16) 编译的
- 这通常是兼容的，因为 vc16 和 vc17 之间的 ABI 兼容性良好
- 如果仍有问题，可能需要使用 Visual Studio 2022 重新编译 OpenCV

## 验证
配置成功后，你应该看到类似这样的输出：
```
-- Found OpenCV version: 4.x.x
-- OpenCV include dirs: C:/opencv/build/include
-- OpenCV libraries   : opencv_core;opencv_imgproc;...
```

