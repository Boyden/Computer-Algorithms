#include<stdio.h>
#define N 10
#define M 10

int a[M][N];
int count=0;
int m,n;
void Read(int *m, int *n){
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, "%d", m);
    fscanf(fp, "%d", n);

}

void Write(int n){
    FILE *f = fopen("output.txt","w");
    fprintf(f,"%d",n);
    fclose(f);
}

//判断数组的每行每列是否有重复的数，如果有，返回false；否则，返回true
bool ok(int x,int y){

	for(int i=0;i<x;i++)
		if(a[i][y]==a[x][y])
			return false;

	for(int j=0;j<y;j++)
		if(a[x][j]==a[x][y])
			return false;

	return true;
}

//进行回溯
void traceback(int x,int y){

	int temp;
	//排列并判断，在每行每列没有重复的情况下
	for(int i=y;i<n;i++){
		temp=a[x][y];
		a[x][y]=a[x][i];
		a[x][i]=temp;

		if(ok(x,y)){
			if((x==m-1) && (y==n-1))   //如果走到最后一层，输出
			{
				count++;
                return ;
			}
			else if((x==m-1) && (y!=n-1))   //如果走到最后一行，但不是最后一列，继续回溯，列加一
				traceback(x,y+1);
			else if((x!=m-1) && (y==n-1))   //如果走到最后一列，但不是最后一行，继续回溯，行加一,列变成第一列
				traceback(x+1,0);
			else        //否则，继续回溯,列加一
				traceback(x,y+1);
		}

		temp=a[x][y];
		a[x][y]=a[x][i];
		a[x][i]=temp;
	}
}

int main()
{	
    Read(&m, &n);
	//给数组进行赋初值
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			a[i][j]=j+1;
	}

	traceback(0,0);

    Write(count);
	return 0;
}
