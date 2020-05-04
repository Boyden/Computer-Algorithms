#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
int  A[SIZE];   //存储输入的检索概率
int  B[SIZE];   //存储修改过顺序的检索概率
void  QuickSort(int *arr,int low, int high);
float greedy_disk_storage(int  A[],int n);
void Read(int *a, int b[]);
void Write(float n);
int main()
{
    int i ,n;
    float min_t;//记录最小时间
    Read(&n, A);
    min_t = greedy_disk_storage(A, n);
    Write(min_t);
    return 0;
}
void QuickSort(int *arr, int low, int high)
{
    if (low < high){
        int i = low;
        int j = high;
        int k = arr[low];
        while (i < j){
            while(i < j && arr[j] >= k)     // 从右向左找第一个小于k的数
                j--;
            if(i < j){
                arr[i++] = arr[j];
            }

            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
                i++;

            if(i < j){
                arr[j--] = arr[i];
            }
        }

        arr[i] = k;
        // 递归调用
        QuickSort(arr, low, i - 1);     // 排序k左边
        QuickSort(arr, i + 1, high);    // 排序k右边
    }
}

float greedy_disk_storage(int *A,int n)
{
    double sum = 0,t = 0;

    int i,j,k = (n-1)/2;
    QuickSort(A, 0, n-1);
    B[k] = A[n-1];                //B数组中间数存储最大的检索概率 B[2] = A[4]
    for(i = k+1;i < n;i++)
    {
        B[i] = A[n-2*(i-k)];     //B[3]= A[3] B[4] = A[1]，第奇数大放在右边
    }
    for(i = k-1;i >= 0;i--)
    {
        B[i] = A[n-2*(k-i)-1];   //B[1] = A[2] B[0] = A[0]，第偶数大放在左边
    }
    for (i = 0;i < n;i++) //计算总期望值，复杂度为O(n^2)
    {
        sum += A[i];
        for(j = i+1; j < n;j++)
            t += B[i]*B[j]*(j-i);
    }
    return t/sum/sum;
}
void Read(int *a, int b[]){
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, "%d", a);
    for(int i=0;i<*a;i++)
        fscanf(fp, "%d", b+i);
}
void Write(float n){
    FILE *f = fopen("output.txt","w");
    fprintf(f,"%f",n);
    fclose(f);
}
