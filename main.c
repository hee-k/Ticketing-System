#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void intro();
void join(char* name, char* password);
int login(char* name, char* password);
int selectMenu(char* name);

int selectShow();
void concertSeating();
void gigSeating();
int booking(int show, int count, struct information* inform, struct information* com);

void details(struct information* com, int count);
void cancle(struct information* com, int count);
void nonDetails();

void game(int* count, struct information* gig, struct information* com);

void template();
void popup();
void ticketScreen();
void cursorView(int n);
void gotoxy(int x, int y);

void circle(int who);
void triangle(int who);
void square(int who);

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
	system("color F0"); // 콘솔창 배경색(흰색)
	system("title 티켓 예매가 필요할 땐, Ticket-C ! (20214116 김희선)"); // 콘솔창 제목

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
		menu = selectMenu(name);
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
					re_booking = booking(show, count, &concert, &completion);
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
					re_booking = booking(show, count, &gig, &completion);
				} while (re_booking == 1);
				break;
			}
			if (total_count % 2 == 0)
			{
				strcpy(gig.name, name);
				game(&count, &gig, &completion);
			}
			break;

		// menu2 : 예매 내역서
		case 2:
			if (total_count == 0)
				nonDetails();
			else
			{
				details(&completion, count);
				printf("\n\n\n\t\t\033[0;34m   enter키를 누르면 메뉴 페이지로 이동합니다>>\033[0m");
				getch();
			}
			break;

		// menu3 : 예매 취소
		case 3:
			if (total_count == 0)
				nonDetails();
			else
			{
				cancle(&completion, count);
				printf("\n\n\n\t\t\033[0;34m   enter키를 누르면 메뉴 페이지로 이동합니다>>\033[0m");
				getch();
			}
			break;

		// menu4 : 프로그램 종료
		case 4:
			cursorView(0);
			gotoxy(26, 27); printf("\033[0;34mTicket-C 를 이용해주셔서 감사합니다.\033[0m\n\n");
			Sleep(2000);
			exit(1);
		
		default : 
			cursorView(0);
			gotoxy(24, 27); printf("\033[0;31m잘못 입력하셨습니다. 다시 입력해주세요!\033[0m");
			Sleep(2000);
			continue;
		}
	}
}

// 프로그램 시작 화면
 void intro()
{
	template();
	cursorView(0);
	gotoxy(27, 10); printf("티켓 예매가 필요할 땐, Ticket-C !\n\n");
	gotoxy(35, 19); printf("20214116 김희선\n\n\n\n");
	gotoxy(30, 27); printf("enter를 눌러 시작하기>>>>\n");
	getch();
}

 // 회원가입
void join(char *name, char *password)
{
	int offset = 0;

	system("cls");
	template();
	cursorView(1);
	gotoxy(17, 10); printf("티켓 예매 프로그램 Ticket-C 에 오신 것을 환영합니다!\n\n");
	gotoxy(17, 13); printf("먼저, 원활한 티켓 예매를 위해 회원가입을 진행해주세요.\n\n");
	gotoxy(26, 17); printf("√이    름 을 입력해주세요 : ");
	scanf("%s", name);
	gotoxy(26, 20); printf("√비밀번호 를 입력해주세요 : ");
	while ((password[offset] = getch()) != '\r')
	{
		putch(password[offset]);
		offset++;
	}
	cursorView(0);
	gotoxy(8, 27); printf("\033[0;34m회원 가입이 완료되었습니다! enter를 누르면 로그인 화면으로 이동합니다.\033[0m\n\n\n");
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
	cursorView(1);
	gotoxy(22, 10); printf("Ticket-C 티켓 예매를 위해 로그인을 해주세요.\n");
	gotoxy(30, 17); printf("√이      름  :  ");
	scanf("%s", receiveName);

	gotoxy(30, 20); printf("√비 밀 번 호 :  ");
	while ((receivePassword[offset] = getch()) != '\r')
	{
		putch('*');
		offset++;
	}
	// 같으면 0 반환
	int n = strcmp(receiveName, name);
	int p = strcmp(receivePassword, password);

	cursorView(0);

	if (n == 0 && p == 0)
	{
		gotoxy(31, 27); printf("\033[0;34m * * 로그인 성공! * * \033[0m\n\n\n");
		Sleep(1000);
		return 1;
	}
		
	else
	{
		gotoxy(20, 27); printf("\033[0;31m로그인에 실패하였습니다. 다시 시도해주세요!\033[0m\n\n");
		Sleep(2000);
		return 2;
	}
}

