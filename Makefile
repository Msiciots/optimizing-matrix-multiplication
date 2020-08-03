
all:
	gcc strassen.c -o strassen -lpthread -w
	gcc traditional.c -o traditional -lpthread
	gcc transpose.c -o transpose 

clean:
	rm -rf strassen
	rm -rf traditional
	rm -rf transpose