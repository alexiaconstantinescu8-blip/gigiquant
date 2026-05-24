#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
struct elem_graf
{
    int destinatie;
    int numarator;
    int numitor;
    struct elem_graf* next;
} ;
typedef struct elem_graf nod_graf;
typedef struct 
{
int V; // nr. varfuri
int E; // nr. muchii
nod_graf** matrice;
} Graph ;
/*
typedef struct 
{
int V; // nr. varfuri
int E; // nr. muchii
int** numitori;
int** numaratori;
} Graph ;*/
void citire_date (int argc ,const char *argv[],int *N,float *d,int *zile,float *p_start,float *p_target,float preturi[]);
Graph * creare_graf (int v);
void eliberare_graf(Graph *g);
void aflare_max(float *maxim ,const float preturi[],int N);
void aflare_minim(float *minim ,const float preturi[],int N);
Graph* populare_graf(int N,float preturi[],Graph *g,float d,int argc , char *argv[]);
long long cmmdc(long long a, long long b);
void probabilitati(int argc , char *argv[]);
