#include <iostream>
#include<fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

bool is_Prime(int num){
    if (num == 1){
        return false;
    }
    if (num == 2 || num == 3){
        return true;
    }
    if (num % 6 != 5 && num % 6 != 1){
        return false;
    }
    else{
        for (int i = 5; i <= sqrt(num); i+=6){
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}

void write_prime(int num){
    FILE *f = fopen("prime_index.txt","w");
    fprintf(f, "%c", '0');
    for (int i = 1; i <= num; i++){
        if(is_Prime(i))
            fprintf(f, "%c", '1');
        else
            fprintf(f, "%c", '0');
    }
    fclose(f);
}

bool get_prime(int num){
    char c;
    FILE *f = fopen("prime_index.txt","r");
    fseek(f, (long)num, SEEK_SET);
    fscanf(f, "%c", &c);
    fclose(f);
    if (c=='1'){
        return true;
    }
    else{
        return false;
    }
}

int solve(int n){
    int i;
    int count = 1;

    if(is_Prime(n))
        return 1;
    else{
        for (i = 2; i <= n/2; i++) {
            if (n%i == 0){
                if (is_Prime(n/i))
                    count += 1;
                else
                    count += solve(n / i);
            }
        }
    }
    return count;
}

int main(){
    int n;
    FILE *f_prime = fopen("prime_index.txt", "r");
    // if (f_prime == NULL){
    //     fclose(f_prime);
    //     write_prime(2000000);
    // }

    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL){
        printf("can't open the file!");
        exit(0);
    }
    fscanf(fp,"%d",&n);
    fclose(fp);
    FILE *f = fopen("output.txt","w");
    fprintf(f,"%d",solve(n));
    fclose(f);

    return 0;
}
