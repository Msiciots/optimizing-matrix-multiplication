
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
	rm -rf output_data/parallel_tradition_output
	rm -rf output_data/tradition_output
	rm -rf output_data/transpose_output
	rm -rf output_data/strassen_output