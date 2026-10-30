
#include "bibliotecastiva.h"
#include "bibliotecaqueue.h"
#ifndef bibliotecaheapmin_h
#define bibliotecaheapmin_h
typedef struct NodAstar
{
    int x,y,f;
    float g,h;
    int cost;
    struct NodAstar *parinte;
}NodAstar;
typedef struct Heapmin
{
    NodAstar **vec; 
    int size, capacity; 
} Heapmin;
void insertHeapmin(Heapmin *h,NodAstar *a);
int resizemin(Heapmin *h);
int leftChildmin(Heapmin *h, int i);
int rightChildmin(Heapmin *h, int i);
void heapifyDownmin(Heapmin *h, int i);
NodAstar*maxValheapmin(Heapmin *h);
void afisaredrum(FILE *f_misiune_iesire,NodAstar *rez,Jucator *jucator, float energie_initiala);
NodAstar* astar(int xi,int yi,int xf,int yf,int **mbool,float **m2,float **m3,int nrlinie,int nrcol,Jucator *jucator,float min_cost,NodAstar *arena,int *j );
void deleteHeapmin(Heapmin**h);
#endif