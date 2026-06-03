# 关闭第三方库测试（很重要！）
set(DOCTEST_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "" FORCE)

# 添加子模块
add_subdirectory(doctest)

# 创建一个名叫 cpp_httplib 的 INTERFACE 库（无源文件）
add_library(cpp_httplib INTERFACE)

# 编译时需要这个头文件路径
target_include_directories(cpp_httplib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp-httplib
)

# 链接时需要 pthread
target_link_libraries(cpp_httplib
    INTERFACE
        pthread
)
