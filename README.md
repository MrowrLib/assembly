# `#include <assembly>`

```cpp
#include <assembly>

void Example() {
    // Generate bytes from assembly-like syntax (provided by xbyak)
    auto bytes = Assembly::GetBytes([](Assembly::Code& code) {
        BeginAssembly;
        code.mov(eax, 0x69);
        code.ret();
    });

    // Disassemble bytes to assembly-like syntax (provided by zydis)
    std::vector<std::string> assemblyText = Assembly::Disassemble64(bytes);
}
```

## Installation

```lua
-- xmake
add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("assembly")
```

```cmake
# CMake/vcpkg (coming soon)
```

## What?

Convenient way to generate and disassemble assembly code.

Also simply a convenient way to use [xbyak](https://github.com/herumi/xbyak) and [zydis](https://github.com/zyantific/zydis).

## Why?

I was frequently using xbyak and zydis in my projects, so I decided to make a very wrapper for them.

## How?

```cpp
#include <assembly>

void Example() {
    auto bytes = Assembly::GetBytes([](Assembly::Code& code) {
        BeginAssembly;
        code.mov(eax, 0x69);
        code.ret();
    });

    // ToHexString from #include <memory_util> - https://github.com/MrowrLib/memory_util.cpp
    std::cout << "Bytes: " << MemoryUtil::ToHexString(bytes) << std::endl;

    // STDOUT
    // Bytes: 0xB8 0x69 0x00 0x00 0x00 0xC3

    auto disassembled = Assembly::Disassemble86(bytes.GetBytes());

    std::cout << "Disassembled: " << std::endl;
    for (auto& instruction : disassembled) {
        std::cout << instruction << std::endl;
    }

    // STDOUT
    // Disassembled:
    // mov eax, 0x69
    // ret
}
```

## License

Use however, no attribution required.

```
BSD Zero Clause License (SPDX: 0BSD)

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
```
