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
//void details();
//void cancle();
//void ticketing_concert();
void ticketing_gig();

void booking(int show, struct information* inform);

void template();
void popup();
void cursorView();
void gotoxy(int x, int y);

typedef struct information {
	char title[50];		// ���� �̸�
	char date[50];		// ���� ��¥
	char name[20];		// ������
	char b_seat[10];	// ���� �¼�
	int num;			// ���� ��ȣ
} information;

int gigSeat[10][10] = { 0 };
int concertSeat[10][10] = { 0 };

void main()
{
	// ȸ�����Խ� �Է��� ���� ����(�̸�, ���)
	char name[20] = { 0 };
	char password[20] = { 0 };

	int show = 0;	// selectShow���� ������ ����
	int count = 0;	// ���� Ƚ��count, ���� ��ȣ

	// ���� �Ϸ�� ����
	information completion[20];
	information gig = {"ũ�������� ����", "2021�� 12�� 25�� 20��", "�̸�", "�¼�", count};
	//information concert = {"���̵� BU �ܼ�Ʈ", "2021�� 12�� 15�� 20��", name, seat, count};

	// ����
	template();
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

	// �Ŵ� ����(����, ���� Ȯ��, ���� ���)
	int menu = selectMenu();
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
			//*p = concert;
			//ticketing_concert(p);
			break;
		// show2 : ���� ����
		case 2:
			//���� ���� ����
			strcpy(gig.name, name);
			gig.num = count;
			
			ticketing_gig();
			booking(show, &gig);

			/*
			//���� ����
			showInform = gig;
			//���� �Ϸ�� ���� ����
			com = completion[count];
			*/

			break;
		}
		break;
	/*
	// menu2 : ���� ������
	case 2:
		details();
		break;
	// menu3 : ���� ���
	case 3:
		//cancle(); break;
	*/
	}
}

// ���α׷� ���� ȭ��
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
	printf("�̿��Ͻ� �޴��� �������ּ���(��ȣ �Է�) : _\b");
	scanf("%d", &menu);
	return menu;
}

int selectShow()
{
	int choice;
	char concert[10];
	char gig[10];

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

// �¼� ����
void booking(int show, struct information *inform)
{
	// �¼� ���� ����
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

	// ����� �¼� ����
	int row = iny - 13;
	int col = (inx - 30) / 2;
	if (show = 1)
		concertSeat[row][col] = 1;
	else if(show = 2)
		gigSeat[row][col] = 1;

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

	// ���� ���� ���
	gotoxy(30, 17);
	printf("���Ű� �Ϸ�Ǿ����ϴ�!\n\n");
	printf("�� �� �� �� �� ��\n");
	printf("�� �� �� �� : %s\n", inform -> title);
	printf("�� �� �� ¥ : %s\n", inform -> date);
	printf("��  ��  ��  : %s\n", inform -> name);
	printf("�� �� �� �� : %s\n", inform -> b_seat);
	printf("�� �� �� ȣ : %d\n", inform -> num);


}
/*
void ticketing_concert()
{

}
*/

void ticketing_gig()
{
	int i, j;

	system("cls");
	template();
	gotoxy(27, 5);
	printf("���� B&U �¼� ���� ������\n\n");
	gotoxy(11, 7);
	printf("����Ű�� ����Ͽ� Ŀ��(��)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");

	// �� �� ���� ���
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