CC = gcc

# change this line to trigger linking errors
LIBS = libx.a liby.a libx.a

target: p.o $(LIBS)
	gcc -static -o $@ $< $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@

libx.a: x1.o x2.o
	ar rcs $@ $^

liby.a: y1.o y2.o
	ar rcs $@ $^

clean:
	rm -f *.o *.a
