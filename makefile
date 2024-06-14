app: derle run

derle:
	gcc -I ./include/ -o ./lib/komut.o -c ./src/komut.c -w
	gcc -I ./include/ -o ./obj/fields.o -c ./src/fields.c -w
	gcc -I ./include/ -o ./obj/jrb.o -c ./src/jrb.c -w
	gcc -I ./include/ -o ./obj/jval.o -c ./src/jval.c -w
	gcc -I ./include/ -o ./obj/dllist.o -c ./src/dllist.c -w

	gcc -I ./include/ -o ./bin/Test ./lib/komut.o ./obj/fields.o ./obj/jrb.o ./obj/dllist.o ./obj/jval.o ./src/pro1.c -w

run:
	./bin/Test