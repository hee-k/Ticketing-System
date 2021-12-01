#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void intro();
void join(char* name, char* password);
int login(char* name, char* password);
int selectMenu();

int selectShow();
void concert_seating();
void gig_seating();
int booking(int show, int count, struct information* inform, struct information* com);

void details(struct information* com, int count);
//void cancle();

void template();
void popup();
void cursorView();
void gotoxy(int x, int y);

typedef struct information {
	char title[50];		// ���� �̸�
	char date[50];		// ���� ��¥
	char name[20];		// ������
	int row;			// ���� �¼�(��)
	int col;			// ���� �¼�(��)
	int num;			// ���� ��ȣ
} information;

int gigSeat[10][10] = { 0 };
int concertSeat[10][10] = { 0 };

void main()
{
	// ȸ�����Խ� �Է��� ���� ����(�̸�, ���)
	char name[20] = { 0 };
	char password[20] = { 0 };

	int show = 0;		 // selectShow���� ������ ����
	int count = 0;		 // ���� Ƚ��count, ���� ��ȣ
	int menu = 0;		 // �޴� ����
	int re_booking = 0;  // �̹� ���õ� �¼��� �� ��� 1 return

	// ���� �Ϸ�� ����
	information completion[100] = { 0 };
	information concert = { "���̵� BU �ܼ�Ʈ", "2021�� 12�� 15�� 20��", 0, 0, 0, 0 };
	information gig = {"ũ�������� ����", "2021�� 12�� 25�� 20��", 0, 0, 0, 0};

	// ����
	intro();
	// ȸ������
	join(name, password);
	while (1)
	{
		// �α���
		int res = login(name, password);
		if (res == 1)
			break;
	}
	while(1)
	{
		// �Ŵ� ����(����, ���� Ȯ��, ���� ���)
		menu = selectMenu();
		switch (menu)
		{
		// menu1 : ���� ���� �ϱ�
		case 1:
			show = selectShow();
			count++; // ���� Ƚ��++
			switch (show)
			{
			// show1 : �ܼ�Ʈ ����
			case 1:
				// ���� ���� ����(�̸�, ���� Ƚ��)
				strcpy(concert.name, name);
				concert.num = count;

				// Ƽ�� ����(�̹� ���õ� �¼��̸� ���� �Ұ�)
				do {
					concert_seating();
					re_booking = booking(show, count, &concert, completion);
				} while (re_booking == 1);
				break;

			// show2 : ���� ����
			case 2:
				// ���� ���� ����(�̸�, ���� Ƚ��)
				strcpy(gig.name, name);
				gig.num = count;

				// Ƽ�� ����(�̹� ���õ� �¼��̸� ���� �Ұ�)
				do {
					gig_seating();
					re_booking = booking(show, count, &gig, completion);
				} while (re_booking == 1);
				break;
			}
			break;

		// menu2 : ���� ������
		case 2:
			details(completion, count);
			break;
		/*
		// menu3 : ���� ���
		case 3:
			//cancle(); break;
		*/
		case 4:
			printf("C-Park�� �̿����ּż� �����մϴ�.");
			Sleep(2000);
			exit(1);
		
		default : 
			printf("���ڸ� �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���!");
			Sleep(2000);
			continue;
		}
	}
}

// ���α׷� ���� ȭ��
 void intro()
{
	template();
	gotoxy(27, 10);
	printf("Ƽ�� ���Ű� �ʿ��� ��, C-Park !\n\n");
	gotoxy(15, 17);
	printf("\t\t\t20214116 ����\n\n\n\n");
	gotoxy(30, 27);
	printf("enter�� ���� �����ϱ�>>>>\n");
	gotoxy(54, 27);
	getch();
}

 // ȸ������
