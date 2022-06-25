vectors : vector.c vector.h
	gcc -Wall vector.c -o vector -lm
cleanup: 
	rm -rf vector 