#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void intro();							// ���α׷� ���� ȭ��(ù ȭ��)
void join(char* name, char* password);  // ȸ������
int login(char* name, char* password);  // �α���
int selectMenu(char* name);				// �޴� ����(����, ���ų���, �������)

int selectShow();	   // ���� ����(1. �ܼ�Ʈ, 2. ����)
void concertSeating(); // �ܼ�Ʈ �¼� ���
void gigSeating();	   // ���� �¼� ���
int booking(int show, int count, struct information* inform, struct information* com); // ���� ���� �� ���� ���� ����

void details(struct information* com, int count); // ���� ����
void cancle(struct information* com, int count);  // ���� ���
void nonDetails();								  // ���� ������ ���� ���

void game(int* count, struct information* gig, struct information* com); // �̱� ����(���� 2ȸ ���ึ�� ����)
void circle(int who);	// (���ӿ�) ���׶�� ���
void triangle(int who); // (���ӿ�) ���� ���
void square(int who);	// (���ӿ�) �׸� ���

void template();			// ���α׷� �⺻ ������(������Ʈ â ���ø�)
void popup();				// �˾� â
void ticketScreen();		// Ƽ�� â
void cursorView(int n);		// Ŀ�� ���� or ����
void gotoxy(int x, int y);  // ��� ��ġ ����

typedef struct information {
	char title[50];		// ���� �̸�
	char date[50];		// ���� ��¥
	char name[20];		// ������
	int row;			// ���� �¼�(��)
	int col;			// ���� �¼�(��)
	int num;			// ���� ��ȣ
} information;

int concertSeat[10][10] = { 0, };// �ܼ�Ʈ ����� �¼� ����
int gigSeat[10][10] = { 0, };	// ���� ����� �¼� ����
int total_count = 0;			// ��ȿ ���� Ƚ�� üũ(��ҵ� Ƽ�� ����)

void main()
{
	system("color F0"); // �ܼ�â ����(���)
	system("title Ƽ�� ���Ű� �ʿ��� ��, Ticket-C ! (20214116 ����)"); // �ܼ�â ����

	// ȸ�����Խ� �Է��� ���� ����(�̸�, ���)
	char name[20] = { 0 };
	char password[20] = { 0 };

	int show = 0;		 // selectShow���� ������ ����
	int count = 0;		 // �� ���� Ƚ�� == information.num, ���� ��ȣ
	int menu = 0;		 // �޴� ����
	int re_booking = 0;  // �̹� ���õ� �¼��� �� ��� 1 return �� booking�� ������

	// ���� �Ϸ�� ����
	information completion[100] = { 0 };
	information concert = { "���̵� BU �ܼ�Ʈ", "2021�� 12�� 15�� 20��", 0, 0, 0, 0 };
	information gig = { "ũ�������� ����", "2021�� 12�� 25�� 20��", 0, 0, 0, 0 };

	// ����
	intro();
	// ȸ������
	join(name, password);
	// ���� ���� ����(�̸�)
	strcpy(concert.name, name);
	strcpy(gig.name, name);

	while (1)
	{
		// �α���
		int res = login(name, password);
		if (res == 1)
			break;
	}
	while (1)
	{
		// �Ŵ� ����(����, ���� Ȯ��, ���� ���)
		menu = selectMenu(name);
		switch (menu)
		{
			// menu1 : ���� ���� �ϱ�
		case 1:
			show = selectShow();
			count++, total_count++; // ���� Ƚ��++
			switch (show)
			{
				// show1 : �ܼ�Ʈ ����
			case 1:
				// ���� ���� ����(���� Ƚ��)
				concert.num = count;

				// Ƽ�� ����(�̹� ���õ� �¼��̸� ���� �Ұ�)
				do {
					concertSeating();
					re_booking = booking(show, count, &concert, completion);
				} while (re_booking == 1);
				break;

				// show2 : ���� ����
			case 2:
				// ���� ���� ����(���� Ƚ��)
				gig.num = count;

				// Ƽ�� ����(�̹� ���õ� �¼��̸� ���� �Ұ�)
				do {
					gigSeating();
					re_booking = booking(show, count, &gig, completion);
				} while (re_booking == 1);
				break;
			}
			if (total_count % 2 == 0)
			{
				strcpy(gig.name, name);
				game(&count, &gig, completion);
			}
			break;

			// menu2 : ���� ����
		case 2:
			details(completion, count);
			if (total_count != 0)
			{
				printf("\n\n\n\t\t\033[0;34m   enterŰ�� ������ �޴� �������� �̵��մϴ�>>\033[0m");
				getch();
			}
			break;

			// menu3 : ���� ���
		case 3:
			cancle(completion, count);
			if (total_count != 0)
			{
				printf("\n\n\n\t\t\033[0;34m   enterŰ�� ������ �޴� �������� �̵��մϴ�>>\033[0m");
				getch();
			}
			break;

			// menu4 : ���α׷� ����
		case 4:
			cursorView(0);
			gotoxy(26, 27); printf("\033[0;34mTicket-C �� �̿����ּż� �����մϴ�.\033[0m\n\n");
			Sleep(2000);
			exit(1);

		default:
			cursorView(0);
			gotoxy(24, 27); printf("\033[0;31m�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���!\033[0m");
			Sleep(2000);
			continue;
		}
	}
}

