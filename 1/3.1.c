#include <stdio.h>

int main(void)
{
    printf("\033[2J");
    printf("\033[12;34H");//перемещение курсора в центр экрана
    printf("Hello, world!\n");
    return 0;
}