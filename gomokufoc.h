#include<stdio.h>
#include<stdlib.h>
#define N 15
#define BOARD_LIM (i>=1 && i<=N && j>=1 && j<=N)
int board[N + 1][N + 1] = { 0 };
int turn = 0;


void initboard(void);/*��ʼ������*/

void displayboard(void);/*��ʾ����*/

void playchess(void);/*��ʼ����*/

void playchess_c(void);/*�˻�����*/

int  winner(int, int);/*�ж���Ӯ*/

int computerjudge(int, int);/*�����ж�*/

void computerdefense(int, int);



void initboard(void)/*���� ��ʼ������ ����*/
{
	char start;

	puts("Please enter the \'A\'to start the gobang:");/*����yȥ��ʼ*/
	while (getchar() != '\n')/*������棨����س����ţ�*/
		continue;
	start = getchar();
	if (start != 'a' && start != 'A')
		exit(0);

	system("cls");
	displayboard();


}

void displayboard(void)/*���� ��ʾ���� ����*/
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
				printf("  �p");
		}
		printf("\n");
	}


}


void playchess(void)/*���� ��ʼ���� ����*/
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

	system("cls");/*ˢ������*/
	displayboard();

	if (winner(i, j))/*�ж���Ӯ*/
	{
		printf("winner is player %c\n", turn % 2 == 1 ? '1' : '2');
		exit(EXIT_SUCCESS);
	}

}

void playchess_c(void)/*���� �˻����� ����*/
{
	int i=0, j=0;
	int t = turn % 2 == 1 ? 1 : 2;
	if (t == 1)											//�������
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

		system("cls");/*ˢ������*/
		displayboard();


	}
	else if (t == 2)												//��������
	{
		
		
		
		
			int rand(void);
			int l = rand() % 15 + 1;
			int r = rand() % 15 + 1;
			i = l;
			j = r;
			board[i][j] = 2;
			
		

		system("cls");/*ˢ������*/
		displayboard();

	}

	if (winner( i, j) == 1)/*�ж���Ӯ*/
	{
		printf("winner is player %c\n", turn % 2 == 1 ? '1' : '2');
		exit(EXIT_SUCCESS);
	}
	

}

int computerjudge(int x, int y)/*���� �����ж� ����*/
{
	int i, j, r;
	int t = 2 - turn % 2;

	for (r = 1, i = x, j = y; board[++i][j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (i = x, j = y; board[--i][j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);/*��������*/

	for (r = 1, i = x, j = y; board[i][++j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	for (i = x, j = y; board[i][--j] == t && BOARD_LIM && r <= 3; r++)
		continue;
	if (r >= 3)
		computerdefense(i, j);/*��������*/

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
		computerdefense(i, j);/*�Խ�������*/

}

void computerdefense(int i,int j)
{

	
		if (board[i - 1][j] == 1) {

			board[i +1 ][j] = 2;
		}
		else if (board[i + 1][j] == 1) {

			board[i - 1][j] = 2;						//��������ʱ����סһ������
		}
		else if (board[i][j - 1] == 1) {

			board[i][j + 1] = 2;
		}
		else if (board[i][j + 1] == 1) {

			board[i][j - 1] = 2;						//��������ʱ����סһ������
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

			board[i + 1][j + 1] = 2;				//�Խ�������ʱ����סһ������
		}
			
}

int winner(int x, int y)/*���� �ж���Ӯ ����*/
{
	int i, j, r;
	int t = 2 - turn % 2;

	for (r = 1, i = x, j = y; board[++i][j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (i = x, j = y; board[--i][j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;/*��������*/

	for (r = 1, i = x, j = y; board[i][++j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	for (i = x, j = y; board[i][--j] == t && BOARD_LIM && r <= 5; r++)
		continue;
	if (r >= 5)
		return 1;/*��������*/

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
		return 1;/*�Խ�������*/

	return 0;

}
