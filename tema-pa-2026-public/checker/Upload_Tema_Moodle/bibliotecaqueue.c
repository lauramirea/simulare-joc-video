#include "bibliotecaqueue.h"
Queue* createQueue()
{
    Queue *q;
    q=malloc(sizeof(Queue));
    if(q==NULL) 
        return NULL;
    q->front=q->rear=NULL;
    return q;
}
int isEmptyqueue(Queue*q)
{
    return(q->front==NULL);
} 
void enQueue(Queue*q,Jucator *j)
{
    QueueNode* newNode=malloc(sizeof(QueueNode));
    newNode->jucator=j;
    newNode->next=NULL;
    ///citeste din fisier energia
    if(q->rear == NULL) 
    {
        q->rear=newNode; 
        q->front = q->rear; 
    }
    else
    {
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }
}

void afisareQueue(Queue *q)
{
    FILE *f_jucatori_iesire=fopen("Pas_1/test_1_1.csv","w");
    if(f_jucatori_iesire==NULL)
        printf("nu s-a dechis fisierul");
    fprintf(f_jucatori_iesire,"PRENUME NUME;ENERGIE;ABILITATE;ID\n");
    QueueNode *temp=q->front; 
    int id=0;
    if(temp==NULL)
        printf("nu intram in while");
    while(temp!=NULL)
    {
        Jucator *j=temp->jucator;
        char abilitate[40];
        fprintf(f_jucatori_iesire,"%s;%.2f;",j->prenume_nume,j->energie);
        if(j->abilitate==REINCERCARE)
            fprintf(f_jucatori_iesire,"REINCERCARE;");
        else
            if(j->abilitate==RENASTERE)
                fprintf(f_jucatori_iesire,"RENASTERE;");
            else
                if(j->abilitate==NEUTRALITATE)
                    fprintf(f_jucatori_iesire,"NEUTRALITATE;");
        j->id=id;
        fprintf(f_jucatori_iesire,"%d",j->id);
        id++;
        temp=temp->next;
    }
    fclose(f_jucatori_iesire);
}
Jucator *deQueue(Queue*q) 
{
    if(isEmptyqueue(q)) return 0; 
    QueueNode* aux=q->front;
    Jucator *j=aux->jucator;
    q->front=(q->front)->next;
    free(aux);
    if(q->front==NULL) 
        q->rear=NULL; 
    return j;
}

void deleteQueue(Queue*q)
{
    QueueNode* aux;
    while(!isEmptyqueue(q))
    {
        aux=q->front;
        q->front=q->front->next;
        free(aux->jucator->prenume_nume);
        free(aux->jucator);
        free(aux);
    }
    free(q);
}