//��Astar�㷨���15��������.cpp 

#include<stdio.h>
#include <stdlib.h>
  

//int s0[4][4];
int sn[4][4]={
	1,2,3,4,
    5,6,7,8,
	9,10,11,12,
	13,14,15,0
};//ʮ�������Ŀ��״̬

typedef struct array{
 int s[4][4];	//ʮ�����������
 int x0;
 int y0;	//��¼0���ڵ�λ��
 int d;		//���
 int w;		//���������ֲ��ڶ�Ӧ��λ�õĸ���
 int f;		//d+w,���ۺ���
 struct array *priori;		//ָ����չ֮ǰ������
}array,*arrays;

typedef struct table{		//����open���close��Ľṹ��
 arrays a[10000];
 int k;
}table,*tables;

tables open = (tables)malloc(sizeof(table));			//����open��
tables close = (tables)malloc(sizeof(table));			//����close��

arrays s0=(arrays)malloc(sizeof(array));			//������ʼʮ������
arrays ssn=(arrays)malloc(sizeof(array));			//����Ŀ��ʮ������



//-----------------------------------------------
void scanf_array() //��ʼ�����飬���û���������
{
 printf("����ʮ����������\n");
 for (int i=0;i<4;i++)
 {
	 for (int j=0;j<4;j++)
	 {
		scanf_s("%d",&s0->s[i][j]);
	 }
 }
}
//-----------------------------------------------
int count_f(arrays s)	//������ۺ���
{
 s->f=s->d+s->w;
 return (s->f);
}
//-----------------------------------------------
int wrong_position(arrays s)		//����ʮ�������в�����ȷλ�õĸ���
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
 if (s->s[4][4]==sn[4][4])  //��һ�����ų�0����ȷλ�õ�ʱ��
 {
	w++;
 }
 return w-1;
}
//-----------------------------------------------
bool left(arrays &s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==0)		//0������࣬��������
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
bool right(arrays &s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (y==3)		//0�����Ҳ࣬��������
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
bool up(arrays &s)		//0����
{
 int x=s->x0;
 int y=s->y0; 
 int t;
 if (x==0)		//0�������棬��������
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
bool down(arrays &s)		//0����
{
 int x=s->x0;
 int y=s->y0;
 int t;
 if (x==3)		//0�������棬��������
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
bool is_equal(arrays s1,arrays s2)	//�ж����������Ƿ���ȣ���������open���close��
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
void copy_array(arrays &s1,arrays s2)		//�ƶ�֮ǰ�ȴ�������,��s1��ֵ��s2
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
void output_array(arrays s)		//���ʮ����������
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
void add_table(tables &t,arrays s)		//��������뵽open�����close����
{
 t->a[t->k++]=s;
}
//-----------------------------------------------
void delete_table(tables &t)		//��open����ɾ������
{
 for (int i=0;i<t->k;i++)
	 t->a[i]=t->a[i+1];
 t->k--;
} 
//-----------------------------------------------
bool search_table(tables t,arrays s)		//��open��close���в����ƶ��������Ƿ�֮ǰ���ֹ�
{
 for (int i=0;i<t->k;i++)
 {
	if (is_equal(t->a[i],s))
		return true;
 }
 return false;
}
//-----------------------------------------------
void expand(arrays s)	//��չ����
{
 arrays pl=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pr=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pu=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 arrays pd=(arrays)malloc(sizeof(array));	//��ʼ�������ƶ�������
 copy_array(s,pl);
 copy_array(s,pr);
 copy_array(s,pu);
 copy_array(s,pd);
 pl->priori=s;
 pr->priori=s;
 pu->priori=s;
 pd->priori=s;

 if(left(pl) && !search_table(close,pl) && !search_table(open,pl))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pl->d++;
  pl->w=wrong_position(pl);
  pl->f=count_f(pl);
  add_table(open,pl);
 }

 if(right(pr) && !search_table(close,pr) && !search_table(open,pr))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pr->d++;
  pr->w=wrong_position(pr);
  pr->f=count_f(pr);
  add_table(open,pr);
 }

 if(up(pu) && !search_table(close,pu) && !search_table(open,pu))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pu->d++;
  //printf("%d\n",pu.d);
  pu->w=wrong_position(pu);
  //printf("%d\n",pu.w);
  pu->f=count_f(pu);
  //printf("%d\n",pu.f);
  add_table(open,pu);
 }

  if(down(pd) && !search_table(close,pd) && !search_table(open,pd))	//0���ƣ���open���к�close���в����Ƿ��Ѿ�����
 {
  pd->d++;
  pd->w=wrong_position(pd);
  pd->f=count_f(pd);
  add_table(open,pd);
 }
}
//-----------------------------------------------
void sort_open(tables &t)	//��ð�������open���е����鰴��f�Ĵ�С��С��������
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
void reverse_array(arrays &s)	//��Ŀ������ͨ�������ڵ㷴�����
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
void inital_array()//��ʼ������
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
 printf("��ʼʮ�����룺\n");
 output_array(s0);
 printf("-------------------\nĿ��ʮ�����룺\n");
 output_array(ssn);
}
//-----------------------------------------------
int main()
{
 arrays n=(arrays)malloc(sizeof(array));
 scanf_array();
 inital_array();
 while(open->k!=0 && close->k<=5000) //���ѭ������5000
 {
    arrays n=open->a[0];
	//output_array(*n); 
	delete_table(open);
	if(is_equal(n,ssn))
	{
	  reverse_array(n);
	  while(n)
	  {
		printf("-------------------\n��%d���ƶ� \n",n->d);
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
  printf("-------------------\n�������޽�\n");
  break;
 } 

system("pause");
}
