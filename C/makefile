CFLAGS=-ansi -Wall -Wextra -pedantic -O2 -std=gnu99

OBJS=$(patsubst %.c , %.o, $(wildcard *.o))

all: clientes.c produtos.c filial.c faturacao.c main.c
	make cat_clientes
	make cat_produtos
	make cat_filiais
	make cat_faturacao
	make main
	make gerevendas
	make clear

cat_clientes: clientes.c clientes.h
	$(CC) $(CFLAGS) -c clientes.c

cat_produtos: produtos.c produtos.h
	$(CC) $(CFLAGS) -c produtos.c

cat_filiais: filial.c filial.h clientes.h produtos.h faturacao.h
	$(CC) $(CFLAGS) -c filial.c

cat_faturacao: faturacao.c faturacao.h clientes.h produtos.h filial.h
	$(CC) $(CFLAGS) -c faturacao.c

main: main.c clientes.h produtos.h filial.h faturacao.h
	$(CC) $(CFLAGS) -c main.c

gerevendas: $(OBJS)
	$(CC) $(OBJS) -o GereVendas
	
clear:
	rm -f *.o
	rm -f *.h.gch

remove:
	rm -f *.o
	rm -f *.h.gch
	rm -f GereVendas
