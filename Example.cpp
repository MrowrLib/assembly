#include <assembly.h>
#include <memory_util.h>
#include <stdint.h>

#include <iostream>

int main() {
    auto bytes = MemoryUtil::Bytes{Assembly::Generate([](Assembly::Code& code) {
        BeginAssembly;
        code.mov(eax, 0x69);
        code.ret();
    })};

    std::cout << "Bytes: " << bytes.ToHexString() << std::endl;

    auto disassembled = Assembly::Disassemble32(bytes.GetBytes());

    std::cout << "Disassembled: " << std::endl;
    for (auto& instruction : disassembled) {
        std::cout << instruction << std::endl;
    }
}