// 메뉴 선택(예매, 예매내역, 예매취소)
int selectMenu(char *name)
{
	int menu = 0;

	system("cls");
	template();
	cursorView(1);
	gotoxy(23, 10); printf("%s님, Ticket-C 에 오신 것을 환영합니다!\n\n\n", name);
	gotoxy(35, 14); printf("1. 티 켓 예 매\n\n");
	gotoxy(35, 16); printf("2. 예 매 내 역\n\n");
	gotoxy(35, 18); printf("3. 예 매 취 소\n\n");
	gotoxy(35, 20); printf("4. 종       료\n\n");
	gotoxy(23, 24); printf("이용하실 메뉴를 선택해주세요(번호 입력) : _\b");
	
	scanf("%d", &menu);
	return menu;
}

// 공연 선택
int selectShow()
{
	int choice;

	system("cls");
	template();
	cursorView(1);

	gotoxy(27, 10); printf("현재 진행중인 공연 리스트입니다.\n\n\n");
	gotoxy(20, 15); printf("1번\t아이돌 BU 콘서트 (2021년 12월 15일 18시)\n\n");
	gotoxy(20, 18); printf("2번\t크리스마스 연극  (2021년 12월 25일 20시)\n\n");
	gotoxy(22, 24); printf("예매 하실 공연을 선택해주세요.(번호 입력) : ");
	scanf("%d", &choice);
	
	return choice;
}

