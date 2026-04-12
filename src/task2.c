#include "task2.h"
//s de la stiva
piata* creaza_stiva (int n)
{
    piata *s=( piata *) malloc ( sizeof ( piata ));
    if (!s) return NULL ;
    s->capacitate =n;
    s->top = -1;
    s->pret = ( int *) malloc ( sizeof ( int ) * s->capacitate );
    if (!s->pret ) return NULL ;
    return s;
}
void stergere_stiva ( piata** s)
{
    if (*s) {
        if ((* s) ->pret ) free ((*s)->pret );
        free (*s);
        (*s)= NULL ;
}
}
int isFull( piata*  s )
{
    return (s->top + 1 == s->capacitate);
}
int isEmpty(    piata*  s)
{
    return  ( s->top == -1 );
}
/*
int dimensiune( piata* s )
{
    if(s==NULL);
    return s->top + 1 ;
}
*/
void crestere_capacitatea(  piata* s )
{
    s->capacitate = s->capacitate +1;
    s->pret = ( int* )realloc( s->pret , s->capacitate * sizeof(int));
}
void push ( piata *s, int x)
{
    if ( isFull (s))  crestere_capacitatea(s);
    s->pret[++s->top ]=x;
}
void citire_stive(piata* s, int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "rt");
    if (fi == NULL) exit(1);
    fscanf(fi, "%s", s->nume_piata);
    int val;
    while (fscanf (fi, "%d" , &val ) == 1)
    {
        push(s,val);
    }

}
int nr_min_stiva ( piata* s1 , piata* s2 , piata* s3 , int mini )
{
    int mini = INT_MAX;
    if(mini < s1->top)
    {
        mini = s1->top;
    }
    else if (mini < s2->top)
          { 
             mini = s2->top;
          }  
        else
          {
               if(mini < s3->top)
              {
                 mini = s3->top;
              }      
          }
    return mini;
}
oportunitati* creaaza_coada()
{
    oportunitati *c;
    c=( oportunitati *) malloc ( sizeof ( oportunitati ));
    if (c == NULL ) return NULL ;
    c->fata = c->spate = NULL ;
    return c;
}
void adaugare_elemente ( oportunitati* q, int dif_piata, int ziua , char nume_p[] )
{
    nod * newNode =( nod *) malloc ( sizeof ( nod ));
    newNode->dif_piata = dif_piata;
    newNode->zi = ziua ;
    strcpy(newNode->nume_piata,nume_p);
    newNode->next = NULL ;
    if (q->spate == NULL ) q->spate = newNode ;
    else {
            (q->spate)->next = newNode ;
            (q->spate) = newNode ;
         }
    if (q->fata == NULL ) q->fata = q->spate ;
}
int isEmpty ( oportunitati *q)
{
    return (q->fata == NULL ); 
}
void stergere_coada ( oportunitati *q)
{   
    nod* aux ;
    while (! isEmpty (q))
        {
             aux =q->fata ;
             q->fata = q->fata->next ;
            free ( aux );
        }
    free (q);
}

void oportunitatile_din_piata ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c )
{
   int mini = nr_min_stiva(s1,s2,s3,mini);
   int i;
   for(i = mini - 1 ; i >= 0 ; i--)
   {
     if( s1->pret[i] == s2->pret[i] && s1->pret[i] != s3->pret[i] )
        {
            int dif_piata =   s1->pret[i] -   s3->pret[i];
            adaugare_elemente(c,dif_piata,i,s3->nume_piata);
        }
     
   }
}
void afisare_coada ( piata* s1 , piata* s2 , piata* s3 , oportunitati* c , int argc, char *argv[] )
{
    
}
