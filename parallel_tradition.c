#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
int array_size;
int *res11,*res12,*res21,*res22; 
/* results matrix
res11 | res12
-------------
res21 | res22
*/

struct arguments{
	int *a1,*a2,*b1,*b2;
	int *res;
};

void* calculate(void* in){
	struct arguments* input = (struct arguments*) in;
	
	for(int i=0; i< array_size*array_size/4; i++){
		int row_index = i / (array_size/2);
		int col_index = i % (array_size/2);
		int sum = 0;
		for(int j=0; j<array_size/2 ; j++){
			sum += (input->a1)[row_index * array_size/2 + j] * (input->b1)[array_size/2 * j + col_index];
			sum += (input->a2)[row_index * array_size/2 + j] * (input->b2)[array_size/2 * j + col_index];
		}
		(input->res)[i] = sum;
		//if(i%array_size==0) printf("counting1 %d / %d\n",i,array_size*array_size/4);
	}
	pthread_exit(NULL);
}

void main(int argc, char* argv[]){
	
	FILE *f = fopen(argv[1], "r");
	FILE *out = fopen("output/traditional_output", "w");

	// read input
	fscanf(f,"%d",&array_size);
	res11 = malloc(array_size * array_size / 4 * sizeof(int));
	res12 = malloc(array_size * array_size / 4 * sizeof(int));
	res21 = malloc(array_size * array_size / 4 * sizeof(int));
	res22 = malloc(array_size * array_size / 4 * sizeof(int));
	int *a11 = malloc(array_size * array_size/4*sizeof(int));
	int *a12 = malloc(array_size * array_size/4*sizeof(int));
	int *a21 = malloc(array_size * array_size/4*sizeof(int));
	int *a22 = malloc(array_size * array_size/4*sizeof(int));
	int *b11 = malloc(array_size * array_size/4*sizeof(int));
	int *b12 = malloc(array_size * array_size/4*sizeof(int));
	int *b21 = malloc(array_size * array_size/4*sizeof(int));
	int *b22 = malloc(array_size * array_size/4*sizeof(int));
	for(int i = 0; i < array_size ; i++){
		for(int j = 0; j < array_size ; j++){
			if(i < array_size/2 && j < array_size/2 ) fscanf(f,"%d",&a11[i*array_size/2 + j]);
			if(i < array_size/2 && j >=array_size/2 ) fscanf(f,"%d",&a12[i*array_size/2 + j - array_size/2]);
			if(i >=array_size/2 && j < array_size/2 ) fscanf(f,"%d",&a21[(i-array_size/2)*array_size/2 + j]);
			if(i >=array_size/2 && j >=array_size/2 ) fscanf(f,"%d",&a22[(i-array_size/2)*array_size/2 + j - array_size/2]);
		}
	}

	fscanf(f,"\n");

	for(int i = 0; i < array_size ; i++){
		for(int j = 0; j < array_size ; j++){
			if(i < array_size/2 && j < array_size/2 ) fscanf(f,"%d",&b11[i*array_size/2 + j]);
			if(i < array_size/2 && j >=array_size/2 ) fscanf(f,"%d",&b12[i*array_size/2 + j - array_size/2]);
			if(i >=array_size/2 && j < array_size/2 ) fscanf(f,"%d",&b21[(i-array_size/2)*array_size/2 + j]);
			if(i >=array_size/2 && j >=array_size/2 ) fscanf(f,"%d",&b22[(i-array_size/2)*array_size/2 + j - array_size/2]);
		}
	}
	fclose(f);
	
	pthread_t t1,t2,t3,t4;
	struct arguments *arg1 = malloc(sizeof *arg1);
	arg1->a1 = a11;
	arg1->a2 = a12;
	arg1->b1 = b11;
	arg1->b2 = b21;
	arg1->res = res11;

	struct arguments *arg2 = malloc(sizeof *arg2);
	arg2->a1 = a11;
	arg2->a2 = a12;
	arg2->b1 = b12;
	arg2->b2 = b22;
	arg2->res = res12;

	struct arguments *arg3 = malloc(sizeof *arg3);
	arg3->a1 = a21;
	arg3->a2 = a22;
	arg3->b1 = b11;
	arg3->b2 = b21;
	arg3->res = res21;

	struct arguments *arg4 = malloc(sizeof *arg4);
	arg4->a1 = a21;
	arg4->a2 = a22;
	arg4->b1 = b12;
	arg4->b2 = b22;
	arg4->res = res22;

	printf("Multiply two %dx%d matrixes\n",array_size,array_size);

	clock_t start,end;
	start = clock();

	pthread_create(&t1,NULL,calculate,(void*)arg1);
	pthread_create(&t2,NULL,calculate,(void*)arg2);
	pthread_create(&t3,NULL,calculate,(void*)arg3);
	pthread_create(&t4,NULL,calculate,(void*)arg4);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);

	end = clock();
	

	fprintf(out,"Elapsed time: %f\n\n",(double)(end-start)/CLOCKS_PER_SEC);

	// output results
	for(int i=0; i<array_size; i++){
		for(int j=0; j<array_size; j++){
			if(i<array_size/2 && j<array_size/2){
				fprintf(out,"%d ",res11[i*array_size/2 + j]);
			}else if(i<array_size/2 && j>=array_size/2){
				fprintf(out, "%d ", res12[i*array_size/2 + j-array_size/2]);
			}else if(i>=array_size/2 && j<array_size/2){
				fprintf(out, "%d ", res21[(i-array_size/2) * array_size/2 + j]);
			}else if(i>=array_size/2 && j>=array_size/2){
				fprintf(out, "%d ", res22[(i-array_size/2) * array_size/2 + j - array_size/2]);
			}
			if(j==array_size-1)
				fprintf(out, "\n");
		}
	}
	
	printf("Elapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
	fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
}
