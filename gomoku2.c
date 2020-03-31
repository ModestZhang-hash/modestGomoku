#include<stdio.h>
#include<stdlib.h>
#include"gomokufoc.h"



int main(void)
{
	int opt;
	int o;
	int run = 1;
	printf("               *************************************\n");
	printf("               *** Welome To The Game of Gobang! ***\n ");/*菜单界面*/
	printf("               *************************************\n");
	printf("               ***************** menu *****************\n");
	printf("               ***********1. Start the game************\n");/*开始游戏选项*/
	printf("               ***********2. Quit  the game************\n");/*退出游戏选项*/
	printf("               ***********3. Play with the computer****\n");
	printf("               ****************************************\n");



	printf("Choose your option:\n");
	scanf_s("%d", &opt);/*输入你的选项*/
	switch (opt)
	{
	case 2:
		while (1)
		{
			//getchar();
			printf("Are you sure to Quit?(y/n)");/*确定是否退出*/
			o = getchar();
			switch (o)
			{
			case'y':
				exit(EXIT_SUCCESS);
				break;
			case'n':
			{
				initboard();
				while (1)
				{

					turn++;

					playchess();
				}
			}
			break;
			default:
				break;

			}
			if ((o == 'y') || (o == 'n'))break;

		}
		break;

	case 1:
		initboard();
		while (1)
		{

			turn++;

			playchess();
		}

		break;
		/*if(opt==1)
		{
		initboard();
			 while(1)
			 {

				turn++;

				playchess();
			 }*//*原始代码*/
	case 3:
		initboard();
		while (1)
		{

			turn++;

			playchess_c();
		}

		break;

	} return 0;

}

/*switch(opt)
{
case 2:
   while(1)
   {
	getchar();
	printf("Are you sure to Quit?(y/n)");
	o=getchar();
	switch(o)
	{
	 case'y':
		exit(EXIT_SUCCESS);
		break;
	 case'n':
		 {
		 initboard();
	while(1)
	{

	   turn++;

	   playchess();
	}
		 }
		 break;
	 default:
			 break;

	}
	if((o=='y')||(o=='n'))break;

	}
	break;

case 1:
	initboard();
	while(1)
	{

	   turn++;

	   playchess();
	}

	   break;


 return 0;

}
*//*有error的代码*/
















