#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
 
using namespace std;
//-----------------------------------------------
//状态空间的定义 
int pos[][2] = {3,3,0,0,0,1,0,2,
                0,3,1,0,1,1,1,2,
                1,3,2,0,2,1,2,2,
                2,3,3,0,3,1,3,2};//构造方阵
                
int dx[] = {0,1,-1,0};//空格的横坐标
int dy[] = {1,0,0,-1};//空格的纵坐标
char dir[] = {'R','D','U','L'};//定义right、down、up、left四个方向 
int en[16] = {
    1,2,3,4,
    5,6,7,8,
    9,10,11,12,
    13,14,15,0
	};//十五数码的目标状态
	
char path[100];//输出路径的数组 
int puz[16];//存放4*4方阵中数码的数组 

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
} //定义h*函数，函数值为为每个数字到目标位置的曼哈顿距离之和
 
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
}//用逆序数的概念对无解的判断进行优化 

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
}//深度优先优化，在每次移动下一步禁止向上一步的反方向移动，减少搜索树的分支，提高效率
 
//----------------------------------------------- 
int main(void)
{
    //freopen("input.txt","r",stdin);
    int T,p;
    printf("请输入15数码数组的个数：\n"); //可实现计算多组15数码数组问题 
    scanf_s("%d",&T);
    while(T--){
    	printf("\n-------------------\n");
	    printf("请输入15数码数组:\n");
        for(int i = 0; i < 16; ++i){  //通过for循环来初始化15数码数组 
            scanf_s("%d",&puz[i]);
            if(puz[i] == 0)
                p = i;
        }
        printf("\n-------------------\n");
//调用solvable（）函数判断是否有解
        if(solvable()){   
            int maxd = 0;
            for(;!dfs(p,-1,0,maxd); ++maxd);
            printf("路径为:\n");
            path[maxd] = 0,puts(path);  //有解的话输出路径 
            printf("\n"); 
        }
        else
            puts("该问题无解");  //无解的话输出"该问题无解" 
    }
    return 0;
}
