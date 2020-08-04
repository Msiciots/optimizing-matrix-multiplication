
all:
	gcc tradition.c -o tradition 
	gcc strassen.c -o strassen -lpthread -w
	gcc parallel_tradition.c -o parallel_tradition -lpthread
	gcc transpose.c -o transpose 

clean:
	rm -rf strassen
	rm -rf parallel_tradition
	rm -rf transpose
	rm -rf output/parallel_tradition_output