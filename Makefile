all: client tserver pserver

client: client.o
	gcc -o client client.o

pserver: server_main.o server_process.o server_activity.o
	gcc -o pserver server_main.o server_process.o server_activity.o

tserver: server_main.o server_thread.o server_activity.o
	gcc -o tserver server_main.o server_thread.o server_activity.o -pthread

process: pserver

thread: tserver

server_main.o: server_main.c
	gcc -c -o server_main.o server_main.c

server_thread.o: server_thread.c
	gcc -c -o server_thread.o server_thread.c -pthread

server_process.o: server_process.c
	gcc -c -o server_process.o server_process.c

server_activity.o: server_activity.c
	gcc -c -o server_activity.o server_activity.c

client.o: client.c
	gcc -c -o client.o client.c

clean:
	rm -rf client pserver tserver *.o

