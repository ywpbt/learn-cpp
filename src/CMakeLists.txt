find_package(spdlog REQUIRED)

add_library(math_utils
    math_utils.cpp
)

target_include_directories(math_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(http_utils
    http_utils.cpp
)

target_include_directories(http_utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(http_utils
    PRIVATE
        cpp_httplib
)

add_library(deepseek_chat
    deepseek_chat.cpp
)

target_include_directories(deepseek_chat
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(deepseek_chat
    PRIVATE
        cpp_httplib
        nlohmann_json::nlohmann_json
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
        http_utils
        deepseek_chat
)

set_target_properties(my_app PROPERTIES CXX_STANDARD 20)

# 自定义 run 目标 — 类似 cargo run
add_custom_target(run
    COMMAND my_app
    DEPENDS my_app
    USES_TERMINAL
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/src
)
