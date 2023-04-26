#pragma once

#include <Zydis/Zydis.h>

#include <string>
#include <vector>

namespace Assembly {

    class Disassembler {
        ZydisMachineMode    _machineMode  = ZydisMachineMode::ZYDIS_MACHINE_MODE_LONG_64;
        ZydisAddressWidth   _addressWidth = ZydisAddressWidth::ZYDIS_ADDRESS_WIDTH_64;
        ZydisFormatterStyle _style        = ZydisFormatterStyle::ZYDIS_FORMATTER_STYLE_INTEL;

    public:
        Disassembler() = default;
        Disassembler(
            ZydisMachineMode machineMode, ZydisAddressWidth addressWidth, ZydisFormatterStyle style
        )
            : _machineMode(machineMode), _addressWidth(addressWidth), _style(style) {}

        Disassembler& Configure(
            ZydisMachineMode machineMode, ZydisAddressWidth addressWidth, ZydisFormatterStyle style
        ) {
            _machineMode  = machineMode;
            _addressWidth = addressWidth;
            _style        = style;
            return *this;
        }

        Disassembler& Configure(ZydisMachineMode machineMode, ZydisAddressWidth addressWidth) {
            _machineMode  = machineMode;
            _addressWidth = addressWidth;
            return *this;
        }

        Disassembler& Configure16() {
            Configure(
                ZydisMachineMode::ZYDIS_MACHINE_MODE_LEGACY_16,
                ZydisAddressWidth::ZYDIS_ADDRESS_WIDTH_16
            );
            return *this;
        }

        Disassembler& Configure32() {
            Configure(
                ZydisMachineMode::ZYDIS_MACHINE_MODE_LONG_COMPAT_32,
                ZydisAddressWidth::ZYDIS_ADDRESS_WIDTH_32
            );
            return *this;
        }

        Disassembler& Configure64() {
            Configure(
                ZydisMachineMode::ZYDIS_MACHINE_MODE_LONG_64,
                ZydisAddressWidth::ZYDIS_ADDRESS_WIDTH_64
            );
            return *this;
        }

        Disassembler& StyleIntel() {
            _style = ZydisFormatterStyle::ZYDIS_FORMATTER_STYLE_INTEL;
            return *this;
        }

        Disassembler& StyleATT() {
            _style = ZydisFormatterStyle::ZYDIS_FORMATTER_STYLE_ATT;
            return *this;
        }

        std::vector<std::string> Disassemble(
            const std::vector<uint8_t>& bytes, uint64_t address = 0x0
        ) {
            ZydisDecoder decoder;
            ZydisDecoderInit(&decoder, _machineMode, _addressWidth);

            ZydisFormatter formatter;
            ZydisFormatterInit(&formatter, _style);

            std::vector<std::string> disassembled_bytes;
            ZydisDecodedInstruction  instruction;
            size_t                   offset = 0;
            while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(
                &decoder, bytes.data() + offset, bytes.size() - offset, &instruction
            ))) {
                char buffer[256];
                ZydisFormatterFormatInstruction(
                    &formatter, &instruction, buffer, sizeof(buffer), address + offset
                );
                disassembled_bytes.push_back(buffer);
                offset += instruction.length;
            }
            return disassembled_bytes;
        }
    };

    std::vector<std::string> Disassemble(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return Disassembler().Disassemble(bytes, address);
    }

    std::vector<std::string> Disassemble16(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return Disassembler().Configure16().Disassemble(bytes, address);
    }

    std::vector<std::string> Disassemble32(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return Disassembler().Configure32().Disassemble(bytes, address);
    }

    std::vector<std::string> Disassemble64(
        const std::vector<uint8_t>& bytes, uint64_t address = 0x0
    ) {
        return Disassembler().Configure64().Disassemble(bytes, address);
    }
}
