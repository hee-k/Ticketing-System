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
	char title[50]; // 공연 이름
	char date[50];  // 공연 날짜
	char name[20];  // 예매자
	char seat[10];  // 예매 좌석
	int num;		// 예매 번호	
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

// 회원가입 or 로그인
 void intro()
{
	int sel;
	gotoxy(27, 10);
	printf("티켓 예매가 필요할 땐, C-Park !\n\n");
	gotoxy(15, 17);
	printf("\t\t\t20214116 김희선\n\n\n\n");
	gotoxy(30, 27);
	printf("enter를 눌러 시작하기>>>>\n");
	gotoxy(54, 27);
	getch();

	system("cls");
	template();
	gotoxy(27, 10);
	printf("티켓 예매 프로그램 C-Park에 오신 것을 환영합니다!\n\n");
	printf("C-Park이 처음이시라면 회원가입을, 이미 가입하셨다면 로그인을 선택해주세요.\n\n\n");
	printf("회 원 가 입  :  1 입력\n");
	printf("로  그  인   :  2 입력\n\n");
	printf("번 호 입 력  :  _\b");
	scanf("%d", &sel);

	switch (sel)
	{
	case 1:
		join(); break;
	case 2:
		login(); break;
	}
}

// 회원가입 함수(파일 입출력으로 만들기)
void join()
{
	system("cls");
	template();
	gotoxy(27, 10);
	printf("파일 입출력으로 회원가입 실행\n\n");
	printf("사용 할 아이디를 입력해주세요 : ");
	printf("사용 할 비밀번호를 입력해주세요 : ");
	getch();

	printf("회원 가입이 완료되었습니다!\n\n");
	printf("enter를 누르면 로그인 화면으로 이동합니다.\n");

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
	printf("C-Park 티켓 예매를 위해 로그인을 해주세요.\n\n\n");
	printf("아  이  디  :  ");
	scanf("%s", name);	// 한글 오류
	printf("\n\n\n비 밀 번 호  :  ");
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
	printf("C-Park에 오신 것을 환영합니다!\n\n\n");
	printf("1. 티 켓 예 매\n\n");
	printf("2. 예 매 확 인\n\n");
	printf("3. 예 매 취 소\n\n");
	printf("이용하실 메뉴를 선택해주세요(번호 입력) : _\b");
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

	printf("현재 진행중인 공연 리스트입니다.\n\n");
	printf("1번  아이돌 BU 콘서트/2021년 12월 15일 18시\n");
	printf("2번  크리스마스 연극/2021년 12월 25일 20시\n");
	printf("예매 하실 공연을 선택해주세요.(번호 입력) : ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		//ticketing_concert(); break;
	case 2:
		//gig[count] = {"크리스마스 연극", "2021년 12월 25일 20시", "홍길동", "A31", 0001};
		ticketing_gig();
		break;
	}
}

// 좌석 선택
void booking(int *seat)
{
	cursorView(); // 커서 숨김
	int key = 0;
	int inx = 30, iny = 13;
	do
	{
		gotoxy(inx, iny);
		printf("♡\b\b");
		key = getch();
		if (key == 224)
		{
			key = getch();
			switch (key)
			{
			case 72: // 위
				gotoxy(inx, iny);
				printf("■");
				iny--;
				if (iny < 13)
					iny = 13;
				break;

			case 80: // 아래
				gotoxy(inx, iny);
				printf("■");
				iny++;
				if (iny > 22)
					iny = 22;
				break;

			case 75: // 왼쪽
				gotoxy(inx, iny);
				printf("■");
				inx -= 2;
				if (inx < 30)
					inx = 30;
				break;

			case 77: // 오른쪽
				gotoxy(inx, iny);
				printf("■");
				inx += 2;
				if (inx > 48)
					inx = 48;
				break;
			}
		}
	} while (key != 13);
	
	seat[iny-13, (inx-30)/2] = 1;

	// 예매중 화면
	for (int i = 0; i < 5; i++)
	{
		system("cls");
		template();
		gotoxy(23, 7);
		printf("\n\t\t\t예매 중입니다. . 잠시 기다려주세요. .\t");

		gotoxy(25, 12);
		for (int j = 0; j < 5; j++) {
			if (j <= i)
				printf("▶\t");
			else
				printf("▷\t");
		}
		Sleep(500);
	}
	gotoxy(30, 17);
	// 예매 정보 구조체로 정의하기
	printf("예매가 완료되었습니다!\n\n");
	printf("※ 예 매 정 보 ※\n");
	printf("공 연 이 름 : \n");
	printf("공 연 날 짜 : \n");
	printf("공 연 시 간 : \n");
	printf("예  매  자  : \n");
	printf("예 매 좌 석 : \n");

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
	printf("연극 B&U 좌석 예매 페이지\n\n");
	gotoxy(11, 7);
	printf("방향키를 사용하여 커서(♡)를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");

	// 행 열 출력
	gotoxy(30, 11);
	for (i = 0; i < 10; i++)
		printf(" %c", 65 + i);

	for (i = 1; i < 11; i++)
	{
		gotoxy(26, 12 + i);
		printf("%2d", i);
	}
	printf("\n");

	// 예약 가능 좌석 출력
	for (i = 0; i < 10; i++)
	{
		gotoxy(30, 13 + i);
		for (j = 0; j < 10; j++)
		{
			// 예약된 자리이면 □
			if (gigSeat[i][j] == 1)
				printf("□");
			else
				printf("■");
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
	printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│  <  >                                                                ―  □  X  │\n");
	printf("├─────────────────────────────────────────────────────────────────────────────────┤\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("│                                                                                 │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
}

void popup()
{
	gotoxy(16, 7);
	printf("┌────────────────────────────────────────────────────────┐\n");
	gotoxy(16, 8);
	printf("│  <  >                                       ―  □  X  │\n");
	gotoxy(16, 9);
	printf("├────────────────────────────────────────────────────────┤\n");
	gotoxy(16, 10);
	printf("│                                                        │\n");
	gotoxy(16, 11);
	printf("│                                                        │\n");
	gotoxy(16, 12);
	printf("│                                                        │\n");
	gotoxy(16, 13);
	printf("│                                                        │\n");
	gotoxy(16, 14);
	printf("│                                                        │\n");
	gotoxy(16, 15);
	printf("│                                                        │\n");
	gotoxy(16, 16);
	printf("│                                                        │\n");
	gotoxy(16, 17);
	printf("│                                                        │\n");
	gotoxy(16, 18);
	printf("└────────────────────────────────────────────────────────┘\n");
}

// 커서 보임 or 숨김 <windows.h>
void cursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 출력 위치 변경 <window.h>
void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}