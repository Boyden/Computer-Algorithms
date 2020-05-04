#include<iostream>
#include<fstream>
#include<string.h>
#include <cstdlib>

using namespace std;

class MaxGap{
public:
    int count;//数据个数
    double maxGap;//最大间隙
    double *num;//存放数据的数组

    MaxGap(const char *filename);//类初始化
    ~MaxGap();//析构函数

    double getMaxGap(int n, double *arr);
};

int minIndex(int n, double *arr){
    int index;
    double temp = arr[0];
    for (int i=1; i<n; i++){
        if (arr[i] < temp){
            temp = arr[i];
            index = i;
        }
    }
    return index;
}

int maxIndex(int n, double *arr){
    int index;
    double temp = arr[0];
    for (int i=1; i<n; i++){
        if (temp < arr[i]){
            temp = arr[i];
            index = i;
        }
    }
    return index;
}

MaxGap::MaxGap(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
        printf("can't open the file!");
        exit(0);
    }
    fscanf(fp,"%d",&count);//读取文件第一行数据
    num = new double[count];
    for (int i=0; i<count; i++)
        fscanf(fp,"%lf",&num[i]);//读取文件第二行数据
    maxGap = 0;
    fclose(fp);
}

MaxGap::~MaxGap(){
    delete[] num;
    num = NULL;
}


double MaxGap::getMaxGap(int n, double *arr){
    int min = minIndex(n,arr);
    double minNum = arr[min];//数组中最小值
    int max = maxIndex(n,arr);
    double maxNum = arr[max];//数组中最大值

    double avrGap = (maxNum - minNum)/(n-1);//等分为n-1个区间(左闭右开，最后一个桶左闭右闭)
    int *blockNum = new int[n];//存放每个区间的数据个数
    double *low = new double[n];//存放每个区间的最小值
    double *high = new double[n];//存放每个区间的最大值

    for (int i=0; i<n; i++){//初始化，空桶最小值为maxNum，最大值为minNum，避免遍历时的边界特殊情况
        blockNum[i] = 0;
        low[i] = maxNum;
        high[i] = minNum;
    }

    int index;//桶编号
    for (int i=0; i<n; i++){//设置n-1个区间中的最大最小值
        index = int((arr[i]-minNum)/avrGap)+1;//取整函数+1，注意，第n个桶的编号为n，不为n-1
        if (index == n)
            index--;//maxNum放入第n-1个区间中
        blockNum[index]++;

        if(arr[i] < low[index])
            low[index] = arr[i];
        if (arr[i] > high[index])
            high[index] = arr[i];
    }

    //第一个桶至少有一个元素，最好情况是第二个桶为空桶，所以遍历是从第二个桶开始

    double tempMaxGap = 0, tempHigh = high[1], tempGap;
    for (int i=2; i<n; i++){
        if (blockNum[i]){//i区间非空
            tempGap = low[i] - tempHigh;
            if (tempGap > tempMaxGap)
                tempMaxGap = tempGap;
            tempHigh = high[i];
        }
    }
    maxGap = tempMaxGap;

    delete[] blockNum;blockNum = NULL;
    delete[] low;low = NULL;
    delete[] high;high = NULL;

    return maxGap;
}


int main()
{
    char input[10];
    const char *filename = "input.txt";
    FILE *f = fopen("output.txt","w");

    MaxGap gap(filename);
    double answer = gap.getMaxGap(gap.count,gap.num);
    printf("Max Gap is: %.2f\n",answer);
    fprintf(f,"%.2f",answer);
    fclose(f);
    return 0;
}
