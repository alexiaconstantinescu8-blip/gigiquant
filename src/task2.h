#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<limits.h>
struct vector_stiva
{
    int top;
    int capacitate;
    int *pret;
    char nume_piata[30];//oras
};
typedef struct vector_stiva piata;
struct lista_coada
{
    int zi;
    int dif_piata;
    char nume_piata[30];
    struct lista_coada* next;
};
typedef struct lista_coada nod;
struct Q
{
    nod *fata,*spate;
};
typedef struct Q oportunitati;
piata* creaza_stiva (int n);
void stergere_stiva ( piata** s);
int isFull( piata*  s );
int isEmpty_stiva ( piata*  s);
void crestere_capacitatea(  piata* s );
void push ( piata *s, int x);
void citire_stive(piata* s, int argc, char *argv[]);
int nr_min_stiva ( piata* s1 , piata* s2 , piata* s3 , int mini );
oportunitati* creaaza_coada();
void adaugare_elemente ( oportunitati* q, int dif_piata, int ziua , char nume_p[] );
int isEmpty_coada ( oportunitati *q);
void stergere_coada ( oportunitati *q);
void oportunitatile_din_piata ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c , int *nr_coada);
void afisare_coada ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c , int argc, char *argv[] );






