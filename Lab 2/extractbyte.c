#include <stdio.h>

int main() {
    printf("Enter a number: ");
    unsigned int num;
    scanf("%d", &num);
    unsigned char byte1 = (num & 0xFF000000) >> 24;
    unsigned char byte2 = (num & 0x00FF0000) >> 16;
    unsigned char byte3 = (num & 0x0000FF00) >> 8;
    unsigned char byte4 = num & 0x000000FF;
    printf("Byte 1: %d\nByte 2: %d\nByte 3: %d\nByte 4: %d\n", byte1, byte2, byte3, byte4);
}