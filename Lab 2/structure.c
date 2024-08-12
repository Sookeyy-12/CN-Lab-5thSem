#include <stdio.h>

struct info {
    int roll_no;
    char name[50];
    float CGPA;
};

void set_info(struct info *s) {
    printf("Enter roll number: ");
    scanf("%d", &s->roll_no);
    printf("Enter name: ");
    scanf("%s", &s->name);
    printf("Enter CGPA: ");
    scanf("%f", &s->CGPA);
    printf("Information set successfully!\n");
}

void get_info(struct info *s) {
    printf("Roll number: %d\n", s->roll_no);
    printf("Name: %s\n", s->name);
    printf("CGPA: %f\n", s->CGPA);
}

int main() {
    struct info suket;
    set_info(&suket);
    get_info(&suket);
    return 0;
}