cmake_minimum_required(VERSION 3.16)

project(Recording VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- OpenCV 设置开始 -------------------------------------------------------
# 如果没有在外部提供 OpenCV_DIR (包含 OpenCVConfig.cmake 的目录)，在 Windows 上使用一个默认路径。
# 请根据你的实际安装调整：通常为 C:/opencv/build 下面再细分到编译器和架构路径。
if (WIN32 AND NOT DEFINED OpenCV_DIR)
    # 典型安装结构示例：C:/opencv/build/x64/vc16/lib (里面有 OpenCVConfig.cmake)
    # 如果你的 OpenCVConfig.cmake 位于其它位置，请在 CMake 设置中覆盖 OpenCV_DIR。
    set(OpenCV_DIR "C:/opencv/build")
endif()

# 查找 OpenCV
find_package(OpenCV QUIET)
if (NOT OpenCV_FOUND)
    message(STATUS "未找到 OpenCV (QUIET)。尝试 REQUIRED 再报错以便提醒配置路径。当前 OpenCV_DIR='${OpenCV_DIR}'")
    find_package(OpenCV REQUIRED)
endif()

message(STATUS "Found OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libraries   : ${OpenCV_LIBS}")
# ---------------------------------------------------------------------------

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        recording.cpp
        recording.h
        recording.ui
        RecordThread.cpp
        RecordThread.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Recording
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Recording SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Recording
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 添加 OpenCV 头文件目录（使用导入目标时一般不必手动添加，但保持兼容旧版本）
include_directories(${OpenCV_INCLUDE_DIRS})

# 链接 Qt 和 OpenCV
target_link_libraries(Recording PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS})

# 如果需要覆盖 OpenCV 路径，可在配置时使用：
# cmake -S . -B build -DOpenCV_DIR=C:\opencv\build
# 或者指向包含 OpenCVConfig.cmake 的其它目录。

# 运行时复制 OpenCV 的 DLL 到可执行文件目录（避免手动设置 PATH）
if (WIN32)
    # 假设预编译包结构：C:/opencv/build/x64/vc16/bin/*.dll
    if (EXISTS "${OpenCV_DIR}/x64/vc16/bin")
        add_custom_command(TARGET Recording POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${OpenCV_DIR}/x64/vc16/bin" $<TARGET_FILE_DIR:Recording>
            COMMENT "复制 OpenCV DLL 到输出目录")
    else()
        message(STATUS "未找到目录 ${OpenCV_DIR}/x64/vc16/bin，若运行时缺少 DLL 请自行复制或添加到 PATH。")
    endif()
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Recording)
endif()
set_target_properties(Recording PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Recording
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Recording)
endif()
