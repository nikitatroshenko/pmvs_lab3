all: client.exe tserver.exe pserver.exe

client.exe: client.o
	gcc -o client.exe client.o

pserver.exe: server_main.o server_process.o server_activity.o
	gcc -o pserver.exe server_main.o server_process.o server_activity.o

tserver.exe: server_main.o server_thread.o server_activity.o
	gcc -o tserver.exe server_main.o server_thread.o server_activity.o -pthread

process: pserver.exe

thread: tserver.exe

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
	rm -rf *.exe *.o

