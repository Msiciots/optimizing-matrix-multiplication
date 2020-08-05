
all:
	gcc tradition.c -o tradition 
	gcc strassen.c -o strassen -lpthread -w
	gcc parallel_tradition.c -o parallel_tradition -lpthread
	gcc transpose.c -o transpose 

clean:
	rm -rf strassen
	rm -rf parallel_tradition
	rm -rf transpose
	rm -rf tradition
	rm -rf output/parallel_tradition_output
	rm -rf output/tradition_output
	rm -rf output/transpose_output
	rm -rf output/strassen_output