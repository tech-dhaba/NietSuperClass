//program to find the number of set bits in a number in its binary representation

#include <stdio.h>

int popcount(unsigned int x) {
    // Count the number of set bits in x
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x3F;
}

int main() {
    unsigned int num = 0b11111111; // Example number
    printf("Popcount of %u: %d\n", num, popcount(num));
    return 0;
}

