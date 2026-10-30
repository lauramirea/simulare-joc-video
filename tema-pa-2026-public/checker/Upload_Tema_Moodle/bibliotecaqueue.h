#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#ifndef bibliotecaqueue_h
#define bibliotecaqueue_h
typedef struct Jucator
{
    char *prenume_nume;
    float energie;
    enum {
        NEUTRALITATE, REINCERCARE, RENASTERE
    }abilitate;
    int id;
    
}Jucator;
typedef struct QueueNode 
{
    Jucator *jucator;
    struct QueueNode *next;
} QueueNode;
typedef struct Queue
{
    QueueNode *front, *rear; 
} Queue; 
Queue* createQueue();
int isEmptyqueue(Queue*q);
void enQueue(Queue*q,Jucator *j);
void afisareQueue(Queue *q);
Jucator *deQueue(Queue*q);
void deleteQueue(Queue*q);
#endif