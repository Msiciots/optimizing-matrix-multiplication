#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error while opening input file.\n");
        exit(EXIT_FAILURE);
    }
    FILE *out = fopen("output_data/tradition_output", "w");
    if (out == NULL) {
        perror("Error while opening the output file.\n");
        exit(EXIT_FAILURE);
    }
    int array_size;
    // read first matrix
    fscanf(f,"%d",&array_size);
    int **first=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)first[i]=(int *)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++) {
        for(int j=0; j<array_size; j++) {
            fscanf(f,"%d",&first[i][j]);
        }
    }
    //read second matrix
    fscanf(f,"\n");
    int **second=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)second[i]=(int *)malloc(array_size*sizeof(int *));

    for(int i=0; i<array_size; i++) {
        for(int j=0; j<array_size; j++) {
            fscanf(f,"%d",&second[i][j]);
        }
    }
    fclose(f);
    // output matrix
    int **output=(int **)malloc(array_size*sizeof(int *));
    for(int i=0; i<array_size; i++)output[i]=(int *)malloc(array_size*sizeof(int *));

    // debug
    // for(int i = 0; i < array_size; i++){
    //     for (int j = 0; j < array_size; j++){
    //         printf("%d ",first[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for(int i = 0; i < array_size; i++){
    //     for (int j = 0; j < array_size; j++){
    //         printf("%d ",second[i][j]);
    //     }
    //     printf("\n");
    // }

    //start clock
    printf("Multiply two %dx%d matrixes\n",array_size,array_size);
    clock_t start, end;
    start = clock();
    //multiply
    long long int sum = 0;
    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            for (int k = 0; k < array_size; k++) {
                sum = sum + first[i][k]*second[k][j];
            }
            output[i][j] = sum;
            sum = 0;
        }
    }
    //end clock
    end = clock();

    fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);

    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            fprintf(out,"%d ",output[i][j]);
        }
        fprintf(out,"\n");
    }

    printf("Elapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
    fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);

    FILE *t = fopen("test_data/tradition_test4096", "a");
    fprintf(t,"%f\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
}