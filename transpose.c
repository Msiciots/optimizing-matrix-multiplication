#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char* argv[])
{
   char ch;
   int n1,n2;
   int i,j,k;
   unsigned long long int sum;
   
//readfile
   FILE *fp;
   fp = fopen(argv[1], "r");

   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
//start clock
   clock_t start, end;
   start = clock();

//input first matrix
   fscanf(fp,"%d",&n1);
   fscanf(fp,"%d",&n2);
  printf("%d %d\n", n1,n2);
  int **first=(int **)malloc(n1*sizeof(int *));
  for(int i=0;i<n1;i++)first[i]=(int *)malloc(n2*sizeof(int *));
  for(i=0;i<n1;i++){
	   for(j=0;j<n1;j++){
      		fscanf(fp,"%d",&first[i][j]);
		}
	}
//input second matrix
   fscanf(fp,"%d",&n1);
   fscanf(fp,"%d",&n2);
   int **second=(int **)malloc(n1*sizeof(int *));
   for(i=0;i<n1;i++)second[i]=(int *)malloc(n2*sizeof(int *));
   for(i=0;i<n1;i++){
	   for(j=0;j<n1;j++){
      		fscanf(fp,"%d",&second[i][j]);
		}
	}
//transpose
  int **transpose=(int **)malloc(n1*sizeof(int *));
  for(int i=0;i<n1;i++)transpose[i]=(int *)malloc(n2*sizeof(int *));
       for(i=0;i<n1;i++){
	   for(j=0;j<n1;j++){
			transpose[i][j]=second[j][i];
		}
	}
//multiply
  int **multiply=(int **)malloc(n1*sizeof(int *));
  for(int i=0;i<n1;i++)multiply[i]=(int *)malloc(n2*sizeof(int *));
    for (i = 0; i < n1; i++) {
      for (j = 0; j < n1; j++) {
        for (k = 0; k < n1; k++) {
          sum = sum + first[i][k]*transpose[j][k];
        }

        multiply[i][j] = sum;
        sum = 0;
      }
    }
   fclose(fp);
//end clock
   end = clock();
	FILE *f;
	f=fopen("traspose_output","w");
	for (i = 0; i < n1; i++) {
      for (j = 0; j < n1; j++) {
		  fprintf(f,"%d ",multiply[i][j]);
	}
	fprintf(f,"\n");
	}
    double diff = end - start; // ms
    printf(" %f  ms" , diff);
    printf(" %f  sec\n", diff / CLOCKS_PER_SEC );

   return 0;
}