void join(char *name, char *password)
{
	int offset = 0;

	system("cls");
	template();
	gotoxy(27, 10);
	printf("Ƽ�� ���� ���α׷� C-Park�� ���� ���� ȯ���մϴ�!\n\n");
	gotoxy(27, 12);
	printf("���α׷� ��� ��, ���� ȸ�������� ���ּ���\n\n");
	gotoxy(27, 17);
	printf("������ �̸��� �Է����ּ��� : ");
	scanf("%s", name);
	gotoxy(27, 20);
	printf("��� �� ��й�ȣ�� �Է����ּ��� : ");
	while ((password[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}

	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�!\n\n");
	printf("enter�� ������ �α��� ȭ������ �̵��մϴ�.\n");
	getch();
}

// �α���
int login(char *name, char *password)
{
	char receiveName[20] = { 0 };
	char receivePassword[20] = { 0 };
	int i = 0, offset = 0;

	system("cls");
	template();
	gotoxy(27, 10);
	printf("C-Park Ƽ�� ���Ÿ� ���� �α����� ���ּ���.\n");
	gotoxy(27, 15);
	printf("��    ��  :  ");
	scanf("%s", receiveName);
	gotoxy(27, 17);
	printf("\n\n\n�� �� �� ȣ  :  ");
	while ((receivePassword[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}
	
	int n = strcmp(receiveName, name);
	int p = strcmp(receivePassword, password);

	if (n == 0 && p == 0)
	{
		printf("�α��� ����!");
		Sleep(1000);
		return 1;
	}
		
	else
	{
		printf("�α��ο� �����Ͽ����ϴ�. �ٽ� �õ����ּ���!");
		Sleep(1000);
		return 2;
	}
}

// �޴� ����(����, ���ų���, �������)
int selectMenu()
{
	int menu = 0;

	system("cls");
	template();
	gotoxy(27, 10);

	printf("C-Park�� ���� ���� ȯ���մϴ�!\n\n\n");
	printf("1. Ƽ �� �� ��\n\n");
	printf("2. �� �� Ȯ ��\n\n");
	printf("3. �� �� �� ��\n\n");
	printf("4. ��      ��\n\n");
	printf("�̿��Ͻ� �޴��� �������ּ���(��ȣ �Է�) : _\b");
	
	scanf("%d", &menu);
	return menu;
}

// ���� ����
int selectShow()
{
	int choice;

	system("cls");
	template();
	gotoxy(27, 10);

	printf("���� �������� ���� ����Ʈ�Դϴ�.\n\n\n");
	printf("1��  ���̵� BU �ܼ�Ʈ/2021�� 12�� 15�� 18��\n\n");
	printf("2��  ũ�������� ����/2021�� 12�� 25�� 20��\n\n");
	printf("���� �Ͻ� ������ �������ּ���.(��ȣ �Է�) : ");
	scanf("%d", &choice);
	
	return choice;
}

// ���� ���� �� ���� ���� ����
int booking(int show, int count, struct information *inform, struct information* com)
{
	// �¼� ���� ����
	cursorView();			 // Ŀ�� ����
	int key = 0;			 // �Է� �޴� Ű(����Ű, ����)
	int inx = 30, iny = 13;  // �¼� ���� ��ġ(A�� 1��)
	int bookingRow = 0;		 // ���� �� 
	int bookingCol = 0;		 // ���� ��

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
				switch (show)
				{
					// ����� �ڸ��� ��� �ٽ� ����, ���� �ڸ��� ��� �ٽ� ����(Ŀ�� �˵��� �Ⱥ��̰� �ϱ� ����)
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				}
				iny--;
				if (iny < 13)
					iny = 13;
				break;

			case 80: // �Ʒ�
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				}
				iny++;
				if (iny > 22)
					iny = 22;
				break;

			case 75: // ����
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				}
				inx -= 2;
				if (inx < 30)
					inx = 30;
				break;

			case 77: // ������
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("��") : printf("��");
					break;
				}
				inx += 2;
				if (inx > 48)
					inx = 48;
				break;
			}
		}
	} while (key != 13);

	// ����� �¼� �ӽ� ����(��, �� ����)
	bookingRow = iny - 13;
	bookingCol = (inx - 30) / 2;

	// �̼��� üũ(�̼��¸� ���� �Ұ� -> �缱��)
	if (concertSeat[bookingRow][bookingCol] == 1)
	{
		printf("�̼����Դϴ�.");
		Sleep(500);
		return 1;
	}
	if (gigSeat[bookingRow][bookingCol] == 1)
	{
		printf("�̼����Դϴ�.");
		Sleep(500);
		return 1;
	}
		
	// �¼� �迭�� ��, �� ���� ����
	if (show == 1)
		concertSeat[bookingRow][bookingCol] = 1;
	else if (show == 2)
		gigSeat[bookingRow][bookingCol] = 1;

	// ����ü�� ��, �� ���� �ӽ� ����
	inform->row = bookingRow;
	inform->col = bookingCol;

	// ���� ���� ����(completion)
	strcpy(com[count - 1].title, inform -> title);
	strcpy(com[count - 1].date, inform -> date);
	strcpy(com[count - 1].name, inform -> name);
	com[count - 1].row = inform -> row;
	com[count - 1].col = inform -> col;
	com[count - 1].num = inform -> num;

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
		Sleep(450);
	}

	// ���� ���� ���
	system("cls");
	template();
	gotoxy(30, 7);
	printf("���Ű� �Ϸ�Ǿ����ϴ�!\n");
	gotoxy(20, 13);
	printf("�� �� �� �� �� ��\n");
	gotoxy(20, 15);
	printf("�� �� �� ȣ : T%05d\n", inform->num);
	gotoxy(20, 17);
	printf("��  ��  ��  : %s\n", inform->name);
	gotoxy(20, 19);
	printf("�� �� �� �� : %s\n", inform->title);
	gotoxy(20, 21);
	printf("�� �� �� ¥ : %s\n", inform->date);
	gotoxy(20, 23);
	printf("�� �� �� �� : %c�� %2d��\n", (inform->row) + 65, (inform->col) + 1);
	gotoxy(30, 27);
	printf("enterŰ�� ������ �޴� �������� �̵��մϴ�>>");
	getch();
}

