#include "bibliotecastiva.h"
void push(Nodestiva**top,misiune m)
{ 
    Nodestiva* newNode=malloc(sizeof(Nodestiva));
    newNode->m=m;
    newNode->next=*top; 
    *top = newNode;
} 
misiune pop(Nodestiva**top) 
{
    if(isEmptystiva(*top)) return (misiune){0,0,0,0};
    Nodestiva* temp = (*top); 
    misiune aux = temp->m;
    *top=(*top)->next;
    free(temp);
    return aux;
}
int isEmptystiva(Nodestiva* top)
{
    return (top==NULL);
}
void afisareStiva(Nodestiva *top)
{
    FILE *f_misiuni_iesire=fopen("Pas_1/test_1_3.csv","w");
    if(f_misiuni_iesire==NULL)
    {
        printf("nu s-a deschis fisierul");
        return;
    }
        
     fprintf(f_misiuni_iesire,"Xi;Yi;Xf;Yf\n");
    Nodestiva *temp=top;
    if(temp==NULL)
        printf("nu intram in while");
    while(temp!=NULL)
    {
        misiune *m=&(temp->m);
        fprintf(f_misiuni_iesire,"%d;%d;%d;%d\n",m->xi,m->yi,m->xf,m->yf);
        temp=temp->next;
    }

    fclose(f_misiuni_iesire);
}
void deleteStack(Nodestiva**top)
{
    Nodestiva *temp;
    while((*top)!= NULL)
    { 
        temp=*top;
        *top=(*top)->next;
        free(temp);
    }
} //O(n)