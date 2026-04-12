#pragma once

#include <stdio.h>

struct elem
{
    double valoare;
    double randament;
    struct elem* next;

};
typedef struct elem node;
node* crearelista(int *n, int argc, char *argv[]);
void volatilitate(double *volat, double rand_mediu, node *caplista, int n);
void calculare_sharp_ratio(double *sharp_ratio, double rand_mediu, double volat, double rand_frisc);
void randament_mediu(double *rand_mediu, node *caplista, int n);
void eliberare_lista(node *caplista);
