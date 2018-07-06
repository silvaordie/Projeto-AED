CC = gcc
CFLAGS = -Wall -ansi -O3
LFLAGS = 
LIBS = -lm
OBJS =main.o fila_p.o lista.o dicionario.o  grafo.o 
EXEC =wordmorph

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) -lm

main.o: main.c lista.c dicionario.c
	$(CC) $(CFLAGS) -c main.c

lista.o: lista.c
	$(CC) $(CFLAGS) -c lista.c

dicionario.o: lista.c dicionario.c
	$(CC) $(CFLAGS) -c dicionario.c

fila_p.o: fila_p.c 
	$(CC) $(CFLAGS) -c fila_p.c

grafo.o: grafo.c dicionario.c lista.c fila_p.c
	$(CC) $(CFLAGS) -c grafo.c	

debug: $(OBJS)
	gdb ./wordmorph
	
clean:
	echo "Apagar todos os ficheiros do programa"
	rm -f *o $(EXEC)

path:
	echo "Apagar todos os ficheiros .path do programa"
	rm -f *path	
	
reset: 
	echo "Apagar todos os ficheiros .pal  e .path do programa"
	rm -f *pal *path