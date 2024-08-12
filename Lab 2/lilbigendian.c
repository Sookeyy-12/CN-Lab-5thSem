#include <stdio.h>

unsigned int reverseEndianness(unsigned char* byte1, unsigned char* byte2, unsigned char* byte3, unsigned char* byte4) {
    printf("Reversed endianness:\n");
    printf("Byte 1: %u\nByte 2: %u\nByte 3: %u\nByte 4: %u\n", *byte4, *byte3, *byte2, *byte1);
    unsigned int rev = (*byte4 << 24) | (*byte3 << 16) | (*byte2 << 8) | *byte1;
    printf("Reversed number: %u\n", rev);
    return rev;
}

void check_endianness() {
    unsigned int test = 1;
    char *byte = (char *)&test;
    if (*byte) {
        printf("The machine is Little Endian.\n");
    } else {
        printf("The machine is Big Endian.\n");
    }
}

int main() {
    check_endianness();
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);
    unsigned char byte1 = (num & 0xFF000000) >> 24;
    unsigned char byte2 = (num & 0x00FF0000) >> 16;
    unsigned char byte3 = (num & 0x0000FF00) >> 8;
    unsigned char byte4 = num & 0x000000FF;
    printf("Byte 1: %u\nByte 2: %u\nByte 3: %u\nByte 4: %u\n", byte1, byte2, byte3, byte4);
    unsigned int reversed = reverseEndianness(&byte1, &byte2, &byte3, &byte4);
}