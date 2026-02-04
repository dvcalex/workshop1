## Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler (GCC, Clang, MSVC)
- Git

## Building

Clone the repo
```bash
git clone https://github.com/dvcalex/openglworkshop1.git
cd openglworkshop1
```

Build the project
```bash
cmake -B build
cmake --build build
```

Run the executable
```bash
# Windows
build\bin\Debug\openglworkshop1.exe

# Linux/macOS
./build/bin/openglworkshop1
```

## Dependencies

All dependencies are automatically fetched with CMake FetchContent
- GLFW 3.4
- GLEW 2.2.0
- GLM (header-only, included in `vendor` directory)
- stb_image (header-only, included in `vendor` directory)
