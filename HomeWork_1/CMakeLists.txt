# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和版本
project(HomeWork_1 VERSION 1.0)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加Eigen头文件路径
include_directories("/Users/xulp/WorkSpace/WorkSpace_VSCode/WorkSpace_101_HomeWork/HomeWork_1/libs/Eigen")

# 将 src 目录中的源文件添加到项目中
add_executable(HomeWork_1 src/Demo.cpp)