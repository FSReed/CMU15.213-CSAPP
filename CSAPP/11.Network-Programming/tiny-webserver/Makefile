.PHONY: all

all: tiny cgi-bin

CC = gcc

tiny: tiny.c ../openfd/openfd.c ../../10.System-Level-IO/rio/rio.c
	$(CC) -o $@ $^

cgi-bin: cgi-bin.c
	$(CC) -o $@ $<

clean:
	rm tiny cgi-bin
