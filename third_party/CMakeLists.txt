# 关闭第三方库测试（很重要！）
set(DOCTEST_WITH_TESTS OFF CACHE BOOL "" FORCE)
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "" FORCE)

# 添加子模块
add_subdirectory(doctest)
