#pragma comment(lib, "ws2_32.lib") //라이브러리 자동으로 못 찾아서 찾아줌
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include <winsock2.h> // 소켓 통신
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // 빈공간
#define WALL 1 // 벽
#define BUSH 2 // 풀숲
#define GUN 3 // 총
#define POTION 5 //  포션
#define GINP 7 // 총을 먹은 상태의 플레이어 1
#define BINP 8 // 부쉬에 있는 상태의 플레이어 1
#define PLAYER 9 // 평상시 플레이어 1
#define GINP2 70 // 총을 먹은 상태의 플레이어2
#define BINP2 80 // 부쉬에 있는 상태의 플레이어 2
#define PLAYER2 90 // 평상시 플레이어 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // 글자 색 지정
#define SHOOTSPEED 5 // 평상시 쐈을때 총알속도
#define BUSHSHOOTSPEED 3 // 부쉬에서 쐈을때 총알속도
#define UP1 'w' // 플레이어 1 방향키
#define DOWN1 's' 
#define LEFT1 'a'
#define RIGHT1 'd'
#define P1SHOOT 32 // 플레이어 1 공격키
#define UP2 72 // 플레이어 2 방향키
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77
#define P2SHOOT '+' // 플레이어 2 공격키
#define BULLETS 20 // 최대 총알 갯수
#define BULLET1 10 // p1의 그냥총알
#define BUSHBULLET1 11 // p1의 부쉬에 있는 총알
#define BULLET2 12 // p2의 그냥총알
#define BUSHBULLET2 13 // p2의 부쉬에 있는 총알
#define P1BULLETCOLOR 5 // p1의 총알 색
#define P2BULLETCOLOR 6 // p2의 총알 색
#define DISTANCEATTACK 0.5 // 총알 간격(공격속도)
#define MAP_RESET 'y' // 리셋버튼

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 목숨
float ginpst, ginpst2;
int p1_ShootX[BULLETS], p1_ShootY[BULLETS], p1_Shoot_See[BULLETS], p1_Now_See, p1_ShootSpeed[BULLETS], p1Bullets = 0, p1DeleteBullets = 0;// 플레이어들의 총알의 x, y좌표, 보고있는방향, 총알속도, 총알갯수
int p2_ShootX[BULLETS], p2_ShootY[BULLETS], p2_Shoot_See[BULLETS], p2_Now_See, p2_ShootSpeed[BULLETS], p2Bullets = 0, p2DeleteBullets = 0;
float gundis1_st, gundis2_st; // 총알 간격제어를 위한 시간을 저장하는 변수
int bulletload1 = 1, bulletload2 = 1; // 공격속도보다 빨리 못 쏘게 하는 변수
float gunst, stpt; // 아이템 생성 시간을 재는 함수
int list; // 메뉴리스트 함수

int map[MAPSIZE][MAPSIZE];

void nocur() {
    CONSOLE_CURSOR_INFO Cur;
    Cur.dwSize = 1;
    Cur.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Cur);
}

char getKey()
{
    Sleep(10);
    if (kbhit()) // kbhit()이용해 입력값이 있는지 확인 
    {
        return getch();     // 입력값이 getch()로 char를 리턴해줌
    }
    return '\0'; // 입력값이 없으면 널 문자 리턴
}

int main(int argc, char *argv[]) {

    nocur(); // 커서 숨김
    system("mode con cols=120 lines=41"); // 콘솔 창 크기 지정


    SOCKET clientsock;
    WSADATA wsa;
    struct sockaddr_in sockinfo;

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)

        printf("초기화 실패\n");

    clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientsock == INVALID_SOCKET)
        printf("소켓 생성 실패\n");

    memset(&sockinfo, 0, sizeof(sockinfo));

    sockinfo.sin_family = AF_INET;
    sockinfo.sin_port = htons(atoi(argv[2]));
    sockinfo.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
        printf(" 서버 접속 실패\n");
    else
        printf("서버 접속 성공\n");
    Sleep(2000);
    system("cls");


    char buf[100];

    while (1) {
        *buf = getKey();
        send(clientsock, buf, sizeof(buf), 0);

        // 맵이랑 피정보 출력
    }
}