/*未解决食物坐标与蛇身重合的问题*/


#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>


#define ULength 20				//基本长度单位，取决于节点图形的大小


		

//定义蛇结构体
struct Snake{

	int x;
	int y;
	struct Snake* Next;

};

//全局变量


int MoveKey = 's';   //存储移动方向，依靠Monitor函数更新
struct Snake* Tail ; //存储蛇尾
struct Snake* Head ; //存储蛇头
struct Snake* P;     //工作指针
int FX;              //食物的横坐标
int FY;				 //食物的纵坐标
int T = 1;           //记录食物是否被吃掉

//函数声明
void Move();
void Update();
void GraphUpdate(int x);
void Monitor();
int KeyJudge(int K);
void Creat();
void Del(int x);
void MKfood();
int Test();
int EatJudge();
void Judge();
void WallJudge();
void MyselfJudge();
void MapPrint();
void SnakePrint(int x,int y);
void Clear(int x,int y);
void IExit();

void main()
{
	initgraph(640,480);
	MapPrint();
	//初始化一个三节蛇身
			
		//初始化蛇尾
	        Tail = (struct Snake*)malloc(sizeof(struct Snake));
			Tail->x = 100;
			Tail->y = 100;

		//初始化蛇身
			P = (struct Snake*)malloc(sizeof(struct Snake));
			P->x = 100;
			P->y = 100 + ULength;
			Tail->Next = P;

		//初始化蛇头
			Head = (struct Snake*)malloc(sizeof(struct Snake));
			Head->x = 100;
			Head->y = 100 + (ULength * 2);
			P->Next = Head;			
			Head->Next = NULL;
	
	
	//初始化蛇身和食物

		PIMAGE Img = newimage();

		getimage(Img,"snake.png");

		putimage(Tail->x,Tail->y,Img);
		putimage(P->x,P->y,Img);
		putimage(Head->x,Head->y,Img);

		MKfood();

		getch();
		
		while(1)
		{
			if(T)
			MKfood();
			Monitor();
			Move();
			delay_fps(10);
		}

	getch();

	closegraph();
}


//蛇身的移动

/*
	坐标的更新依靠新建蛇头节点，删除蛇尾节点实现
	图像的移动依靠在蛇尾处绘制背景图形，蛇头处绘制新蛇头实现


*/
void Move(){
  
	Update();	
  
}
			/*
				坐标的更新
					按照移动方向创建新的蛇头节点，Head指针赋新值，并删除蛇尾节点，Tail指针赋新值
					
			*/
			void Update(){
					
				switch(MoveKey)
				{
				   case 'w' : Creat(); (P->x) = (Head->x); (P->y) = ((Head->y) - ULength); Head = P;Judge();GraphUpdate(EatJudge());Del(EatJudge());break;   
				   case 's' : Creat(); (P->x) = (Head->x); (P->y) = ((Head->y) + ULength); Head = P;Judge();GraphUpdate(EatJudge());Del(EatJudge());break;
				   case 'a' : Creat(); (P->y) = (Head->y); (P->x) = ((Head->x) - ULength); Head = P;Judge();GraphUpdate(EatJudge());Del(EatJudge());break;
				   case 'd' : Creat(); (P->y) = (Head->y); (P->x) = ((Head->x) + ULength); Head = P;Judge();GraphUpdate(EatJudge());Del(EatJudge());break;
				}
			}
			void GraphUpdate(int x){
				  if(!x)   //参数x接收EatJudge函数的返回值，决定是否擦除蛇尾
				//清除蛇尾
					Clear(Tail->x ,Tail->y);
				//画上蛇头	
					SnakePrint(Head->x,Head->y);
				
			}


//键盘监听
void Monitor(){
	if(kbhit())
	{
		int A = getch();
		if((A == 'w' )||(A == 'a' )||(A == 's' ) ||(A == 'd' ))
			{

				if(KeyJudge(A))		//判断输入方向是否与原方向相反				
				    MoveKey = A;
			}
		else 
			{
				A = A + 32;    //判断是否为大写输入
						if((A == 'w' )||(A == 'a' )||(A == 's' ) ||(A == 'd' ))
							{
			
								if(KeyJudge(A))		//判断输入方向是否与原方向相反				
									MoveKey = A;					
							}
			}
		
	}
	
}

