cmake_minimum_required(VERSION 3.15)
project(TDX_Indicator VERSION 1.0.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows特定设置
if(WIN32)
    add_definitions(-DWIN32 -D_WINDOWS -D_USRDLL)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# 添加DLL项目
add_library(TDX_Indicator SHARED
    src/main.cpp
    src/TCalcFuncSets.cpp
    src/indicators.cpp
)

# 包含目录
target_include_directories(TDX_Indicator PRIVATE src)

# Windows链接选项
if(WIN32)
    target_link_libraries(TDX_Indicator)
    set_target_properties(TDX_Indicator PROPERTIES
        PREFIX ""
        SUFFIX ".dll"
    )
endif()