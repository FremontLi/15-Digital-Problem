#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
 
using namespace std;
//-----------------------------------------------
//״̬�ռ�Ķ��� 
int pos[][2] = {3,3,0,0,0,1,0,2,
                0,3,1,0,1,1,1,2,
                1,3,2,0,2,1,2,2,
                2,3,3,0,3,1,3,2};//���췽��
                
int dx[] = {0,1,-1,0};//�ո�ĺ�����
int dy[] = {1,0,0,-1};//�ո��������
char dir[] = {'R','D','U','L'};//����right��down��up��left�ĸ����� 
int en[16] = {
    1,2,3,4,
    5,6,7,8,
    9,10,11,12,
    13,14,15,0
	};//ʮ�������Ŀ��״̬
	
char path[100];//���·�������� 
int puz[16];//���4*4��������������� 

//-----------------------------------------------
int hstar()
{
    int h = 0;
    for(int i = 0; i < 16; ++i){
        int x = puz[i];
        if(x == 0) continue;
        h += abs(i / 4 - pos[x][0]) + abs(i % 4- pos[x][1]);
    }
    return h;
} //����h*����������ֵΪΪÿ�����ֵ�Ŀ��λ�õ������پ���֮��
 
//-----------------------------------------------
 bool solvable()
{
    int cnt = 0;
    for(int i = 0; i < 16; ++i){
        if(puz[i] == 0)
            cnt += 3 - i / 4;
        else{
            for(int j = 0; j < i; ++j)
                if(puz[j] && puz[j] > puz[i])
                    cnt++;
        }
    }
    return !(cnt&1);
}//���������ĸ�����޽���жϽ����Ż� 

//-----------------------------------------------
bool dfs(int p,int pre,int d, int maxd)
{
    if(d + hstar() > maxd) return false;
 
    if(d == maxd)
        return memcmp(puz,en,sizeof(en)) == 0;
 
    int x = p / 4, y = p % 4;
    for(int j = 0; j < 4; ++j){
        if(pre + j == 3) continue;
        int nx = x + dx[j], ny = y + dy[j];
        int nz = 4 * nx + ny;
        if(nx >= 0 && nx < 4 && ny >= 0 && ny < 4){
            swap(puz[p],puz[nz]);
            path[d] = dir[j];
            if(dfs(nz,j,d+1,maxd)) return true;
            swap(puz[p],puz[nz]);
        }
    }
    return false;
}//��������Ż�����ÿ���ƶ���һ����ֹ����һ���ķ������ƶ��������������ķ�֧�����Ч��
 
//----------------------------------------------- 
int main(void)
{
    //freopen("input.txt","r",stdin);
    int T,p;
    printf("������15��������ĸ�����\n"); //��ʵ�ּ������15������������ 
    scanf_s("%d",&T);
    while(T--){
    	printf("\n-------------------\n");
	    printf("������15��������:\n");
        for(int i = 0; i < 16; ++i){  //ͨ��forѭ������ʼ��15�������� 
            scanf_s("%d",&puz[i]);
            if(puz[i] == 0)
                p = i;
        }
        printf("\n-------------------\n");
//����solvable���������ж��Ƿ��н�
        if(solvable()){   
            int maxd = 0;
            for(;!dfs(p,-1,0,maxd); ++maxd);
            printf("·��Ϊ:\n");
            path[maxd] = 0,puts(path);  //�н�Ļ����·�� 
            printf("\n"); 
        }
        else
            puts("�������޽�");  //�޽�Ļ����"�������޽�" 
    }
    return 0;
}
