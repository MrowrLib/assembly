#pragma once

#include <xbyak/xbyak.h>

#include <functional>
#include <vector>

#define BeginAssembly using namespace Xbyak::util

namespace Assembly {

    typedef Xbyak::CodeGenerator& Code;

    std::vector<uint8_t> Generate(std::function<void(Xbyak::CodeGenerator&)> generator) {
        Xbyak::CodeGenerator code;
        try {
            generator(code);
        } catch (Xbyak::Error err) {
            throw std::runtime_error(err.what());
        } catch (...) {
            throw std::runtime_error("Unknown error generating assembly code");
        }
        auto byteArray = code.getCode();
        return std::vector<uint8_t>(byteArray, byteArray + code.getSize());
    }
}
