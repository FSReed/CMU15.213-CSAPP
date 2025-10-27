.PHONY: all clean

all: compile link runtime

CC = gcc
C_DEF = -DCOMPILE_TIME
L_DEF = -DLINK_TIME
L_FLAG = -Wl,--wrap,malloc -Wl,--wrap,free
R_FLAG = -DRUNTIME -shared -fpic

compile: int.c mymalloc_compile.o
	$(CC) -I. $^ -o $@

link: int_link.o mymalloc_link.o
	$(CC) $(L_FLAG) $^ -o $@

runtime: mymalloc_runtime.so int_runtime.o
	LD_PRELOAD="./$<" ./int_runtime.o

int_runtime.o: int.c
	$(CC) -o $@ $<

int_link.o: int.c
	$(CC) -c $< -o $@

mymalloc_compile.o: mymalloc_compile.c
	$(CC) $(C_DEF) -c $< -o $@

mymalloc_link.o: mymalloc_link.c
	$(CC) $(L_DEF) -c $< -o $@

mymalloc_runtime.so: mymalloc_runtime.c
	$(CC) $(R_FLAG) -o $@ $< -ldl

clean:
	rm *.o *.so compile link
