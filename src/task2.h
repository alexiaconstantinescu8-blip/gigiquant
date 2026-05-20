#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<limits.h>
struct vector_stiva
{
    int top;
    int capacitate;
    float *pret;
    char nume_piata[30];//oras
};
typedef struct vector_stiva piata;
struct lista_coada
{
    int zi;
    float dif_piata;
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
int isFull( const piata*  s );
int isEmpty_stiva ( piata*  s);
void crestere_capacitatea( piata* s );
void push ( piata *s, float x);
void citire_stive(piata* s1 , piata* s2,piata* s3,int argc,const char *argv[]);
int nr_min_stiva ( const piata* s1 , const piata* s2 , const piata* s3 );
oportunitati* creaaza_coada();
void adaugare_elemente ( oportunitati* q, float dif_piata, int ziua , const char nume_p[] );
int isEmpty_coada ( const oportunitati *q);
void stergere_coada ( oportunitati *q);
void oportunitatile_din_piata ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c);
void afisare_coada ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c , int argc,const char *argv[] );






