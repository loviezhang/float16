#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "float16.h"

void dump_32(const char* prefix, uint32_t v) {
    printf("%s: ", prefix);
    for (int i = 0; i < 32; i++) {
        printf(" %d", (v >> (31-i)) & 1);
    }
    printf("\n");
}

void dump_float(const char* prefix, float v) {
    dump_32(prefix, *((uint32_t*)&v));
}

void dump_16(const char* prefix, uint16_t v) {
    printf("%s: ", prefix);
    for (int i = 0; i < 16; i++) {
        printf(" %d", (v >> (15-i)) & 1);
    }
    printf("\n");
}

void parse_float(float v) {
    printf("value = [%.64f]\n", v);

    uint32_t bits = *(uint32_t*)&v;
    dump_32("bits    ", bits);
    int sign = bits >> 31;
    dump_32("sign    ", sign);
    int exponent = (bits >> 23) & 0xff;
    dump_32("exponent", exponent);
    int fraction = bits & 0x007fffff;
    dump_32("fraction", fraction);

    double r;
    if (exponent == 0) {
        if (fraction == 0) {
            r = 0;
        } else {
            printf("fraction:  %d\n", fraction);
            r = (double)fraction * pow(2, -23) * pow(2, -126);
        }
    } else {
        exponent = exponent - 127;
        printf("exponent:  %d\n", exponent);
        printf("fraction:  %d\n", fraction);
        r = ((double)1 + (double)fraction * pow(2, -23)) * pow(2, exponent);
    }

    if (sign == 1) {
        r = -r;
    }

    printf("r = %.64f\n", r);
}

int main(int argc, char** argv) {
    float a = atof(argv[1]);
    printf("value = [%.8f]\n", a);
    uint16_t a16 = float16(a);
    float c = float32(a16);
    printf("convert = [%.8f]\n", c);

    return 0;
}
