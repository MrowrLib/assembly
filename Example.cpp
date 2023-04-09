#include <Assembly.h>
#include <Memory.h>
#include <StringFormatting.h>
#include <stdint.h>

#include <iostream>

int main() {
    auto bytes = Memory::Bytes{Assembly::GetBytes([](Assembly::Code& code) {
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
