#include "http_utils.h"
#include <httplib.h>
void get_ip_address()
{
    // http://ip-api.com
    httplib::Client cli("https://httpbin.org");
    auto res = cli.Get("/ip");
    if (res && res->status == 200) {
        std::cout << "Your IP address is: " << res->body << std::endl;
    }
    else {
        std::cerr << "Failed to get IP address:" << res->reason << std::endl;
    }
}
