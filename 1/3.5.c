#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/wait.h>
#include <sys/types.h> 

int main(int argc, char* argv[])
{
    /*Аргументы команды*/
    char *first = "ls";
    char *second = "-l";
    char *third = "/bin";
    char *fourth = "grep";
    char *fifth = "log";

    /*Создание каналов*/
    int fd[2];
    if (pipe(pfd) == -1)
    {
        fprintf(stderr, "Pipe create error\n");
        exit(1);
    }

    /*1 процесс - выполняет ls*/
    switch (fork())
    {
        case -1:
            printf("Proc 1 create error\n");
            exit(1);
        case 0:
            if (close(fd[0]) == -1)
            {
                fprintf(stderr, "Closing pipe 1 error\n");
                exit(1);
            }
            if (fd[1] != 1)
            {
                if (dup2(fd[1], 1) == -1)
                {
                    fprintf(stderr, "Dup2 error\n");
                    exit(1);
                }
                if (close(fd[1]) == -1)
                {
                    fprintf(stderr, "Closing pipe 2 error\n");
                    exit(1);
                }
            }
            execlp(first, first, second, third, 0);
            exit(1);
        default:
            break;
    }

    /*2 процесс - выполняет grep*/
    switch (fork())
    {
        case -1:
            printf("Proc 2 create error\n");
            exit(1);
        case 0:
            if (close(fd[1]) == -1)
            {
                fprintf(stderr, "Closing pipe 2 error\n");
                exit(1);
            }
            if (fd[0] != 0)
            {
                if (dup2(fd[0], 0) == -1)
                {
                    fprintf(stderr, "Dup1 error\n");
                    exit(1);
                }
                if (close(fd[0]) == -1)
                {
                    fprintf(stderr, "Closing pipe 2 error\n");
                    exit(1);
                }
            }
            execlp(fourth, fourth, fifth, 0);
            exit(1);
        default:
            break;
    }

    /*Закрытие дескрипторов*/
    if (close(fd[0]) == -1)
    {
        fprintf(stderr, "Closing pipe 1 error\n");
        exit(1);
    }
    if (close(fd[1]) == -1)
    {
        fprintf(stderr, "Closing pipe 2 error\n");
        exit(1);
    }

    /*Ожидание завершения дочерних процессов*/
    if (wait(NULL) == -1)
    {
        exit(1);
    }
    if (wait(NULL) == -1)
    {
        exit(1);
    }

    return 0;
}