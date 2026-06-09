# 关闭第三方库测试（很重要！）
set(DOCTEST_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "" FORCE)

# 添加子模块
add_subdirectory(doctest)

# 使用静态 OpenSSL（libssl.a / libcrypto.a），支持 -static 链接
set(OPENSSL_USE_STATIC_LIBS ON)
find_package(OpenSSL REQUIRED)

# 创建一个名叫 cpp_httplib 的 INTERFACE 库（无源文件）
add_library(cpp_httplib INTERFACE)

# 编译时需要这个头文件路径
target_include_directories(cpp_httplib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp-httplib
)

# 启用 OpenSSL 支持
target_compile_definitions(cpp_httplib
    INTERFACE
        CPPHTTPLIB_OPENSSL_SUPPORT
)

# 链接时需要 pthread + OpenSSL
target_link_libraries(cpp_httplib
    INTERFACE
        pthread
        OpenSSL::SSL
        OpenSSL::Crypto
)


# nlohmann/json — 头文件库，使用 upstream CMake 配置
add_subdirectory(nlohmann_json)
