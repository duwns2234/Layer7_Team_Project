#pragma comment(lib, "ws2_32.lib") //���̺귯�� �ڵ����� �� ã�Ƽ� ã����
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include <winsock2.h> // ���� ���
#include<windows.h>

#define MAPSIZE 40
#define SPACE 0 // �����
#define WALL 1 // ��
#define BUSH 2 // Ǯ��
#define GUN 3 // ��
#define POTION 5 //  ����
#define GINP 7 // ���� ���� ������ �÷��̾� 1
#define BINP 8 // �ν��� �ִ� ������ �÷��̾� 1
#define PLAYER 9 // ���� �÷��̾� 1
#define GINP2 70 // ���� ���� ������ �÷��̾�2
#define BINP2 80 // �ν��� �ִ� ������ �÷��̾� 2
#define PLAYER2 90 // ���� �÷��̾� 2
#define COL GetStdHandle(STD_OUTPUT_HANDLE) // ���� �� ����
#define SHOOTSPEED 5 // ���� ������ �Ѿ˼ӵ�
#define BUSHSHOOTSPEED 3 // �ν����� ������ �Ѿ˼ӵ�
#define UP1 'w' // �÷��̾� 1 ����Ű
#define DOWN1 's' 
#define LEFT1 'a'
#define RIGHT1 'd'
#define P1SHOOT 32 // �÷��̾� 1 ����Ű
#define UP2 72 // �÷��̾� 2 ����Ű
#define DOWN2 80
#define LEFT2 75
#define RIGHT2 77
#define P2SHOOT '+' // �÷��̾� 2 ����Ű
#define BULLETS 20 // �ִ� �Ѿ� ����
#define BULLET1 10 // p1�� �׳��Ѿ�
#define BUSHBULLET1 11 // p1�� �ν��� �ִ� �Ѿ�
#define BULLET2 12 // p2�� �׳��Ѿ�
#define BUSHBULLET2 13 // p2�� �ν��� �ִ� �Ѿ�
#define P1BULLETCOLOR 5 // p1�� �Ѿ� ��
#define P2BULLETCOLOR 6 // p2�� �Ѿ� ��
#define DISTANCEATTACK 0.5 // �Ѿ� ����(���ݼӵ�)
#define MAP_RESET 'y' // ���¹�ư

int playerX, playerY, playerX2, playerY2, flag = 0, flag2 = 0, gun_x, gun_y, potion_x, potion_y;
int p1 = 3, p2 = 3; // p1, p2 ���
float ginpst, ginpst2;
int p1_ShootX[BULLETS], p1_ShootY[BULLETS], p1_Shoot_See[BULLETS], p1_Now_See, p1_ShootSpeed[BULLETS], p1Bullets = 0, p1DeleteBullets = 0;// �÷��̾���� �Ѿ��� x, y��ǥ, �����ִ¹���, �Ѿ˼ӵ�, �Ѿ˰���
int p2_ShootX[BULLETS], p2_ShootY[BULLETS], p2_Shoot_See[BULLETS], p2_Now_See, p2_ShootSpeed[BULLETS], p2Bullets = 0, p2DeleteBullets = 0;
float gundis1_st, gundis2_st; // �Ѿ� ������� ���� �ð��� �����ϴ� ����
int bulletload1 = 1, bulletload2 = 1; // ���ݼӵ����� ���� �� ��� �ϴ� ����
float gunst, stpt; // ������ ���� �ð��� ��� �Լ�
int list; // �޴�����Ʈ �Լ�

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
    if (kbhit()) // kbhit()�̿��� �Է°��� �ִ��� Ȯ�� 
    {
        return getch();     // �Է°��� getch()�� char�� ��������
    }
    return '\0'; // �Է°��� ������ �� ���� ����
}

int main(int argc, char *argv[]) {

    nocur(); // Ŀ�� ����
    system("mode con cols=120 lines=41"); // �ܼ� â ũ�� ����


    SOCKET clientsock;
    WSADATA wsa;
    struct sockaddr_in sockinfo;

    if (argc != 3) {
        printf("Usage : %s <IP> <PORT> \n", argv[0]);
        exit(1);
    }

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)

        printf("�ʱ�ȭ ����\n");

    clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientsock == INVALID_SOCKET)
        printf("���� ���� ����\n");

    memset(&sockinfo, 0, sizeof(sockinfo));

    sockinfo.sin_family = AF_INET;
    sockinfo.sin_port = htons(atoi(argv[2]));
    sockinfo.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
        printf(" ���� ���� ����\n");
    else
        printf("���� ���� ����\n");
    Sleep(2000);
    system("cls");


    char buf[100];

    while (1) {
        *buf = getKey();
        send(clientsock, buf, sizeof(buf), 0);

        // ���̶� ������ ���
    }
}