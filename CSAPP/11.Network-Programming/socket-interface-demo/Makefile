.PHONY: all clean

CC = gcc

all: server client ad_server ad_client wrapper_server wrapper_client server_demo client_demo

server: server.c
	$(CC) -o $@ $<

client: client.c
	$(CC) -o $@ $<

ad_server: ad_server.c
	$(CC) -o $@ $<

ad_client: ad_client.c
	$(CC) -o $@ $<

wrapper_server: wrapper_server.c ../openfd/openfd.c
	$(CC) -o $@ $^

wrapper_client: wrapper_client.c ../openfd/openfd.c
	$(CC) -o $@ $^

server_demo: server_demo.c ../openfd/openfd.c ../../10.System-Level-IO/rio/rio.c
	$(CC) -o $@ $^

client_demo: client_demo.c ../openfd/openfd.c ../../10.System-Level-IO/rio/rio.c
	$(CC) -o $@ $^

clean:
	rm server client ad_server ad_client wrapper_server wrapper_client server_demo client_demo
