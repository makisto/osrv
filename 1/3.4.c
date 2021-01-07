#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//��� ������ � ������ �������� - ./3.4 (������ ����������) > _���_���������_
//������ - gcc 3.4.c -o 3.4
//./test4 1 1 1 1 100000 3 5 > /dev/ttyp1

void sigint_handler(int sig)
{
	/*�������������� ��������� ���� ���������*/
	printf("\033[=7F");
	printf("\033[=0G");
	printf("\033[?25H");
	printf("\033[2J");
	exit(1);
}

int main(int argc, char* argv[])
{
	if (8 > argc)//���� �� ��� ��������� �������
	{
		printf("NOT ENOUGH PARAMETRS\n");
		return -1;
	}

	int x = atoi(argv[1]);//��������� ��������� �� x
	if (x < 0)
	{
		printf("INCORRECT X COORDS!!!\n");
		return -2;
	}

	int y = atoi(argv[2]);//��������� ��������� �� y
	if (y < 0)
	{
		printf("INCORRECT Y COORDS!!!\n");
		return -3;
	}

	int x_dx = atoi(argv[3]);//�������� �������� �� x
	int y_dy = atoi(argv[4]);//�������� �������� �� y

	int speed = atoi(argv[5]);//�������� ������������ (����� � ��)
	if (speed <= 0)
	{
		printf("INCORRECT SPEED!!!\n");
		return -4;
	}

	int symbol_color = atoi(argv[6]);//���� �������
	if (symbol_color < 0 || symbol_color > 7)
	{
		printf("INCORRECT SYMBOL COLOR!!!\n");
		return -5;
	}

	int background_color = atoi(argv[7]);//���� �������
	if (background_color < 0 || background_color > 7)
	{
		printf("INCORRECT BACKGROUND COLOR!!!\n");
		return -6;
	}

	signal(SIGINT, sigint_handler);//��������� ����������� �������

	/*��������� ���������� ���������*/
	printf("\033[?25l");
	printf("\033[=%dF", symbol_color);
	printf("\033[=%dG", background_color);
	printf("\033[2J");
	fflush(stdout);

	for (;;)//�������� �������(���������� � 3.3)
	{
		printf("\033[%d;%dH", x, y);
		printf("A");
		fflush(stdout);
		printf("\033[%d;%dH", x, y);
		printf(" ");
		usleep(speed);
		x += x_dx;
		y += y_dy;
	}

	return 0;
}