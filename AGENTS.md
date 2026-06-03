# AGENTS.md

## Build System

- **CMake** with **Unix Makefiles** generator on **Linux** (GCC 14.2.0 via `/usr/bin/g++`)
- C++ standard: **C++20**
- Presets defined in `CMakePresets.json`

### Setup (first time)

```bash
git submodule update --init --recursive
```

System dependencies must be installed before building:
- `spdlog` (e.g., `sudo apt install libspdlog-dev` on Debian/Ubuntu)

### Build commands

```bash
# Configure
cmake --preset default

# Build
cmake --build --preset debug

# Run the app
./build/src/my_app
```

### Tests

Tests use the **doctest** framework (submodule at `third_party/doctest/`).

```bash
# Build & run all tests
cmake --build --preset debug
cd build && ctest --output-on-failure
```

Available test targets:
- `test_math_utils` — tests for `math_utils` (via `doctest::doctest_with_main`)
- `test_read_lines` — read-line utilities (via `doctest::doctest_with_main`, includes `learn_unique_ptr.cpp`)

## Code Style

- **4-space indent**, LF line endings, UTF-8, trailing whitespace trimmed — see `.editorconfig`
- **clang-format**: Microsoft-based style with **left pointer alignment** (`int* p`), see `.clang-format`
- `.gitattributes` forces LF line endings for all files

## Dependencies

| Dependency     | Type         | CMake Target                |
| -------------- | ------------ | --------------------------- |
| fmt            | submodule    | `fmt::fmt`                  |
| cxxopts        | submodule    | (not yet linked)            |
| hical          | submodule    | (not yet linked)            |
| cpp-httplib    | submodule    | `cpp_httplib` (INTERFACE)   |
| doctest        | submodule    | `doctest::doctest_with_main` / `doctest::doctest` |
| spdlog         | system       | `spdlog::spdlog`            |

## Architecture

```
learn-cpp/
├── src/
│   ├── CMakeLists.txt       — builds my_app + math_utils library
│   ├── main.cpp             — entrypoint, uses spdlog + fmt + math_utils
│   ├── math_utils.h/.cpp    — utility library (e.g. add function)
│   └── learn_unique_ptr.cpp — shared source compiled into test_read_lines
├── tests/
│   ├── CMakeLists.txt       — test targets using doctest
│   ├── test_math_utils.cpp  — tests for math_utils
│   └── test_read_lines.cpp  — tests for read-line logic
├── third_party/
│   ├── CMakeLists.txt       — aggregates all submodules, disables their tests
│   ├── cpp-httplib/         — header-only HTTP library (INTERFACE target)
│   ├── cxxopts/             — command-line option parser
│   ├── doctest/             — header-only test framework
│   ├── fmt/                 — formatting library
│   └── hical/               — (not yet linked)
├── CMakeLists.txt           — root build file
└── CMakePresets.json        — GCC 14.2.0 debug preset
```

- Build output goes to `build/` (gitignored)
- `compile_commands.json` is generated at `build/compile_commands.json`

## Plan Mode

When exiting Plan mode, auto-save the plan to `.opencode/plans/<YYYY-MM-DD>-<short-title>.md`.
Create the `.opencode/plans/` directory if it does not exist. The plan file should contain the
goal, approach, and steps planned, suitable for resuming the task later.
