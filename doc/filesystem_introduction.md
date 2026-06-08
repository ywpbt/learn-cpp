## `std::filesystem` 主要解决什么问题？

在 C++17 之前，C++ 标准库**没有跨平台的文件系统操作**能力（比如判断文件是否存在、创建目录、遍历文件夹等）。开发者不得不使用平台 API（Windows 的 `GetFileAttributes`、Linux 的 `stat` / `opendir`）或者依赖第三方库（如 Boost.Filesystem）。

`std::filesystem` 正是为解决这些问题而引入的，它提供了：

- **可移植性** – 同一份代码在 Windows、Linux、macOS 上都能运行。
- **类型安全** – 使用 `std::filesystem::path` 类型表示路径，避免字符串拼接的错误。
- **常用文件系统操作** – 检查文件状态、创建/删除/复制/重命名文件与目录、递归遍历目录等。
- **错误处理** – 支持异常或 `std::error_code` 返回。

它不是用来“读文件内容”的，而是用来操作**文件系统本身**（路径、属性、目录结构）。

---

## 包含哪些主要功能？

| 类别 | 函数/类举例 |
|------|-------------|
| **路径处理** | `path::string()`、`path::extension()`、`path::stem()`、`operator/`、`relative()`、`absolute()` |
| **文件状态与属性** | `exists()`、`is_directory()`、`is_regular_file()`、`file_size()`、`last_write_time()`、`permissions()` |
| **目录操作** | `create_directory()`、`create_directories()`、`remove()`、`remove_all()`、`rename()`、`copy()` |
| **目录迭代** | `directory_iterator`（单层）、`recursive_directory_iterator`（递归） |
| **空间信息** | `space()`（返回总空间、剩余空间等） |
| **当前路径** | `current_path()`（获取/设置） |

---

## 与文件流库（`fstream`）有功能重叠吗？

**几乎没有重叠**，它们解决的是完全不同的需求：

| 对比维度 | `std::filesystem` | 文件流 (`ifstream`/`ofstream`/`fstream`) |
|----------|-------------------|------------------------------------------|
| **核心目的** | **文件系统操作**（路径、属性、目录） | **文件内容读写**（字节、字符、格式化数据） |
| **能否打开文件？** | 不能（打开操作不是它的职责） | 能，通过 `open()` / 构造函数 |
| **能否读写内容？** | 不能（`file_size` 是查询大小，不是读取内容） | 能，支持 `<<`、`>>`、`getline`、`read`、`write` |
| **常见操作** | `copy()`、`rename()`、`remove()`、`create_directory()` | `open()`、`close()`、`seekg()`、`tellp()`、读写数据 |
| **元数据** | 提供 `file_size`、`last_write_time`、`permissions` | 不涉及 |

两者经常**配合使用**：先用 `std::filesystem` 检查文件是否存在或获取大小，再打开 `fstream` 读/写内容。例如：

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    fs::path p = "data.txt";
    if (fs::exists(p) && fs::file_size(p) > 0) {
        std::ifstream fin(p);
        std::string content;
        std::getline(fin, content);
        std::cout << content << '\n';
    }
}
```

所以它们是**互补**的关系，「文件系统库」这个名字可能会让人误解为又一个文件处理库，但它的定位非常明确：操作文件**系统**；而 `fstream` 操作文件中的**数据**。
