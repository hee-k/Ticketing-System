#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

void intro();
void join(char* name, char* password);
int login(char* name, char* password);
int selectMenu();

int selectShow();
void concertSeating();
void gigSeating();
int booking(int show, int count, struct information* inform, struct information* com);

int details(struct information* com, int count);
int cancle(struct information* com, int count);

void template();
void popup();
void cursorView();
void gotoxy(int x, int y);

typedef struct information {
	char title[50];		// 공연 이름
	char date[50];		// 공연 날짜
	char name[20];		// 예매자
	int row;			// 예매 좌석(행)
	int col;			// 예매 좌석(열)
	int num;			// 예매 번호
} information;

int concertSeat[10][10] = { 0 };// 콘서트 예약된 좌석 정보
int gigSeat[10][10] = { 0 };	// 공연 예약된 좌석 정보
int total_count = 0;			// 유효 예매 횟수 체크(취소된 티켓 제외)

void main()
{
	// 회원가입시 입력한 정보 저장(이름, 비번)
	char name[20] = { 0 };
	char password[20] = { 0 };

	int show = 0;		 // selectShow에서 선택한 공연
	int count = 0;		 // 총 예매 횟수 == information.num, 예매 번호
	int menu = 0;		 // 메뉴 선택
	int re_booking = 0;  // 이미 선택된 좌석을 고를 경우 1 return

	// 예매 완료된 정보
	information completion[100] = { 0 };
	information concert = { "아이돌 BU 콘서트", "2021년 12월 15일 20시", 0, 0, 0, 0 };
	information gig = {"크리스마스 연극", "2021년 12월 25일 20시", 0, 0, 0, 0};

	// 시작
	intro();
	// 회원가입
	join(name, password);
	while (1)
	{
		// 로그인
		int res = login(name, password);
		if (res == 1)
			break;
	}
	while(1)
	{
		// 매뉴 선택(예매, 예매 확인, 예매 취소)
		menu = selectMenu();
		switch (menu)
		{
		// menu1 : 공연 예매 하기
		case 1:
			show = selectShow();
			count++, total_count++; // 예매 횟수++
			switch (show)
			{
			// show1 : 콘서트 예매
			case 1:
				// 예매 정보 저장(이름, 예매 횟수)
				strcpy(concert.name, name);
				concert.num = count;

				// 티켓 예매(이미 선택된 좌석이면 선택 불가)
				do {
					concertSeating();
					re_booking = booking(show, count, &concert, completion);
				} while (re_booking == 1);
				break;

			// show2 : 연극 예매
			case 2:
				// 예매 정보 저장(이름, 예매 횟수)
				strcpy(gig.name, name);
				gig.num = count;

				// 티켓 예매(이미 선택된 좌석이면 선택 불가)
				do {
					gigSeating();
					re_booking = booking(show, count, &gig, completion);
				} while (re_booking == 1);
				break;
			}
			break;

		// menu2 : 예매 내역서
		case 2:
			details(completion, count);
			break;

		// menu3 : 예매 취소
		case 3:
			cancle(completion, count);
			break;

		case 4:
			printf("C-Park를 이용해주셔서 감사합니다.");
			Sleep(2000);
			exit(1);
		
		default : 
			printf("숫자를 잘못 입력하셨습니다. 다시 입력해주세요!");
			Sleep(2000);
			continue;
		}
	}
}

// 프로그램 시작 화면
 void intro()
{
	template();
	gotoxy(27, 10);
	printf("티켓 예매가 필요할 땐, C-Park !\n\n");
	gotoxy(15, 17);
	printf("\t\t\t20214116 김희선\n\n\n\n");
	gotoxy(30, 27);
	printf("enter를 눌러 시작하기>>>>\n");
	gotoxy(54, 27);
	getch();
}

 // 회원가입
