#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "float16.h"

void dump_32(uint32_t v) {
    printf("bits: ");
    for (int i = 0; i < 32; i++) {
        printf(" %d", (v >> (31-i)) & 1);
    }
    printf("\n");
}

void dump_float(float v) {
    dump_32(*((uint32_t*)&v));
}

void dump_16(uint16_t v) {
    printf("bits: ");
    for (int i = 0; i < 16; i++) {
        printf(" %d", (v >> (15-i)) & 1);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    float a = atof(argv[1]);
    printf("value = [%.8f]\n", a);
    dump_float(a);

    uint16_t a16 = float16(a);

    printf("fp16 bits: ");
    dump_16(a16);

    float c = float32(a16);
    printf("c = [%.8f]\n", c);
    dump_float(c);

    return 0;
}