//判断输入方向是否与原方向相反
int KeyJudge(int K){
	
	switch(MoveKey)
		{
			 case 'w' : if(K == 's') return 0;break;
			 case 's' : if(K == 'w') return 0;break;
			 case 'a' : if(K == 'd') return 0;break;
			 case 'd' : if(K == 'a') return 0;break;
		}
	return 1;
}
 
//生成新的蛇身节点
void Creat(){
	
	P = (struct Snake*)malloc(sizeof(struct Snake));

	P->Next = NULL;

	Head->Next = P;

}
//更新尾部
void Del(int x){
	
	if(!x)    //参数x接收EatJudge的返回值，决定是否删除尾部节点
		{
			//更新指针Tail的值
			P = Tail;
			Tail = Tail->Next;
			//释放原Tail处的内存
			free(P);

			P = NULL;
		}
}

//随机生成食物
/*
	需判断食物坐标是否与蛇身重叠


*/
void MKfood(){
	T = 0;

		do{
			srand((unsigned)time(NULL));
			
			FX = rand()%28+1;
			
			FY = rand()%18+1;
		}while(!Test());
	
	PIMAGE Img = newimage();

	getimage(Img,"food.png");

	putimage(FX*ULength,FY*ULength,Img);

	delimage(Img);
}
//判断生成的食物是否与蛇身坐标重叠
int Test(){
	struct Snake* p = Tail;
	
	for(;p != NULL;p = p->Next)
	{
		if((FX==(p->x))&&(FY==(p->y)))
			return 0;
	}
	return 1;
}


//判断是否吃到食物
/*
	判断即将创建的下个蛇头节点是否与食物坐标相同
	如果相同，则不删除尾部节点

*/

int EatJudge(){
		int x = Head->x;
		int y = Head->y;
	if((x==FX*ULength)&&(y==FY*ULength)) 
	{
		T = 1;
		return 1;
	}

	return 0;
}



//判断是否结束游戏

void Judge()
{
	WallJudge();
	MyselfJudge();
}
			//判断是否撞墙

			/*

				判断即将创建的头部节点是否横纵坐标是否越界

			*/
			void WallJudge(){
				int x = Head->x;
				int y = Head->y;
				if((x==0)||(x==(30*ULength))) 
					IExit();
				if((y==0)||(y==(20*ULength)))
					IExit();
				
			}

			//判断是否咬到自身
			/*
				遍历链表查询即将创建的头部节点是否坐标与其他节点相同
			*/
			void MyselfJudge(){
				
				struct Snake* p = Tail->Next;
				int x = Head->x;
				int y = Head->y;

				for(;p!=Head;p=(p->Next))
				{
					if((x==(p->x))&&(y==(p->y)))
						IExit();	
				}
				
				
					
			}

//初始化地图
void MapPrint(){
	
	int i;

	PIMAGE Img = newimage();

	getimage(Img ,"wall.png");

	for(i=0;i<=20;i++)
	{
		putimage(0*ULength,i*ULength,Img);
	}

	for(i=0;i<=20;i++)
	{
		putimage(30*ULength,i*ULength,Img);
	}
	
	for(i=0;i<=30;i++)
	{
		putimage(i*ULength,0*ULength,Img);
	}

	
	for(i=0;i<=30;i++)
	{
		putimage(i*ULength,20*ULength,Img);
	}

	delimage(Img);

}

//画蛇身
void SnakePrint(int x,int y){
	PIMAGE Img = newimage();
	
	getimage(Img,"snake.png");

	putimage(x,y,Img);

	delimage(Img);
}

//擦除蛇尾
void Clear(int x,int y){
	
	PIMAGE Img = newimage();
	
	getimage(Img,"Black.png");

	putimage(x,y,Img);

	delimage(Img);
}


//游戏结束

void IExit()
{
	//显示结束界面
	
	

	setcolor(EGERGB(0xFF, 0xFF, 0xFF));

	setfontbkcolor(EGERGB(0x80, 0x80, 0x80));

	setfont(100,0,"楷体");

	outtextxy(120,120,"游戏结束");

	getch();

	exit(0);
	  

}