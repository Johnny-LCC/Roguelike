CFLAGS=-Wall -Wextra -pedantic -O2
LIBS=-lm -lcurses

jogo: main.o mapa.o action.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
clean:
	rm jogo *.o
