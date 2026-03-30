#include "task2.h"
//s de la stiva
int isFull( piata*  s )
{
    return (s->top + 1 == s->capacitate);
}
int isEmpty(    piata*  s)
{
    return  ( s->top == -1 );
}
int dimensiune( piata* s )
{
    if(s==NULL);
    return s->top + 1 ;
}
void crestere_capacitatea(  piata* s )
{
    s->capacitate = s->capacitate +1;
    s->vector_pret = ( int* )realloc( s->vector_pret , s->capacitate * sizeof(int));
}
void citire_stive(piata* s,int argc, char *argv[])
{
    FILE *fi = fopen(argv[1], "rt");
    if (fi == NULL) exit(1);
    fscanf(fi, "%s", s->nume_piata);
    int val;
    while (fscanf (fi, "%d" , &val ) == 1)
    {
        if(isFull(s))
        {
            crestere_capacitatea(s);
        }
        s->vector_pret[++s->top]=val;

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
void oportunitatile_din_piata ( piata* s1 , piata* s2 ,piata* s3 ,oportunitati c)
{
   int mini = nr_min_stiva(s1,s2,s3,mini);
   int i;
   for(i=mini-1;i>=0;i--)
   {
     if( s1->vector_pret[i] == s2->vector_pret[i] && s1->vector_pret[i] != s3->vector_pret[i] )
     c->dif_pret=s1->vector_pret[i]-s3->vector_pret[i];
     strcpy(c->nume_piata,
   }
}
