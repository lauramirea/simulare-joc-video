#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecaqueue.h"
#ifndef bibliotecaarbore_h
#define bibliotecaarbore_h
typedef struct Nodearbore 
{
    Jucator *j; 
    struct Nodearbore *left,*right;
}Nodearbore;
Nodearbore* newNode(Jucator *j);
Nodearbore* insert(Nodearbore* node,Jucator *j);
void inorder(Nodearbore*root,Jucator *j);
Nodearbore* newNodeconcurs(Nodearbore *left,Nodearbore *right);
Nodearbore *arboreconcurs(Nodearbore *root);
void postorder(Nodearbore*root,FILE *f_lupta_iesire);
void lupta(Nodearbore*root);
void eliberarearbore(Nodearbore *root);
#endif
