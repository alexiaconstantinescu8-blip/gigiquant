#include"task3.h"
actiune* nou_nod(const char* denumire)
{
    actiune *node = (actiune*)malloc(sizeof(actiune));
     if( node == NULL)
    {
        printf("Alocarea a esuat");
        exit(1);
    }
    node->next = NULL;
    node->pret = (float*)malloc(1000*sizeof(float));
    strcpy(node->nume,denumire);
    return node ;
}
arbore* nod_arbore(int h)
{
    arbore *node = (arbore*)malloc(sizeof(arbore));
    if( node == NULL)
    {
        printf("Alocarea a esuat");
        exit(1);
    }
    node->act = NULL;
    node->h = h;
    node->left = node->right=NULL;
    return node ;
}
void adauga_in_arbore( arbore *nod ,const char *denumire )
{
    actiune* new_node = nou_nod(denumire);
    new_node->next = nod->act;
    nod->act = new_node;
}
void eliberare_actiuni (actiune *aux[] , int nr_act )
{
    for(int i = 0 ; i < nr_act ; i++)
    {
        if(aux[i] != NULL)
        {
            if(aux[i]->pret != NULL)
            {
                free (aux[i]->pret);
            }
            free (aux[i]);
        }
    }
}
void eliberare_arbore (arbore *root)
{
    if(root == NULL) return;
    eliberare_arbore(root->left);
    eliberare_arbore(root->right);
    actiune *actiune_curenta = root->act;
    while (actiune_curenta != NULL)
    {
        actiune *temp= actiune_curenta;
        actiune_curenta=actiune_curenta->next;
        if(temp->pret != NULL)
        {
            free(temp->pret);
        }
        free(temp);
    }
    free(root);
}
void eliberare_drumuri (char *drum[] , int nr_act )
{
    for(int i = 0 ; i < nr_act ; i++)
    {
        if(drum[i] != NULL)
        {
            free (drum[i]);
        }
    }
}
void nr_zile(int argc,const char *argv[] , int* nr_randuri)//nr zile == nr randuri
{
     FILE *fi = fopen(argv[1], "rt");
     if (fi == NULL) exit(1);
     *nr_randuri = 0;
     char enter;
     int ultim_enter=0;
     while((enter=fgetc(fi)) != EOF)
     {
        if( enter == '\n')
        {
            (*nr_randuri)++;
            ultim_enter=1;
        }
        else
        {
            ultim_enter=0;
        }
     }
     if(ultim_enter == 0)
     {
        (*nr_randuri)++;
     }
     fclose(fi);
}
void citire_actiuni(int argc , char *argv[] , actiune** aux)
{
    FILE *fi = fopen(argv[1], "rt");
    if (fi == NULL) exit(1);
    char nume[2000];
    fscanf(fi, " %1999[^\n]" , nume);
    const char *denumire;
    denumire = strtok(nume," ,\r\n");
    int nr_act = 0;
    //cand citim prima linie o vedem ca pe un sir lung de carcatere ce trb despartit in cuv
    while (denumire != NULL && nr_act < 10)
    {
        aux[nr_act++] = nou_nod(denumire);//umplem prima linie,teoretic nu mi trb nr_act sa l numar,pt ca stiu ca i 10,l am pus sa verific daca vede bn cuv
        denumire = strtok(NULL," ,\r\n");
    }
    int nr_tzile;//nr total de zile
    nr_zile(argc,argv,&nr_tzile);
    nr_tzile = nr_tzile-1;
    float val;
    //fisierul nostru putem sa l asemnam cu o matrice  cu 10 coloane,caci sunt 10 companii si cu nr_zile linii
     for(int zi = 1 ; zi <= nr_tzile ;zi++)//zi=0,prima line,deja citita
     {
            {
                for(int j = 0 ; j < 10 ; j++)
                
                {
                   if(fscanf(fi,"%f,",&val) == 1) aux[j]->pret[zi] = val;
                }
            }
     }

     fclose(fi);
}
void populare_arbore( actiune **aux , arbore **tree , int argc , char *argv[] , char* drum[])
{
    citire_actiuni(argc,argv,aux);
    arbore* root = nod_arbore(1);
    *tree=root;
    int nr_tzile;
    int nr_act=10;
    nr_zile(argc,argv,&nr_tzile);
    nr_tzile = nr_tzile-1;
    //construim un vector de drumuri pt fiecare companie
    for(int j = 0 ; j<nr_act ; j++)
    {
        drum[j] = (char*)malloc((nr_tzile+1)*sizeof(char));
        drum[j][0] = '\0';
        arbore *curent = root;
        adauga_in_arbore(curent,aux[j]->nume);//ziua 1,compania e mom in root
        for(int zi = 2; zi <= nr_tzile ; zi++)
         {
             if (aux[j]->pret[zi] < aux[j]->pret[zi-1]) 
             {
                  if (curent->left == NULL)
                   {
                     curent->left = nod_arbore(zi);//ziua reprez cat de adanc e nodul
                     //daca o ia la stanga vectorului de drum i se adauga val aceasta
                    }
                strcat(drum[j],"0");
                 curent = curent->left;//trecem la stanga
            }
        
             else
            {
                 if(curent->right == NULL)
                 {
                    curent->right = nod_arbore(zi);
                    //daca o ia la dreapta vectorului de drum i se adauga val aceasta
                }
                strcat(drum[j],"1");
                 curent = curent->right;//trecem la dreapta
             }
        adauga_in_arbore(curent,aux[j]->nume);//dupa ce "ne am plimbat" cu nodu arbore pana am ajuns la capat,punem compania
        }
  }
}
void afisare_oglindit ( int argc , char *argv[])
{
    FILE *fo = fopen(argv[2], "wt");
    actiune *aux[10];
    char* drum[10];
    arbore *root=NULL;
    populare_arbore(aux , &root , argc , argv , drum);
    int nr_tzile;
    nr_zile(argc,argv,&nr_tzile);
    nr_tzile = nr_tzile-1;
    int nr_act=10;
    int ok;
    int amafisat_primu = 0; //dupa prima afisare il fac 1
    for(int j1 = 0 ; j1 < nr_act-1 ; j1 ++)
    {
        for(int j2 = j1+1 ; j2 < nr_act ; j2 ++)
        {
            ok=1;
            for (int carcacter=0 ;drum[j1][carcacter] != '\0' && drum[j2][carcacter]; carcacter++ )
            {
                if(drum[j1][carcacter] == drum[j2][carcacter])
                {
                    ok = 0;
                    break;
                }
            }
            if (ok == 1) 
            {
                if (amafisat_primu == 0) 
                {
                    fprintf(fo,"%s-%s", aux[j1]->nume , aux[j2]->nume);
                     amafisat_primu = 1;
                }
                else
                {fprintf(fo,"\n%s-%s", aux[j1]->nume , aux[j2]->nume);}
                /*fprintf(fo,"%s-%s\n", aux[j1]->nume , aux[j2]->nume);*/
            }
        }
    }
    eliberare_actiuni (aux, nr_act );
    eliberare_arbore (root);
    eliberare_drumuri (drum , nr_act );
    fclose(fo);
}