void join(char *name, char *password)
{
	int offset = 0;

	system("cls");
	template();
	gotoxy(27, 10);
	printf("티켓 예매 프로그램 C-Park에 오신 것을 환영합니다!\n\n");
	gotoxy(27, 12);
	printf("프로그램 사용 전, 먼저 회원가입을 해주세요\n\n");
	gotoxy(27, 17);
	printf("예매자 이름을 입력해주세요 : ");
	scanf("%s", name);
	gotoxy(27, 20);
	printf("사용 할 비밀번호를 입력해주세요 : ");
	while ((password[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}

	printf("회원 가입이 완료되었습니다!\n\n");
	printf("enter를 누르면 로그인 화면으로 이동합니다.\n");
	getch();
}

// 로그인
int login(char *name, char *password)
{
	char receiveName[20] = { 0 };
	char receivePassword[20] = { 0 };
	int i = 0, offset = 0;

	system("cls");
	template();
	gotoxy(27, 10);
	printf("C-Park 티켓 예매를 위해 로그인을 해주세요.\n");
	gotoxy(27, 15);
	printf("이    름  :  ");
	scanf("%s", receiveName);
	gotoxy(27, 17);
	printf("\n\n\n비 밀 번 호  :  ");
	while ((receivePassword[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}
	// 같으면 0 반환
	int n = strcmp(receiveName, name);
	int p = strcmp(receivePassword, password);

	if (n == 0 && p == 0)
	{
		printf("로그인 성공!");
		Sleep(1000);
		return 1;
	}
		
	else
	{
		printf("로그인에 실패하였습니다. 다시 시도해주세요!");
		Sleep(1000);
		return 2;
	}
}

// 메뉴 선택(예매, 예매내역, 예매취소)
int selectMenu()
{
	int menu = 0;

	system("cls");
	template();
	gotoxy(27, 10);

	printf("C-Park에 오신 것을 환영합니다!\n\n\n");
	printf("1. 티 켓 예 매\n\n");
	printf("2. 예 매 확 인\n\n");
	printf("3. 예 매 취 소\n\n");
	printf("4. 종      료\n\n");
	printf("이용하실 메뉴를 선택해주세요(번호 입력) : _\b");
	
	scanf("%d", &menu);
	return menu;
}

// 공연 선택
int selectShow()
{
	int choice;

	system("cls");
	template();
	gotoxy(27, 10);

	printf("현재 진행중인 공연 리스트입니다.\n\n\n");
	printf("1번  아이돌 BU 콘서트/2021년 12월 15일 18시\n\n");
	printf("2번  크리스마스 연극/2021년 12월 25일 20시\n\n");
	printf("예매 하실 공연을 선택해주세요.(번호 입력) : ");
	scanf("%d", &choice);
	
	return choice;
}

// 공연 예매 및 예매 정보 저장
int booking(int show, int count, struct information *inform, struct information* com)
{
	// 좌석 선택 과정
	cursorView();			 // 커서 숨김
	int key = 0;			 // 입력 받는 키(방향키, 엔터)
	int inx = 30, iny = 13;  // 좌석 시작 위치(A행 1열)
	int bookingRow = 0;		 // 예매 행 
	int bookingCol = 0;		 // 예매 열

	// 콘서트 예매를 위한 랜덤 변수 사용
	int r = 0;
	int c = 0;
	// rr, cc : r, c로 계산해서 gotoxy에 쓸 값
	int rr = 0, cc = 0;

	do
	{
		gotoxy(inx, iny);
		printf("♡\b\b");
		key = getch();
		if (key == 224)
		{
			if (show == 1)
			{
				srand(time(NULL));
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
				(concertSeat[r][c] == 1) ? printf("□") : printf("■");
			}

			key = getch();
			switch (key)
			{
			case 72: // 위
				gotoxy(inx, iny);
				switch (show)
				{
					// 예약된 자리는 □로 다시 놓고, 남은 자리는 ■로 다시 놓기(커서 궤도를 안보이게 하기 위해)
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				}
				iny--;
				if (iny < 13)
					iny = 13;
				break;

			case 80: // 아래
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				}
				iny++;
				if (iny > 22)
					iny = 22;
				break;

			case 75: // 왼쪽
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				}
				inx -= 2;
				if (inx < 30)
					inx = 30;
				break;

			case 77: // 오른쪽
				gotoxy(inx, iny);
				switch (show)
				{
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("□") : printf("■");
					break;
				}
				inx += 2;
				if (inx > 48)
					inx = 48;
				break;
			}
		}
	} while (key != 13);

	// 예약된 좌석의 행, 열 정보에 콘솔상 위치 저장
	bookingRow = iny - 13;
	bookingCol = (inx - 30) / 2;

	// 이선좌 체크(이선좌면 선택 불가 -> 재선택)
	if (concertSeat[bookingRow][bookingCol] == 1 || gigSeat[bookingRow][bookingCol] == 1)
	{
		printf("이미 선택된 좌석입니다.");
		Sleep(500);
		return 1;
	}

	// 좌석 배열에 행, 열 정보 저장
	if (show == 1)
		concertSeat[bookingRow][bookingCol] = 1;
	else if (show == 2)
		gigSeat[bookingRow][bookingCol] = 1;

	// 구조체에 행, 열 정보 저장
	inform->row = bookingRow;
	inform->col = bookingCol;

	// 예매 정보 저장(completion)
	strcpy(com[count].title, inform -> title);
	strcpy(com[count].date, inform -> date);
	strcpy(com[count].name, inform -> name);
	com[count].row = inform -> row;
	com[count].col = inform -> col;
	com[count].num = inform -> num;

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
		Sleep(450);
	}

	// 예매 정보 출력
	system("cls");
	template();
	gotoxy(30, 7);
	printf("예매가 완료되었습니다!\n");
	gotoxy(20, 13);
	printf("※ 예 매 정 보 ※\n");
	gotoxy(20, 15);
	printf("예 매 번 호 : T%05d\n", inform->num);
	gotoxy(20, 17);
	printf("예  매  자  : %s\n", inform->name);
	gotoxy(20, 19);
	printf("공 연 이 름 : %s\n", inform->title);
	gotoxy(20, 21);
	printf("공 연 날 짜 : %s\n", inform->date);
	gotoxy(20, 23);
	printf("예 매 좌 석 : %c행 %2d열\n", (inform->row) + 65, (inform->col) + 1);
	gotoxy(30, 27);
	printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
	getch();
}

// concert 좌석 출력
void concertSeating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(26, 5);
	printf("아이돌 BU 콘서트 좌석 예매 페이지\n\n");
	gotoxy(11, 7);
	printf("방향키를 사용하여 커서(♡)를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");

	// 행 열 정보 출력
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf("%2d", i);

	for (i = 0; i < 10; i++)
	{
		gotoxy(26, 13 + i);
		printf("%c", 65 + i);
	}
	printf("\n");

	// 예약 가능 좌석 출력
	for (i = 0; i < 10; i++)
	{
		gotoxy(30, 13 + i);
		for (j = 0; j < 10; j++)
		{
			// 예약된 자리이면 □
			if (concertSeat[i][j] == 1)
				printf("□");
			else
				printf("■");
		}
		printf("\n");
	}
}

