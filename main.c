#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

void box();
void intro();
void join();
void login();
void selectMenu();
void selectShow();
//void details();
//void cancle();
//void ticketing_concert();
void ticketing_gig();

int getKey();

void gotoxy(int x, int y);

void main()
{
	box();
	intro();
	selectMenu();
	//github test
}


void box()
{
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��  <  >                                                                ��  ��  X  ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("��                                                                                 ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

// ȸ������ or �α���
 void intro()
{
	int sel;
	gotoxy(27, 10);
	printf("Ƽ�� ���Ű� �ʿ��� ��, C-Park !\n\n");
	gotoxy(15, 17);
	printf("\t\t\t20214116 ����\n\n\n\n");
	gotoxy(30, 27);
	printf("enter�� ���� �����ϱ�>>>>\n");
	gotoxy(54, 27);
	getch();

	system("cls");
	box();
	gotoxy(27, 10);
	printf("Ƽ�� ���� ���α׷� C-Park�� ���� ���� ȯ���մϴ�!\n\n");
	printf("C-Park�� ó���̽ö�� ȸ��������, �̹� �����ϼ̴ٸ� �α����� �������ּ���.\n\n\n");
	printf("ȸ �� �� ��  :  1 �Է�\n");
	printf("��  ��  ��   :  2 �Է�\n\n");
	printf("�� ȣ �� ��  :  _\b");
	scanf("%d", &sel);

	switch (sel)
	{
	case 1:
		join(); break;
	case 2:
		login(); break;
	}
}

// ȸ������ �Լ�(���� ��������� �����)
void join()
{
	system("cls");
	box();
	gotoxy(27, 10);
	printf("���� ��������� ȸ������ ����\n\n");
	printf("��� �� ���̵� �Է����ּ��� : ");
	printf("��� �� ��й�ȣ�� �Է����ּ��� : ");
	getch();

	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�!\n\n");
	printf("enter�� ������ �α��� ȭ������ �̵��մϴ�.\n");

	login();
}

void login()
{
	system("cls");
	box();
	gotoxy(27, 10);

	char name[10];
	int password[20] = { 0 };
	int i = 0, offset = 0;
	printf("C-Park Ƽ�� ���Ÿ� ���� �α����� ���ּ���.\n\n\n");
	printf("��  ��  ��  :  ");
	scanf("%s", name);	// �ѱ� ����
	printf("\n\n\n�� �� �� ȣ  :  ");
	while (password[offset] = getch() != '\r')
	{
		putch('*');
		offset++;
	}
}

void selectMenu()
{
	box();
	gotoxy(27, 10);

	int menu = 0;
	system("cls");
	printf("C-Park�� ���� ���� ȯ���մϴ�!\n\n\n");
	printf("1. Ƽ �� �� ��\n\n");
	printf("2. �� �� Ȯ ��\n\n");
	printf("3. �� �� �� ��\n\n");
	printf("�̿��Ͻ� �޴��� �������ּ���(��ȣ �Է�) : _\b");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		selectShow(); break;
		/*
	case 2:
		//details(); break;
	case 3:
		//cancle(); break;
		*/
	}
}

void selectShow()
{
	system("cls");
	box();
	gotoxy(27, 10);
	int choice;
	printf("���� �������� ���� ����Ʈ�Դϴ�.\n\n");
	printf("1��  ���̵� BU �ܼ�Ʈ/2021�� 12�� 15�� 20��\n");
	printf("2��  ���� B&U/2021�� 12�� 15�� 20��\n");
	printf("���� �Ͻ� ������ �������ּ���.(��ȣ �Է�) : ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		//ticketing_concert(); break;
	case 2:
		ticketing_gig(); break;
	}
}

// Ű �Է� �ޱ�
int getKey()
{
	if (kbhit() != 0) //Ű �Է��� ��ȿ�ϸ�
	{
		return getch(); //�Է��� Ű ��ȯ
	}
	return 0;
}

// ����Ű �̵�
void move()
{
	int key;
	int inx = 0, iny = 0;
	key = getKey();

	if (key == 0)
		key = ketKey();
	switch (key)
	{
	case 72: // ��
		inx
		break;

	case 80: // �Ʒ�
		break;

	case 75: // ����
		break;

	case 77: // ������
		break;
	}
}
}
/*
void ticketing_concert()
{

}
*/

void ticketing_gig()
{
	system("cls");
	int i, j;
	box();
	gotoxy(27, 10);
	printf("���� B&U �¼� ���� ������\n\n");
	printf("����Ű�� ����Ͽ� Ŀ���� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			printf("��");
		printf("\n");
	}


}
/*
void details();
{

}

void cancle();
{

}
*/

void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}