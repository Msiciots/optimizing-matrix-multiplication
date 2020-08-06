#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int matrix_size;
int **matrix1,**matrix2,**result;
int **m1,**m2,**m3,**m4,**m5,**m6,**m7;
int **r1,**r2,**r3,**r4;
int ** allocate_memery( int size );
void m1_evalue(int n);
void m2_evalue(int n);
void m3_evalue(int n);
void m4_evalue(int n);
void m5_evalue(int n);
void m6_evalue(int n);
void m7_evalue(int n);
int main(int argc, char* argv[]) {
    int i;
    FILE *f;
    f=fopen(argv[1],"r");
    if (f == NULL) {
        perror("Error while opening the input file.\n");
        exit(EXIT_FAILURE);
    }
    fscanf(f,"%d",&matrix_size);

    matrix1=allocate_memery(matrix_size);
    matrix2=allocate_memery(matrix_size);
    result=allocate_memery(matrix_size);
    read_matrix(matrix1,matrix_size,1,argv[1]);
    read_matrix(matrix2,matrix_size,2,argv[1]);
    //printf("Read file finished.\n");
    fclose(f);
    m1=allocate_memery(matrix_size/2);
    m2=allocate_memery(matrix_size/2);
    m3=allocate_memery(matrix_size/2);
    m4=allocate_memery(matrix_size/2);
    m5=allocate_memery(matrix_size/2);
    m6=allocate_memery(matrix_size/2);
    m7=allocate_memery(matrix_size/2);

    clock_t start,end;
    printf("Multiply two %dx%d matrixes\n",matrix_size,matrix_size);
    pthread_t thread[7];
    start=clock();
    //printf("Calculating...\n");
    pthread_create(&thread[0],NULL, &m1_evalue,matrix_size);
    pthread_create(&thread[1],NULL, &m2_evalue, matrix_size);
    pthread_create(&thread[2],NULL, &m3_evalue, matrix_size);
    pthread_create(&thread[3],NULL, &m4_evalue, matrix_size);
    pthread_create(&thread[4],NULL, &m5_evalue, matrix_size);
    pthread_create(&thread[5],NULL, &m6_evalue, matrix_size);
    pthread_create(&thread[6],NULL, &m7_evalue, matrix_size);
    for(i=0; i<7; i++)
        pthread_join(thread[i], NULL);

    r1=allocate_memery(matrix_size/2);
    r2=allocate_memery(matrix_size/2);
    r3=allocate_memery(matrix_size/2);
    r4=allocate_memery(matrix_size/2);
    for(int i=0; i<matrix_size/2; i++) {
        for(int j=0; j<matrix_size/2; j++) {
            r1[i][j]=m1[i][j]+m4[i][j]-m5[i][j]+m7[i][j];
            r2[i][j]=m3[i][j]+m5[i][j];
            r3[i][j]=m2[i][j]+m4[i][j];
            r4[i][j]=(m1[i][j]-m2[i][j])+(m3[i][j]+m6[i][j]);
        }
    }
    end=clock();
    free(m1);
    free(m2);
    free(m3);
    free(m4);
    free(m5);
    free(m6);
    free(m7);
    int n=matrix_size;
    for(i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if(i<n/2&&j<n/2)
                result[i][j]=r1[i][j];
            else if(i>=n/2&&j<n/2)
                result[i][j]=r3[i-n/2][j];
            else if(i<n/2&&j>=n/2)
                result[i][j]=r2[i][j-n/2];
            else if(i>=n/2&&j>=n/2)
                result[i][j]=r4[i-n/2][j-n/2];

        }
    }
    free(r1);
    free(r2);
    free(r3);
    free(r4);

    print_matrix(result,matrix_size);
    // float exc_time = (float)(t_end - t_start) / CLOCKS_PER_SEC;
    //printf("strassen execution time: %f\n",exc_time);
    printf("Elapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);

    return 0;
}
int ** allocate_memery( int n ) {
    int * value = (int *) malloc( n * n * sizeof(int) );
    int ** ptr = (int **) malloc( n * sizeof(int*) );
    int i;
    for (i = 0; i < n; ++i) {
        ptr[ i ] = &value[ i * n ];
    }
    return ptr;
}
void read_matrix(int **m,int size,int num,char * test_file) {
    FILE *f;
    // f=fopen(argv[1],"r");
    f=fopen(test_file,"r");
    int i, j,temp;
    if(num==1) {
        fscanf(f,"%d",&temp);
        fscanf(f,"%d",&temp);
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fscanf(f,"%d",&matrix1[i][j]);
            }
        }
    } else if(num==2) {
        fscanf(f,"%d",&temp);
        fscanf(f,"%d",&temp);
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fscanf(f,"%d",&temp);

            }
        }
        fscanf(f,"%d",&temp);
        fscanf(f,"%d",&temp);

        for (i = 0; i < size; ++i) {
            for (j = 0; j < size; ++j) {
                fscanf(f,"%d",&matrix2[i][j]);

            }
        }
    }
    fclose(f);
}
void print_matrix(int **m,int size) {
    //printf("Exporting file...\n");
    FILE *f;
    f=fopen("output_data/strassen_output","w");
    if (f == NULL) {
        perror("Error while opening the output file.\n");
        exit(EXIT_FAILURE);
    }
    int i,j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            fprintf(f,"%d ",m[i][j]);
        }
        fprintf(f,"\n");
    }
    //printf("Exporting file finished.\n");
}
void m1_evalue(int n) {
    int ** a = allocate_memery(n/2);
    int ** b = allocate_memery(n/2);
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            a[i][j]=matrix1[i][j]+matrix1[n/2+i][n/2+j];
            b[i][j]=matrix2[i][j]+matrix2[n/2+i][n/2+j];
        }
    }

    for (int i=0; i<n/2; i++) {

        for (int j=0; j<n/2; j++) {
            int sum=0;
            for (int k=0; k<n/2; k++) {
                sum += a[i][k] * b[k][j];
            }
            m1[ i ][ j ] = sum;
        }
    }
    free(a);
    free(b);
}

