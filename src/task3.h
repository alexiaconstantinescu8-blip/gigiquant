#include <stdlib.h>
#include <stdio.h>
#include<string.h>
typedef struct actiune
{
    char nume[4];
    float *pret;
    struct actiune *next;
}actiune;
typedef struct arbore
{
    actiune *act;
    struct arbore *left;
    struct arbore *right;
    int h;
}arbore;
actiune* nou_nod(const char* denumire);
arbore* nod_arbore(int h);
void adauga_in_arbore( arbore *nod ,const char *denumire );
void eliberare_actiuni (actiune *aux[] , int nr_act );
void eliberare_arbore (arbore *root);
void eliberare_drumuri (char *drum[] , int nr_act );
void nr_zile(int argc,const char *argv[] , int* nr_randuri);
void citire_actiuni(int argc , char *argv[] , actiune** aux);
//void populare_arbore( actiune **aux , arbore **tree , int argc , char *argv[]);
void afisare_oglindit ( int argc , char *argv[]);
void populare_arbore( actiune **aux , arbore **tree , int argc , char *argv[] , char** drum);



