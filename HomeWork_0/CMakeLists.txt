# 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 2.8.11)

# 定义项目名称和版本
project(HomeWork_0)

# 添加Eigen头文件路径
find_package(Eigen3 REQUIRED)
include_directories(EIGEN3_INCLUDE_DIR)

# 将 src 目录中的源文件添加到项目中
add_executable(HomeWork_0 src/Demo.cpp)