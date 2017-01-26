/*
 Daniel Cancelmo
 CSC 173 - Computation & Formal Systems
 Prof. Ferguson
 I attest that all work herein is my own and I did not collaborate with anyone.
 */

#include <stdio.h>
#include <stdlib.h>
#include "BST.h"


//Main method: Contents of main method used for testing.
int main(int argc, const char * argv[]) {
    
    struct node* root1 = newTree(5);
    insert(3, root1);
    insert(8, root1);
    insert(2, root1);
    insert(1, root1);
    insert(7, root1);
    insert(10, root1);
    insert(6, root1);
    insert(4, root1);
    insert(9, root1);
    printf("Root: %d\nLeft child: %d\nParent of left child: %d\n", root1->value, root1->left->value, root1->left->parent->value);
    printf("Is 7 in the tree? %d\n", lookup(7, root1));
    printf("Is 11 in the tree? %d\n", lookup(11, root1));
    printf("Is 5 in the tree? %d\n", lookup(5, root1));
    printIn(&root1);
    printPre(&root1);
    printPost(&root1);
    deleteNode(4, root1);
    printIn(&root1);
    
    return 0;
}

//Creates a new BST by returning a node with no parent to serve as the root
struct node* newTree(int val) {
    struct node* newN = (struct node*)malloc(sizeof(struct node));
    newN->value = val;
    newN->left = NULL;
    newN->right = NULL;
    newN->parent = NULL;
    return newN;
}
//Creates a new node by returning a node with given value and parent value
struct node* newNode(int val, struct node* parentN) {
    struct node* newN = (struct node*)malloc(sizeof(struct node));
    newN->value = val;
    newN->left = NULL;
    newN->right = NULL;
    newN->parent = parentN;
    return newN;
}

//Sets up the insertH helper function by allowing the user to insert without specifying a parent. Passes NULL as a parent to the initial insert of the value
struct node* insert(int val, struct node* rootNode) {
    return insertH(val, rootNode, NULL);
}


//Inserts val into its proper location in the BST
struct node* insertH(int val, struct node* rootNode, struct node* nodePar) {
    //If the tree is empty, return a new node
    if (rootNode == NULL) {
        return newNode(val, nodePar);
    }
    //Otherwise, go to left if val is lower or gith if val is higher using recursion
    if (val < rootNode->value) {
        rootNode->left  = insertH(val, rootNode->left, rootNode);
    }
    else if (val > rootNode->value) {
        rootNode->right = insertH(val, rootNode->right, rootNode);
    }
    // return the original node pointer
    return rootNode;
}

//Sets up the deleteH helper function by allowing the user to delete without specifying a parent. Passes NULL as a parent to the initial delete of the value
struct node* deleteNode(int val, struct node* rootNode) {
    return deleteH(val, rootNode, NULL);
}

//Deletes a node from the subtree. Considers all cases: node not in tree, node has no children, nodes has exactly one child, node has two children
struct node* deleteH(int val, struct node* rootNode, struct node* nodePar) {
    //Case 0: Empty tree-Do nothing and node not in tree
    if (rootNode == NULL) {
        return NULL;
    }
    if (val == rootNode->value) {
        //Case 1: No children
        if (rootNode->left == NULL && rootNode->right == NULL) {
            //Node is a left child of the parent
            if (nodePar->left->value == rootNode->value) {
                free(nodePar->left);
                nodePar->left = NULL;
            //Node is a right child of the parent
            } else {
                free(nodePar->right);
                nodePar->right = NULL;
            }
        //Case 2: Exactly one child/subtree
        } else if (!(rootNode->left == NULL) != !(rootNode->right == NULL)) {
            //Node has left child
            if (rootNode->left != NULL) {
                struct node* temp = rootNode->left;
                //Node is a left child of the parent
                if (nodePar->left->value == rootNode->value) {
                    free(nodePar->left);
                    nodePar->left = temp;
                //Node is a right child of the parent
                } else {
                    free(nodePar->right);
                    nodePar->right = temp;
                }
                free(temp);
            //Node has right child
            } else {
                struct node* temp = rootNode->right;
                //Node is a left child of the parent
                if (nodePar->left->value == rootNode->value) {
                    free(nodePar->left);
                    nodePar->left = temp;
                //Node is a right child of the parent
                } else {
                    free(nodePar->right);
                    nodePar->right = temp;
                }
                free(temp);
            }
        //Case 3: Two children/subtree
        } else if ((rootNode->left != NULL) && (rootNode->right != NULL)) {
            //Finds lowest value in right subtree of node
            struct node* temp = findLowest(rootNode->right);
            //Replaces nodes value with that of the lowest in the right sub tree
            rootNode->value = temp->value;
            //Frees the lowest value node of the right subtree
            free((temp->parent)->left);
            
        }
    } else if (val < rootNode->value) {
        deleteH(val, rootNode->left, rootNode);
    }
    else if (val > rootNode->value) {
        deleteH(val, rootNode->right, rootNode);
    }
    // return the original node pointer
    return rootNode;
}

