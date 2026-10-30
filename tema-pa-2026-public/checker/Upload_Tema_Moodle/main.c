#include "bibliotecaqueue.h"
#include "bibliotecastiva.h"
#include "bibliotecaarbori.h"
#include "bibliotecaheap.h"
#include "bibliotecaheapmin.h"
int main() 
{

    Queue *q=createQueue();
    FILE *f_jucatori_intrare=fopen("Pas_1/jucatori.csv","r");
    if(f_jucatori_intrare==NULL)
        printf("Nu s-a putut deschide fisierul ");
    else
    {
        
        char line[256];
        fgets(line, sizeof(line), f_jucatori_intrare);
        float energie;
        char prenume_nume[60],abilitate[40];
        int id=0;
        while(fscanf(f_jucatori_intrare, "%[^;]; %f; %s",prenume_nume ,&energie,abilitate)==3)
        {
            Jucator *jucator;
            jucator=malloc(sizeof(Jucator));
            jucator->prenume_nume=malloc(sizeof(char)*(strlen(prenume_nume)+1));
            strcpy(jucator->prenume_nume,prenume_nume);
            //strcpy(jucator->prenume_nume,prenume_nume);
            jucator->energie=energie;
            jucator->id=id;
            id++;
            if(strcmp(abilitate,"NEUTRALITATE")==0)
                jucator->abilitate=NEUTRALITATE;
            else 
                if(strcmp(abilitate,"REINCERCARE")==0)
                    jucator->abilitate=REINCERCARE;
                else    
                    if(strcmp(abilitate,"RENASTERE")==0)
                        jucator->abilitate=RENASTERE;
            enQueue(q,jucator);
        }

    }
    fclose(f_jucatori_intrare);
    afisareQueue(q);

    FILE *f_harta_intrare=fopen("Pas_1/harta.txt","r");
    int **mbool;
    float **m2,**m3;
    int nrlinie=0,nrcol=0,linie=0;
    float nr,nraux;
    char line[256];
    int caracter,parcurgere=0;
    while(fgets(line,sizeof(line),f_harta_intrare)!=NULL)
    {
        if(nrlinie==0)
        {
            int caracter,parcurgere=0;
            while(sscanf(line+parcurgere,"%f %n",&nraux,&caracter)==1)
            {
                    if(linie%2==0)nrcol++;
                    linie++;
                    parcurgere=caracter+parcurgere;
            }
        }

        nrlinie++;
    }
    mbool=malloc((nrlinie+1)/2*sizeof(int*));
    m2=malloc((nrlinie/2)*sizeof(float*));
    m3=malloc(((nrlinie+1)/2)*sizeof(float*));
    nrlinie=0;
    FILE *f_harta_iesire=fopen("Pas_1/test_1_2.txt","w");
    rewind(f_harta_intrare);
    while(fgets(line,sizeof(line),f_harta_intrare)!=NULL)
    {
        if(nrlinie%2==0)
        {
            int coloana=0,coloanabool=0,coloanam3=0;
            int caracter,parcurgere=0;
            mbool[nrlinie/2]=malloc(nrcol*sizeof(int));
            m3[nrlinie/2]=malloc((nrcol-1)*sizeof(float));
            while(sscanf(line+parcurgere,"%f %n",&nr,&caracter)==1)
            {
                if(coloana%2==0)
                {
                    mbool[nrlinie/2][coloanabool]=(int)nr;
                    coloanabool++;
                }
                else
                {
                    m3[nrlinie/2][coloanam3]=nr;
                    coloanam3++;
                }
                coloana++;
                parcurgere=parcurgere+caracter;
            }

        }
        else
        {
            int coloanam2=0,caracter,parcurgere=0;
            m2[nrlinie/2]=malloc(nrcol*sizeof(float));
            while(sscanf(line+parcurgere,"%f %n",&nr,&caracter)==1)
            {
                m2[nrlinie/2][coloanam2]=nr;
                coloanam2++;
                parcurgere=parcurgere+caracter;
            }
            
        }
        nrlinie++;
    }
    for(int i=0;i<(nrlinie+1)/2;i++)
    {
        for(int j=0;j<nrcol;j++)
            fprintf(f_harta_iesire,"%d ",mbool[i][j]);
        if(i!=nrlinie-1)
            fprintf(f_harta_iesire,"\n");
    }
    for(int i=0;i<nrlinie/2;i++)
    {
        for(int j=0;j<nrcol;j++)
            fprintf(f_harta_iesire,"%.2f ", m2[i][j]);
        if(i!=nrlinie-1)
            fprintf(f_harta_iesire,"\n");
    }
    for(int i=0;i<(nrlinie+1)/2;i++)
    {
        for(int j=0;j<nrcol-1;j++)
            fprintf(f_harta_iesire,"%.2f ",m3[i][j]);
        if(i!=(nrlinie+1)/2-1)
            fprintf(f_harta_iesire,"\n");
        //fprintf(f_harta_iesire,"\n");
    }
    fclose(f_harta_iesire);
    fclose(f_harta_intrare);
    FILE *f_misiuni_intrare=fopen("Pas_1/misiuni.csv","r");
    int i;
    Nodestiva* stackTop=NULL;
    misiune m;
    fgets(line,sizeof(line),f_misiuni_intrare);
    while((fscanf(f_misiuni_intrare,"%d;%d;%d;%d",&m.xi,&m.yi,&m.xf,&m.yf))==4)
        push(&stackTop,m);
    fclose(f_misiuni_intrare);
    afisareStiva(stackTop);
    Nodearbore *root=NULL;
    Jucator **toti=malloc(sizeof(Jucator*)*1000);
    int capacity=0;
    while(isEmptyqueue(q)==0)
    {
        Jucator *jucator=deQueue(q);
        root=insert(root,jucator);
        toti[capacity]=jucator;
        capacity++;
    }
    FILE *f_lupta_iesire=fopen("Pas_2/test_2_1.txt","w");
    root=arboreconcurs(root);
    if(f_lupta_iesire==NULL)
        printf("nu s-a dechis fisierul");
    else
    {
        postorder(root,f_lupta_iesire);
        fclose(f_lupta_iesire);
    }
    lupta(root);
    Heapmax *h=create(capacity);
    for(int i=0;i<capacity;i++)
    {
        insertHeap(h,toti[i]);
        //insertHeapmin(h,toti[i]);
    }   
    FILE *f_concurs_iesire=fopen("Pas_2/test_2_2.txt","w");
    if(f_concurs_iesire==NULL)  return 1;
    int k=1;
    while(k*2<=capacity)
        k=k*2;
    Jucator **clasament=malloc(k*sizeof(Jucator*));
    for(int i=0;i<k;i++)
    {
        Jucator *castigator=maxVal(h);
        if(castigator)
        {
            clasament[i]=castigator;
            fprintf(f_concurs_iesire,"J%d %.2f\n",castigator->id,castigator->energie);
        }     
    }
    fclose(f_concurs_iesire);
    float min_cost=100000.0;
    for(int i=0;i<nrlinie/2;i++)
    {
        for(int j=0;j<nrcol;j++)
        {
            if(m2[i][j]<min_cost)
                min_cost=m2[i][j];
        }
    }
    for(int i=0;i<(nrlinie+1)/2;i++)
    {
        for(int j=0;j<nrcol-1;j++)
        {
            if(m3[i][j]<min_cost)
                min_cost=m3[i][j];
        }
    }
    FILE *f_misiune_iesire=fopen("Pas_3/test_3.txt","w");
    if(f_misiune_iesire==NULL)printf("nu s-a deschis fisierul");
    else
    {
            int max_noduri=((nrlinie+1)/2)*nrcol*4;
            NodAstar *arena=malloc(max_noduri*sizeof(NodAstar));
            for(int i=0;i<k;i++)
            {
                if(stackTop==NULL) break;
                misiune m=pop(&stackTop);
                Jucator *jucator_curent=clasament[i];
                int j=0;
                NodAstar *rez=astar(m.xi,m.yi,m.xf,m.yf,mbool,m2,m3,nrlinie,nrcol,jucator_curent,min_cost,arena,&j);
                if(rez!=NULL)
                {
                    afisaredrum(f_misiune_iesire, rez,jucator_curent,jucator_curent->energie);
                    if(i!=k-1)
                        fprintf(f_misiune_iesire,"\n");
                }
                else
                {
                    fprintf(f_misiune_iesire, "J%d: Nu s-a putut efectua misiunea", jucator_curent->id);
                    if(i!=k-1)
                        fprintf(f_misiune_iesire,"\n");
                }
                    
            }
            free(arena);
            fclose(f_misiune_iesire);
    }
   
    for(int i=0;i<(nrlinie+1)/2;i++)
            free(mbool[i]);
    free(mbool);
    for(int i=0;i<nrlinie/2;i++)
        free(m2[i]);
    free(m2);
    for(int i=0;i<(nrlinie+1)/2;i++)
        free(m3[i]);
    free(m3);
    eliberarearbore(root);
    deleteQueue(q);
    deleteStack(&stackTop);
    deleteHeap(&h);
    free(clasament);
    /*for(int i=0;i<capacity;i++)
    {
        free(toti[i]->prenume_nume);
        free(toti[i]);
    }*/
    free(toti);


}

