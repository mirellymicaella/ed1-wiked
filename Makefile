gcc:Editor.c Contribuicao.c ListaHet.c Pagina.c main.c
	gcc -o wiked *.c

val: gcc
	clear
	valgrind --tool=memcheck  --leak-check=full --read-var-info=yes -s ./wiked ./entrada/entrada.txt

