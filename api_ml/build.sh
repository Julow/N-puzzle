ocamlc lol.mli -o lol.cmi &&

ocamlc -I . -c test.ml -o test.cmo &&
ocamlc -I . -c lol_init.ml -o lol_init.cmo &&

ocamlc -output-obj lol_init.cmo test.cmo -o test_ml.o &&

clang -c main.c -I`ocamlc -where` -o main.o &&

clang main.o test_ml.o -L`ocamlc -where` -lcamlrun -lncurses
