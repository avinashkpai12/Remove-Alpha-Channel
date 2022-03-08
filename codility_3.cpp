#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define HEX 16




struct Results{
    int *R;
    int M; //Length of the array
};


void removeA(int A[], int N){

    int RGB[4] = {};
    for(int i=0;i<N;i++){
        int r = A[i]/pow(16,(2*N-1));
        A[i] = A[i] - r*pow(16,(2*N-1));
        int p = A[i]/pow(16, (2*N-2));
        A[i] = A[i] - p*pow(16,(2*N-2));
    }


}

int newPixVal(int A, int B, int n, int N){

    int tempAdd = 0; // new channel value to be added
    int shifted_A = 0;

    //calculate shifted_A if n-2>0
    if(n-2 > 0){
        //converted 332211 to 332200 1st case
        for(int j =0;j<n-2;j++ ){
            int r = A%16;
            A = A - r*pow(16, j);
        }
        shifted_A = A/pow(16, n-2);
    }
    //adding
    for(int i=0;i<n;i++){
        int r = B%16;
        tempAdd = tempAdd + r*pow(16, 2*N - (n-i));
        B = B/16; 
    }

    if(shifted_A != 0)
        return  shifted_A + tempAdd;
    else
        return A + tempAdd;
}

Results* solution(int A[], int N){

    //check RGBA format of input

    Results *results = (struct Results*)malloc((N-1)*sizeof(int)); //creating result size i.e. N-1
   // int *RGBA = getRGBA(A, N);
   
    removeA(A, N); // remove alpha channel from RGBA
    //after remooving A RGB = 3351057 = 0x332211 {332211, 332211, 332211, 332211}
    //for(int i=0;i<4;i++){
    //     printf("%d\n", A[i]);
    // }
    int *RGB = (int*)malloc((N-1)*sizeof(int));

    //send pair of consecutive pixels to create new pixel(332211, 332211, 2) for 1st case
   for(int i=0;i<N-1;i++){
       int val =  newPixVal(A[i], A[i+1], 2*(i+1), N);
       RGB[i] = val; 
      // printf("%d \n", RGB[i]);
   }
    results->R = RGB;
    int l = sizeof(RGB)/sizeof(int);
    results->M = l;
    return results; 
}


int convertValtoRGB(int A){

    int hexVal = 0;
    int i=0;
    while(A!=0){
        int r = A%16;
        A = A/16;
        hexVal = hexVal + r*pow(10,i);
        i++;
    }

    return hexVal;
}


int main(){
    
    //const char* data = getData();
    //converting 0x44332211 to int from hex manually
    int RGBA[] = {
        1144201745,
        1144201745,
        1144201745,
        1144201745
    }; //input data 
    
    int length = sizeof(RGBA)/sizeof(int);

  
     //for(int i=0;i<4;i++){
     //    printf("%d\n", RGBA[i]);
     //}

    //int *final_RGB = solution(RGBA, length);
    Results *r = solution(RGBA, length);
    //int l = sizeof(final_RGB)/sizeof(int);
    for(int i=0;i<=r->M;i++){
        printf("Decimal Value : %d\n",r->R[i]);
        int conVal = convertValtoRGB(r->R[i]);
        printf("Hex value after removing Alpha channel : 0x%d\n", conVal);
    }
    
    //Results *result = solution(RGBA, length);
    


}