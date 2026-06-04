#include "deepseek_chat.h"
#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>

using n_json = nlohmann::json;

void live_chat()
{
    n_json j = R"({
        "name": "cpp",
        "age": 50,
        "live": true
    })";

    std::string s1 = j.dump();

    // std::cout << std::setw(4) << j << "\n";
    std::cout << s1 << "\n";
    // std::cout << j.dump(4) << "\n";
}
