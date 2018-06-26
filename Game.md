# Game

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define SPACE 0
#define WALL 1
#define PLAYER1 2
#define PLAYER2 3
#define PLAYER3 4
#define PLAYER4 5
#define WATERB 6

struct ballon //물풍선 좌표 구조체
{
   int x; int y;
}Wballon[8] = { 0 };
int player1X = 1, player1Y = 1, palyer2X = 18, palyer2Y = 18; // 플레이어 초기 좌표
int waterb = 0; //물풍선 초기 개수
int map[20][20] = {
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
   { 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
   { 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1 },
   { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

void removeCursor(); //커서 지우기 함수
void gotoxy(int, int);
void printMap(); //맵 출력 함수
void playerInput(); //플레이어 입력 함수
void movePlayer(int, int); //플레이어 이동 함수
void BmovePlayer(); //물풍선 생성 직후 플레이어 이동 함수
void PmovePlayer(int, int); //물풍선 터짐 함수 도중 플레이어 이동 함수
void printWaterb(int); //물풍선 출력 함수
void popWaterb(int, int); //물풍선 터짐 함수
void printpopwater(int, int); //물풍선 터짐 연출 함수
void removewaterb(int); //물풍선 터짐 연출 삭제 함수

int main(){
   int life = 1;

   removeCursor();
   printMap();

   while (life != 0)
   {
      playerInput();
   }
}

void removeCursor()
{
   CONSOLE_CURSOR_INFO cursorInfo = { 0, };
   cursorInfo.dwSize = 1;
   cursorInfo.bVisible = FALSE;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y)
{
   COORD Pos;
   Pos.X = x * 2;
   Pos.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void playerInput()
{
   int playerInput;

   playerInput = getch();
   if (playerInput == -32)
      playerInput = getch();
   if (playerInput == 75) //left
      movePlayer(-1, 0);
   else if (playerInput == 77) //right
      movePlayer(1, 0);
   else if (playerInput == 72) //up
      movePlayer(0, -1);
   else if (playerInput == 80) //down
      movePlayer(0, 1);
   else if (playerInput == 32) //waterballon
      printWaterb(0);
}

void movePlayer(int dx, int dy)   //플레이어 이동 함수
{
   if (map[player1Y + dy][player1X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
   {
      gotoxy(player1X, player1Y);
      printf("  "); //원래 좌표에 공백 출력
      map[player1Y][player1X] = SPACE; //원래 좌표 공간에 SPACE 저장
      player1X += dx;
      player1Y += dy;
      gotoxy(player1X, player1Y);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      printf("▲"); //이동 좌표에 플레이어 출력
      map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
   }
}

void BmovePlayer() //물풍선 생성 직후 플레이어 이동 함수
{
   int playerInput, dx, dy;

   playerInput = getch();

   if (playerInput == 224)
      playerInput = getch();

      if (playerInput == 75) //left
      {
         dx = -1;
         dy = 0;
      }
      else if (playerInput == 77) //right
      {
         dx = 1;
         dy = 0;
      }
      else if (playerInput == 72) //up
      {
         dx = 0;
         dy = -1;
      }
      else if (playerInput == 80) //down
      {
         dx = 0;
         dy = 1;
      }
      else BmovePlayer();

   if (map[player1Y + dy][player1X + dx] == SPACE) //이동할 공간에 아무것도 없는지 비교
   {
      gotoxy(player1X, player1Y);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      printf("○"); //원래 좌표에 물풍선 출력
      map[player1Y][player1X] = WATERB; //원래 좌표 공간에 WATERB 저장
      player1X += dx;
      player1Y += dy;
      gotoxy(player1X, player1Y);
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
      printf("▲"); //이동 좌표에 플레이어 출력
      map[player1Y][player1X] = PLAYER1; //이동 좌표 공간에 PLAYER1 저장
   }
   else BmovePlayer();
}

void PmovePlayer(int num1, int num) //popWaterb 전용 플레이어 이동 함수
{
   int playerInput, dx, dy, i;

   for (i = 1; i < 150; i++){
      if (_kbhit()){ //키보드 입력 시만 실행
         playerInput = getch();

         if (playerInput == 224)
            playerInput = getch();
         if (playerInput == 75) //left
            movePlayer(-1, 0);
         else if (playerInput == 77) //right
            movePlayer(1, 0);
         else if (playerInput == 72) //up
            movePlayer(0, -1);
         else if (playerInput == 80) //down
            movePlayer(0, 1);
         else if (playerInput == 32) //waterballon
            printWaterb(num1);
      }
      Sleep(10); //0.01초 동안 for문 한 번 실행 : 키보드 입력 없을 시 다음으로 넘어감
    }
   for (i = 1; i < 18; i++){
      if (_kbhit()){ //키보드 입력 시만 실행
         playerInput = getch();

         if (playerInput == 224)
            playerInput = getch();
         if (playerInput == 75) //left
            movePlayer(-1, 0);
         else if (playerInput == 77) //right
            movePlayer(1, 0);
         else if (playerInput == 72) //up
            movePlayer(0, -1);
         else if (playerInput == 80) //down
            movePlayer(0, 1);
         else if (playerInput == 32) //waterballon
            printWaterb(num1);
      }
      if (i % 3 == 0)
         printpopwater(i/3, num);
      Sleep(10);
   }
   removewaterb(num);
   gotoxy(Wballon[num].x, Wballon[num].y); printf("  ");
}

void printMap() //맵 출력 함수
{
   int i, j;

   for (i = 0; i < 20; i++)
   {
      for (j = 0; j < 20; j++)
      {
         if (map[i][j] == SPACE)
            printf("  ");
         else if (map[i][j] == WALL)
            printf("■");
         else if (map[i][j] == PLAYER1)
            printf("▲");
         else if (map[i][j] == PLAYER2)
            printf("▽");
         else if (map[i][j] == PLAYER3)
            printf("△");
         else if (map[i][j] == PLAYER4)
            printf("▼");
      }
      printf("\n");
   }
}   

void printWaterb(int num1) //물풍선 출력 함수
{
   int i;
   if (waterb < 2) //현재 생성되어있는 물풍선 개수 비교
   {
      for (i = 0; i <= 1; i++)
      {
         if (Wballon[i].x == 0) //비어있는 구조체인지 확인
         {
            Wballon[i].x = player1X; //i번 물풍선 X좌표에 플레이어 X좌표 저장
            Wballon[i].y = player1Y; //i번 물풍선 Y좌표에 플레이어 Y좌표 저장
            break;
         }
      }
      BmovePlayer();
      waterb++;
      popWaterb(i, num1);
   }
}

void popWaterb(int num, int num1) //물풍선 터짐 함수
{ 
   int i;
   if (waterb == 1){ //생성된 물풍선이 한 개일 경우
      num1 = num; 
      PmovePlayer(num1, num1);
      if (waterb == 1)
      {
         Wballon[num].x = 0;
         waterb--; //물풍선 터짐 이후 현재 물풍선의 개수 --
      }
   }
   else if (waterb == 2)
   {
      PmovePlayer(num1, num1); //물풍선이 두개이기 때문에 먼저 들어온 물풍선과 나중에 들어온 물풍선을 비교하기 위해 num1 사용
      Wballon[num1].x = 0;
      num1 = num;
      waterb--;
      PmovePlayer(num1, num);
      Wballon[num1].x = 0;
      waterb--;
   }
}

void printpopwater(int i, int num)
{
   if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
   {
      if (Wballon[num].y - i > 0)
      {
         gotoxy(Wballon[num].x, Wballon[num].y - i);
         if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1)
            printf("●");
         else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
            printf("○");
         else printf("▒");
      }
   }
   if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //물풍선 아래쪽에 벽이 있는지 비교
   {
      if (Wballon[num].y + i < 20)
      {
         gotoxy(Wballon[num].x, Wballon[num].y + i);
         if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1)
            printf("●");
         else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
            printf("○");
         else printf("▒");
      }
   }
   if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //물풍선 왼쪽에 벽이 있는지 비교
   {
      if (Wballon[num].x - i > 0)
      {
         gotoxy(Wballon[num].x - i, Wballon[num].y);
         if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1)
            printf("●");
         else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
            printf("○");
         else printf("▒");
      }
   }
   if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //물풍선 오른쪽에 벽이 있는지 비교
   {
      if (Wballon[num].x + i < 20)
      {
         gotoxy(Wballon[num].x + i, Wballon[num].y);
         if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1)
            printf("●");
         else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
            printf("○");
         else printf("▒");
      }
   }

}

void removewaterb(int num)
{
   int i;

   for (i = 0; i <= 6; i++)
   {
      if (map[Wballon[num].y - i][Wballon[num].x] != WALL) //물풍선 위쪽에 벽이 있는지 비교
      {
         if (Wballon[num].x >= 0 && Wballon[num].y - i >= 0)
         {
            gotoxy(Wballon[num].x, Wballon[num].y - i);
            if (map[Wballon[num].y - i][Wballon[num].x] == PLAYER1)
               printf("●");
            else if (map[Wballon[num].y - i][Wballon[num].x] == WATERB)
               printf("○");
            else printf(" ");
         }
      }
      if (map[Wballon[num].y + i][Wballon[num].x] != WALL) //물풍선 아래쪽에 벽이 있는지 비교
      {
         if (Wballon[num].x >= 0 && Wballon[num].y + i >= 0)
         {
            gotoxy(Wballon[num].x, Wballon[num].y + i);
            if (map[Wballon[num].y + i][Wballon[num].x] == PLAYER1)
               printf("●");
            else if (map[Wballon[num].y + i][Wballon[num].x] == WATERB)
               printf("○");
            else printf(" ");
         }
      }
      if (map[Wballon[num].y][Wballon[num].x - i] != WALL) //물풍선 왼쪽에 벽이 있는지 비교
      {
         if (Wballon[num].x - i >= 0 && Wballon[num].y >= 0)
         {
            gotoxy(Wballon[num].x - i, Wballon[num].y);
            if (map[Wballon[num].y][Wballon[num].x - i] == PLAYER1)
               printf("●");
            else if (map[Wballon[num].y][Wballon[num].x - i] == WATERB)
               printf("○");
            else printf(" ");
         }
      }
      if (map[Wballon[num].y][Wballon[num].x + i] != WALL) //물풍선 오른쪽에 벽이 있는지 비교
      {
         if (Wballon[num].x + i >= 0 && Wballon[num].y >= 0)
         {
            gotoxy(Wballon[num].x + i, Wballon[num].y);
            if (map[Wballon[num].y][Wballon[num].x + i] == PLAYER1)
               printf("●");
            else if (map[Wballon[num].y][Wballon[num].x + i] == WATERB)
               printf("○");
            else printf(" ");
         }
      }
   }
   map[Wballon[num].y][Wballon[num].x] = SPACE;
}