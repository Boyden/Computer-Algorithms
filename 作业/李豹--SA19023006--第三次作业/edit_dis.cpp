#include <iostream>
#include<fstream>
#include <cmath>
#include <cstdlib>
#include <string.h>

using namespace std;

int min_of_three(int a, int b, int c){
    int min_num;
    if (a<b){
        min_num = a;
    }
    else{
        min_num = b;
    }
    if (min_num<c){
        return min_num;
    }
    else
        return c;
}

int min_distance(char *a, char *b){
    int lena = strlen(a);
    int lenb = strlen(b);
    int d[lena+1][lenb+1];
    int i, j;

    for (i = 0; i <= lena; i++) {
        d[i][0] = i;
    }
    for (j = 0; j <= lenb; j++) {
        d[0][j] = j;
    }

    for (i = 1; i <= lena; i++) {
        for (j = 1; j <= lenb; j++) {

            if (a[i-1] == b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = min_of_three(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+1);
            }
        }
    }

    return d[lena][lenb];
}

void Read(char *a, char *b){
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, "%s", a);
    fscanf(fp, "%s", b);
}

void Write(int n){
    FILE *f = fopen("output.txt","w");
    fprintf(f,"%d",n);
    fclose(f);
}

int main(){
    int n;
    char a[1000], b[1000];
    Read(a, b);
    n = min_distance(a, b);
    Write(n);
    return 0;
}
