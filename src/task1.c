#include "task1.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//curs pclp
//trebuie facut separata o functie de creare a nodurilor
node* crearelista_populare(int *n, int argc,const char *argv[])
{   
     FILE *fi = fopen(argv[1], "rt");
    fscanf(fi, "%d", n);
    node* e1 = (node*)malloc(sizeof(node));
    if (e1 == NULL)//in cazul in c,are alocarea dinamica a esuat , mai bn sa fiu anuntata si sa mi iasa din program ,decat sa ruleze degeaba
    {
        printf("Alocare dinamica a esuat");
        exit(1);
    }
    fscanf(fi, "%lf", &e1->valoare);
    e1->randament = 0;//primu randament am zis ca-l pun 0 pentru ca nu am un termen anterior cu care sa-l calculez
    e1->next = NULL;
    node *caplista = e1;
    int i;
    for (i = 1; i < *n; i++)
    {
        node* e2 = (node*)malloc(sizeof(node));//e2 e elementul curent cu care lucram
        if (e2 == NULL) 
        {
           printf("Alocare dinamica a esuat");
           exit(1);
        }
        fscanf(fi, "%lf", &e2->valoare);
        e2->randament = (e2->valoare - e1->valoare) / e1->valoare;
        e2->next = NULL; 
        e1->next = e2;
        e1 = e2;
    }
    fclose(fi);
    return caplista;
}
void randament_mediu(double *rand_mediu, node *caplista, int n)
{
    int i;
    double suma = 0;
    caplista = caplista->next;//primu randament e 0
    for (i = 1; i < n ; i++)
    {
        suma = caplista->randament + suma;//fac suma elementelor
        caplista = caplista->next;
    }
    *rand_mediu = (suma / (n - 1)) ;//nu-l iau pe primu la  calcul ,daia e n-1
}

void volatilitate(double *volat, double rand_mediu, node *caplista, int n)
{
    int i;
    double suma = 0;
    caplista = caplista->next;//primu randament e 0,deci mergem la urm arg
    for (i = 1; i < n ; i++)
    {
        suma += (caplista->randament - rand_mediu) * (caplista->randament - rand_mediu);//fac suma patratelor
        caplista = caplista->next;//trec la urm element
    }
    if (n > 1)
    {
        *volat = sqrt(suma / (n - 1));
    }
    else
    {
        *volat = 0;//daca n e mai mic ca 1 da ori numar complex ori cazu 1/0
    }
}

void calculare_sharp_ratio(double *sharp_ratio, double rand_mediu, double volat, double rand_frisc)
{
    //
    if (volat != 0)
    {
        *sharp_ratio = (rand_mediu - rand_frisc) / volat;//chiar daca randamentu fara risc e 0 in problema,si in teorie absenta lui nu afecteaza cu nmc in acest caz,am zis sa respect formula,desi variabila o sa ocupa o parte din memorie,nu o sa ocupe foarte mult,si aceia va fi eliberata cand se termina programu
    }
    else
    {
        *sharp_ratio = 0;//daca volat e 0 da cazu 1/0 care tinde spre infint
    }
}
void eliberare_lista(node *caplista) //eliberam lista pt a scapa de pc cu memory leak
{   
    node *aux;
    while(caplista != NULL)
    {
        aux = caplista->next;      
        free(caplista);//eliberam elementele ,unul cate unul pana ce ajungem la capat
        caplista = aux;
    }
}
void afisare_randament_volatilitate_sharp_ratio(int argc,char *argv[])
{
    FILE *fo = fopen(argv[2], "wt");
    int n;
    node*caplista=crearelista_populare(&n,argc,argv);
    double rand_mediu = 0.0, volat = 0.0, sharp_ratio = 0.0, rand_frisc = 0.0;
    //volat e volatilitatea,dar suna cam gresit sa va spun sincer 
    //rand_frist e randamentul fara risc
    randament_mediu(&rand_mediu, caplista, n);
    volatilitate(&volat, rand_mediu, caplista, n);
    calculare_sharp_ratio(&sharp_ratio, rand_mediu, volat, rand_frisc);
    //trunchierea
    rand_mediu = ((double)((int)(rand_mediu * 1000))) / 1000;//
    volat = ((double)((int)(volat * 1000))) / 1000;
    sharp_ratio = ((double)((int)(sharp_ratio * 1000))) / 1000;
    //explicatie: eu vreau doar primele 3 zecimale,dar nu le vreau aproximate/rotunjite,deci mai intai inmultesc cu 1000 ca sa am cele 3 zecimale si dupa il fac de tip int ca sa dispara restu,il fac inapoi double ca sa apar numaru ca un numar cu zecimale si impart la 1000 ca cele 3 zecimale sa se duca inapoi dupa virgula
    fprintf(fo, "%.3lf\n%.3lf\n%.3lf\n", rand_mediu, volat, sharp_ratio);
    fclose(fo);
    eliberare_lista(caplista);
}