// ���α׷� ���� ȭ��
void intro()
{
	template();
	cursorView(0);
	gotoxy(27, 10); printf("Ƽ�� ���Ű� �ʿ��� ��, Ticket-C !\n\n");
	gotoxy(35, 19); printf("20214116 ����\n\n\n\n");
	gotoxy(30, 27); printf("enter�� ���� �����ϱ�>>>>\n");
	getch();
}

// ȸ������
void join(char* name, char* password)
{
	int offset = 0;

	system("cls");
	template();
	cursorView(1);
	gotoxy(17, 10); printf("Ƽ�� ���� ���α׷� Ticket-C �� ���� ���� ȯ���մϴ�!\n\n");
	gotoxy(17, 13); printf("����, ��Ȱ�� Ƽ�� ���Ÿ� ���� ȸ�������� �������ּ���.\n\n");
	gotoxy(26, 17); printf("����    �� �� �Է����ּ��� : ");
	scanf("%s", name);
	gotoxy(26, 20); printf("���й�ȣ �� �Է����ּ��� : ");
	while ((password[offset] = getch()) != '\r')
	{
		putch(password[offset]);
		offset++;
	}
	cursorView(0);
	gotoxy(8, 27); printf("\033[0;34mȸ�� ������ �Ϸ�Ǿ����ϴ�! enter�� ������ �α��� ȭ������ �̵��մϴ�.\033[0m\n\n\n");
	getch();
}

