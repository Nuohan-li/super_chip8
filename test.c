#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


#define ERROR -1
#define FALSE 0
#define TRUE 1


int msbIdentify(int num){

    int shiftCount = 0;
    int result = num % 2;
    num /=2;

    while(num != 0){
        shiftCount += 1;
        num /=2;
    }

    return shiftCount;
}


int carryCalc(int numOne, int numTwo, int msb){
    //15 and 10 have a carry as a result of their addition.
    int numOneMsb = msbIdentify(numOne);
    int numTwoMsb = msbIdentify(numTwo);

    int max = numOneMsb;

    if(numTwoMsb > numOneMsb){
        max = numTwoMsb;
    }

    if(max > msb)
        return ERROR;


    int shiftCount = 0;

    int carry = 0;
    
    while(shiftCount <= max){
        int numOneBit = (numOne & (1 << shiftCount)) >> shiftCount; //mask off bit at position i and shift it down to position 0.
        int numTwoBit = (numTwo & (1 << shiftCount)) >> shiftCount;

        int currentBitResult = numOneBit ^ numTwoBit;

        if(numOneBit & numTwoBit)
            carry = 1;
        else if(currentBitResult & carry)
            carry = 1;
        else
            carry = 0;

        //add the result of the carry.
        currentBitResult = currentBitResult ^ carry;
        // printf("The current bit result with carry is %d \n", currentBitResult);

        if(shiftCount == max && max == msb){
            //printf("Scenario one");
            return carry;
        } //can also be shiftCount = msb.
            
        if(shiftCount == max && max != msb){
            //printf("Scenario two");
            return 0;
        }
            
        shiftCount += 1;
    }

    return ERROR;
}



int binaryAdditionwC(int numOne, int numTwo, int msb, int *result){

    *result = 0;
    //15 and 10 have a carry as a result of their addition.
    int numOneMsb = msbIdentify(numOne);
    int numTwoMsb = msbIdentify(numTwo);

    int max = numOneMsb;

    if(numTwoMsb > numOneMsb){
        max = numTwoMsb;
    }

    if(max > msb)
        return ERROR;


    int shiftCount = 0;
  

    int carry = 0;
    
    while(shiftCount <= max){
        int numOneBit = (numOne & (1 << shiftCount)) >> shiftCount; //mask off bit at position i and shift it down to position 0.
        int numTwoBit = (numTwo & (1 << shiftCount)) >> shiftCount;

        int currentBitResult = (numOneBit ^ numTwoBit) ^ carry;

        // printf("The current carry is %d \n", carry);
        // printf("The current bit is %d \n", numOneBit ^ numTwoBit);
        // printf("The current bit with the carry is %d \n", currentBitResult);

        //add the result of the carry.
        if(currentBitResult)
            *result += (currentBitResult << shiftCount);
        
        if((numOneBit & numTwoBit))
            carry = 1;
        else if((numOneBit ^ numTwoBit) && !(numOneBit ^ numTwoBit ^ carry))
            carry = 1;
        else
            carry = 0;

        

        //printf("The current bit result with carry is %d \n", currentBitResult);
        if(shiftCount == max && max == msb){
            //printf("Scenario one");
            return carry;
        } //can also be shiftCount = msb.
            
        if(shiftCount == max && max != msb){
            //printf("Scenario two");
            return 0;
        }
            
        shiftCount += 1;
    }

    return ERROR;
}


void testCase(int *result){

    double max_for_msb = 0;
    double max_based_on_msb = 0;
   
    for(int i = 0; i < 8; i++){

        max_for_msb = pow(2, i);

        if(i > 0)
            max_based_on_msb += pow(2, i); //This marks the point at which there should be a carry.
        else
            max_based_on_msb = max_for_msb;
        
        printf("The max for msb is %lf \n", max_for_msb);
        printf("The max based on msb is %lf \n \n \n \n", max_based_on_msb);

        for(int j = 1; j <= max_based_on_msb/2 + 1; j++){
            int carry_or_no = binaryAdditionwC(max_for_msb, j, i, result); //you want to check anything the value of your msb to the max value based on msb+1

            if(carry_or_no)
                printf("Carries?: True \n");
            else
                printf("Carries?: False %d \n", *result);

        }
    }
}








int main(){

    int testNum = 255;

    int result = 0;


    int standardNum = 9;


    // int carryNum = binaryAdditionwC(8, 7, 3, &result);
    // printf("The addition result is %d \n", result);

   // testCase(&result);

   int x = 10;

//    while(x --> 0){
//     printf("The num is %d \n", x);
//    }


    int array[16];
    for(int i = 0; i < 16; i++){
        array[i] = i;
    }

   // int *array = {1, 2, 4, 5, 6};

    printf("The number is %d  \n", *(array+1));


    


    

    




    return 0;
}