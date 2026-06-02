#include "doctest.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

// read_lines_from_file 定义在 learn_unique_ptr.cpp 中，通过编译单元链接进来
std::unique_ptr<std::vector<std::string>> read_lines_from_file(std::string& file_name);

// 辅助函数：创建临时测试文件
std::string create_temp_file(const std::vector<std::string>& lines)
{
    auto tmp = std::filesystem::temp_directory_path() / "test_read_lines_XXXXXX.txt";
    auto path = tmp.string();

    std::ofstream f(path);
    for (const auto& line : lines) {
        f << line << "\n";
    }
    f.close();
    return path;
}

TEST_CASE("testing read_lines_from_file")
{
    SUBCASE("file with multiple lines")
    {
        // 注意：该函数会在末尾多读一个空行（eof() 判断的经典问题）
        std::vector<std::string> expected = {"hello", "world", "c++20"};
        auto path = create_temp_file(expected);
        std::string filename = path;

        auto result = read_lines_from_file(filename);

        REQUIRE(result != nullptr);
        CHECK(result->size() == 4); // 3行 + 末尾多一个空行
        CHECK((*result)[0] == "hello");
        CHECK((*result)[1] == "world");
        CHECK((*result)[2] == "c++20");
        CHECK((*result)[3] == "");

        std::filesystem::remove(path);
    }

    SUBCASE("empty file")
    {
        auto path = create_temp_file({});
        std::string filename = path;

        auto result = read_lines_from_file(filename);

        REQUIRE(result != nullptr);
        CHECK(result->size() == 1); // 空文件也会产生一个空串
        CHECK((*result)[0] == "");

        std::filesystem::remove(path);
    }

    SUBCASE("single line file")
    {
        std::vector<std::string> expected = {"only one line"};
        auto path = create_temp_file(expected);
        std::string filename = path;

        auto result = read_lines_from_file(filename);

        REQUIRE(result != nullptr);
        CHECK(result->size() == 2); // 1行 + 末尾空行
        CHECK((*result)[0] == "only one line");
        CHECK((*result)[1] == "");

        std::filesystem::remove(path);
    }

    SUBCASE("file with empty lines")
    {
        std::vector<std::string> expected = {"first", "", "third"};
        auto path = create_temp_file(expected);
        std::string filename = path;

        auto result = read_lines_from_file(filename);

        REQUIRE(result != nullptr);
        CHECK(result->size() == 4); // 3行 + 末尾空行
        CHECK((*result)[0] == "first");
        CHECK((*result)[1] == "");
        CHECK((*result)[2] == "third");
        CHECK((*result)[3] == "");

        std::filesystem::remove(path);
    }

    SUBCASE("non-existent file returns empty")
    {
        std::string filename = "/tmp/non_existent_file_xyz.txt";

        auto result = read_lines_from_file(filename);

        REQUIRE(result != nullptr);
        CHECK(result->empty());
    }
}
