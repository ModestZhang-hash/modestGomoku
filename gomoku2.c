#include<stdio.h>
#include<stdlib.h>
#include"gomokufoc.h"



int main(void)
{
	int opt;
	int o;
	int run = 1;
	printf("               *************************************\n");
	printf("               *** Welome To The Game of Gobang! ***\n ");/*�˵�����*/
	printf("               *************************************\n");
	printf("               ***************** menu *****************\n");
	printf("               ***********1. Start the game************\n");/*��ʼ��Ϸѡ��*/
	printf("               ***********2. Quit  the game************\n");/*�˳���Ϸѡ��*/
	printf("               ***********3. Play with the computer****\n");
	printf("               ****************************************\n");



	printf("Choose your option:\n");
	scanf_s("%d", &opt);/*�������ѡ��*/
	switch (opt)
	{
	case 2:
		while (1)
		{
			//getchar();
			printf("Are you sure to Quit?(y/n)");/*ȷ���Ƿ��˳�*/
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
			 }*//*ԭʼ����*/
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
*//*��error�Ĵ���*/
















