# Regra principal
all: lista

# Comando para criar o executável
lista: lista.o arvore_avl.o conjunto.o main.o
	gcc lista.o arvore_avl.o conjunto.o main.o -o lista -std=c99 -Wall

# Regras para compilar cada arquivo objeto
lista.o: lista.c lista.h
	gcc -c lista.c -o lista.o

arvore_avl.o: arvore_avl.c arvore_avl.h
	gcc -c arvore_avl.c -o arvore_avl.o

conjunto.o: conjunto.c conjunto.h
	gcc -c conjunto.c -o conjunto.o

main.o: main.c conjunto.h
	gcc -c main.c -o main.o

# Limpeza dos arquivos objetos e do executável
clean:
	rm -f *.o lista

# Regra para executar o programa
run: all
	./lista
