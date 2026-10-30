#include "bibliotecastiva.h"
#include "bibliotecaheapmin.h"
#include "bibliotecaarbori.h"
Heapmin * createmin(int capacitate)
{
    Heapmin * h=malloc(sizeof(Heapmin));
    if(h==NULL) 
    { 
        printf("Nu s-a putut aloca spatiu");
        return NULL;
    }
    h->size=0;
    h->capacity=capacitate;
    h->vec=malloc(sizeof(NodAstar*)*h->capacity);
    if(h->vec == NULL) 
    { 
        free(h); 
        printf("Nu s-a putut aloca spatiu"); 
        return NULL;
    }
    return h;
}
int resizemin(Heapmin *h)
{
     h->capacity=2*h->capacity;
    NodAstar**v=realloc(h->vec, sizeof(NodAstar*)*h->capacity); 
    if (v==NULL) 
    {   
        printf("out-of-memory"); 
        return 0;
    }
    h->vec=v;
    return 1;
}
void insertHeapmin(Heapmin *h,NodAstar *a)
{
    int i=h->size;
    if (h->size==h->capacity) 
    {
        int ok=resizemin(h); 
        if(ok==0) return;
    }
    h->vec[i]=a;
    h->size++; 
    while(i>0 && h->vec[(i-1)/2]->f>h->vec[i]->f)
    { 
        NodAstar *astar=h->vec[i];
        h->vec[i]=h->vec[(i-1)/2];
        h->vec[(i-1)/2]=astar;
        i=(i-1)/2;
    } 
} 

int leftChildmin(Heapmin *h, int i)
{
    int poz = 2*i+1;
    if(h==NULL || poz>h->size-1 || i<0)
        return -1; 
    return poz;
}
int rightChildmin(Heapmin *h, int i)
{
    int poz=2*i+2;
    if (h==NULL || poz > h->size-1 || i<0)
        return -1; 
    return poz;
}
void heapifyDownmin(Heapmin *h, int i)
{ 
    int l, r, max;
    NodAstar*aux;
    while(1)
    { 
        max=i; 
        l=leftChildmin(h,i); 
        r=rightChildmin(h,i); 
        if (l!=-1 && h->vec[l]->f<h->vec[max]->f) 
            max=l; 
        if (r!=-1 && h->vec[r]->f<h->vec[max]->f) 
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
NodAstar*maxValheapmin(Heapmin *h)
{
    if (h==NULL || h->size==0)
        return NULL;
    else
    {  
        NodAstar *astar=h->vec[0];
        h->vec[0]=h->vec[h->size-1];
        h->size--;
        heapifyDownmin(h,0);
        return astar;
    }  
}
void afisaredrum(FILE *f_misiune_iesire,NodAstar *rez,Jucator *jucator, float energie_initiala)
{
    NodAstar *curent=rez;
    int nrpasi=0,drumx[1000],drumy[1000];
    while(curent)
    {
        drumx[nrpasi]=curent->x;
        drumy[nrpasi]=curent->y;
        nrpasi++;
        curent=curent->parinte;
    }
    float energie_ramasa=energie_initiala-rez->g;
    fprintf(f_misiune_iesire,"J%d - %.2f: ",jucator->id,energie_ramasa);
    for(int i=nrpasi-1;i>=0;i--)
    {
        fprintf(f_misiune_iesire,"[%d, %d]",drumx[i],drumy[i]);
        if(i>0) fprintf(f_misiune_iesire," -- ");
    }  
}
NodAstar* astar(int xi,int yi,int xf,int yf,int **mbool,float **m2,float **m3,int nrlinie,int nrcol,Jucator *jucator,float min_cost,NodAstar *arena,int *j )
{
    Heapmin *h=createmin((nrlinie+1)/2*nrcol); NodAstar *start=&arena[(*j)++];
    start->x=xi;start->y=yi;start->parinte=NULL;
    start->g=0.0;start->h=abs(xi-xf)+abs(yi-yf);start->f=start->g+start->h;
    insertHeapmin(h,start);float cost_mutare=0.0;
    int vizitat[(nrlinie+1)/2][nrcol];
    for(int i=0;i<(nrlinie+1)/2;i++)
        for(int j=0;j<nrcol;j++)
            vizitat[i][j]=0;
    int drumx[]={-1,1,0,0},drumy[]={0,0,-1,1};
    while(h->size>0)
    {
        NodAstar *nod=maxValheapmin(h);
        if(nod->x==xf && nod->y==yf) 
        {
            deleteHeapmin(&h);
            return nod;
        }
        if(vizitat[nod->x][nod->y]==1)continue;
        vizitat[nod->x][nod->y]=1;
        for(int i=0;i<4;i++)
        {
            int xnou=nod->x+drumx[i],ynou=nod->y+drumy[i];
            if(xnou>=0 && xnou<(nrlinie+1)/2 && ynou>=0 && ynou<nrcol && mbool[xnou][ynou]==0 && vizitat[xnou][ynou]==0)
            {
                float cost=0.0;
                if(i==0) cost=m2[xnou][ynou];
                else if(i==1) cost=m2[nod->x][nod->y];
                else if(i==2)cost=m3[xnou][ynou];
                else if(i==3)cost=m3[nod->x][nod->y];
                float g_nou=nod->g+cost;
                if(jucator->energie-g_nou>0)
                {
                    NodAstar *vecin=&arena[(*j)++];
                    vecin->x=xnou; vecin->y=ynou;
                    vecin->g=g_nou;
                    vecin->h=abs(xnou-xf)+abs(ynou-yf);
                    vecin->f=vecin->g+vecin->h*min_cost; 
                    vecin->parinte=nod;
                    insertHeapmin(h,vecin);
                }
            }    
        }
    }
    deleteHeapmin(&h);return NULL;
}
void deleteHeapmin(Heapmin**h)
{
    if (*h==NULL) return;
    free((*h)->vec); 
    free(*h );
    *h=NULL;
}