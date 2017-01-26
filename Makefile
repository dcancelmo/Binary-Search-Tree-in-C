#Daniel Cancelmo
#MakeFile to create an executable of the BST data structure implemented in main.c and BST.h
CC=gcc

makeBST : main.c
	$(CC) -o bst main.c
