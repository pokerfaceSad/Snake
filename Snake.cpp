/*δ���ʳ�������������غϵ�����*/


#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>


#define ULength 20				//�������ȵ�λ��ȡ���ڽڵ�ͼ�εĴ�С


		

//�����߽ṹ��
struct Snake{

	int x;
	int y;
	struct Snake* Next;

};

//ȫ�ֱ���


int MoveKey = 's';   //�洢�ƶ���������Monitor��������
struct Snake* Tail ; //�洢��β
struct Snake* Head ; //�洢��ͷ
struct Snake* P;     //����ָ��
int FX;              //ʳ��ĺ�����
int FY;				 //ʳ���������
int T = 1;           //��¼ʳ���Ƿ񱻳Ե�

//��������
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
	//��ʼ��һ����������
			
		//��ʼ����β
	        Tail = (struct Snake*)malloc(sizeof(struct Snake));
			Tail->x = 100;
			Tail->y = 100;

		//��ʼ������
			P = (struct Snake*)malloc(sizeof(struct Snake));
			P->x = 100;
			P->y = 100 + ULength;
			Tail->Next = P;

		//��ʼ����ͷ
			Head = (struct Snake*)malloc(sizeof(struct Snake));
			Head->x = 100;
			Head->y = 100 + (ULength * 2);
			P->Next = Head;			
			Head->Next = NULL;
	
	
	//��ʼ�������ʳ��

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


//������ƶ�

/*
	����ĸ��������½���ͷ�ڵ㣬ɾ����β�ڵ�ʵ��
	ͼ����ƶ���������β�����Ʊ���ͼ�Σ���ͷ����������ͷʵ��


*/
void Move(){
  
	Update();	
  
}
			/*
				����ĸ���
					�����ƶ����򴴽��µ���ͷ�ڵ㣬Headָ�븳��ֵ����ɾ����β�ڵ㣬Tailָ�븳��ֵ
					
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
				  if(!x)   //����x����EatJudge�����ķ���ֵ�������Ƿ������β
				//�����β
					Clear(Tail->x ,Tail->y);
				//������ͷ	
					SnakePrint(Head->x,Head->y);
				
			}


//���̼���
void Monitor(){
	if(kbhit())
	{
		int A = getch();
		if((A == 'w' )||(A == 'a' )||(A == 's' ) ||(A == 'd' ))
			{

				if(KeyJudge(A))		//�ж����뷽���Ƿ���ԭ�����෴				
				    MoveKey = A;
			}
		else 
			{
				A = A + 32;    //�ж��Ƿ�Ϊ��д����
						if((A == 'w' )||(A == 'a' )||(A == 's' ) ||(A == 'd' ))
							{
			
								if(KeyJudge(A))		//�ж����뷽���Ƿ���ԭ�����෴				
									MoveKey = A;					
							}
			}
		
	}
	
}

//�ж����뷽���Ƿ���ԭ�����෴
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
 
//�����µ�����ڵ�
void Creat(){
	
	P = (struct Snake*)malloc(sizeof(struct Snake));

	P->Next = NULL;

	Head->Next = P;

}
//����β��
void Del(int x){
	
	if(!x)    //����x����EatJudge�ķ���ֵ�������Ƿ�ɾ��β���ڵ�
		{
			//����ָ��Tail��ֵ
			P = Tail;
			Tail = Tail->Next;
			//�ͷ�ԭTail�����ڴ�
			free(P);

			P = NULL;
		}
}

//�������ʳ��
/*
	���ж�ʳ�������Ƿ��������ص�


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
//�ж����ɵ�ʳ���Ƿ������������ص�
int Test(){
	struct Snake* p = Tail;
	
	for(;p != NULL;p = p->Next)
	{
		if((FX==(p->x))&&(FY==(p->y)))
			return 0;
	}
	return 1;
}


//�ж��Ƿ�Ե�ʳ��
/*
	�жϼ����������¸���ͷ�ڵ��Ƿ���ʳ��������ͬ
	�����ͬ����ɾ��β���ڵ�

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



//�ж��Ƿ������Ϸ

void Judge()
{
	WallJudge();
	MyselfJudge();
}
			//�ж��Ƿ�ײǽ

			/*

				�жϼ���������ͷ���ڵ��Ƿ���������Ƿ�Խ��

			*/
			void WallJudge(){
				int x = Head->x;
				int y = Head->y;
				if((x==0)||(x==(30*ULength))) 
					IExit();
				if((y==0)||(y==(20*ULength)))
					IExit();
				
			}

			//�ж��Ƿ�ҧ������
			/*
				���������ѯ����������ͷ���ڵ��Ƿ������������ڵ���ͬ
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

//��ʼ����ͼ
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

//������
void SnakePrint(int x,int y){
	PIMAGE Img = newimage();
	
	getimage(Img,"snake.png");

	putimage(x,y,Img);

	delimage(Img);
}

//������β
void Clear(int x,int y){
	
	PIMAGE Img = newimage();
	
	getimage(Img,"Black.png");

	putimage(x,y,Img);

	delimage(Img);
}


//��Ϸ����

void IExit()
{
	//��ʾ��������
	
	

	setcolor(EGERGB(0xFF, 0xFF, 0xFF));

	setfontbkcolor(EGERGB(0x80, 0x80, 0x80));

	setfont(100,0,"����");

	outtextxy(120,120,"��Ϸ����");

	getch();

	exit(0);
	  

}