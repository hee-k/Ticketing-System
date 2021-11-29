#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

void intro();
void join();
void login();
int selectMenu();

void selectShow(int count);
//void details();
//void cancle();
//void ticketing_concert();
void ticketing_gig();

void booking(int *seat);

void template();
void popup();
void cursorView();
void gotoxy(int x, int y);

typedef struct information
{
	char title[50]; // ���� �̸�
	char date[50];  // ���� ��¥
	char name[20];  // ������
	char seat[10];  // ���� �¼�
	int num;		// ���� ��ȣ	
} info;

void main()
{
	int count = 0;
	template();
	intro();
	int menu = selectMenu();
	switch (menu)
	{
	case 1:
		selectShow(count);
		count++;
		break;
		/*
	case 2:
		//details(); break;
	case 3:
		//cancle(); break;
		*/
	}
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
	template();
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
	template();
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
	template();
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

int selectMenu()
{
	template();
	gotoxy(27, 10);

	int menu = 0;
	system("cls");
	printf("C-Park�� ���� ���� ȯ���մϴ�!\n\n\n");
	printf("1. Ƽ �� �� ��\n\n");
	printf("2. �� �� Ȯ ��\n\n");
	printf("3. �� �� �� ��\n\n");
	printf("�̿��Ͻ� �޴��� �������ּ���(��ȣ �Է�) : _\b");
	scanf("%d", &menu);
	return menu;
}

void selectShow(int count)
{
	system("cls");
	template();
	gotoxy(27, 10);
	int choice;
	info concert[10];
	info gig[10];

	printf("���� �������� ���� ����Ʈ�Դϴ�.\n\n");
	printf("1��  ���̵� BU �ܼ�Ʈ/2021�� 12�� 15�� 18��\n");
	printf("2��  ũ�������� ����/2021�� 12�� 25�� 20��\n");
	printf("���� �Ͻ� ������ �������ּ���.(��ȣ �Է�) : ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		//ticketing_concert(); break;
	case 2:
		//gig[count] = {"ũ�������� ����", "2021�� 12�� 25�� 20��", "ȫ�浿", "A31", 0001};
		ticketing_gig();
		break;
	}
}

// �¼� ����
void booking(int *seat)
{
	cursorView(); // Ŀ�� ����
	int key = 0;
	int inx = 30, iny = 13;
	do
	{
		gotoxy(inx, iny);
		printf("��\b\b");
		key = getch();
		if (key == 224)
		{
			key = getch();
			switch (key)
			{
			case 72: // ��
				gotoxy(inx, iny);
				printf("��");
				iny--;
				if (iny < 13)
					iny = 13;
				break;

			case 80: // �Ʒ�
				gotoxy(inx, iny);
				printf("��");
				iny++;
				if (iny > 22)
					iny = 22;
				break;

			case 75: // ����
				gotoxy(inx, iny);
				printf("��");
				inx -= 2;
				if (inx < 30)
					inx = 30;
				break;

			case 77: // ������
				gotoxy(inx, iny);
				printf("��");
				inx += 2;
				if (inx > 48)
					inx = 48;
				break;
			}
		}
	} while (key != 13);
	
	seat[iny-13, (inx-30)/2] = 1;

	// ������ ȭ��
	for (int i = 0; i < 5; i++)
	{
		system("cls");
		template();
		gotoxy(23, 7);
		printf("\n\t\t\t���� ���Դϴ�. . ��� ��ٷ��ּ���. .\t");

		gotoxy(25, 12);
		for (int j = 0; j < 5; j++) {
			if (j <= i)
				printf("��\t");
			else
				printf("��\t");
		}
		Sleep(500);
	}
	gotoxy(30, 17);
	// ���� ���� ����ü�� �����ϱ�
	printf("���Ű� �Ϸ�Ǿ����ϴ�!\n\n");
	printf("�� �� �� �� �� ��\n");
	printf("�� �� �� �� : \n");
	printf("�� �� �� ¥ : \n");
	printf("�� �� �� �� : \n");
	printf("��  ��  ��  : \n");
	printf("�� �� �� �� : \n");

	return seat;
}
/*
void ticketing_concert()
{

}
*/

void ticketing_gig()
{
	system("cls");
	int gigSeat[10][10] = { 0 };
	int i, j;
	template();
	gotoxy(27, 5);
	printf("���� B&U �¼� ���� ������\n\n");
	gotoxy(11, 7);
	printf("����Ű�� ����Ͽ� Ŀ��(��)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");

	// �� �� ���
	gotoxy(30, 11);
	for (i = 0; i < 10; i++)
		printf(" %c", 65 + i);

	for (i = 1; i < 11; i++)
	{
		gotoxy(26, 12 + i);
		printf("%2d", i);
	}
	printf("\n");

	// ���� ���� �¼� ���
	for (i = 0; i < 10; i++)
	{
		gotoxy(30, 13 + i);
		for (j = 0; j < 10; j++)
		{
			// ����� �ڸ��̸� ��
			if (gigSeat[i][j] == 1)
				printf("��");
			else
				printf("��");
		}
		printf("\n");
	}
	booking(gigSeat);
}
/*
void details();
{

}

void cancle();
{

}
*/

void template()
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

void popup()
{
	gotoxy(16, 7);
	printf("��������������������������������������������������������������������������������������������������������������������\n");
	gotoxy(16, 8);
	printf("��  <  >                                       ��  ��  X  ��\n");
	gotoxy(16, 9);
	printf("��������������������������������������������������������������������������������������������������������������������\n");
	gotoxy(16, 10);
	printf("��                                                        ��\n");
	gotoxy(16, 11);
	printf("��                                                        ��\n");
	gotoxy(16, 12);
	printf("��                                                        ��\n");
	gotoxy(16, 13);
	printf("��                                                        ��\n");
	gotoxy(16, 14);
	printf("��                                                        ��\n");
	gotoxy(16, 15);
	printf("��                                                        ��\n");
	gotoxy(16, 16);
	printf("��                                                        ��\n");
	gotoxy(16, 17);
	printf("��                                                        ��\n");
	gotoxy(16, 18);
	printf("��������������������������������������������������������������������������������������������������������������������\n");
}

// Ŀ�� ���� or ���� <windows.h>
void cursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
	cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ��� ��ġ ���� <window.h>
void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}