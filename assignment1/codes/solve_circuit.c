#include <stdio.h>
#include <stdlib.h>

int main() 
{


    double **B;                 // Tie set matrix of the given circuit
    double **Zb;                          //Creating matrix Zb(impedance matrix)
    double **vs;                          //Creating matrix vs (source voltage)
    double **Bt;                    //Creating matrix Bt (Tranpose of B matrix)

    B = (double **) malloc(3 * sizeof(double*)) ;     //Allocating memory
    for(int i = 0; i<3; i++) {
        B[i] = (double *) malloc(4 * sizeof(double));
    }  
    B[0][0]=B[0][1]=B[1][2]=1;                   //Assigning values
    B[0][2]=B[0][3]=B[1][0]=B[1][3]=B[2][0]=B[2][1]=0;
    B[1][1]=B[2][2]=B[2][3]=-1;

   
    Zb = (double **) malloc(4 * sizeof(double*)) ;     //memory allocation 
    for(int i = 0; i<4; i++) {
        Zb[i] = (double *) malloc(4 * sizeof(double));
    } 
    Zb[0][0]=2;
    Zb[1][1]=5;                  
    Zb[2][2]=10;
    Zb[3][3]=1;
    Zb[0][1]=Zb[0][2]=Zb[0][3]=Zb[1][0]=Zb[1][2]=Zb[1][3]=Zb[2][0]=Zb[2][1]=Zb[2][3]=Zb[3][0]=Zb[3][1]=Zb[3][2]=0;

    

    vs = (double **) malloc(4 * sizeof(double*)) ;     
    for(int i = 0; i<4; i++) {                         //Allocating memory 
        vs[i] = (double *) malloc(sizeof(double));
    } 
    vs[0][0]=10;
    vs[1][0]=12;
    vs[2][0]=0;                 //Assigning values
    vs[3][0]=20;

   
    
    Bt = (double **) malloc(4 * sizeof(double*)) ;          //Allocating memory
    for(int i = 0; i<4; i++) {
        Bt[i] = (double *) malloc(3 * sizeof(double));
    } 

    //Transpose of B
    Bt[0][0]=Bt[1][0]=Bt[2][1]=1;
    Bt[0][1]=Bt[0][2]=Bt[1][2]=Bt[2][0]=Bt[3][0]=Bt[3][1]=0;            //Assigning values
    Bt[1][1]=Bt[2][2]=Bt[3][2]=-1;

    double **a;
    a = (double **) malloc(4 * sizeof(double*)) ;   
    for(int i = 0; i<4; i++) {
        a[i] = (double *) malloc(3 * sizeof(double));
    } 

    for (int i = 0; i < 4; i++)       //Matrix Multiplication
    {
        for (int j = 0; j < 3; j++) 
        {
            a[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                a[i][j] += Zb[i][k] * Bt[k][j];
            }
        }
    }

    double **b;

    b = (double **) malloc(3 * sizeof(double*)) ;   
    for(int i = 0; i<3; i++) {
        b[i] = (double *) malloc(3 * sizeof(double));
    } 

    for (int i = 0; i < 3; i++)        
    {
        for (int j = 0; j < 3; j++) 
        {
            b[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                b[i][j] += B[i][k] * a[k][j];
            }
        }
    }

    double **c;

    c = (double **) malloc(3 * sizeof(double*)) ;        
    for(int i = 0; i<3; i++) {
        c[i] = (double *) malloc(sizeof(double));
    } 
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 1; j++) 
        {
            c[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                c[i][j] += -1*B[i][k] * vs[k][j];
            }
        }
    }


    double **inverseB;
    inverseB = (double **) malloc(3 * sizeof(double*)) ;   
    for(int i = 0; i<3; i++) {
        inverseB[i] = (double *) malloc(3 * sizeof(double));
    }
    double detB=0;            //Calculating determinant

    for(int i = 0; i < 3; i++)
        detB = detB + (b[0][i]*(b[1][(i+1)%3]*b[2][(i+2)%3] - b[1][(i+2)%3]*b[2][(i+1)%3]));

    for(int i=0;i<3;i++)                  //Inverse matrix
    {
        for(int j=0;j<3;j++)
            inverseB[i][j]=((b[(i+1)%3][(j+1)%3] * b[(i+2)%3][(j+2)%3]) - (b[(i+1)%3][(j+2)%3]*b[(i+2)%3][(j+1)%3]))/ detB;
    }

    double **result;

    result = (double **) malloc(3 * sizeof(double*)) ;   
    for(int i = 0; i<3; i++) {
        result[i] = (double *) malloc(sizeof(double));
    }

    for (int i = 0; i < 3; i++)           
    {
        for (int j = 0; j < 1; j++) 
        {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += inverseB[i][k] * c[k][j];   //loop currents 
            }
        }
    }
    printf("%s","Current in loop 1 " );    
    printf("%lf", result[0][0] );
    printf("%s","\n" ); 
    printf("%s","Current in loop 2 " );
    printf("%lf", result[1][0] );
    printf("%s","\n" );
    printf("%s","Current in loop 3 " );
    printf("%lf", result[2][0] );
    printf("%s","\n" );
    free(B);                      
    free(Zb);
    free(Bt);
    free(vs);
    free(a);
    free(b);
    free(c);
    free(inverseB);
    free(result);
    return 0;
}