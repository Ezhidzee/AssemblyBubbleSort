#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    unsigned int len = 1;
    while (!feof(input)) if (fgetc(input) == '\n') len++;
    rewind(input);
    int *nums = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) fscanf(input, "%d", &nums[i]);
    --len;
    FILE *output = fopen("output.txt", "w");
    int c;
    asm(
            "start:\n\t"
            "mov %1, %%r8;"
            "mov %1, %%ebx;"
            "mov %2, %%rdi;"
            "jmp mainLoop;"

            "sort:\n\t"
            "cmp $0, %%ebx;"
            "je mainLoop;"
            "mov (%%rdi), %%eax;"
            "add $4, %%rdi;"
            "mov (%%rdi), %%ecx;"
            "cmp %%ecx, %%eax;"
            "jle bar;"
            "call swap;"
            "jmp sort;"

            "bar:\n\t"
            "dec %%ebx;"
            "jmp sort;"

            "swap:\n\t"
            "mov $1, %%r8;"
            "mov %%eax, (%%rdi);"
            "sub $4, %%rdi;"
            "mov %%ecx, (%%rdi);"
            "add $4, %%rdi;"
            "dec %%ebx;"
            "RET;"

            "retToLoop:\n\t"
            "mov %1, %%ebx;"
            "jmp sort;"

            "decVal:\n\t"
            "cmp $0, %%ebx;"
            "je retToLoop;"
            "dec %%ebx;"
            "sub $4, %%rdi;"
            "jmp decVal;"

            "restoreVars:\n\t"
            "mov %1, %%ebx;"
            "mov $0, %%r8;"
            "jmp decVal;"

            "mainLoop:\n\t"
            "cmp $0, %%r8;"
            "je programEnd;"
            "cmp $1, %%r8;"
            "je restoreVars;"
            "mov $0, %%r8;"
            "jmp sort;"

            "programEnd:\n\t"
            : "=r"(c)
            :"m"(len), "r" (nums)
            );
    for (int i = 0; i < len + 1; ++i) {
        fprintf(output, "%d\n", nums[i]);
        printf("%d ", nums[i]);
    }
}
