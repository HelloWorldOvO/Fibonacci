/*
1120530218 陳彥宇 資工系網攻組
題目:求費伯那西數列第1000個數
作法:將數字的每一位數拆開來放在陣列裡別運算，若是進位就將下一位數加一

*/
#include<stdio.h>
#include<stdbool.h>
#include<time.h>

// judge the int val is even or not
bool is_even(int target){
    if(target%2 == 0){
        return true;
    }
    else{
        return false;
    }
}

// judge the carry 
int is_carry(int target){
    if(target >= 10){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    clock_t begin = clock();    //begin time

    int num_length = 300;   // number length
    int times = 1000;   // nth Fibonacci
    int i,j;

    int Farr1[num_length];  // Fi or Fi+1
    int Farr2[num_length]; // Fi or Fi+1
    int Fans[num_length];   //final answer
    int carry = 0;  // carry

    bool pre_pad = true;    // judge if the padding zero

    // initial value
    for(i=0;i<num_length;i++){
        Farr1[i] = 0;
        Farr2[i] = 0;
    }
    Farr1[0] = 1;
    // F0 = Farr2 = 0, Feven = Farr2
    // F1 = Farr1 = 1, Fodd = Farr1
    // F999 = Farr1

    // calculate one digit by one digit
    for(i=2;i<times;i++){
        carry = 0;
        // calculate Fi, i=even, ex:F2
        if(is_even(i)){
            for(j=0;j<num_length;j++){
                Farr2[j] = Farr1[j] + Farr2[j] + carry;
                carry = is_carry(Farr2[j]);
                Farr2[j] %= 10;
            }
        }
        // calculate Fi, i=odd, ex:F3
        else{
            for(j=0;j<num_length;j++){
                Farr1[j] = Farr1[j] + Farr2[j] + carry;
                carry = is_carry(Farr1[j]);
                Farr1[j] %= 10;
            }
        }
    }

    // choose the answer from two array
    if(is_even(times)){
        for(i=0;i<num_length;i++){
            Fans[i] = Farr1[i];
        }
    }
    else{
        for(i=0;i<num_length;i++){
            Fans[i] = Farr2[i];
        }
    }
    // print answer
    printf("the %dth number in Fibonacci(F%d) is ", times, times-1);

    for(i=num_length-1;i>=0;i--){
        if(pre_pad){
            if(Fans[i] != 0){
                pre_pad = false;
                printf("%d",Fans[i]);
            }
            continue;
        }
        printf("%d",Fans[i]);
    }

    clock_t end = clock();  //end time
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //translate time
    printf("\nthis program execute %lf seconds\n",time_spent);   // print execute time

    return 0;
}