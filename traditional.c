#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

int *res11,*res12,*res21,*res22; // results
int row_res,col_res;
struct arguments{
	int *a1,*a2,*b1,*b2;
	int *res;
	int size;
};

void* calculate(void* in){
	struct arguments* input = (struct arguments*) in;
	int array_size = input->size;

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
void print_matrix(FILE *out){
	int row = row_res;
	int col = col_res;
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			if(i<row/2 && j<col/2){
				fprintf(out,"%d ",res11[i*row/2 + j]);
			}else if(i<row/2 && j>=col/2){
				fprintf(out, "%d ", res12[i*row/2 + j-col/2]);
			}else if(i>=row/2 && j<col/2){
				fprintf(out, "%d ", res21[(i-row/2) * row/2 + j]);
			}else if(i>=row/2 && j>=col/2){
				fprintf(out, "%d ", res22[(i-row/2) * row/2 + j - col/2]);
			}
			if(j==col-1)
				fprintf(out, "\n");
		}
	}
}
void main(int argc, char* argv[]){
	
	FILE *f = fopen(argv[1], "r");
	FILE *out = fopen("output/traditional_output", "w");
	// read input
	// int row,col;
	int row,col;
	fscanf(f,"%d",&row);
	fscanf(f,"%d",&col);
	row_res=row;
	res11 = malloc(row * col / 4 * sizeof(int));
	res12 = malloc(row * col / 4 * sizeof(int));
	res21 = malloc(row * col / 4 * sizeof(int));
	res22 = malloc(row * col / 4 * sizeof(int));
	int *a11 = malloc(row*col/4*sizeof(int));
	int *a12 = malloc(row*col/4*sizeof(int));
	int *a21 = malloc(row*col/4*sizeof(int));
	int *a22 = malloc(row*col/4*sizeof(int));
	int *b11 = malloc(row*col/4*sizeof(int));
	int *b12 = malloc(row*col/4*sizeof(int));
	int *b21 = malloc(row*col/4*sizeof(int));
	int *b22 = malloc(row*col/4*sizeof(int));
	for(int i = 0; i < row ; i++){
		for(int j = 0; j < col ; j++){
			if(i < row/2 && j < col/2 ) fscanf(f,"%d",&a11[i*row/2 + j]);
			if(i < row/2 && j >=col/2 ) fscanf(f,"%d",&a12[i*row/2 + j - col/2]);
			if(i >=row/2 && j < col/2 ) fscanf(f,"%d",&a21[(i-row/2)*row/2 + j]);
			if(i >=row/2 && j >=col/2 ) fscanf(f,"%d",&a22[(i-row/2)*row/2 + j - col/2]);
		}
	}

	fscanf(f,"%d",&row);
	fscanf(f,"%d",&col);
	col_res=col;
	for(int i = 0; i < row ; i++){
		for(int j = 0; j < col ; j++){
			if(i < row/2 && j < col/2 ) fscanf(f,"%d",&b11[i*row/2 + j]);
			if(i < row/2 && j >=col/2 ) fscanf(f,"%d",&b12[i*row/2 + j - col/2]);
			if(i >=row/2 && j < col/2 ) fscanf(f,"%d",&b21[(i-row/2)*row/2 + j]);
			if(i >=row/2 && j >=col/2 ) fscanf(f,"%d",&b22[(i-row/2)*row/2 + j - col/2]);
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
	arg1->size = row;

	struct arguments *arg2 = malloc(sizeof *arg2);
	arg2->a1 = a11;
	arg2->a2 = a12;
	arg2->b1 = b12;
	arg2->b2 = b22;
	arg2->res = res12;
	arg2->size = row;

	struct arguments *arg3 = malloc(sizeof *arg3);
	arg3->a1 = a21;
	arg3->a2 = a22;
	arg3->b1 = b11;
	arg3->b2 = b21;
	arg3->res = res21;
	arg3->size = row;

	struct arguments *arg4 = malloc(sizeof *arg4);
	arg4->a1 = a21;
	arg4->a2 = a22;
	arg4->b1 = b12;
	arg4->b2 = b22;
	arg4->res = res22;
	arg4->size = row;

	printf("Multiply two %dx%d matrixes\n",row,col);
	clock_t start,end;
	start = clock();
	// pthread_create(&t1,NULL,calculate11,(void*)arg1);
	// pthread_create(&t2,NULL,calculate12,(void*)arg2);
	// pthread_create(&t3,NULL,calculate21,(void*)arg3);
	// pthread_create(&t4,NULL,calculate22,(void*)arg4);
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
	// for(int i=0; i<row; i++){
	// 	for(int j=0; j<col; j++){
	// 		if(i<row/2 && j<col/2){
	// 			fprintf(out,"%d ",res11[i*row/2 + j]);
	// 		}else if(i<row/2 && j>=col/2){
	// 			fprintf(out, "%d ", res12[i*row/2 + j-col/2]);
	// 		}else if(i>=row/2 && j<col/2){
	// 			fprintf(out, "%d ", res21[(i-row/2) * row/2 + j]);
	// 		}else if(i>=row/2 && j>=col/2){
	// 			fprintf(out, "%d ", res22[(i-row/2) * row/2 + j - col/2]);
	// 		}
	// 		if(j==col-1)
	// 			fprintf(out, "\n");
	// 	}
	// }
	print_matrix((FILE*)out);
	printf("Elapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
	fprintf(out,"\nElapsed time: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
}