//Finds the smallest value in a given subtree
struct node* findLowest(struct node* current) {
    if(current == NULL) return current;
    else if(current->left == NULL) return current;
    return findLowest(current->left);
}

//Finds if a given value is in the tree already or not
Boolean lookup(int val, struct node* rootNode) {
    if (rootNode == NULL) {
        return false;
    }
    if (val == rootNode->value) {
        return true;
    } else if (val < rootNode->value) {
        return lookup(val, rootNode->left);
    } else if (val > rootNode->value) {
        return lookup(val, rootNode->right);
    }
    return false;
}

//Adds the newline character after done printng. Uses helper function 'H' to actually print.
void printIn(struct node** rootNode) {
    printInH(rootNode);
    printf("\n");
}

//In-order print
void printInH(struct node** rootNode) {
    if (*rootNode) {
        printInH(&(*rootNode)->left);
        printf("%d\t", (*rootNode)->value);
        printInH(&(*rootNode)->right);
    }
}

//Adds the newline character after done printng. Uses helper function 'H' to actually print.
void printPre(struct node** rootNode) {
    printPreH(rootNode);
    printf("\n");
}

//pre-order print
void printPreH(struct node** rootNode) {
    if (*rootNode) {
        printf("%d\t", (*rootNode)->value);
        printPreH(&(*rootNode)->left);
        printPreH(&(*rootNode)->right);
    }
}

//Adds the newline character after done printng. Uses helper function 'H' to actually print.
void printPost(struct node** rootNode) {
    printPostH(rootNode);
    printf("\n");
}

//post-order print
void printPostH(struct node** rootNode) {
    if (*rootNode) {
        printPostH(&(*rootNode)->left);
        printPostH(&(*rootNode)->right);
        printf("%d\t", (*rootNode)->value);
    }
}

//This insert method does not insert correctly
/*
//Does an initial comparison to set up the helper function 'H' to actually insert the value.
void insert(int val, struct node* rootNode) {
    //printf("%d\n", rootNode);
    if (val < (rootNode)->value) {
        insertH(val, rootNode, "left");
    } else if (val > (rootNode)->value) {
        insertH(val, rootNode, "right");
    }
}

//Inserts val into the BST in its proper location
void insertH(int val, struct node* rootNode, char* helper) {
    if (!strcmp(helper, "left")) {
        if (rootNode->left == NULL) {
            rootNode->left = (struct node*)malloc(sizeof(struct node));
            rootNode->left->value = val;
            (rootNode->left)->parent = rootNode;
            rootNode->left->left = NULL;
            rootNode->left->right = NULL;
        } else {
            if (val < (rootNode)->value) {
                insertH(val, rootNode->left, "left");
            } else if (val > (rootNode)->value) {
                insertH(val, rootNode->left, "right");
            }
        }
    } else if (!strcmp(helper, "right")) {
        if (rootNode->right == NULL) {
            rootNode->right = (struct node*)malloc(sizeof(struct node));
            rootNode->right->value = val;
            (rootNode->right)->parent = rootNode;
            rootNode->right->left = NULL;
            rootNode->right->right = NULL;
            
        } else {
            if (val < (rootNode)->value) {
                insertH(val, rootNode->right, "left");
            } else if (val > (rootNode)->value) {
                insertH(val, rootNode->right, "right");
            }
        }
    }
}
*/
