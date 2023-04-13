#include <stdint.h>

#include <assembly>
#include <iostream>
#include <memory_util>

int main() {
    auto bytes = MemoryUtil::Bytes{Assembly::GetBytes([](Assembly::Code& code) {
        BeginAssembly;
        code.mov(eax, 0x69);
        code.ret();
    })};

    std::cout << "Bytes: " << bytes.ToHexString() << std::endl;

    auto disassembled = Assembly::Disassemble86(bytes.GetBytes());

    std::cout << "Disassembled: " << std::endl;
    for (auto& instruction : disassembled) {
        std::cout << instruction << std::endl;
    }
}
