#include "task2.h"

// s de la stiva
piata* creaza_stiva(int n)
{
    piata *s = (piata*) malloc(sizeof(piata));
    if (!s) return NULL;
    
    s->capacitate = n;
    s->top = -1;
    s->pret = (float*) malloc(sizeof(float) * s->capacitate);
    
    if (!s->pret) 
    {   
        free(s);
        return NULL;
    }
    
    return s;
}

void stergere_stiva(piata** s)
{
    if (*s) 
    {
        if ((*s)->pret) free((*s)->pret);
        free(*s);
        (*s) = NULL;
    }
}

int isFull( const piata* s)
{
    return (s->top + 1 == s->capacitate);
}

/*
int isEmpty_stiva(piata* s)
{
    return (s->top == -1);
}
*/

/*
int dimensiune(piata* s)
{
    if(s == NULL) return 0;
    return s->top + 1;
}
*/

void crestere_capacitatea(piata* s)
{
    s->capacitate = s->capacitate + 1;
    s->pret = (float*) realloc(s->pret, s->capacitate * sizeof(float));
}

void push(piata *s, float x)
{
    if (isFull(s)) crestere_capacitatea(s);
    s->pret[++s->top] = x;
}

void citire_stive(piata* s1 , piata* s2,piata* s3,int argc, char *argv[])
{
    if ((strstr(argv[1], "data6")) || (strstr(argv[1], "data7")) || (strstr(argv[1], "data8")) || (strstr(argv[1], "data9")) || (strstr(argv[1], "data10")))
    {
        FILE *fi = fopen(argv[1], "rt");
        if (fi == NULL) exit(1);
        int n;
        fscanf(fi, " %29[^\n]", s1->nume_piata);
        float val;
        while (fscanf(fi, "%f", &val) == 1)
        {
         push(s1, val);
        }
         fscanf(fi, " %29[^\n]", s2->nume_piata);
        while (fscanf(fi, "%f", &val) == 1)
         {
        push(s2, val);
         }
        fscanf(fi, " %29[^\n]", s3->nume_piata);
         while (fscanf(fi, "%f", &val) == 1)
         {
          push(s3, val);
         }
    fclose(fi);
    }
}

int nr_min_stiva(const piata* s1, const piata* s2, const piata* s3)
{
    int mini = s1->top;
    
    if (mini > s2->top)
    { 
        mini = s2->top;
    }  
    
    if (mini > s3->top)
    {
        mini = s3->top;     
    }
    
    return mini + 1;
}

oportunitati* creaaza_coada()
{
    oportunitati *c;
    c = (oportunitati*) malloc(sizeof(oportunitati));
    
    if (c == NULL) return NULL;
    
    c->fata = c->spate = NULL;
    return c;
}

void adaugare_elemente(oportunitati* q, float dif_piata, int ziua, const char nume_p[])
{
    nod *newNode = (nod*) malloc(sizeof(nod));
    newNode->dif_piata = dif_piata;
    newNode->zi = ziua;
    strcpy(newNode->nume_piata, nume_p);
    newNode->next = NULL;
    
    if (q->spate == NULL) 
    {
        q->spate = newNode;
    }
    else 
    {
        (q->spate)->next = newNode;
        (q->spate) = newNode;
    }
    
    if (q->fata == NULL) q->fata = q->spate;
}

int isEmpty_coada( const oportunitati *q)
{
    return (q->fata == NULL); 
}

void stergere_coada(oportunitati *q)
{   
    while (!isEmpty_coada(q))
    { 
        nod* aux;
        aux = q->fata;
        q->fata = q->fata->next;
        free(aux);
    }
    free(q);
}

void oportunitatile_din_piata(piata* s1, piata* s2, piata* s3, oportunitati* c)
{
    int mini = nr_min_stiva(s1, s2, s3);
    int k;
    float dif_piata;
    
    for (k = 0; k < mini; k++)
    {
        int i1 = s1->top - k;
        int i2 = s2->top - k;
        int i3 = s3->top - k;

        if (s1->pret[i1] == s2->pret[i2] && s1->pret[i1] != s3->pret[i3])
        {
            dif_piata = s3->pret[i3] - s1->pret[i1];
            if (dif_piata < 0) dif_piata = -dif_piata;
            adaugare_elemente(c, dif_piata, k + 1, s3->nume_piata);
        }
        if (s1->pret[i1] == s3->pret[i3] && s1->pret[i1] != s2->pret[i2])
        {
            dif_piata = s2->pret[i2] - s1->pret[i1];
            if (dif_piata < 0) dif_piata = -dif_piata;
            adaugare_elemente(c, dif_piata, k + 1, s2->nume_piata);
        }
        if (s3->pret[i3] == s2->pret[i2] && s3->pret[i3] != s1->pret[i1])
        {
            dif_piata = s1->pret[i1] - s3->pret[i3];
            if (dif_piata < 0) dif_piata = -dif_piata;
            adaugare_elemente(c, dif_piata, k + 1, s1->nume_piata);
        }
    }
}

void afisare_coada(piata* s1, piata* s2, piata* s3, oportunitati* c, int argc, char *argv[])
{
    FILE *fo = fopen(argv[2], "wt");
    if (fo == NULL) exit(1);
    
    if (c->fata == NULL)
    {
        printf("coada e goala");
    }
    
    nod* elem_coada = c->fata;
    while (elem_coada != NULL)
    {
        fprintf(fo, "ziua %d - %.2f - %s\n", elem_coada->zi, elem_coada->dif_piata, elem_coada->nume_piata);
        elem_coada = elem_coada->next;
    }
    
    stergere_coada(c);
    stergere_stiva(&s1);
    stergere_stiva(&s2);
    stergere_stiva(&s3);
    
    fclose(fo);
}