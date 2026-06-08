#include "deepseek_chat.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <httplib.h>
#include <nlohmann/json.hpp>

using n_json = nlohmann::json;

char print_char(const char*, size_t);

std::string read_mutiline_input()
{
    printf("\n*YOU* (输入 exit 单独一行结束) \n");
    printf(">");

    std::string inputs;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line == "exit") {
            break;
        }
        inputs += line + "\n";

        if (!std::cin.eof()) {
            printf(">");
        }
    }

    if (!inputs.empty()) {
        inputs.pop_back();
    }

    if (std::cin.eof()) {
        std::cin.clear();
    }

    return inputs;
}

std::string read_sys_prompt()
{
    namespace fs = std::filesystem;

    fs::path path = "sys_prompt.md";
    if (!fs::exists(path)) {
        std::cout << path.c_str() << " not found!" << '\n';
        return "";
    }

    auto abs_path = fs::absolute(path);

    auto size = fs::file_size(abs_path);
    std::string content(size, '\0');

    std::ifstream ifs(abs_path);
    ifs.read(content.data(), size);

    if (content.back() == '\n') {
        content.pop_back();
    }

    return content;
}

void live_chat()
{
    const char* apikey = std::getenv("APIKEY");
    if (!apikey) {
        std::cerr << "错误：未设置环境变量 APIKEY" << "\n";
        return;
    }
    std::string bearer = "Bearer " + std::string(apikey);

    std::string sys_prompt = read_sys_prompt();
    if (sys_prompt.empty()) {
        return;
    }

    const std::string url = "https://api.deepseek.com";

    httplib::Client cli(url);
    cli.set_default_headers({
        {"Authorization", bearer},
    });

    n_json payload = {
        {"model", "deepseek-v4-flash"},
        {"stream", true},
        {"reasoning_effort", "max"},
        {"messages", {{{"role", "system"}, {"content", sys_prompt}}}},
    };

    while (true) {
        std::string inputs = read_mutiline_input();
        if (inputs.empty()) {
            break;
        }

        payload["messages"].push_back({
            {"role", "user"},
            {"content", inputs},
        });
        // std::cout << payload.dump() << "\n\n";

        std::string assistant_reply;
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
                                assistant_reply.append(answer.get<std::string>());
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
            continue;
        }
        payload["messages"].push_back({
            {"role", "assistant"},
            {"content", assistant_reply},
        });
        assistant_reply.clear();
    }
    std::cout << "\n";
}

char print_char(const char* str, size_t len)
{
    const char* data = str;
    size_t len1 = len;
    const char* start = data;
    const char* end = start + len;

    printf("\n%.*s", (int)len, data);
    printf("\n======\n");

    char returned = -1;

    for (const char* p = data; p <= end; p++) {
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
