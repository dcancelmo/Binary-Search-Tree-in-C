#MakeFile to create an executable of the BST data structure implemented in main.c and BST.h
CC=gcc

BSTMake: main.o BST.h
     $(CC) -o BST1-10 main.o BST.h