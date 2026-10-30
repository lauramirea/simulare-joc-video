#include "bibliotecaheap.h"
#include "bibliotecaarbori.h"
#include "bibliotecaqueue.h"
Heapmax * create(int capacitate)
{
    Heapmax * h=malloc(sizeof(Heapmax));
    if(h==NULL) 
    { 
        printf("Nu s-a putut aloca spatiu");
        return NULL;
    }
    h->size=0;
    h->capacity=capacitate;
    h->vec=malloc(sizeof(Jucator*)*h->capacity);
    if(h->vec == NULL) 
    { 
        free(h); 
        printf("Nu s-a putut aloca spatiu"); 
        return NULL;
    }
    return h;
}
int resize(Heapmax *h)
{
     h->capacity=2*h->capacity;
    Jucator**v=realloc(h->vec, sizeof(Jucator*)*h->capacity); 
    if (v==NULL) 
    {   
        printf("out-of-memory"); 
        return 0;
    }
    h->vec=v;
    return 1;
}

void insertHeap(Heapmax *h,Jucator *j)
{
    int i=h->size;
    if (h->size==h->capacity) 
    {
        int ok=resize(h); 
        if(ok==0) return;
    }
    h->vec[i]=j;
    h->size++; 
    while(i>0 && h->vec[(i-1)/2]->energie<h->vec[i]->energie)//sau apelez functia parent
    { 
        Jucator *jucator=h->vec[i];
        h->vec[i]=h->vec[(i-1)/2];
        h->vec[(i-1)/2]=jucator;
        i=(i-1)/2;
    } 
} 

int leftChild(Heapmax *h, int i)
{
    int poz = 2*i+1;
    if(h==NULL || poz>h->size-1 || i<0)
        return -1; 
    return poz;
}
int rightChild(Heapmax *h, int i)
{
    int poz = 2*i+2;
    if (h==NULL || poz > h->size-1 || i<0)
        return -1; 
    return poz;
}
void heapifyDown(Heapmax *h, int i)
{ 
    int l, r, max;
    Jucator *aux;
    while(1)
    { 
        max=i; 
        l=leftChild(h,i); 
        r=rightChild(h,i); 
        if (l!=-1 && h->vec[l]->energie> h->vec[max]->energie) 
            max=l; 
        if (r!=-1 && h->vec[r]->energie> h->vec[max]->energie) 
            max=r;
        if(max!=i)
        { 
            aux=h->vec[i];
            h->vec[i]=h->vec[max];
            h->vec[max]=aux;
            i=max; 
        }
        else break; 
    }
} 
Jucator *maxVal(Heapmax *h)
{
    if (h==NULL || h->size==0)
        return NULL;
    else
    {  
         Jucator *j=h->vec[0];
        h->vec[0]=h->vec[h->size-1];
        h->size--;
        heapifyDown(h,0);
        return j;
    }  
}
void deleteHeap(Heapmax**h)
{
    if (*h==NULL) return;
    free((*h)->vec); 
    free(*h );
    *h=NULL;
}