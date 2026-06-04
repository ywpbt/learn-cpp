#include <iostream>
#include <spdlog/spdlog.h>
// #include "http_utils.h"
// #include "math_utils.h"
#include "deepseek_chat.h"

int main(int argc, char* argv[])
{
    std::cout << "argc:" << argc << ",argv:" << argv[0] << "\n";
    std::cout << "current c++ version:" << __cplusplus << "\n";

    // spdlog::info("Calling add function from math_utils:");
    // int sum1 = add(200, 199);
    // spdlog::info("The sum of 200 and 199 is {}", sum1);

    // spdlog::info("Getting IP address:");
    // get_ip_address();

    // spdlog::info("Getting request headers:");
    // get_req_headers();

    spdlog::info("nlohmann json example:\n");
    live_chat();

    return 0;
}
