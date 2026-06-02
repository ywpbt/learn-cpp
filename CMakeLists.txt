cmake_minimum_required(VERSION 3.30)

project(MyProject VERSION 1.0 LANGUAGES CXX)

# C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 生成 compile_commands.json（供 VS Code 智能提示使用）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 子目录
add_subdirectory(third_party)
add_subdirectory(src)

# 可选：测试
option(ENABLE_TESTS "Enable tests" ON)
if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
