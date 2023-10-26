CC = gcc
CFLAGS = -Wall -std=c99 -O3
DEPS = functions.h dicionario.h auxiliar_opcoes.h cabecalho.h
OBJ = wordz.o functions.o dicionario.o auxiliar_opcoes.o
EXEC = wordz

%.o: %.c $(DEPS)
	$(CC)  $(CFLAGS) -c -o $@ $<

wordz: $(OBJ)
	$(CC) $(CFLAGS) -o  $@ $^
