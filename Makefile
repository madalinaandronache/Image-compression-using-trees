CC = gcc
CFLAGS = -Wall -g

build: quadtree

quadtree: main.o c1.o c2.c c3.c
	$(CC) -o quadtree $^ 

main.o: main.c
	$(CC) $(CFLAGS) -c $^

c1.o: c1.c
	$(CC) $(CFLAGS) -c $^

c2.o: c2.c
	$(CC) $(CFLAGS) -c $^

c3.o: c3.c
	$(CC) $(CFLAGS) -c $^

run: build
	./quadtree

clean:
	rm -f *.o quadtree