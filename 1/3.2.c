#include <stdio.h>
#include </root/raw.h>

int main(void)
{
	setraw();

	int c = 0;
	while (c != 50)
	{
		c = getchar();//���� �������
		printf("%c - %d ", (char)c, c);//����� ������� � ��� ����
	}
	/*�������������� ��������� ���� ���������*/
	printf("\033[2J");
	printf("\033[1;1H");
	printf("\033[=7F");
	printf("\033[=0G");

	unsetraw();

	return 0;
}