// gig 좌석 출력
void gigSeating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(27, 5);
	printf("크리스마스 연극 예매 페이지\n\n");
	gotoxy(11, 7);
	printf("방향키를 사용하여 커서(♡)를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");

	// 행 열 정보 출력
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf("%2d", i);

	for (i = 0; i < 10; i++)
	{
		gotoxy(26, 13 + i);
		printf("%c", 65 + i);
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
}

// 예매 내역
int details(struct information* com, int count)
{
	system("cls");
	template();
	gotoxy(27, 10);
	if (total_count == 0)
	{
		printf("예매 내역이 없습니다.\n");
		printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
		getch();
		return 0;
	}
	printf("※ 예매 내역 확인 ※\n\n");
	for (int i = 1; i <= count; i++)
	{
		if (com[i].num == -1)
			continue;
		printf("＃상 세 내 역\n\n");
		printf("예 매 번 호 : T%05d\n", com[i].num);
		printf("예  매  자  : %s\n", com[i].name);
		printf("공 연 이 름 : %s\n", com[i].title);
		printf("공 연 날 짜 : %s\n", com[i].date);
		printf("예 매 좌 석 : %c행 %2d열\n", com[i].row+65, com[i].col+1);
		printf("\n\n");
	}
	printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
	getch();
}

