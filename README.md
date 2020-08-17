# Optimizing matrix multiplication
An exercise to optimize matrix multiplication which implemented in C. Then compare the time of executions. 
## Optimize methods
The way of matrix multiplication.

![matrix multiplication](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/matrix-mul.png)
![equation](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/mul-equation.png)
**Use symbols for simplicity**  
A : The multiplicand matrix  
B : The multiplier matrix  
C : The product matrix

### Transpose matrix
C stores matrix elements in row-major order, but we access B in col-major order. Therefore, we can transfer B into a transposed matrix, and accelerate the time of matrix multiplication.

![transpose](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/trans.png)
### Parallelize process
Divide matrix into four small matrix and multiply. Use C pthread to create four thread for parallel computing.

![parallel](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/paralell.png)
### Strassen algorithm
The time complexity of standard matrix multiplication is ![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/complexity-1.png). Strassen’s algorithm only has seven matrix multiplication operations in each divide and conquer method, The output time complexity is ![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/complexity-2.png).

Let A, B be two square matrices over a ring R. We want to calculate the matrix product C as

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-1.png)

If the matrices A, B are not of type 2^n × 2^n we fill the missing rows and columns with zeros.

We partition A, B and C into equally sized block matrices

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-2.png)

with  

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-3.png)

The naive algorithm would be:

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-4.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-5.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-6.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-7.png)  

With this construction we have not reduced the number of multiplications. We still need 8 multiplications to calculate the Ci,j matrices, the same number of multiplications we need when using standard matrix multiplication.

The Strassen algorithm defines instead new matrices:

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-8.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-9.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-10.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-11.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-12.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-13.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-14.png)  

only using 7 multiplications (one for each Mk) instead of 8. We may now express the Ci,j in terms of Mk:

![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-15.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-16.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-17.png)  
![](https://github.com/Msiciots/optimizing-matrix-multiplication/raw/master/doc-img/derivation-18.png)  

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
