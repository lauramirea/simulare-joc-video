#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#ifndef bibliotecastiva_h
#define bibliotecastiva_h
typedef struct misiune
{
    int xi,yi,xf,yf;

}misiune;
struct misiune;
typedef struct Nodestiva 
{
    misiune m;
    struct Nodestiva *next;
} Nodestiva;
typedef struct Stiva
{
    Nodestiva *top;
}Stiva;
void push(Nodestiva**top,misiune m);
misiune pop(Nodestiva**top);
int isEmptystiva(Nodestiva* top);
void afisareStiva(Nodestiva *top);
void deleteStack(Nodestiva**top);
#endif
