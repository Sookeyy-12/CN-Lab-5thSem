#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int a, b;
    printf("Enter a: ");
    scanf("%d", &a);
    printf("Enter b: ");
    scanf("%d", &b);
    printf("Values before swapping:\na: %d\nb: %d\n", a, b);
    swap(&a, &b);
    printf("Values after swapping:\na: %d\nb: %d\n", a, b);
    return 0;
}