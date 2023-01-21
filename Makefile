default: main.o pessoa.o arquivo.o
	gcc main.o pessoa.o arquivo.o -o final.o

main.o: main.c
	gcc -c main.c -o main.o

pessoa.o: pessoa.c
	gcc -c pessoa.c -o pessoa.o

arquivo.o: arquivo.c
	gcc -c arquivo.c -o arquivo.o

execute:
	./final.o