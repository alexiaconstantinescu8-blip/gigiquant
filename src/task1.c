#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 struct elem
{
    double valoare;
    double randament;
    struct elem* next;

};
typedef struct elem node;
node* crearelista(node *caplista,int n)
{
  int i;
  node *e2;
  for(i=1;i<n;i++)
  {
    e2=(node*)malloc(sizeof(node));
    if(e2==NULL)
      {
        printf("Alocare dinamica a esuat");
        exit(1);
      }
    fscanf(fi,"%lf",&e2->valoare);
    e2->randament=(e2->valoare-(caplista->valoare))/(e2->valoare);
    e2->next=NULL;
    caplista->next=e2;
    caplista=e2;
    }
    return caplista;
}
void randament_mediu(double *rand_mediu,node *caplista,int n)
{
    int i;
    double suma=0;
    for(i=0;i<n;i++)
    {
        suma=caplista->randament+suma;
        caplista=caplista->next;
    }
    *rand_mediu=suma/n;
}
void volatilitate(double *volat,double rand_mediu,node *caplista,int n)
{
    int i;
    double suma=0;
    for(i=0;i<n;i++)
    {
        suma=(caplista->randament-rand_mediu)*(caplista->randament-rand_mediu)+suma;
        caplista=caplista->next;
    }
    *volat=sqrt(suma/n);
}
void calculare_sharp_ratio(double *sharp_ratio,double rand_mediu,double volat,double rand_frisc)
{
    *sharp_ratio=(rand_mediu-rand_frisc)/volat;
}
int main(int argc, char *argv[])
{
  FILE *fi = fopen(argv[1], "r");
  FILE *fo = fopen(argv[2], "w"); 
  node *e1,*caplista;
  int n;
  fscanf(fi,"%d",&n);
  e1=(node*)malloc(sizeof(node));
  if(e1==NULL)
  {
    printf("Alocare dinamica a esuat");
    exit(1);
  }
  fscanf(fi,"%lf",&e1->valoare);
  e1->randament=0;
  caplista=e1;
  e1=crearelista(e1,n);
  double rand_mediu,volat,sharp_ratio,rand_frisc;
  rand_frisc=0;
  randament_mediu(&rand_mediu,caplista,n);
  volatilitate(&volat,rand_mediu,caplista,n);
  calculare_sharp_ratio(&sharp_ratio,rand_mediu,volat,rand_frisc);
  fprintf(fo,"%lf\n%lf\n%lf",rand_mediu,volat,sharp_ratio);
  fclose(fi); 
  fclose(fo);
  return 0;
}