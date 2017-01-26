/*
 Daniel Cancelmo
 CSC 173 - Computation & Formal Systems
 Prof. Ferguson
 I attest that all work herein is my own and I did not collaborate with anyone.
 */


#ifndef BST_h
#define BST_h

//Node structure
struct node {
    int value;
    struct node *left;
    struct node *right;
    struct node *parent;
};
//Boolean type
typedef int Boolean;
#define true 1;
#define false 0;

//Function declarations
struct node* newTree(int val);
struct node* newNode(int val, struct node* parentN);
struct node* insert(int val, struct node* node);
struct node* insertH(int val, struct node* rootNode, struct node* nodePar);
struct node* deleteNode(int val, struct node* rootNode);
struct node* deleteH(int val, struct node* rootNode, struct node* nodePar);
struct node* findLowest(struct node* current);
Boolean lookup(int val, struct node* rootNode);
void printIn(struct node** rootNode);
void printInH(struct node** rootNode);
void printPre(struct node** rootNode);
void printPreH(struct node** rootNode);
void printPost(struct node** rootNode);
void printPostH(struct node** rootNode);


#endif /* BST_h */
