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
	box();
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
	box();
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
	box();
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

void selectMenu()
{
	box();
	gotoxy(27, 10);

	int menu = 0;
	system("cls");
	printf("C-Park에 오신 것을 환영합니다!\n\n\n");
	printf("1. 티 켓 예 매\n\n");
	printf("2. 예 매 확 인\n\n");
	printf("3. 예 매 취 소\n\n");
	printf("이용하실 메뉴를 선택해주세요(번호 입력) : _\b");
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
	printf("현재 진행중인 공연 리스트입니다.\n\n");
	printf("1번  아이돌 BU 콘서트/2021년 12월 15일 20시\n");
	printf("2번  연극 B&U/2021년 12월 15일 20시\n");
	printf("예매 하실 공연을 선택해주세요.(번호 입력) : ");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		//ticketing_concert(); break;
	case 2:
		ticketing_gig(); break;
	}
}

// 키 입력 받기
int getKey()
{
	if (kbhit() != 0) //키 입력이 유효하면
	{
		return getch(); //입력한 키 반환
	}
	return 0;
}

// 방향키 이동
void move()
{
	int key;
	int inx = 0, iny = 0;
	key = getKey();

	if (key == 0)
		key = ketKey();
	switch (key)
	{
	case 72: // 위
		inx
		break;

	case 80: // 아래
		break;

	case 75: // 왼쪽
		break;

	case 77: // 오른쪽
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
	printf("연극 B&U 좌석 예매 페이지\n\n");
	printf("방향키를 사용하여 커서를 예매하실 좌석에 놓고 엔터를 눌러주세요\n\n");

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			printf("■");
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