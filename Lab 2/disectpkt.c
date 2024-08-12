#include <stdio.h>

struct pkt {
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};

int main() {
    unsigned int og_num;
    printf("Enter a number: ");
    scanf("%d", &og_num);
    struct pkt p;
    p.ch1 = (og_num & 0xFF000000) >> 24;
    p.ch2[0] = (og_num & 0x00FF0000) >> 16;
    p.ch2[1] = (og_num & 0x0000FF00) >> 8;
    p.ch3 = og_num & 0x000000FF;
    printf("Packet:\nch1: %d\nch2[0]: %d\nch2[1]: %d\nch3: %d\n", p.ch1, p.ch2[0],p.ch2[1], p.ch3);
    unsigned int reconstructed_num = (p.ch1 << 24) | (p.ch2[0] << 16) | (p.ch2[1] << 8) | p.ch3;
    printf("Reconstructed number: %d\n", reconstructed_num);
    return 0;
}