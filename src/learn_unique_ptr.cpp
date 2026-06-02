#include <bits/unique_ptr.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

std::unique_ptr<std::vector<std::string>> read_lines_from_file(std::string& file_name)
{
    std::unique_ptr<std::vector<std::string>> lines(new std::vector<std::string>);
    std::string line;

    std::ifstream file_handle(file_name.c_str());
    while (file_handle.good() && !file_handle.eof()) {
        std::getline(file_handle, line);
        lines->push_back(line);
    }
    file_handle.close();
    return lines;
}

// int main(int argc, char* argv[])
// {
//     std::cout << argv[0] << "\n";
//     std::string filename(argv[1]);
//     auto file_lines = read_lines_from_file(filename);
//     int count = file_lines.get()->size();

//     std::cout << "file name:" << filename << ",containes:" << count << "\n";
// }
