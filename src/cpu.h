#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef void(*inst_t)();

uint8_t fetch();
void execute(uint8_t op);

#endif // CPU_H