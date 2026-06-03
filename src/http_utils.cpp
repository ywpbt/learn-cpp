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

void get_req_headers()
{
    // http://httpbin.org/headers
    httplib::Headers headers = {{"Accept", "application/json"}};
    httplib::Client cli("https://httpbin.org");
    auto res = cli.Get("/headers", headers);
    if (res && res->status == 200) {
        std::cout << "Your request headers are: " << res->body << std::endl;
    }
    else {
        std::cerr << "Failed to get request headers:" << res->reason << std::endl;
    }
}
