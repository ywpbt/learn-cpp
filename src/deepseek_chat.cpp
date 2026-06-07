#include "deepseek_chat.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>

using n_json = nlohmann::json;

char print_char(const char*, size_t);

void live_chat()
{
    const char* apikey = std::getenv("APIKEY");
    if (!apikey) {
        std::cerr << "错误：未设置环境变量 APIKEY" << "\n";
        return;
    }
    std::string bearer = "Bearer " + std::string(apikey);

    const std::string url = "https://api.deepseek.com";
    // httplib::Headers headers = {
    //     {"content-type", "application/json"},
    //     {"Authorization", bearer},
    // };
    httplib::Client cli(url);
    cli.set_default_headers({
        {"Authorization", bearer},
    });

    n_json payload = {
        {"model", "deepseek-v4-flash"},
        {"stream", true},
        {"reasoning_effort", "max"},
        {"messages", {{{"role", "system"}, {"content", "You are a helpful assistant."}}}},
    };
    payload["messages"].push_back(
        {{"role", "user"},
         {"content", "我想要知道现在的时间点2026年6月为止gcc各版本对应的C++标准能让我在工作中能方便的选择适合项目的C++标准."}});
    std::cout << payload.dump() << "\n\n";

    bool has_shown_hint = true;
    bool is_integrity = true;

    auto stream = httplib::stream::Post(cli, "/chat/completions", payload.dump(), "application/json");
    if (stream && stream.status() == 200) {
        std::string chunked;

        while (stream.next()) {
            chunked.append(stream.data(), stream.size());
            if (chunked.back() != '\n' && chunked.back() != '\0') {
                is_integrity = false;
                continue;
            }
            if (!is_integrity) {
                is_integrity = true;
            }

            std::istringstream iss(chunked);
            std::string line;

            while (std::getline(iss, line)) {
                if (line.empty()) {
                    continue;
                }

                if (line.starts_with("data:")) {

                    std::string json_str = line.substr(6);
                    if (json_str == "[DONE]") {
                        break;
                    }
                    n_json json;
                    try {
                        json = n_json::parse(json_str);
                    }
                    catch (const std::exception& e) {
                        std::cerr << "\nJSON解析错误:" << e.what() << '\n';
                        std::cerr << "\n" << "json_str:" << json_str << "\n\n";
                        std::cerr << "\n" << "line:" << line << "\n\n";
                        std::cerr << "\n" << "chunked:" << chunked << "\n\n";
                        std::cerr << "\n" << "stream data:" << stream.data() << "\n" << "stream size:" << stream.size() << "\n\n";
                        return;
                    }

                    try {

                        auto reasoning = json["choices"][0]["delta"]["reasoning_content"];
                        if (!reasoning.empty() && !reasoning.is_null()) {
                            if (has_shown_hint) {
                                std::cout << "[思考]: " << std::flush;
                                has_shown_hint = false;
                            }
                            std::cout << reasoning.get<std::string>() << std::flush;
                        }

                        auto answer = json["choices"][0]["delta"]["content"];
                        if (!answer.empty() && !answer.is_null()) {
                            if (!has_shown_hint) {
                                std::cout << "\n\n";
                                std::cout << "[回复]: " << std::flush;
                                has_shown_hint = true;
                            }
                            std::cout << answer.get<std::string>() << std::flush;
                        }
                    }
                    catch (std::exception& e) {
                        std::cerr << "JSON读取错误:" << e.what() << "\n";
                        return;
                    }
                }
            }

            if (is_integrity) {
                chunked.clear();
            }
        }
    }
    else {
        std::cerr << stream.status() << ":" << stream.error() << "\n";
    }
    std::cout << "\n";
}

char print_char(const char* str, size_t len)
{
    const char* data = str;
    size_t len1 = len;
    const char* start = data;
    const char* end = start + len;

    printf("%.*s", (int)len, data);
    printf("======\n");

    char returned = -1;

    for (const char* p = data; p < end; p++) {
        switch (*p) {
        case '\r':
            printf("\\r\n");
            fflush(stdout);
            returned = 0;
            break;
        case '\n':
            printf("\\n\n");
            fflush(stdout);
            returned = 1;
            break;
        case '\t':
            printf("\\t\n");
            fflush(stdout);
            returned = 2;
            break;
        case '\0':
            printf("\\0\n");
            fflush(stdout);
            returned = 3;
            break;
        default:
            printf("\r%c", *p);
            fflush(stdout);
            returned = 4;
        }
    }
    printf("\n");
    return returned;
}
