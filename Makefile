################################## CAPITULO 1 ######################################

capitulo1:listing-1.1
clean_c1:
	rm obj/capitulo_1/*.o
	rm bin/capitulo_1/reciproco

listing-1.1: obj/capitulo_1/main.o obj/capitulo_1/reciprocal.o
	g++ obj/capitulo_1/main.o obj/capitulo_1/reciprocal.o -o bin/capitulo_1/reciproco
obj/capitulo_1/main.o:
	gcc -c -Isrc/capitulo_1 src/capitulo_1/main.c -o obj/capitulo_1/main.o
obj/capitulo_1/reciprocal.o:
	g++ -c -Isrc/capitulo_1 src/capitulo_1/reciprocal.cpp -o obj/capitulo_1/reciprocal.o
