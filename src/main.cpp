#include <iostream>
#include <spdlog/spdlog.h>
#include "http_utils.h"
#include "math_utils.h"

int main(int argc, char* argv[])
{
    std::cout << "argc:" << argc << ",argv:" << argv[0] << "\n";
    std::cout << "current c++ version:" << __cplusplus << "\n";

    int sum = add(100, 99);
    std::cout << "sum=" << sum << std::endl;

    spdlog::info("Another calculation:");

    int sum1 = add(200, 199);
    spdlog::info("The sum of 200 and 199 is {}", sum1);

    spdlog::info("Getting IP address:");
    get_ip_address();

    return 0;
}
