a.out: asgn1_client_mod.o asgn1_implementation_mod.o
	gcc asgn1_client_mod.o asgn1_implementation_mod.o -lm
asgn1_client_mod.o: asgn1_client_mod.c asgn1_header_mod.h
	gcc -c asgn1_client_mod.c asgn1_header_mod.h
asgn1_implementation_mod.o: asgn1_implementation_mod.c asgn1_header_mod.h
	gcc -c asgn1_implementation_mod.c asgn1_header_mod.h

