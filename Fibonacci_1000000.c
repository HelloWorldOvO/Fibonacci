/*
使用Linux環境撰寫一個程式，這個程式必須算出「費伯納西數列」，到第1,000個「費伯納西數」，並印出執行時間。
費伯納西數列
f(0) = 0
f(1) = 1
f(n) = f(n-1) + f(n-2) for n >= 2
*/
#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#define DEGIT_LEN 1000000000000000000 // the max degits in an array space 
#define ARR_LEN 120000 //the length of the array
#define TARGET 1000001 // target Fibonacci number

int main(){
    clock_t begin = clock(); //begin time

    int i,j;
    unsigned long long carry = 0; //the carry
    int valid_digit_num = 1; // the digit need to calculate

    bool pad_zero = true; // judge if it is padding zero

    // put each continues 19 digits in an array space 
    // initial F0 and F1
    unsigned long long Farr1[ARR_LEN] = {0};
    unsigned long long Farr2[ARR_LEN] = {0};
    Farr1[0] = 1;
    
    unsigned long long *big = Farr1;
    unsigned long long *small = Farr2;
    unsigned long long *temp = NULL;

    // calculate F2 to Fi, i is target
    for(i=2;i<TARGET;++i){
        carry = 0;

        // calculate from low digit to high digit
        for(j=0;j<=valid_digit_num;++j){
            small[j] = small[j] + big[j] +carry;
            // judge if this array space carry
            if(small[j] >= DEGIT_LEN){
                small[j] -= DEGIT_LEN;
                carry = 1;
                // highest digit carry
                if(j==valid_digit_num){
                    valid_digit_num += 1;
                }
            }
            else{
                carry = 0;
            }
        }
        
        // always put the bigger Fibonacci number in big
        temp = small;
        small =big;
        big = temp;
        
    }

    clock_t end = clock();  //end time
    
    // print Fi, i is target, which is in big and print other information
    printf("the %dth number in Fibonacci(F%d) is ", TARGET, TARGET-1);
    for(i=ARR_LEN-1;i>=0;--i){
        // ignore the zero at first
        if(pad_zero){
            if(big[i] != 0){
                printf("%llu",big[i]);
                pad_zero = false;
            }
            continue;
        }
        printf("%llu",big[i]);
    }
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //translate time
    printf("\nthis program consume %lf seconds to calculate F1000000\n",time_spent);   // print execute time

    return 0;
}