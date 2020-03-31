#include<stdio.h>
#include<stdlib.h>
#define N 15
#define BOARD_LIM (i>=1 && i<=N && j>=1 && j<=N)
int board[N + 1][N + 1] = { 0 };
int turn = 0;


void initboard(void);/*初始化棋盘*/

void displayboard(void);/*显示棋盘*/

void playchess(void);/*开始走棋*/

void playchess_c(void);/*人机下棋*/

int  winner(int, int);/*判断输赢*/

int computerjudge(int, int);/*电脑判断*/

void computerdefense(int, int);



void initboard(void)/*定义 初始化棋盘 函数*/
{
	char start;

	puts("Please enter the \'A\'to start the gobang:");/*输入y去开始*/
	while (getchar() != '\n')/*清除缓存（清除回车符号）*/
		continue;
	start = getchar();
	if (start != 'a' && start != 'A')
		exit(0);

	system("cls");
	displayboard();


}

void displayboard(void)/*定义 显示棋盘 函数*/
{
	int i, j;
	for (i = 0; i <= N; i++)
	{
		for (j = 0; j <= N; j++)
		{
			if (i == 0)
				printf("%3d", j);
			else if (j == 0)
				printf("%3d", i);
			else if (board[i][j] == 1)
				printf("  O");
			else if (board[i][j] == 2)
				printf("  X");
			else
				printf("  ╬");
		}
		printf("\n");
	}


}


void playchess(void)/*定义 开始走棋 函数*/
{
	int i, j;
	printf("Turn to player %c,Please enter the position :", turn % 2 == 1 ? '1' : '2');
	scanf_s("%d,%d", &i, &j);


	while (!BOARD_LIM)
	{
		fprintf(stderr, "Not in the size of board,try again:");
		scanf_s("%d,%d", &i, &j);

	}
	while (board[i][j] != 0)
	{
		printf("This position has been occupied,please enter the position again:");
		scanf_s("%d,%d", &i, &j);

	}

	board[i][j] = turn % 2 == 1 ? 1 : 2;

	system("cls");/*刷新棋盘*/
	displayboard();

	if (winner(i, j))/*判断输赢*/
	{
		printf("winner is player %c\n", turn % 2 == 1 ? '1' : '2');
		exit(EXIT_SUCCESS);
	}

}

void playchess_c(void)/*定义 人机下棋 函数*/
{
	int i=0, j=0;
	int t = turn % 2 == 1 ? 1 : 2;
	if (t == 1)											//玩家走棋
	{

		printf("Turn to player ,Please enter the position :");
		scanf_s("%d,%d", &i, &j);


		while (!BOARD_LIM)
		{
			fprintf(stderr, "Not in the size of board,try again:");
			scanf_s("%d,%d", &i, &j);

		}
		while (board[i][j] != 0)
		{
			printf("This position has been occupied,please enter the position again:");
			scanf_s("%d,%d", &i, &j);

		}

		board[i][j] = 1;

		computerjudge(i, j);
		//computerdefense(i, j);

		system("cls");/*刷新棋盘*/
		displayboard();


	}
	else if (t == 2)												//电脑走棋
	{
		
		
		
		
			int rand(void);
			int l = rand() % 15 + 1;
			int r = rand() % 15 + 1;
			i = l;
			j = r;
			board[i][j] = 2;
			
		

		system("cls");/*刷新棋盘*/
		displayboard();

	}

	if (winner( i, j) == 1)/*判断输赢*/
	{
		printf("winner is player %c\n", turn % 2 == 1 ? '1' : '2');
		exit(EXIT_SUCCESS);
	}
	

}

int computerjudge(int x, int y)/*定义 电脑判断 函数*/
{
	int i, j, r;
	int t = 2 - turn % 2;

	for (r = 1, i = x, j = y; board[++i][j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (i = x, j = y; board[--i][j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);/*横向三子*/

	for (r = 1, i = x, j = y; board[i][++j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (i = x, j = y; board[i][--j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);/*纵向三子*/

	for (r = 1, i = x, j = y; board[++i][--j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (i = x, j = y; board[--i][++j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);

	for (r = 1, i = x, j = y; board[++i][++j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (r = 1, i = x, j = y; board[--i][--j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);/*对角线三子*/

}

void computerdefense(int i,int j)
{

	
		if (board[i - 1][j] == 1) {

			board[i +1 ][j] = 2;
		}
		else if (board[i + 1][j] == 1) {

			board[i - 1][j] = 2;						//横向三子时，堵住一个方向
		}
		else if (board[i][j - 1] == 1) {

			board[i][j + 1] = 2;
		}
		else if (board[i][j + 1] == 1) {

			board[i][j - 1] = 2;						//纵向三子时，堵住一个方向
		}
		else if (board[i - 1][j + 1] == 1) {

			board[i + 1][j - 1] = 2;
		}
		else if (board[i + 1][j - 1] == 1) {

			board[i - 1][j + 1] = 2;
		}
		else if (board[i + 1][j + 1] == 1) {

			board[i - 1][j - 1] = 2;
		}
		else if (board[i - 1][j - 1] == 1) {

			board[i + 1][j + 1] = 2;				//对角线三子时，堵住一个方向
		}
			
}

int winner(int x, int y)/*定义 判断输赢 函数*/
{
	int i, j, r;
	int t = 2 - turn % 2;

	for (r = 1, i = x, j = y; board[++i][j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (i = x, j = y; board[--i][j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;/*横向五子*/

	for (r = 1, i = x, j = y; board[i][++j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (i = x, j = y; board[i][--j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;/*纵向五子*/

	for (r = 1, i = x, j = y; board[++i][--j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (i = x, j = y; board[--i][++j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;

	for (r = 1, i = x, j = y; board[++i][++j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (r = 1, i = x, j = y; board[--i][--j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;/*对角线五子*/

	return 0;

}
