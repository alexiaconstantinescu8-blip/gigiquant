#include <stdlib.h>
#include <stdio.h>
#include<string.h>
struct vector_stiva
{
    int top;
    int capacitate;
    int *vector;
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




