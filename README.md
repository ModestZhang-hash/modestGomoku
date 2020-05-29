# 五子棋程序设计的几点个人理解

本人在对简单五子棋程序设计的过程中的几个难点的个人思考和理解， 当然没到使用极大值极小值算法和Alpha-Beta剪枝的那种高级算法的程度， 只是能够使用最基本的C语言知识来尽可能的进行合理的模拟。在这过程中会有几个难点，写在这里便于理解思考：

## 1.棋盘的设置

首先面临的难点就是棋盘的设置，暂且不谈使用调用window.h 来实现一个完美的五子棋封面，仅仅通过终端窗口来实现棋盘的展现难免需要我们有一定的想象力，我们可以通过一个16 * 16的“ * ” 阵来展现属于自己设计的棋盘，当然棋盘的设计是由你自己决定，你完全可以使用“ + ”来代替 “ * ” （实际上使用“ + ” 似乎效果更好一点..）实际的效果类似是这样的：
![](https://img-blog.csdnimg.cn/20200526185255453.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQyNjk5MTI5,size_16,color_FFFFFF,t_70)
在这里我利用的是“ * ”来构造的棋盘，当然你也可以使用“ + ” 来完成棋盘的构造。
这里给出我构造这种“简陋”棋盘的代码块：

```
void initboard(void)/*定义 初始化棋盘 函数*/
{
	 char start;
	 
     puts("Please enter the \'A\'to start the gobang:");/*输入y去开始*/
	 while (getchar()!='\n')/*清除缓存（清除回车符号）*/
		 continue;
     start=getchar();
	 if(start!='a' && start!='A')
		 exit(0);

	 system("cls");
	 displayboard();


}
```

如你所见，简单的利用while 循环而已，当然我是用函数封装了代码块，这么做的目的是为了代码的简洁性以及可读性。（实际上之后讲到的一些功能都是通过函数封装过的）这里用了一个小技巧：

```
while (getchar()!='\n')/*清除缓存（清除回车符号）*/
		 continue;
```

你或许问这段是想干嘛用的，是否有点多此一举了，然而不仅不多此一举，反而大有用处，它为了当你在从键盘输入A之后输入回车， 防止计算机接收到的是你输入的回车而不是你想让计算机接收的A。
接着比较重要的的就是这个清屏函数：

```
#include<stdlib.h>
...
...
system("cls");
```

当然，前面你必须有加标准库头文件<stdlib.h>。

## 2.玩家对战

当然在你刚开始考虑这个难点时似乎真的无从下手，即使你从百度百科或是CSDN社区查找相关的资料关于五子棋的程序设计思路，甚至条件允许登录外网wiki, stack overflow, 查找，询问相关问题， 自己还是不知道从哪里开始想，从哪里入手，因为毕竟这是要你自己去做的程序啊，你或许查找得到极大值极小值算法，厉害的话再加上Alpha-Beta剪枝优化，wiki 上仔细阅读极大值极小值算法的原理，但就算你真的理解了极大值极小值原理的精髓所在（当时的我甚至查找了2010年 某高校的关于威胁空间搜索树的算法的论文拿来仔细的研读，但实际上就算我读完论文我也不知道该如何再我的程序设计中实现）。这让我不得不考虑暂时放下算法方面的东西， 从最简单的原理做起。先给出整体的代码块：

```
void playchess(void)/*定义 开始走棋 函数*/
{	
     int i,j;
     printf("Turn to player %c,Please enter the position :",turn%2==1?'1':'2');
	 scanf("%d,%d",&i,&j);


	 while(!BOARD_LIM)
	 {
	      fprintf(stderr,"Not in the size of board,try again:");

          scanf("%d,%d",&i,&j);
	 
	 }
	 while(board[i][j]!=0)
	 {
	      printf("This position has been occupied,please enter the position again:");
		  scanf("%d,%d",&i,&j);
	 
	 }

	 board[i][j]=turn%2==1?1:2;

	 system("cls");/*刷新棋盘*/
	 displayboard();
	 
	 if(winner(i,j))/*判断输赢*/
	 {
		 printf("winner is player %c\n",turn%2==1?'1':'2');
	     exit(EXIT_SUCCESS);
	 }

}
```

在这里我想到了几点需要解决的：

  1. 棋子不能超出棋盘边界：
     这一点应该不用过多解释吧，不解决人家还以为你写了个BUG
      	这一点再解决时的代码具体是这样的：


```
#define BOARD_LIM (i>=1 && i<=N && j>=1 && j<=N)
....
....
while(!BOARD_LIM)
	 {
	      fprintf(stderr,"Not in the size of board,try again:");

          scanf("%d,%d",&i,&j);
	 
	 }
```

如你所见，我用了一个简单的宏定义不至于到后面写起来太麻烦，当然也是为了代码的可读性。原理也很简单，while 语句保证让玩家输入棋子坐标超出边界时让他重复输入知道他输入正确（不超出边界）

  2. 如果某个位置有棋子，当然就不能再次在那个位置下棋：
     这一点也是应该想到的，但是并不难。具体代码是这样的：


```
while(board[i][j]!=0)
	 {
	      printf("This position has been occupied,please enter the position again:");
		  scanf("%d,%d",&i,&j);
	 
	 }
```

  3. 什么时候轮到谁下棋：
     这个难点刚开始想似乎真的不懂怎么整，不过我自己使用的是用一个turn变量来计算回合，赋初值turn = 0;之后每回合结束累加一次，也就是说，玩家一下棋是turn是个偶数(能被2整除)，玩家二下棋时turn是个奇数(不能被2整除)：

```
board[i][j] = turn % 2 == 1 ? 1 : 2;
```

## 人机对战

当你真正想通玩家对战并完成代码开始考虑人机对战的时候，你发现并不是想象中的那么相似，或者说，容易。因为就目前的个人能力来说还无法做到使用理论上的各种算法（诸如比较经典的专门针对五子棋等棋类博弈问题的极大值极小值算法，加上Alpha-Beta剪枝算法优化），我们尽可能地想让计算机在跟我们下棋对战时不至于看起来那么的笨，这就需要我们解决另外一些难点，这里先给出代码块：

```
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


```

（看起来明显比玩家对战的代码多了不少）

  1. 计算机在哪下棋：
     在哪下棋的问题， 我们优先考虑的是利用随机数来生成：


```
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
```

当然我不敢保证计算机能够聪明的按部就班的尽力连成五子，但至少能保证的时他能下棋。

  2. 如何让电脑变得“聪明”：
     在不会使用高级的算法的情况下想让计算机下棋能够变得聪明似乎不切实际，但我们还是尽力的想让它看起来不是那么的笨，我们根据输赢的危机感，从最简单的情况开始考虑的话，当玩家快要连成五子时（横竖斜对角线四子），我们至少要让计算机想到要努力堵住玩家的下一步胜利：


```
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
```

```
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
```

这是我个人能够想到的最笨的方式让计算机变得“聪明”的方式了，说实话，代码看起来真的很冗长（甚至有点笨重），但至少还算是变”聪明“让它看起来真的不是那么呆。

  4. 一点额外的想法：我甚至想过通过修改计算机的下棋方式（随机数生成）来让计算机更加智能，比如我让第一步棋随机数生成，接下来的几步棋在第一步棋周围布置（上下左右），接着第三步棋在第二步棋周围布置，但实际的能力并没有做到那里。

 ## 3.判断输赢

 相对于前面两个难点，判断输赢函数似乎并不是那么的难，只需要判断横竖斜对角线是否连成五子来定输赢，这里直接给出代码块：


```
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
```

```
if (winner( i, j) == 1)/*判断输赢*/
	{
		printf("winner is player %c\n", turn % 2 == 1 ? '1' : '2');
		exit(EXIT_SUCCESS);
	}
```


## 参考文献及网站

  1. CSDN社区：[https://www.csdn.net/](https://www.csdn.net/)
  2. 百度百科：极大值极小值算法：[百度百科极大值极小值算法](https://baike.baidu.com/item/%E6%9E%81%E5%A4%A7%E6%9E%81%E5%B0%8F%E5%80%BC%E7%AE%97%E6%B3%95/19473878)
  3. 维基中文镜像:
     [https://zh.jinzhao.wiki/wiki/Wikipedia:%E7%BB%B4%E5%9F%BA%E7%99%BE%E7%A7%91%E6%8B%B7%E8%B4%9D%E7%BD%91%E7%AB%99](https://zh.jinzhao.wiki/wiki/Wikipedia:%E7%BB%B4%E5%9F%BA%E7%99%BE%E7%A7%91%E6%8B%B7%E8%B4%9D%E7%BD%91%E7%AB%99)
  4. 《一种 改进 的威胁空 间搜索算法》（湖南文理学院报（自然科学报）2010年9月 第22卷 第3期）
  5. Alpha-Beta剪枝优化的极大值极小值算法讲解网站：
     [https://www.hackerearth.com/blog/developers/minimax-algorithm-alpha-beta-pruning/](https://www.hackerearth.com/blog/developers/minimax-algorithm-alpha-beta-pruning/)
  6. 春季网(Spring):
     [https://www.baeldung.com/category/spring/](https://www.baeldung.com/category/spring/)

  7. Stack Overflow问答社区:
     [https://stackoverflow.com/?newreg=d96b742d5b104cfa93249cdd9d56bb13](https://stackoverflow.com/?newreg=d96b742d5b104cfa93249cdd9d56bb13)
  8. CS 161复习笔记：带有Alpha-Beta剪枝的Minmax:
     [http://web.cs.ucla.edu/~rosen/161/notes/alphabeta.html](
