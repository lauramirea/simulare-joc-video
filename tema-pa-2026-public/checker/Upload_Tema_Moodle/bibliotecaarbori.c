#include "bibliotecaarbori.h"
#include "bibliotecaqueue.h"
Nodearbore* newNode(Jucator *j) 
{ 
    Nodearbore* node=malloc(sizeof(Nodearbore));
    node->j=j;
    node->left=node->right=NULL;
    return node;
}
Nodearbore* insert(Nodearbore* node,Jucator *j) 
{
    if(node==NULL) 
        return newNode(j);
    if(j->energie<node->j->energie)
        node->left=insert(node->left,j); 
    else 
        if(j->energie>node->j->energie) 
            node->right=insert(node->right,j); 
    return node;
} 
void inorder(Nodearbore*root,Jucator *j) 
{
    if(root)
    {
        inorder(root->left,j);
        //printf("%d ",root->j->energie);
        inorder(root->right,j);
    }
}
Nodearbore* newNodeconcurs(Nodearbore *left,Nodearbore *right) 
{ 
    Nodearbore* node=malloc(sizeof(Nodearbore));
    node->j=NULL;
    node->left=left;node->right=right;
    return node;
}
Nodearbore *arboreconcurs(Nodearbore *root)
{
    if(root==NULL) return NULL;
    Nodearbore *aux=NULL;
    //inorder(root,j);
    if(root->left==root->right && root->right==NULL)
        return root;
    else
    {
        Nodearbore *stanga=arboreconcurs(root->left),*dreapta=arboreconcurs(root->right);
        root->left=root->right=NULL;
        if(stanga==NULL && dreapta!=NULL)
        {
            dreapta=newNodeconcurs(root,dreapta);
            return dreapta;
        }
        else
            if(stanga!=NULL && dreapta==NULL)
            {
                stanga=newNodeconcurs(stanga,root);
                return stanga;
            }
            else
            {
                if(stanga!=NULL && dreapta!=NULL)
                {
                    Nodearbore *aux2=newNodeconcurs(stanga,root);
                    aux=newNodeconcurs(aux2,dreapta);
                    return aux;
                }
            } 
            return root;
    }
}
void printLevel(Nodearbore* root, FILE *f_lupta_iesire)
{
    if (root==NULL) return;
    if(root->j!=NULL &&root->left==root->right && root->right==NULL) 
    {
        fprintf(f_lupta_iesire, "J%d", root->j->id);
    }
    else 
    {
        printLevel(root->left,f_lupta_iesire);
        printLevel(root->right,f_lupta_iesire);
    }
}
void postorder(Nodearbore*root,FILE *f_lupta_iesire) 
{     
    if(root)
    {
        postorder(root->left,f_lupta_iesire);
        postorder(root->right,f_lupta_iesire);
        printLevel(root,f_lupta_iesire);
        /*char sir[5];
        strcat(sir,"J");
        strcat(sir,root->j->id);
        fprintf(f_lupta_iesire,"%s ",sir);*/
        fprintf(f_lupta_iesire,"\n");
    }
    
}
void lupta(Nodearbore*root)
{
    if(root==NULL) return;
    lupta(root->left);lupta(root->right);
    if(root->left!=NULL &&root->right!=NULL)
    {
        Jucator *j1=root->left->j,*j2=root->right->j;
        if(j1->energie>=j2->energie)
        {
            root->j=j1;
            root->j->energie=j1->energie+(j1->energie-j2->energie);
        }
        else
        {
            root->j=j2;
            root->j->energie=j2->energie+(j2->energie-j1->energie);
        }
    }
    if(root->left!=NULL && root->right==NULL) root->j=root->left->j;
    if(root->right!=NULL && root->left==NULL) root->j=root->right->j;
}
void eliberarearbore(Nodearbore*root)
{
    if(root)
    {
        eliberarearbore(root->left);
        eliberarearbore(root->right);
        if(root->j && root->left==root->right && root->right==NULL)
        {
            free(root->j->prenume_nume);
            free(root->j);
        }
        free(root);
    }

        
}
/*Node* Create ()
{ 
    Data val;
    char c;
    Node* root= malloc(sizeof(Node));
    printf(“Dati valoarea pentru nod: "); scanf("%d", &val);
    root->val =val;

    printf(“Nodul adaugat are subarbore stang? d/n "); scanf("%c", &c);
    if (c=='d') root->left= Create( );
    else root->left=NULL;
    printf(" Nodul adaugat are subarbore drept? d/n " ); scanf("%c", &c);
    if (c=='d') root->right= Create( );
    else root->right=NULL;
    return root; 
}*/