void m2_evalue(int n) {

    int ** a = allocate_memery(n/2);
    for(int i=0; i<n/2; i++)
        for(int j=0; j<n/2; j++)
            a[i][j]=matrix1[n/2+i][j]+matrix1[n/2+i][n/2+j];
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum +=a[i][k]*matrix2[k][j];
            }
            m2[i][j]=sum;
        }
    }
    free(a);
}

void m3_evalue(int n) {

    int ** b = allocate_memery(n/2);
    for(int i=0; i<n/2; i++)
        for(int j=0; j<n/2; j++)
            b[i][j]= matrix2[i][n/2+j]-matrix2[n/2+i][n/2+j];
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum+=matrix1[i][k]*b[k][j];
            }
            m3[i][j]=sum;
        }
    }
    free(b);
}

void m4_evalue(int n) {

    int ** b = allocate_memery(n/2);
    for(int i=0; i<n/2; i++)
        for(int j=0; j<n/2; j++)
            b[i][j]=matrix2[n/2+i][j]-matrix2[i][j];
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum+=matrix1[n/2+i][n/2+k]*b[k][j];
            }
            m4[i][j]=sum;
        }
    }
    free(b);
}

void m5_evalue(int n) {

    int ** a = allocate_memery(n/2);
    for(int i=0; i<n/2; i++)
        for(int j=0; j<n/2; j++)
            a[i][j]=matrix1[i][j]+matrix1[i][n/2+j];
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum+=a[i][k]*matrix2[n/2+k][n/2+j];
            }
            m5[i][j]=sum;
        }
    }
    free(a);
}

void m6_evalue(int n) {

    int** a = allocate_memery(n/2);
    int** b = allocate_memery(n/2);
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            a[i][j]=matrix1[n/2+i][j]-matrix1[i][j];
            b[i][j]=matrix2[i][j]+matrix2[i][n/2+j];
        }
    }
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum+=a[i][k]*b[k][j];
            }
            m6[i][j]=sum;
        }
    }
    free(a);
    free(b);

}

void m7_evalue(int n) {

    int ** a = allocate_memery(n/2);
    int ** b = allocate_memery(n/2);

    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            a[i][j]=matrix1[i][n/2+j]-matrix1[n/2+i][n/2+j];
            b[i][j]=matrix2[n/2+i][j]+matrix2[n/2+i][n/2+j];
        }
    }
    for(int i=0; i<n/2; i++) {
        for(int j=0; j<n/2; j++) {
            int sum=0;
            for(int k=0; k<n/2; k++) {
                sum+=a[i][k]*b[k][j];
            }
            m7[i][j]=sum;
        }
    }
    free(a);
    free(b);
}