// concert �¼� ���
void concert_seating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(26, 5);
	printf("���̵� BU �ܼ�Ʈ �¼� ���� ������\n\n");
	gotoxy(11, 7);
	printf("����Ű�� ����Ͽ� Ŀ��(��)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");

	// �� �� ���� ���
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf("%2d", i);

	for (i = 0; i < 10; i++)
	{
		gotoxy(26, 13 + i);
		printf("%c", 65 + i);
	}
	printf("\n");

	// ���� ���� �¼� ���
	for (i = 0; i < 10; i++)
	{
		gotoxy(30, 13 + i);
		for (j = 0; j < 10; j++)
		{
			// ����� �ڸ��̸� ��
			if (concertSeat[i][j] == 1)
				printf("��");
			else
				printf("��");
		}
		printf("\n");
	}
}

// gig �¼� ���
void gig_seating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(27, 5);
	printf("ũ�������� ���� ���� ������\n\n");
	gotoxy(11, 7);
	printf("����Ű�� ����Ͽ� Ŀ��(��)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");

	// �� �� ���� ���
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf("%2d", i);

	for (i = 0; i < 10; i++)
	{
		gotoxy(26, 13 + i);
		printf("%c", 65 + i);
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
}

// ���� ����
void details(struct information* com, int count)
{
	system("cls");
	template();
	gotoxy(27, 10);
	printf("�� ���� ���� Ȯ�� ��\n\n");
	for (int i = 0; i < count; i++)
	{
		printf("��%3d��\n", i + 1);
		printf("�� �� �� ȣ : T%05d\n", com[i].num);
		printf("��  ��  ��  : %s\n", com[i].name);
		printf("�� �� �� �� : %s\n", com[i].title);
		printf("�� �� �� ¥ : %s\n", com[i].date);
		printf("�� �� �� �� : %c�� %2d��\n", com[i].row+65, com[i].col+1);
		printf("\n\n");
	}
	printf("enterŰ�� ������ �޴� �������� �̵��մϴ�>>");
	getch();
}

// ���ø� â
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

// �˾� â
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

// Ƽ�� â

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

/*
���� ����� ����
// ȸ������ �Լ�(���� ��������� �����)
void join()
{
	system("cls");
	template();
	gotoxy(27, 10);

	char name[20] = { 0 };
	char password[20] = { 0 };
	printf("���� ��������� ȸ������ ����\n\n");
	printf("��� �� ���̵� �Է����ּ��� : ");
	scanf("%s", name);
	printf("��� �� ��й�ȣ�� �Է����ּ��� : ");
	scanf("%s", password);

	FILE* fp = NULL;

	fp = fopen("user.txt", "w");
	fputs(name, fp);
	fputs(password, fp);

	//���� ���� ���� ��
	if (fp == NULL)
		printf("���� ���⿡ �����߽��ϴ�.\n");

	fclose(fp);

	printf("ȸ�� ������ �Ϸ�Ǿ����ϴ�!\n\n");
	printf("enter�� ������ �α��� ȭ������ �̵��մϴ�.\n");
	getch();

	login();
}

void login()
{
	system("cls");
	template();
	gotoxy(27, 10);

	char name[20] = { 0 };
	char password[20] = { 0 };
	int i = 0, offset = 0;
	printf("C-Park Ƽ�� ���Ÿ� ���� �α����� ���ּ���.\n");
	gotoxy(27, 15);
	printf("��  ��  ��  :  ");
	scanf("%s", name);	// �ѱ� ����
	gotoxy(27, 17);
	printf("\n\n\n�� �� �� ȣ  :  ");
	while (password[offset] = getch() != '\r')
	{
		putch('*');
		offset++;
	}

	FILE* fp = NULL;
	char getName[20];
	char getPassword[20];

	fp = fopen("user.txt", "r");

	fgets(getName, sizeof(getName), fp);
	fgetc('\n', fp);
	fgets(getPassword, sizeof(getPassword), fp);

	fclose(fp);
	int n = strcmp(getName, name);
	int p = strcmp(getPassword, password);

	if (n == 0 && p == 0)
		printf("�α��� ����");
	else
		printf("�α��� ����");
	getch();
}

*/