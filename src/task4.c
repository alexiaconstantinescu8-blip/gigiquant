#include "task4.h"
#include <stdlib.h>
#include <stdio.h>
void citire_date(int argc,const char *argv[], int *N, float *d, int *zile, float *p_start, float *p_target,float preturi[])
{
    FILE *fi = fopen(argv[1], "rt");
    if (fi == NULL) exit(1);
    fscanf(fi, "%d", N);
    fscanf(fi, "%f", d);
    fscanf(fi, "%d", zile);
    fscanf(fi, "%f", p_start);
    fscanf(fi, "%f", p_target);
    for(int i = 0; i <= (*N); i++)
    {
        fscanf(fi, "%f", &preturi[i]);
    }
    fclose(fi);
}
//am luat un numarator si un numitor separat ,pt a scrie sub forma de fractie
Graph * creare_graf(int v)
{
    Graph *g = (Graph *) malloc(sizeof(Graph)); 
    g->V = v;
    g->matrice=(nod_graf**)malloc(g->V *sizeof(nod_graf*));
    for (int i = 0; i < g->V; i++)
        g->matrice[i] = NULL;
    //Facusem initial cu matrici
    /*
    g->numaratori = (int **) malloc(g->V * sizeof(int *));
    g->numitori = (int **) malloc(g->V * sizeof(int *));
    for (int i = 0; i < g->V; i++)
        g->numaratori[i] = (int *) calloc(g->V, sizeof(int));
    for (int i = 0; i < g->V; i++)
        g->numitori[i] = (int *) calloc(g->V, sizeof(int));
   */
    g->E = 0;
    return g;
}
void eliberare_graf(Graph *g) {
    if (g == NULL) return;
    for (int i = 0; i < g->V; i++) 
    {
        nod_graf* aux = g->matrice[i];
        while(aux != NULL)
        {
            nod_graf* temp =aux;
            aux=aux->next;
            free(temp);
        }
        /*free(g->numaratori[i]);
        free(g->numitori[i]);*/
    }
    free(g->matrice);
    /*
    free(g->numaratori);
    free(g->numitori);*/
    free(g);
}
void aflare_max(float *maxim,const float preturi[], int N)//aflam maximul pt afla nr de noduri
{
    *maxim = preturi[0];
    for(int i = 1; i < N; i++)
    {
        if(*maxim < preturi[i]) *maxim = preturi[i];
    }
}
void aflare_minim(float *minim,const float preturi[], int N)//aflam minimul pt afla nr de noduri si pozitiilor din graf numerelor din interval
{
    *minim = preturi[0];
    for(int i = 1; i < N; i++)
    {
        if(*minim > preturi[i]) *minim = preturi[i];
    }
}
Graph* populare_graf(int N,float preturi[], Graph *g, float d, int argc, char *argv[])
{
    int zile;
    float p_target, p_start;
    citire_date(argc, argv, &N, &d, &zile, &p_start, &p_target, preturi);
    float minim, maxim;
    aflare_max(&maxim, preturi, N);
    aflare_minim(&minim, preturi, N);
    //p start si target nu se afla in vector,dar le folosim pt probabilitati,respectiv in graf daca din sunt intervale neexistente in preturi
    if (p_target > maxim) maxim = p_target;
    if (p_start > maxim) maxim = p_start;
    //folosim int pt o aproximare a pozitie mai buna,sa nu fie pb cu zecimalele
    int pret_minim = (int)minim;
    while (p_start < pret_minim) pret_minim=(int)p_start;
    while (p_target < pret_minim) pret_minim=(int)p_target;
    int v = (int)((maxim - pret_minim) / d) + 1;
    g = creare_graf(v);
    //Punerea muchiilor si numararea tranzitiilor
    for(int i = 0 ; i < N-1 ; i++)
    {
        //Tranformarea preturilor in noduri
        int poz1 = (int)((preturi[i] - pret_minim) / d); //nod plecare
        int poz2 = (int)((preturi[i+1] - pret_minim) / d); //nod destinatie
        nod_graf *aux = g->matrice[poz1];
        int gasit = 0;
        //Parcurgem vecinii nodului de plecare pentru a vedea daca am mai mers pe aici
        while(aux != NULL)
        {
            if(aux->destinatie == poz2)
            {
                //tranzitia a avut loc in trecut ,crestem frecventa(numaratorul)
                aux->numarator++;
                gasit=1;
                break;
            }
            aux=aux->next;
        }
        //daca nu exista muchia setam noi datele initiale
        if( gasit == 0)
        {
            nod_graf* nod_nou=(nod_graf*)malloc(sizeof(nod_graf));
            nod_nou->destinatie = poz2;
            nod_nou->numarator = 1; //prima data cand observam aceasta tranzitie
            nod_nou->numitor = 1; 
            nod_nou->next = g->matrice[poz1];
            g->matrice[poz1] = nod_nou;
        }
    }
    //aflare numarului total de plecari dintr un nod (numitori ,cazuri posibile ,i-> orice nod)
    for(int i = 0 ; i < g->V  ; i++)
    {
        int nr_muchii = 0;
        nod_graf *aux = g->matrice[i];
        //Calculam suma tuturor tranzitiilor care pleaca din nodul 'i'
        while(aux != NULL)
        {
            nr_muchii += aux->numarator; 
            aux=aux->next;
        }
        //Actualizam numitorul pentru fiecare muchie care pleaca din 'i'
        aux = g->matrice[i];
        while(aux != NULL)
        {
             if(nr_muchii == 0)
            {
                // Setam numitorul comun pentru toate rutele care pleaca din acest nod
               aux->numitor= 1;
            }
           else aux->numitor = nr_muchii;//numitor=numara cazuri posibile=toate muchiile
            aux=aux->next;
        }

    }
    //varianta cu matrice
    /*
    for(int i = 0; i < N-1; i++)
    {
        int poz1 = (int)((preturi[i] - pret_minim) / d);
        int poz2 = (int)((preturi[i+1] - pret_minim) / d);
        g->numaratori[poz1][poz2]++;//numaram muchiile intre 2 valori
    }
    for(int i = 0; i < g->V; i++)
    {
        int nr_muchii = 0;
        for(int j = 0; j < g->V; j++) 
        {
            nr_muchii += g->numaratori[i][j];//aflam gradul lui i,adc cate muchii sunt"conectate" la el
        }
        for(int j = 0; j < g->V; j++)
        {
            if(nr_muchii == 0)
            {
               g->numitori[i][j] = 1; 
            }
           else g->numitori[i][j] = nr_muchii;//cazuri favorabile
        }
    }*/
    return g;
}
long long cmmdc(long long a, long long b) {
  if(a<0) a=a*(-1);
  if(b<0) b=b*(-1);
  if(a==0)return a;
  if(b==0)return b;
  while(a!=b)
  {
    if(a>b) a=a-b;
    else b=b-a;
  }
  return a;
}
void probabilitati(int argc, char *argv[])
{
    FILE *fo = fopen(argv[2], "wt");
    int N, zile;
    float d, p_target, p_start;
    float *preturi = (float*)malloc(10 * sizeof(float));
    Graph *g = NULL;
    citire_date(argc, argv, &N, &d, &zile, &p_start, &p_target, preturi);
    g = populare_graf(N, preturi, g, d, argc, argv);
    long long* numitor_curent = (long long*)calloc(g->V, sizeof(long long));
    long long* numarator_curent = (long long*)calloc(g->V, sizeof(long long));
    long long* numitor_urmator = (long long*)calloc(g->V, sizeof(long long));
    long long* numarator_urmator = (long long*)calloc(g->V, sizeof(long long));
    float minim;
    aflare_minim(&minim, preturi, N);
    //folosim int pt o aproximare a pozitie mai buna,sa nu fie pb cu zecimalele
    int pret_minim = (int)minim;
    while (p_start < pret_minim) pret_minim=(int)p_start;
    while (p_target < pret_minim) pret_minim=(int)p_target;
     // inintializam numaratori si numitorii
    for(int i = 0; i < g->V; i++) {
        numarator_curent[i] = 0;
        numitor_curent[i] = 1;
    }
    int pozitie_start = (int)((p_start - pret_minim) / d);
    //ZIUA 0,pornim din p_start ,unde probabilitatile suntr de 1
    if(pozitie_start >= 0 && pozitie_start < g->V) {
        numarator_curent[pozitie_start] = 1;
        numitor_curent[pozitie_start] = 1;
    }
    int pozitie_target = (int)((p_target - pret_minim) / d);
    for(int zi_curent = 0; zi_curent < zile; zi_curent++)
    {
        //facem afisarea inainte pt a afisa ziua 0
        if(pozitie_target >= 0 && pozitie_target < g->V) 
        {
            if (numarator_curent[pozitie_target] == 0) //daca numarator e 0 sa afiseze direct 0 fara "/""
            {
                fprintf(fo, "0");
            }
            else if(numitor_curent[pozitie_target] == 1 )//daca numitoru e 1 sa afiseze direct 0 fara "/""
            {   
                fprintf(fo, "%lld", numarator_curent[pozitie_target]);
            }
            else //daca nu sunt pb de mai sus sa se afiseze asa cum e
            {
                fprintf(fo, "%lld/%lld", numarator_curent[pozitie_target], numitor_curent[pozitie_target]);
            }
        } 
        else //daca pozitia e negeativa,sau e mai mare ca nr de noduri(adc nu se afla in graf),proabilitatea e 0 sa ajungi la ea
        {
            fprintf(fo, "0");
        }
        //daca nu e ultima zi sa puna enteru,ca sa nu mai punem un enter in plus
        if (zi_curent < zile - 1) {
            fprintf(fo, "\n");
        }
        //incepem sa calculam pt ziua urmatoare probabilitatea
        for(int i = 0; i < g->V; i++) {
            numarator_urmator[i] = 0;
            numitor_urmator[i] = 1;//numitoru nu are voie sa fie 0
        }
        for(int i = 0; i < g->V; i++)
        {
            if (numarator_curent[i] != 0) //daca numitoru e 0 nu mai merge
            {
                nod_graf* vecin = g->matrice[i];
                while( vecin != NULL)
                {
                    int j = vecin->destinatie;
                        //regula de baza : probabilitatea nodului=probabilitatea veche*probabilitatea din graf a lui(cea initiala)//asta cand intra in el+suma din (probabilitatea initiala(din graf)de la vecin la nodul acesta*probabilitatea vecinului din ziua trecuta)
                        //P_{nou}(j) = suma(P_{curent}(i)*P_{tranzitie}(i->j))
                        //luam vecini care "intra in el"(adc exista muchie de la vecin la nodul caruia ii fac probabilitatea)
                        //i e vecinu,j e nodul pentru care calculam
                        //luam long lonmg pt ca pot da numere mari
                        long long suma_numarator = numarator_urmator[j] * (numitor_curent[i] * vecin->numitor) + (numarator_curent[i] * vecin->numarator)* numitor_urmator[j];//suma numaratorilor,am adus direct la acelas numitor
                        //P azi (i)  = numarator_curent[i] / numitor_curent[i];
                        //P (i->j) = vecin->numarator / vecin->numitor //ce e in graf adc
                        // P vechi (j) = numarator_urmator[j]/numitor_urmator[j] (asta ca sa facem suma din toti vecinii) //suma stransa pana acu
                        // P nou (j) = P vechi(j)+P azi i * P (i->j)
                        long long numitor_probab = numitor_urmator[j] * (numitor_curent[i] * vecin->numitor) ;//aducem la acelas numitor
                        long long simplificare = cmmdc(suma_numarator, numitor_probab);//pt aduce la o forma ireductibila
                        numarator_urmator[j] = suma_numarator / simplificare;
                        numitor_urmator[j] = numitor_probab / simplificare;
                    vecin=vecin->next;
                }
                /*
                for(int j = 0; j < g->V; j++)
                {
                    if(g->numaratori[i][j] != 0) //daca numitoru e 0 nu mai merge
                    {
                        //regula de baza : probabilitatea nodului=probabilitatea veche*probabilitatea din graf a lui(cea initiala)//asta cand intra in el+suma din (probabilitatea initiala(din graf)de la vecin la nodul acesta*probabilitatea vecinului din ziua trecuta)
                        //luam vecini care "intra in el"(adc exista muchie de la vecin la nodul caruia ii fac probabilitatea)
                        //i e vecinu,j e nodul pentru care calculam
                        //luam long lonmg pt ca pot da numere mari
                        long long suma_numarator = numarator_urmator[j] * (numitor_curent[i] * g->numitori[i][j]) + (numarator_curent[i] * g->numaratori[i][j])* numitor_urmator[j];//suma numaratorilor,am adus direct la acelas numitor
                        long long numitor_probab = numitor_urmator[j] * (numitor_curent[i] * g->numitori[i][j]);//aducem la acelas numitor
                        long long simplificare = cmmdc(suma_numarator, numitor_probab);//pt aduce la o forma ireductibila
                        numarator_urmator[j] = suma_numarator / simplificare;
                        numitor_urmator[j] = numitor_probab / simplificare;
                    }
                }
                    */
            }
        }
        //trecem la urmatoarea zi
        for(int i = 0; i < g->V; i++) 
        {
            numarator_curent[i] = numarator_urmator[i];
            numitor_curent[i] = numitor_urmator[i];
        }
    }
    fclose(fo);
    free(numitor_curent);
    free(numarator_curent);
    free(numitor_urmator);
    free(numarator_urmator);
    free(preturi);
    eliberare_graf(g);
}
//Metoda 2:matruce de adiacenta
//
