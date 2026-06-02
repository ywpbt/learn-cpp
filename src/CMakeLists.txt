find_package(spdlog REQUIRED)

add_library(math_utils
    math_utils.cpp
)

target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)



add_executable(my_app
    main.cpp
)

target_include_directories(my_app
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(my_app
    PRIVATE
        fmt::fmt
        spdlog::spdlog
        math_utils
)

set_target_properties(my_app PROPERTIES CXX_STANDARD 20)

# 自定义 run 目标 — 类似 cargo run
add_custom_target(run
    COMMAND my_app
    DEPENDS my_app
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src
)
