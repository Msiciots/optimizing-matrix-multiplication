#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[]) {
    char ch;
    int array_size;

//read input
    FILE *fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("Error while opening input file.\n");
        exit(EXIT_FAILURE);
    }
    
//input first matrix
    fscanf(fp,"%d",&array_size);

    int **first=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)first[i]=(int *)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++) {
        for(int j=0; j<array_size; j++) {
            fscanf(fp,"%d",&first[i][j]);
        }
    }

//input second matrix
    fscanf(fp,"\n");
    int **second=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)second[i]=(int *)malloc(array_size*sizeof(int *));

    for(int i=0; i<array_size; i++) {
        for(int j=0; j<array_size; j++) {
            fscanf(fp,"%d",&second[i][j]);
        }
    }
    fclose(fp);
//transpose second matrix
    int **transpose=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)transpose[i]=(int *)malloc(array_size*sizeof(int *));

    for(int i=0; i<array_size; i++) {
        for(int j=0; j<array_size; j++) {
            transpose[i][j]=second[j][i];
        }
    }
//start clock
    printf("Multiply two %dx%d matrixes\n",array_size,array_size);
    clock_t start, end;
    start = clock();
//multiply
    int **multiply=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)multiply[i]=(int *)malloc(array_size*sizeof(int *));
    long long int sum = 0;
    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            for (int k = 0; k < array_size; k++) {
                sum = sum + first[i][k]*transpose[j][k];
            }
            multiply[i][j] = sum;
            sum = 0;
        }
    }

//end clock
    end = clock();

    FILE *out;
    out=fopen("output_data/transpose_output","w");
    if (out == NULL) {
        perror("Error while opening the output file.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            fprintf(out,"%d ",multiply[i][j]);
        }
        fprintf(out,"\n");
    }

    printf("Elapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
    fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
