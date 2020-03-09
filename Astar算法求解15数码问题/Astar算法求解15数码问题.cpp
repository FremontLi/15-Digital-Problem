//用Astar算法求解15数码问题.cpp 

#include<stdio.h>
#include <stdlib.h>
  

//int s0[4][4];
int sn[4][4]={
	1,2,3,4,
    5,6,7,8,
	9,10,11,12,
	13,14,15,0
};//十五数码的目标状态

typedef struct array{
 int s[4][4];	//十五数码的数组
 int x0;
 int y0;	//记录0所在的位置
 int d;		//深度
 int w;		//矩阵中数字不在对应的位置的个数
 int f;		//d+w,估价函数
 struct array *priori;		//指向扩展之前的数组
}array,*arrays;

typedef struct table{		//创建open表和close表的结构体
 arrays a[10000];
 int k;
}table,*tables;

tables open = (tables)malloc(sizeof(table));			//创建open表
tables close = (tables)malloc(sizeof(table));			//创建close表

arrays s0=(arrays)malloc(sizeof(array));			//创建初始十五数码
arrays ssn=(arrays)malloc(sizeof(array));			//创建目标十五数码



//-----------------------------------------------
void scanf_array() //初始化数组，即用户输入数组
{
 printf("输入十五数码数组\n");
 for (int i=0;i<4;i++)
 {
	 for (int j=0;j<4;j++)
	 {
		scanf_s("%d",&s0->s[i][j]);
	 }
 }
}
//-----------------------------------------------
int count_f(arrays s)	//计算估价函数
{
 s->f=s->d+s->w;
 return (s->f);
}
//-----------------------------------------------
int wrong_position(arrays s)		//计算十五数码中不在正确位置的个数
{
 int w=0;
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		if (s->s[i][j]!=sn[i][j])
		{
			w++;
		}
	}
 }
 if (s->s[4][4]==sn[4][4])  //这一步是排除0在正确位置的时候
 {
	w++;
 }
 return w-1;
}
//-----------------------------------------------
bool left(arrays &s)		//0左移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==0)		//0在最左侧，不能左移
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y-1];
 s->s[x][y-1]=t;
 s->y0--;
 return true;
}
//-----------------------------------------------
bool right(arrays &s)		//0右移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==3)		//0在最右侧，不能右移
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x][y+1];
 s->s[x][y+1]=t;
 s->y0++;
 return true;
}
//-----------------------------------------------
bool up(arrays &s)		//0上移
{
 int x=s->x0;
 int y=s->y0; 
 int t;
 if (x==0)		//0在最上面，不能上移
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x-1][y];
 s->s[x-1][y]=t;
 s->x0--;
 return true;
}
//-----------------------------------------------
bool down(arrays &s)		//0下移
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==3)		//0在最下面，不能下移
 {
	return false;
 }
 t=s->s[x][y];
 s->s[x][y]=s->s[x+1][y];
 s->s[x+1][y]=t;
 s->x0++;
 return true;
}
//-----------------------------------------------
bool is_equal(arrays s1,arrays s2)	//判断两个数组是否相等，用于搜索open表和close表
{
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (s1->s[i][j]!=s2->s[i][j])
				return false;
		}
	}
	return true;
}
//-----------------------------------------------
void copy_array(arrays &s1,arrays s2)		//移动之前先创建数组,将s1赋值给s2
{
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			s2->s[i][j]=s1->s[i][j];
		}
	}
	s2->x0=s1->x0;
	s2->y0=s1->y0;
	s2->d=s1->d;
	s2->w=s1->w;
	s2->f=s1->f;
	s2->priori=s1->priori;
}
//-----------------------------------------------
void output_array(arrays s)		//输出十五数码数组
{
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		printf("%5d",s->s[i][j]);
	}
	printf("\n");
 }
}
//-----------------------------------------------
void add_table(tables &t,arrays s)		//把数组加入到open表或者close表中
{
 t->a[t->k++]=s;
}
//-----------------------------------------------
void delete_table(tables &t)		//从open表中删除数组
{
 for (int i=0;i<t->k;i++)
	 t->a[i]=t->a[i+1];
 t->k--;
} 
//-----------------------------------------------
bool search_table(tables t,arrays s)		//在open和close表中查找移动的数组是否之前出现过
{
 for (int i=0;i<t->k;i++)
 {
	if (is_equal(t->a[i],s))
		return true;
 }
 return false;
}
//-----------------------------------------------
void expand(arrays s)	//扩展数组
{
 arrays pl=(arrays)malloc(sizeof(array));	//初始化向左移动的数组
 arrays pr=(arrays)malloc(sizeof(array));	//初始化向右移动的数组
 arrays pu=(arrays)malloc(sizeof(array));	//初始化向上移动的数组
 arrays pd=(arrays)malloc(sizeof(array));	//初始化向下移动的数组
 copy_array(s,pl);
 copy_array(s,pr);
 copy_array(s,pu);
 copy_array(s,pd);
 pl->priori=s;
 pr->priori=s;
 pu->priori=s;
 pd->priori=s;

 if(left(pl) && !search_table(close,pl) && !search_table(open,pl))	//0左移，在open表中和close表中查找是否已经存在
 {
  pl->d++;
  pl->w=wrong_position(pl);
  pl->f=count_f(pl);
  add_table(open,pl);
 }

 if(right(pr) && !search_table(close,pr) && !search_table(open,pr))	//0右移，在open表中和close表中查找是否已经存在
 {
  pr->d++;
  pr->w=wrong_position(pr);
  pr->f=count_f(pr);
  add_table(open,pr);
 }

 if(up(pu) && !search_table(close,pu) && !search_table(open,pu))	//0上移，在open表中和close表中查找是否已经存在
 {
  pu->d++;
  //printf("%d\n",pu.d);
  pu->w=wrong_position(pu);
  //printf("%d\n",pu.w);
  pu->f=count_f(pu);
  //printf("%d\n",pu.f);
  add_table(open,pu);
 }

  if(down(pd) && !search_table(close,pd) && !search_table(open,pd))	//0下移，在open表中和close表中查找是否已经存在
 {
  pd->d++;
  pd->w=wrong_position(pd);
  pd->f=count_f(pd);
  add_table(open,pd);
 }
}
//-----------------------------------------------
void sort_open(tables &t)	//用冒泡排序对open表中的数组按照f的大小从小到大排序
{
 int flag=1;
  arrays temp=(arrays)malloc(sizeof(array));
 for (int i=0;i<t->k && flag;i++)
 {
  flag=0;
  for (int j=t->k-1;j>i;j--)
  {
	if (t->a[j]->f<t->a[j-1]->f)
	{	
	 copy_array(t->a[j],temp);
	 copy_array(t->a[j-1],t->a[j]);
	 copy_array(temp,t->a[j-1]);
	 flag=1;
	}
  }
 }
}
//-----------------------------------------------
void reverse_array(arrays &s)	//把目标数组通过先驱节点反序输出
{
//	printf("1111");
 arrays s_p;
 arrays s_s;
 s_p=NULL;
 s_s=s->priori;
 while(s)
 {
  s->priori=s_p;
  s_p=s;
  if(s_s==NULL)
  {
   break;
  }
  s=s_s;
  s_s=s_s->priori;
 }
}
//-----------------------------------------------
void inital_array()//初始化矩阵
{
 for (int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
	{
		if (s0->s[i][j]==0)
		{
			s0->x0=i;
			s0->y0=j;
		}	
	}
	printf("\n");
 }
 s0->d=0;
 s0->w=wrong_position(s0);
 s0->f=count_f(s0);
 s0->priori=NULL;
 for ( int i=0;i<4;i++)
 {
	for (int j=0;j<4;j++)
		ssn->s[i][j]=sn[i][j];
 }
 open->k=0;
 close->k=0;
 add_table(open,s0);
 printf("初始十五数码：\n");
 output_array(s0);
 printf("-------------------\n目标十五数码：\n");
 output_array(ssn);
}
//-----------------------------------------------
int main()
{
 arrays n=(arrays)malloc(sizeof(array));
 scanf_array();
 inital_array();
 while(open->k!=0 && close->k<=5000) //最多循环次数5000
 {
    arrays n=open->a[0];
	//output_array(*n); 
	delete_table(open);
	if(is_equal(n,ssn))
	{
	  reverse_array(n);
	  while(n)
	  {
		printf("-------------------\n第%d次移动 \n",n->d);
		output_array(n);  
		n=n->priori;
	  }
	 break;
	}
    add_table(close,n);
    expand(n);
    sort_open(open);
 }
while(open->k==0 || close->k>5000)
 {
  printf("-------------------\n该问题无解\n");
  break;
 } 

system("pause");
}