// 예매 취소
int cancle(struct information* com, int count)
{
	int i = 0, res = 0, can = 0;
	char str1[50] = { 0 };
	char str2[] = "크리스마스";

	system("cls");
	template();
	gotoxy(27, 10);
	if (total_count == 0)
	{
		printf("예매 내역이 없습니다.\n");
		printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
		getch();
		return 0;
	}
	printf("※ 예매 내역 확인 ※\n\n");
	for (i = 1; i <= count; i++)
	{
		if (com[i].num == -1)
			continue;
		printf("＃상 세 내 역\n\n");
		printf("예 매 번 호 : T%05d\n", com[i].num);
		printf("예  매  자  : %s\n", com[i].name);
		printf("공 연 이 름 : %s\n", com[i].title);
		printf("공 연 날 짜 : %s\n", com[i].date);
		printf("예 매 좌 석 : %c행 %2d열\n", com[i].row + 65, com[i].col + 1);
		printf("\n\n");
	}

	printf("\n\n취소 할 티켓의 예매번호 유효숫자를 입력해주세요 (예, T00001 -> 1입력) : ");
	scanf("%d", &can);

	for (i = 1; i <= count; i++)
	{

		if (com[i].num == can)
		{
			system("cls");
			template();
			gotoxy(27, 10);
			printf("취소 할 티켓의 정보를 확인해주세요. 엔터를 누르면 취소됩니다.\n\n");
			printf("＃상 세 내 역\n\n");
			printf("예 매 번 호 : T%05d\n", com[i].num);
			printf("예  매  자  : %s\n", com[i].name);
			printf("공 연 이 름 : %s\n", com[i].title);
			printf("공 연 날 짜 : %s\n", com[i].date);
			printf("예 매 좌 석 : %c행 %2d열\n", com[i].row + 65, com[i].col + 1);

			// completion의 num에 해당하는 title 문자열을 비교해서, 좌석의 행열 정보를 0으로 만들어주기
			strcpy(com[i].title, str1); // 오류
			res = strcmp(str1, str2);
			(res == 0) ? gigSeat[com[i].row][com[i].col] == 0 : concertSeat[com[i].row][com[i].col] == 0;
			// 삭제된 completion의 num에는 -1 넣기
			com[i].num = -1;
			total_count--;
		}
	}
	getch();

	printf("\n\n티켓이 취소되었습니다!\n\n");
	printf("잠시 후 예매 내역 확인 페이지로 이동합니다.\n");
	Sleep(1000);
	details(com, count);
}

// 템플릿 창
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

// 팝업 창
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

// 티켓 창

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

/*
파일 입출력 보류
// 회원가입 함수(파일 입출력으로 만들기)
void join()
{
	system("cls");
	template();
	gotoxy(27, 10);

	char name[20] = { 0 };
	char password[20] = { 0 };
	printf("파일 입출력으로 회원가입 실행\n\n");
	printf("사용 할 아이디를 입력해주세요 : ");
	scanf("%s", name);
	printf("사용 할 비밀번호를 입력해주세요 : ");
	scanf("%s", password);

	FILE* fp = NULL;

	fp = fopen("user.txt", "w");
	fputs(name, fp);
	fputs(password, fp);

	//파일 열기 실패 시
	if (fp == NULL)
		printf("파일 열기에 실패했습니다.\n");

	fclose(fp);

	printf("회원 가입이 완료되었습니다!\n\n");
	printf("enter를 누르면 로그인 화면으로 이동합니다.\n");
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
	printf("C-Park 티켓 예매를 위해 로그인을 해주세요.\n");
	gotoxy(27, 15);
	printf("아  이  디  :  ");
	scanf("%s", name);	// 한글 오류
	gotoxy(27, 17);
	printf("\n\n\n비 밀 번 호  :  ");
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
		printf("로그인 성공");
	else
		printf("로그인 실패");
	getch();
}

*/