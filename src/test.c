#include "utils.h"

void pts(unsigned short* mem, char* msg) {
    int n = strlen(msg);
    for (int i = 0; i < n; i++) mem[i] = (0b0011010 << 8 | msg[i]);
}