// �α���
int login(char* name, char* password)
{
	char receiveName[20] = { 0 };
	char receivePassword[20] = { 0 };
	int i = 0, offset = 0;

	system("cls");
	template();
	cursorView(1);
	gotoxy(22, 10); printf("Ticket-C Ƽ�� ���Ÿ� ���� �α����� ���ּ���.\n");
	gotoxy(30, 17); printf("����      ��  :  ");
	scanf("%s", receiveName);

	gotoxy(30, 20); printf("��� �� �� ȣ :  ");
	while ((receivePassword[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}
	// ������ 0 ��ȯ
	int n = strcmp(receiveName, name);
	int p = strcmp(receivePassword, password);

	cursorView(0);

	if (n == 0 && p == 0)
	{
		gotoxy(31, 27); printf("\033[0;34m * * �α��� ����! * * \033[0m\n\n\n");
		Sleep(1000);
		return 1;
	}

	else
	{
		gotoxy(20, 27); printf("\033[0;31m�α��ο� �����Ͽ����ϴ�. �ٽ� �õ����ּ���!\033[0m\n\n");
		Sleep(2000);
		return 2;
	}
}

// �޴� ����(����, ���ų���, �������)
int selectMenu(char* name)
{
	int menu = 0;

	system("cls");
	template();
	cursorView(1);
	gotoxy(23, 10); printf("%s��, Ticket-C �� ���� ���� ȯ���մϴ�!\n\n\n", name);
	gotoxy(35, 14); printf("1. Ƽ �� �� ��\n\n");
	gotoxy(35, 16); printf("2. �� �� �� ��\n\n");
	gotoxy(35, 18); printf("3. �� �� �� ��\n\n");
	gotoxy(35, 20); printf("4. ��       ��\n\n");
	gotoxy(23, 24); printf("�̿��Ͻ� �޴��� �������ּ���(��ȣ �Է�) : _\b");

	scanf("%d", &menu);
	return menu;
}

// ���� ����
int selectShow()
{
	int choice;

	system("cls");
	template();
	cursorView(1);

	gotoxy(27, 10); printf("���� �������� ���� ����Ʈ�Դϴ�.\n\n\n");
	gotoxy(20, 15); printf("1��\t���̵� BU �ܼ�Ʈ (2021�� 12�� 15�� 18��)\n\n");
	gotoxy(20, 18); printf("2��\tũ�������� ����  (2021�� 12�� 25�� 20��)\n\n");
	gotoxy(22, 24); printf("���� �Ͻ� ������ �������ּ���.(��ȣ �Է�) : ");
	scanf("%d", &choice);

	return choice;
}

// ���� ���� �� ���� ���� ����
int booking(int show, int count, struct information* inform, struct information* completion)
{
	cursorView(0);

	// �¼� ���� ����
	int key = 0;			 // �Է� �޴� Ű(����Ű, ����)
	int inx = 30, iny = 13;  // �¼� ���� ��ġ(A�� 1��)
	int bookingRow = 0;		 // ���� �� 
	int bookingCol = 0;		 // ���� ��

	// �ܼ�Ʈ �ڵ� ���Ÿ� ���� ���� ���� ���
	int r = 0;
	int c = 0;
	// rr, cc : r, c�� ����ؼ� gotoxy�� �� ��
	int rr = 0, cc = 0;

	do
	{
		gotoxy(inx, iny);
		printf("\033[1;31m��\033[0m\b\b"); // ������ ��Ʈ�� Ŀ�� ǥ��
		key = getch();
		if (key == 224)
		{
			// �ܼ�Ʈ�� �������� �¼� �����(���ŵ�)
			if (show == 1)
			{
				srand((unsigned int)time(NULL));
				r = rand() % 10;
				c = rand() % 10;
				concertSeat[r][c] = 1;
				cc = 2 * c + 30;
				rr = r + 13;

				gotoxy(cc, rr);
				if (rr < 13)
					rr = 13;
				else if (rr > 22)
					rr = 22;
				else if (cc < 30)
					cc = 30;
				else if (cc > 48)
					cc = 48;
				(concertSeat[r][c] == 1) ? printf("��") : printf("��");
			}

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

	// ����� �¼��� ��, �� ������ �ֻܼ� ��ġ ����
	bookingRow = iny - 13;
	bookingCol = (inx - 30) / 2;

	// �̼��� üũ(�̼��¸� ���� �Ұ� -> �缱��)
	if ((show == 1 && concertSeat[bookingRow][bookingCol] == 1 || show == 2 && gigSeat[bookingRow][bookingCol] == 1))
	{
		system("cls");
		template();
		popup();
		gotoxy(27, 16); printf("�̹� �ٸ� ����� ������ �¼��Դϴ�.");
		Sleep(1000);
		return 1;
	}

	// �¼� �迭�� ��, �� ���� ����
	if (show == 1)
		concertSeat[bookingRow][bookingCol] = 1;
	else if (show == 2)
		gigSeat[bookingRow][bookingCol] = 1;

	// ����ü�� ��, �� ���� ����
	inform->row = bookingRow;
	inform->col = bookingCol;

	// ���� ���� ���� ����(completion)
	strcpy(completion[count].title, inform->title);
	strcpy(completion[count].date, inform->date);
	strcpy(completion[count].name, inform->name);
	completion[count].row = inform->row;
	completion[count].col = inform->col;
	completion[count].num = inform->num;

	// ������ ȭ��
	for (int i = 0; i < 5; i++)
	{
		system("cls");
		template();
		gotoxy(23, 11);
		printf("\n\t\t\t���� ���Դϴ�. . ��� ��ٷ��ּ���. .\t");

		gotoxy(25, 17);
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
	gotoxy(32, 7); printf("\033[0;32m���Ű� �Ϸ�Ǿ����ϴ� !\033[0m\n");
	gotoxy(34, 11); printf("�� �� �� �� �� ��\n");
	gotoxy(27, 14); printf("�� �� �� ȣ : T%05d\n", inform->num);
	gotoxy(27, 16); printf("��  ��  ��  : %s\n", inform->name);
	gotoxy(27, 18); printf("�� �� �� �� : %s\n", inform->title);
	gotoxy(27, 20); printf("�� �� �� ¥ : %s\n", inform->date);
	gotoxy(27, 22); printf("�� �� �� �� : %c�� %2d��\n", (inform->row) + 65, (inform->col) + 1);
	gotoxy(22, 26); printf("enterŰ�� ������ �޴� �������� �̵��մϴ�>>");
	getch();
	return 0;
}

// �ܼ�Ʈ �¼� ���
void concertSeating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(26, 5); printf("���̵� BU �ܼ�Ʈ �¼� ���� ������\n\n");
	gotoxy(11, 7); printf("����Ű�� ����Ͽ� Ŀ��(\033[1;31m��\033[0m)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");
	gotoxy(16, 26); printf("���� ������ �¼� : ��\t\t���� �Ұ����� �¼� : ��");

	// �� �� ���� ���
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf(" %d", i);

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

// ���� �¼� ���
void gigSeating()
{
	int i, j;

	system("cls");
	template();

	gotoxy(28, 5); printf("ũ�������� ���� ���� ������\n\n");
	gotoxy(11, 7); printf("����Ű�� ����Ͽ� Ŀ��(\033[1;31m��\033[0m)�� �����Ͻ� �¼��� ���� ���͸� �����ּ���\n\n");
	gotoxy(16, 26); printf("���� ������ �¼� : ��\t\t���� �Ұ����� �¼� : ��");

	// �� �� ���� ���
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf(" %d", i); // ���� �ȸ´� �κ� �����ϱ�

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

// ���� ����(��� ���� �Ϸ�)
void details(struct information* completion, int count)
{
	int ticket_y = 4;				// Ƽ�� â ��� ��ġ
	int detail_x = 28, detail_y = 6;// Ƽ�� ���� ��� ��ġ
	int num_x = 4, num_y = 8;		// Ƽ�� ���� ��ȣ ��� ��ġ

	// ���� ������ ������
	if (total_count == 0)
	{
		nonDetails();
		return;
	}

	system("cls");
	cursorView(0);
	gotoxy(34, 2); printf("\033[0;34m��  ��  ��  ��  ��  ��\033[0m\n");
	for (int i = 0; i < count; i++)
	{
		// ��ҵ� Ƽ���� ��� X
		if (completion[i + 1].num == -1)
			continue;

		// Ƽ�� â ���
		gotoxy(1, ticket_y); ticketScreen();
		// Ƽ�� ���� ���(Ƽ�� ���� ->  ������ȣ)
		gotoxy(num_x, num_y);	 printf("Ƽ�� ���� ��ȣ");
		gotoxy(num_x, num_y + 3); printf("%7d", completion[i + 1].num);
		// Ƽ�� ���� ���(Ƽ�� ������ ->  ���� ����)
		gotoxy(detail_x, detail_y);		printf("��  ��  ��  ȣ  :  T%05d\n", completion[i + 1].num);
		gotoxy(detail_x, detail_y + 2); printf("��    ��    ��  :  %s\n", completion[i + 1].name);
		gotoxy(detail_x, detail_y + 4); printf("��  ��  ��  ��  :  %s\n", completion[i + 1].title);
		gotoxy(detail_x, detail_y + 6); printf("��  ��  ��  ¥  :  %s\n", completion[i + 1].date);
		gotoxy(detail_x, detail_y + 8); printf("��  ��  ��  ��  :  %c�� %2d��\n", completion[i + 1].row + 65, completion[i + 1].col + 1);
		ticket_y += 13; detail_y += 13; num_y += 13;
	}
}

// ���� ���
void cancle(struct information* completion, int count)
{
	int i = 0, cancle_number = 0;
	int j = 0; // do-while Ż���(��ȿ���� ���� ���� üũ�� ���)
	char str1[50] = { 0 };
	char str2[] = "ũ�������� ����";

	// ���� ������ ������
	if (total_count == 0)
	{
		nonDetails();
		return;
	}

	// Ƽ�� �󼼳��� ���
	do
	{
		j = 0;
		// Ƽ�� �󼼳��� ���
		details(completion, count);
		cursorView(1);
		printf("\n\n\n\t\t\033[0;34m   ��� �� Ƽ���� ���� ��ȣ�� �Է����ּ��� : _\b\033[0m");
		scanf("%d", &cancle_number);

		if (cancle_number < 1 || cancle_number > count)
		{
			printf("\n\n\t\t\033[0;31m   ��ȿ���� ���� �����Դϴ�. �ٽ� �Է��ϼ���.\033[0m");
			Sleep(1500);
			j = 1;
			continue;
		}

		for (i = 1; i <= count; i++)
		{
			if ((cancle_number == i) && (completion[i].num == -1))
			{
				printf("\n\n\t\t\033[0;31m   ��ȿ���� ���� �����Դϴ�. �ٽ� �Է��ϼ���.\033[0m");
				Sleep(1500);
				j = 1;
				break;
			}

			if (completion[i].num == cancle_number)
			{
				system("cls");
				template();
				cursorView(0);
				gotoxy(8, 7);  printf("\033[0;32m��� �� Ƽ���� ������ Ȯ�����ּ���. enterŰ�� ������ Ƽ���� ��ҵ˴ϴ�.\033[0m\n");
				gotoxy(34, 11); printf("�� Ƽ �� Ȯ �� ��\n\n");
				gotoxy(27, 14); printf("�� �� �� ȣ : T%05d\n", completion[i].num);
				gotoxy(27, 16); printf("��  ��  ��  : %s\n", completion[i].name);
				gotoxy(27, 18); printf("�� �� �� �� : %s\n", completion[i].title);
				gotoxy(27, 20); printf("�� �� �� ¥ : %s\n", completion[i].date);
				gotoxy(27, 22); printf("�� �� �� �� : %c�� %2d��\n", completion[i].row + 65, completion[i].col + 1);

				// completion�� num�� �ش��ϴ� title ���ڿ��� ���ؼ�, �¼��� �࿭ ������ 0���� ������ֱ�
				strcpy(str1, completion[i].title);
				(strcmp(str1, str2) == 0) ? (gigSeat[completion[i].row][completion[i].col]) = 0 : (concertSeat[completion[i].row][completion[i].col] = 0);
				// ������ completion�� num���� -1 �ֱ�
				completion[i].num = -1;
				total_count--;
			}
		}
	} while (j != 0);
	getch();

	system("cls");
	template();
	popup();

	int m = 0, n = 3;
	for (m = 0; m < 3; m++, n--)
	{
		gotoxy(32, 15); printf("Ƽ���� ��ҵǾ����ϴ�!\n\n");
		gotoxy(24, 18); printf("%d�� �� ���� ���� Ȯ�� �������� �̵��մϴ�.\n", n);
		Sleep(800);
	}
	details(completion, count);
}

// ���ų����� ���� ���
void nonDetails()
{
	system("cls");
	template();
	popup();
	gotoxy(34, 15); printf("���� ������ �����ϴ�.\n");
	gotoxy(22, 18); printf("enterŰ�� ������ �޴� �������� �̵��մϴ�>>");
	getch();
}

// 2�� ���Ŵ� ���� 1ȸ
void game(int* count, struct information* gig, struct information* completion)
{
	char ch;

	system("cls");
	template();
	popup();
	cursorView(1);
	gotoxy(32, 14); printf("��        ��        ��");
	gotoxy(30, 17); printf("Ư�� �̺�Ʈ�� �����Ͽ����ϴ�.\n");
	gotoxy(24, 19); printf("�̱� ���ӿ� �����Ͻðڽ��ϱ�?(Y or N) : ");
	scanf(" %c", &ch);

	cursorView(0);
	//�ҹ��� �Է½� �빮�ڷ� ��ȯ
	if (islower(ch))
		ch = toupper(ch);
	if (ch == 'Y')
	{
		srand((unsigned int)time(NULL));
		int computer = rand() % 3 + 1; // ��ǻ�Ͱ� �����ϴ� ����
		int player = 0;   // ����ڰ� �����ϴ� ����

		// ���� ����
		system("cls");
		template();
		popup();
		gotoxy(33, 15); printf("������ �����ϼ̽��ϴ�.\n\n");
		gotoxy(24, 18); printf("���ݺ��� �� �� �� �̱� ������ �����մϴ� !\n\n");
		Sleep(2000);

		system("cls");
		template();
		gotoxy(11, 5);  printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ� �� �� �� Ģ �١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�");
		gotoxy(35, 8); printf("��Ģ�� �����մϴ�.\n");
		gotoxy(15, 11); printf("�� �� �� �߿��� ������ ��� ���� �� ���� �̾��ּ���.");
		gotoxy(7, 13);  printf("���� ��ǻ�Ϳ� ���� ������ �̾Ҵٸ� �¸�, �ٸ� ������ �̾Ҵٸ� �й��Դϴ�.\n\n");
		gotoxy(22, 16); printf("��ȸ�� �� �� �� ���̴�, ������ �������ּ���.");
		gotoxy(10, 19); printf("\033[0;31m������������������������������������������������������������WARNING������������������������������������������������������������\033[0m");
		gotoxy(10, 20); printf("\033[0;31m��                                                                 ��\033[0m");
		gotoxy(10, 21); printf("\033[0;31m��     ���ӿ��� �¸� �� �������� ���� Ƽ�� �� ���� �����˴ϴ�.     ��\033[0m");
		gotoxy(10, 22); printf("\033[0;31m��                                                                 ��\033[0m");
		gotoxy(10, 23); printf("\033[0;31m��          ��, �й�� ����� ���� Ƽ�� �� �� ���� ��ҵ˴ϴ�.     ��\033[0m");
		gotoxy(10, 24); printf("\033[0;31m��                                                                 ��\033[0m");
		gotoxy(10, 25); printf("\033[0;31m��������������������������������������������������������������������������������������������������������������������������������������\033[0m");
		gotoxy(26, 27); printf("enterŰ�� ������ ������ �����մϴ�!");
		gotoxy(60, 27);
		getch();

		while (1)
		{
			system("cls");
			template();
			cursorView(1);
			gotoxy(23, 5); printf("���ݺ��� �� �� �� �̱� ������ �����մϴ� !\n");
			gotoxy(20, 7); printf("�� �� �� �� ������ ��� ���� �ϳ��� �̾��ּ��� !\n");
			gotoxy(20, 9); printf("[ �� : 1 �Է� ] [ �� : 2 �Է� ] [ �� : 3 �Է� ]\n");
			gotoxy(35, 11); printf("\033[0;34m����� ������ ? ? _\b\033[0m");
			scanf("%d", &player);

			// 1, 2, 3 ���� �ٸ� ���ڸ� �Է��� ��� �ٽ� �Է�
			cursorView(0);
			if (player < 1 || player > 3)
			{
				system("cls");
				template();
				popup();
				gotoxy(23, 16); printf("�߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���.\n\n");
				Sleep(1000);
				continue;
			}

			// ���� ��� (player == 1, computer == 2)
			gotoxy(23, 13); printf("YOU");
			switch (player)
			{
			case 1:
				circle(1); break;
			case 2:
				triangle(1); break;
			case 3:
				square(1); break;
			}
			Sleep(2000);

			gotoxy(56, 13); printf("COMPUTER");
			switch (computer)
			{
			case 1:
				circle(2); break;
			case 2:
				triangle(2); break;
			case 3:
				square(2); break;
			}
			Sleep(1000);

			// �̱� ��� -> ���� Ƽ�� �¼� ���� ��÷
			if (player == computer)
			{
				int r = 0, c = 0;
				(*count) += 1;
				gig->num = *count;
				gotoxy(5, 27); printf("\033[0;32m�����մϴ�! �̱� ���ӿ��� �¸��߽��ϴ�! enterŰ�� ������ ������ �����˴ϴ� !\033[0m\n");
				gotoxy(79, 27);
				getch();

				// �ڸ� ���� ���� ( �̹� ����� �ڸ��̸� �ٽ� ���� )
				do {
					srand((unsigned int)time(NULL));
					r = rand() % 10;
					c = rand() % 10;
				} while (gigSeat[r][c] != 0);

				// ��, �� ���� ����
				gig->row = r;
				gig->col = c;
				gigSeat[r][c] = 1;

				// ���� ���� ����(completion)
				strcpy(completion[*count].title, gig->title);
				strcpy(completion[*count].date, gig->date);
				strcpy(completion[*count].name, gig->name);
				completion[*count].row = gig->row;
				completion[*count].col = gig->col;
				completion[*count].num = gig->num;

				// ���� Ƽ�� ���� ���
				system("cls");
				template();
				gotoxy(8, 7); printf("\033[0;32m�������� Ƽ���� �����Ǿ����ϴ�. ���ӿ� �������ּż� �����մϴ� ^____^\033[0m\n");
				gotoxy(34, 11); printf("�� �� �� Ƽ �� �� �� ��\n");
				gotoxy(27, 14); printf("�� �� �� ȣ : T%05d\n", gig->num);
				gotoxy(27, 16); printf("��  ��  ��  : %s\n", gig->name);
				gotoxy(27, 18); printf("�� �� �� �� : %s\n", gig->title);
				gotoxy(27, 20); printf("�� �� �� ¥ : %s\n", gig->date);
				gotoxy(27, 22); printf("�� �� �� �� : %c�� %2d��\n", (gig->row) + 65, (gig->col) + 1);
				gotoxy(22, 26); printf("enterŰ�� ������ �޴� �������� �̵��մϴ� >>>");
				getch();
				break;
			}

			// �� ��� -> �ֱ� ���� Ƽ�� ���
			else
			{

				char str1[50] = { 0 };
				char str2[] = "ũ�������� ����";

				// completion�� num�� �ش��ϴ� title ���ڿ��� ���ؼ�, �¼��� �࿭ ������ 0���� ������ֱ�
				strcpy(str1, completion[*count].title);
				(strcmp(str1, str2) == 0) ? (gigSeat[completion[*count].row][completion[*count].col]) = 0 : (concertSeat[completion[*count].row][completion[*count].col] = 0);
				completion[*count].num = -1;


				gotoxy(6, 26); printf("\033[0;31m�̱� ���ӿ��� �й��߽��ϴ�. . ��Ģ��� ���ŵ� Ƽ�� �� ������ ��ҵ˴ϴ�. .\033[0m\n");
				gotoxy(30, 28); printf("enterŰ�� �����ּ���. . .");
				getch();
				break;
			}

		}
	}

	else
	{
		gotoxy(30, 17); printf("���� ������ ����ϼ̽��ϴ�. .\n");
		gotoxy(23, 19); printf("enterŰ�� ������ �޴� �������� �̵��մϴ�.\n");
		getch();
	}
}

// ���� ��¿� ���� => who == 1  : player, who == 2 : computer �ڸ��� ���
// ���׶��(��)
void circle(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("      �ܡܡܡ�\n");
	gotoxy(x, 16); printf("   ��          ��\n");
	gotoxy(x, 17); printf(" ��              ��\n");
	gotoxy(x, 18); printf("��                ��\n");
	gotoxy(x, 19); printf("��                ��\n");
	gotoxy(x, 20); printf("��                ��\n");
	gotoxy(x, 21); printf("��                ��\n");
	gotoxy(x, 22); printf(" ��              ��\n");
	gotoxy(x, 23); printf("   ��          ��\n");
	gotoxy(x, 24); printf("      �ܡܡܡ�\n");
}
// ����(��)
void triangle(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("         ��\n");
	gotoxy(x, 16); printf("        ���\n");
	gotoxy(x, 17); printf("       ��  ��\n");
	gotoxy(x, 18); printf("      ��    ��\n");
	gotoxy(x, 19); printf("     ��      ��\n");
	gotoxy(x, 20); printf("    ��        ��\n");
	gotoxy(x, 21); printf("   ��          ��\n");
	gotoxy(x, 22); printf("  ��            ��\n");
	gotoxy(x, 23); printf(" ��              ��\n");
	gotoxy(x, 24); printf("�����������\n");
}
// �׸�(��)
void square(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("�����������\n");
	gotoxy(x, 16); printf("��                ��\n");
	gotoxy(x, 17); printf("��                ��\n");
	gotoxy(x, 18); printf("��                ��\n");
	gotoxy(x, 19); printf("��                ��\n");
	gotoxy(x, 20); printf("��                ��\n");
	gotoxy(x, 21); printf("��                ��\n");
	gotoxy(x, 22); printf("��                ��\n");
	gotoxy(x, 23); printf("��                ��\n");
	gotoxy(x, 24); printf("�����������\n");
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
	gotoxy(14, 10); printf("��������������������������������������������������������������������������������������������������������������������\n");
	gotoxy(14, 11); printf("��                                                     X  ��\n");
	gotoxy(14, 12); printf("��������������������������������������������������������������������������������������������������������������������\n");
	gotoxy(14, 13); printf("��                                                        ��\n");
	gotoxy(14, 14); printf("��                                                        ��\n");
	gotoxy(14, 15); printf("��                                                        ��\n");
	gotoxy(14, 16); printf("��                                                        ��\n");
	gotoxy(14, 17); printf("��                                                        ��\n");
	gotoxy(14, 18); printf("��                                                        ��\n");
	gotoxy(14, 19); printf("��                                                        ��\n");
	gotoxy(14, 20); printf("��                                                        ��\n");
	gotoxy(14, 21); printf("��������������������������������������������������������������������������������������������������������������������\n");
}

// Ƽ�� â
void ticketScreen()
{
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("��                  |                                                              ��\n");
	printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

// Ŀ�� ���� or ���� <windows.h>
void cursorView(int n)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };

	//Ŀ�� ���� (1 ~ 100)
	cursorInfo.dwSize = 1;

	//Ŀ�� Visible TRUE(����) FALSE(����)
	if (n == 0)
		cursorInfo.bVisible = FALSE;
	else if (n == 1)
		cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ��� ��ġ ���� <window.h>
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}