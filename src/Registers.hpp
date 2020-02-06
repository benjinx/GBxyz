#ifndef REGISTERS_HPP
#define REGISTERS_HPP

#include <cstdint>

struct Registers {
    union {
        uint16_t AF;
        struct {
            union {
                uint8_t F;
                struct {
                    uint8_t _ : 4;
                    bool FC : 1; // Carry Flag
                    bool FH : 1; // Half Carry Flag
                    bool FN : 1; // Subtract Flag
                    bool FZ : 1; // Zero Flag
                };
            };
            uint8_t A;
        };
    };

    union {
        uint16_t BC;
        struct {
            uint8_t C;
            uint8_t B;
        };
    };

    union {
        uint16_t DE;
        struct {
            uint8_t E;
            uint8_t D;
        };
    };

    union {
        uint16_t HL;
        struct {
            uint8_t L;
            uint8_t H;
        };
    };

    uint16_t SP;
    uint16_t PC;
};

extern Registers R;

#endif REGISTERS_HPP