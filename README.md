# Optimizing matrix multiplication
An exercise to optimize matrix multiplication which implemented in C. Then compare the time of executions. 
## Optimize methods
The way of matrix multiplication.

![matrix multiplication](https://i.imgur.com/7uDlrL1.png)
![equation](https://i.imgur.com/IAwAYeM.png)
**Use symbols for simplicity**  
A : The multiplicand matrix  
B : The multiplier matrix  
C : The product matrix

### Transpose matrix
C stores matrix elements in row-major order, but we access B in col-major order. Therefore, we can transfer B into a transposed matrix, and accelerate the time of matrix multiplication.

![transpose](https://i.imgur.com/vvaYDJd.png)
### Parallelize process
Divide matrix into four small matrix and multiply. Use C pthread to create four thread for parallel computing.

![parallel](https://i.imgur.com/bGP329z.png)
### Strassen algorithm
The time complexity of standard matrix multiplication is ![](https://i.imgur.com/bBvwcei.png). Strassen’s algorithm only has seven matrix multiplication operations in each divide and conquer method, The output time complexity is ![](https://i.imgur.com/YMHoJ7G.png).

Let A, B be two square matrices over a ring R. We want to calculate the matrix product C as

![](https://i.imgur.com/9qNlNPt.png)

If the matrices A, B are not of type 2^n × 2^n we fill the missing rows and columns with zeros.

We partition A, B and C into equally sized block matrices

![](https://i.imgur.com/JnVFjMp.png)

with  

![](https://i.imgur.com/hMZc52A.png)

The naive algorithm would be:

![](https://i.imgur.com/8Qa8qyL.png)  
![](https://i.imgur.com/l7qqp8u.png)  
![](https://i.imgur.com/CqZOO5p.png)  
![](https://i.imgur.com/3bRtdJ3.png)  

With this construction we have not reduced the number of multiplications. We still need 8 multiplications to calculate the Ci,j matrices, the same number of multiplications we need when using standard matrix multiplication.

The Strassen algorithm defines instead new matrices:

![](https://i.imgur.com/7Z3xNWe.png)  
![](https://i.imgur.com/Th5FPhT.png)  
![](https://i.imgur.com/9vw8nou.png)  
![](https://i.imgur.com/ld8H1gH.png)  
![](https://i.imgur.com/QZHuNR1.png)  
![](https://i.imgur.com/4KC9K25.png)  
![](https://i.imgur.com/DuEGbKR.png)  

only using 7 multiplications (one for each Mk) instead of 8. We may now express the Ci,j in terms of Mk:

![](https://i.imgur.com/kDjXAJA.png)  
![](https://i.imgur.com/T8sUNeR.png)  
![](https://i.imgur.com/J16rIjD.png)  
![](https://i.imgur.com/doaa9mJ.png)  

I used Strassen algorithm to multiply matrixes and divide M1 ~ M7 to seven threads in parallel computing.  

**Reference from:**  
- Strassen algorithm. (2020, June 18). In *Wikipedia, the free encyclopedia*. Retrieved August 5, 2020, from https://en.wikipedia.org/wiki/Strassen_algorithm

## Build & Run
Build source files use make in linux environment. 
```
# move to source file directory
$ make
```
Run program
```
$ ./[Executable file] [input file]
# For examples
$ ./strassen ./input_data/test_data_1
```
The running results are in ./output_data .
The terminal will also show the time of matrix multiplication.
## Test
Each result value is the average of 20 execution times.
| Method  | test_data_2 |test_data_3 |
| -------- | -------- | -------- |
| Tradition|||
| Parallel Tradition |||
| Transpose|||
| Strassen|||