// 공연 예매 및 예매 정보 저장
int booking(int show, int count, struct information* inform, struct information* com)
{
	cursorView(0);

	// 좌석 선택 과정
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
		printf("\033[1;31m♥\033[0m\b\b"); // 빨간색 하트로 커서 표시
		key = getch();
		if (key == 224)
		{
			// 콘서트는 랜덤으로 좌석 사라짐(예매됨)
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
				(concertSeat[r][c] == 1) ? printf("■") : printf("□");
			}

			key = getch();
			switch (key)
			{
			case 72: // 위
				gotoxy(inx, iny);
				switch (show)
				{
					// 예약된 자리는 ■로 다시 놓고, 남은 자리는 □로 다시 놓기(커서 궤도를 안보이게 하기 위해)
				case 1:
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
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
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
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
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
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
					(concertSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
					break;
				case 2:
					(gigSeat[iny - 13][(inx - 30) / 2] == 1) ? printf("■") : printf("□");
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
	if ((show == 1 && concertSeat[bookingRow][bookingCol] == 1 || show == 2 && gigSeat[bookingRow][bookingCol] == 1))
	{
		system("cls");
		template();
		popup();
		gotoxy(27, 16); printf("이미 다른 사람이 선택한 좌석입니다.");
		Sleep(1000);
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
		gotoxy(23, 11);
		printf("\n\t\t\t예매 중입니다. . 잠시 기다려주세요. .\t");

		gotoxy(25, 17);
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
	gotoxy(32, 7); printf("\033[0;32m예매가 완료되었습니다 !\033[0m\n");
	gotoxy(34, 11);printf("※ 예 매 정 보 ※\n");
	gotoxy(27, 14);printf("예 매 번 호 : T%05d\n", inform->num);
	gotoxy(27, 16);printf("예  매  자  : %s\n", inform->name);
	gotoxy(27, 18);printf("공 연 이 름 : %s\n", inform->title);
	gotoxy(27, 20);printf("공 연 날 짜 : %s\n", inform->date);
	gotoxy(27, 22);printf("예 매 좌 석 : %c행 %2d열\n", (inform->row) + 65, (inform->col) + 1);
	gotoxy(22, 26);printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
	getch();
}

// concert 좌석 출력
void concertSeating()
{
	int i, j;

	system("cls");
	template();
	gotoxy(26, 5); printf("아이돌 BU 콘서트 좌석 예매 페이지\n\n");
	gotoxy(11, 7); printf("방향키를 사용하여 커서(\033[1;31m♥\033[0m)를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");
	gotoxy(16, 26); printf("예매 가능한 좌석 : □\t\t예매 불가능한 좌석 : ■");

	// 행 열 정보 출력
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf(" %d", i);

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
			// 예약된 자리이면 ■
			if (concertSeat[i][j] == 1)
				printf("■");
			else
				printf("□");
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

	gotoxy(28, 5); printf("크리스마스 연극 예매 페이지\n\n");
	gotoxy(11, 7); printf("방향키를 사용하여 커서(\033[1;31m♥\033[0m)를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");
	gotoxy(16, 26); printf("예매 가능한 좌석 : □\t\t예매 불가능한 좌석 : ■");

	// 행 열 정보 출력
	gotoxy(30, 11);
	for (i = 1; i < 11; i++)
		printf(" %d", i); // 정렬 안맞는 부분 수정하기

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
			// 예약된 자리이면 ■
			if (gigSeat[i][j] == 1)
				printf("■");
			else
				printf("□");
		}
		printf("\n");
	}
}

// 예매 내역(출력 수정 완료)
void details(struct information* com, int count)
{
	int ticket_y = 4;				// 티켓 창 출력 위치
	int detail_x = 28, detail_y = 6;// 티켓 내용 출력 위치
	int num_x = 4, num_y = 8;		// 티켓 번호 출력 위치

	system("cls");
	cursorView(0);

	gotoxy(34, 2); printf("\033[0;34m※  예  매  내  역  ※\033[0m\n");
	for (int i = 0; i < count; i++)
	{
		// 취소된 티켓은 출력 X
		if (com[i+1].num == -1)
			continue;
		
		// 티켓 창 출력
		gotoxy(1, ticket_y); ticketScreen();
		// 티켓 정보 출력
		gotoxy(num_x, num_y);		  printf("티켓 고유 번호");
		gotoxy(num_x, num_y+3);		  printf("%7d", com[i + 1].num);
		gotoxy(detail_x, detail_y);   printf("예  매  번  호  :  T%05d\n", com[i + 1].num);
		gotoxy(detail_x, detail_y+2); printf("예    매    자  :  %s\n", com[i+1].name);
		gotoxy(detail_x, detail_y+4); printf("공  연  이  름  :  %s\n", com[i+1].title);
		gotoxy(detail_x, detail_y+6); printf("공  연  날  짜  :  %s\n", com[i+1].date);
		gotoxy(detail_x, detail_y+8); printf("예  매  좌  석  :  %c행 %2d열\n", com[i+1].row+65, com[i+1].col+1);
		ticket_y += 13; detail_y += 13; num_y += 13;
	}
}

// 예매 취소
void cancle(struct information* com, int count)
{
	int i = 0, cancle_number = 0;
	char str1[50] = { 0 };
	char str2[] = "크리스마스 연극";

	// 티켓 상세내역 출력
	details(com, count);
	cursorView(1);
	printf("\n\n\n\t\t\033[0;34m   취소 할 티켓의 고유 번호를 입력해주세요 : _\b\033[0m");
	scanf("%d", &cancle_number);

	for (i = 1; i <= count; i++)
	{

		if (com[i].num == cancle_number)
		{
			system("cls");
			template();
			cursorView(0);
			gotoxy(8, 7);  printf("\033[0;32m취소 할 티켓의 정보를 확인해주세요. enter키를 누르면 티켓이 취소됩니다.\033[0m\n");
			gotoxy(34, 11); printf("※ 티 켓 확 인 ※\n\n");
			gotoxy(27, 14); printf("예 매 번 호 : T%05d\n", com[i].num);
			gotoxy(27, 16); printf("예  매  자  : %s\n", com[i].name);
			gotoxy(27, 18); printf("공 연 이 름 : %s\n", com[i].title);
			gotoxy(27, 20); printf("공 연 날 짜 : %s\n", com[i].date);
			gotoxy(27, 22); printf("예 매 좌 석 : %c행 %2d열\n", com[i].row + 65, com[i].col + 1);

			// completion의 num에 해당하는 title 문자열을 비교해서, 좌석의 행열 정보를 0으로 만들어주기
			strcpy(str1, com[i].title);
			(strcmp(str1, str2) == 0) ? (gigSeat[com[i].row][com[i].col]) = 0 : (concertSeat[com[i].row][com[i].col] = 0);
			// 삭제된 completion의 num에는 -1 넣기
			com[i].num = -1;
			total_count--;
		}
	}
	getch();

	system("cls");
	template();
	popup();

	int m = 0, n = 3;
	for (m = 0; m < 3; m++, n--)
	{
		gotoxy(32, 15); printf("티켓이 취소되었습니다!\n\n");
		gotoxy(24, 18); printf("%d초 후 예매 내역 확인 페이지로 이동합니다.\n", n);
		Sleep(800);
	}
	details(com, count);
}

// 예매내역이 없는 경우
void nonDetails()
{
	system("cls");
	template();
	popup();
	gotoxy(34, 15); printf("예매 내역이 없습니다.\n");
	gotoxy(22, 18); printf("enter키를 누르면 메뉴 페이지로 이동합니다>>");
	getch();
}

// 2장 예매당 게임 1회
void game(int* count, struct information* gig, struct information* com)
{
	char ch = NULL;

	system("cls");
	template();
	popup();
	cursorView(1);
	gotoxy(32, 14); printf("○        △        □");
	gotoxy(30, 17); printf("특별 이벤트가 도착하였습니다.\n");
	gotoxy(24, 19); printf("뽑기 게임에 도전하시겠습니까?(Y or N) : ");
	scanf(" %c", &ch);

	cursorView(0);
	//소문자 입력시 대문자로 변환
	if (islower(ch))
		ch = toupper(ch);
	if (ch == 'Y')
	{
		srand(time(NULL));
		int computer = rand() % 3 + 1; // 컴퓨터가 선택하는 도형
		int player = 0;   // 사용자가 선택하는 도형

		// 게임 설명
		system("cls");
		template();
		popup();
		gotoxy(33, 15); printf("게임을 수락하셨습니다.\n\n");
		gotoxy(24, 18); printf("지금부터 ○ △ □ 뽑기 게임을 시작합니다 !\n\n");
		Sleep(2000);

		system("cls");
		template();
		gotoxy(11, 5);  printf("☆★☆★☆★☆★☆★☆★☆ 게 임 규 칙 ☆★☆★☆★☆★☆★☆★☆");
		gotoxy(35, 8); printf("규칙은 간단합니다.\n");
		gotoxy(15, 11); printf("○ △ □ 중에서 마음에 드는 도형 한 개를 뽑아주세요.");
		gotoxy(7, 13);  printf("만약 컴퓨터와 같은 도형을 뽑았다면 승리, 다른 도형을 뽑았다면 패배입니다.\n\n");
		gotoxy(22, 16); printf("기회는 단 한 번 뿐이니, 신중히 선택해주세요.");
		gotoxy(10, 19); printf("\033[0;31m┌─────────────────────────────WARNING─────────────────────────────┐\033[0m");
		gotoxy(10, 20); printf("\033[0;31m│                                                                 │\033[0m");
		gotoxy(10, 21); printf("\033[0;31m│     게임에서 승리 시 보상으로 연극 티켓 한 장이 제공됩니다.     │\033[0m");
		gotoxy(10, 22); printf("\033[0;31m│                                                                 │\033[0m");
		gotoxy(10, 23); printf("\033[0;31m│          단, 패배시 당신이 가진 티켓 중 한 장이 취소됩니다.     │\033[0m");
		gotoxy(10, 24); printf("\033[0;31m│                                                                 │\033[0m");
		gotoxy(10, 25); printf("\033[0;31m└─────────────────────────────────────────────────────────────────┘\033[0m");
		gotoxy(26, 27); printf("enter키를 누르면 게임을 시작합니다!");
		gotoxy(60, 27);
		getch();

		while (1)
		{
			system("cls");
			template();
			cursorView(1);
			gotoxy(23, 5); printf("지금부터 ○ △ □ 뽑기 게임을 시작합니다 !\n");
			gotoxy(20, 7); printf("○ △ □ 중 마음에 드는 도형 하나를 뽑아주세요 !\n");
			gotoxy(20, 9); printf("[ ○ : 1 입력 ] [ △ : 2 입력 ] [ □ : 3 입력 ]\n");
			gotoxy(35, 11); printf("\033[0;34m당신의 선택은 ? ? _\b\033[0m");
			scanf("%d", &player);

			// 1, 2, 3 외의 다른 숫자를 입력한 경우 다시 입력
			cursorView(0);
			if (player < 1 || player > 3)
			{
				system("cls");
				template();
				popup();
				gotoxy(23, 16); printf("잘못 입력했습니다. 다시 입력하세요.\n\n");
				Sleep(1000);
				continue;
			}

			// 도형 출력 (player == 1, computer == 2)
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

			// 이길 경우 -> 연극 티켓 좌석 랜덤 추첨
			if (player == computer)
			{
				int r = 0, c = 0;
				(*count) += 1;
				gig->num = *count;
				gotoxy(5, 27); printf("\033[0;32m축하합니다! 뽑기 게임에서 승리했습니다! enter키를 누르면 보상이 제공됩니다 !\033[0m\n");
				gotoxy(79, 27);
				getch();

				// 자리 랜덤 선택 ( 이미 예약된 자리이면 다시 선택 )
				do {
					srand(time(NULL));
					r = rand() % 10;
					c = rand() % 10;
				} while (gigSeat[r][c] != 0);

				// 행, 열 정보 저장
				gig->row = r;
				gig->col = c;
				gigSeat[r][c] = 1;

				// 예매 정보 저장(completion)
				strcpy(com[*count].title, gig->title);
				strcpy(com[*count].date, gig->date);
				strcpy(com[*count].name, gig->name);
				com[*count].row = gig->row;
				com[*count].col = gig->col;
				com[*count].num = gig->num;

				// 보상 티켓 정보 출력
				system("cls");
				template();
				gotoxy(8, 7); printf("\033[0;32m보상으로 티켓이 제공되었습니다. 게임에 참여해주셔서 감사합니다 ^____^\033[0m\n");
				gotoxy(34, 11); printf("※ 제 공 티 켓 정 보 ※\n");
				gotoxy(27, 14); printf("예 매 번 호 : T%05d\n", gig->num);
				gotoxy(27, 16); printf("예  매  자  : %s\n", gig->name);
				gotoxy(27, 18); printf("공 연 이 름 : %s\n", gig->title);
				gotoxy(27, 20); printf("공 연 날 짜 : %s\n", gig->date);
				gotoxy(27, 22); printf("예 매 좌 석 : %c행 %2d열\n", (gig->row) + 65, (gig->col) + 1);
				gotoxy(22, 26); printf("enter키를 누르면 메뉴 페이지로 이동합니다 >>>");
				getch();
				break;
			}

			// 진 경우 -> 최근 예매 티켓 취소
			else
			{

				char str1[50] = { 0 };
				char str2[] = "크리스마스 연극";

				// completion의 num에 해당하는 title 문자열을 비교해서, 좌석의 행열 정보를 0으로 만들어주기
				strcpy(str1, com[*count].title);
				(strcmp(str1, str2) == 0) ? (gigSeat[com[*count].row][com[*count].col]) = 0 : (concertSeat[com[*count].row][com[*count].col] = 0);
				com[*count].num = -1;


				gotoxy(6, 26); printf("\033[0;31m뽑기 게임에서 패배했습니다. . 규칙대로 예매된 티켓 중 한장이 취소됩니다. .\033[0m\n");
				gotoxy(30, 28); printf("enter키를 눌러주세요. . .");
				getch();
				break;
			}

		}
	}

	else
	{
		gotoxy(30, 17); printf("게임 도전을 취소하셨습니다. .\n");
		gotoxy(23, 19); printf("enter키를 누르면 메뉴 페이지로 이동합니다.\n");
		getch();
	}
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
	gotoxy(14, 10); printf("┌────────────────────────────────────────────────────────┐\n");
	gotoxy(14, 11); printf("│                                                     X  │\n");
	gotoxy(14, 12); printf("├────────────────────────────────────────────────────────┤\n");
	gotoxy(14, 13); printf("│                                                        │\n");
	gotoxy(14, 14); printf("│                                                        │\n");
	gotoxy(14, 15); printf("│                                                        │\n");
	gotoxy(14, 16); printf("│                                                        │\n");
	gotoxy(14, 17); printf("│                                                        │\n");
	gotoxy(14, 18); printf("│                                                        │\n");
	gotoxy(14, 19); printf("│                                                        │\n");
	gotoxy(14, 20); printf("│                                                        │\n");
	gotoxy(14, 21); printf("└────────────────────────────────────────────────────────┘\n");
}

// 티켓 창
void ticketScreen()
{
	printf("┌─────────────────────────────────────────────────────────────────────────────────┐\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("│                  |                                                              │\n");
	printf("└─────────────────────────────────────────────────────────────────────────────────┘\n");
}

// 커서 보임 or 숨김 <windows.h>
void cursorView(int n)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };

	//커서 굵기 (1 ~ 100)
	cursorInfo.dwSize = 1;

	//커서 Visible TRUE(보임) FALSE(숨김)
	if (n == 0)
		cursorInfo.bVisible = FALSE;
	else if (n == 1)
		cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 출력 위치 변경 <window.h>
void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 게임 출력용 도형 => who == 1  : player, who == 2 : computer 자리에 출력
void circle(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("      ●●●●\n");
	gotoxy(x, 16); printf("   ●          ●\n");
	gotoxy(x, 17); printf(" ●              ●\n");
	gotoxy(x, 18); printf("●                ●\n");
	gotoxy(x, 19); printf("●                ●\n");
	gotoxy(x, 20); printf("●                ●\n");
	gotoxy(x, 21); printf("●                ●\n");
	gotoxy(x, 22); printf(" ●              ●\n");
	gotoxy(x, 23); printf("   ●          ●\n");
	gotoxy(x, 24); printf("      ●●●●\n");
}

void triangle(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("         ▲\n");
	gotoxy(x, 16); printf("        ▲▲\n");
	gotoxy(x, 17); printf("       ▲  ▲\n");
	gotoxy(x, 18); printf("      ▲    ▲\n");
	gotoxy(x, 19); printf("     ▲      ▲\n");
	gotoxy(x, 20); printf("    ▲        ▲\n");
	gotoxy(x, 21); printf("   ▲          ▲\n");
	gotoxy(x, 22); printf("  ▲            ▲\n");
	gotoxy(x, 23); printf(" ▲              ▲\n");
	gotoxy(x, 24); printf("▲▲▲▲▲▲▲▲▲▲\n");
}

void square(int who)
{
	int x = 0;
	(who == 1) ? (x = 15) : (x = 50);
	gotoxy(x, 15); printf("■■■■■■■■■■\n");
	gotoxy(x, 16); printf("■                ■\n");
	gotoxy(x, 17); printf("■                ■\n");
	gotoxy(x, 18); printf("■                ■\n");
	gotoxy(x, 19); printf("■                ■\n");
	gotoxy(x, 20); printf("■                ■\n");
	gotoxy(x, 21); printf("■                ■\n");
	gotoxy(x, 22); printf("■                ■\n");
	gotoxy(x, 23); printf("■                ■\n");
	gotoxy(x, 24); printf("■■■■■■■■■■\n");
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