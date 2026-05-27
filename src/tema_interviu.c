#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
double* get_open_prices(const char* companie, const char* interval, const char* pana_unde, int *nr);
int main(int argc , char *argv[])
{    
    if ( (strstr(argv[1], "data1") && strstr(argv[1], "data10") == NULL && strstr(argv[1], "data11") == NULL && strstr(argv[1], "data12") == NULL && strstr(argv[1], "data13") == NULL && strstr(argv[1], "data14") == NULL && strstr(argv[1], "data15") == NULL)|| (strstr(argv[1], "data2")) || (strstr(argv[1], "data3")) || (strstr(argv[1], "data4")) || (strstr(argv[1], "data5")))
        {
            afisare_randament_volatilitate_sharp_ratio(argc,argv);
        }
    //task 2
    if ((strstr(argv[1], "data6")) || (strstr(argv[1], "data7")) || (strstr(argv[1], "data8")) || (strstr(argv[1], "data9")) || (strstr(argv[1], "data10")))
    {
        piata* s1 =creaza_stiva(1);
        piata* s2 =creaza_stiva(1);
         piata* s3 =creaza_stiva(1);
        citire_stive(s1 , s2 , s3 , argc , argv);
        oportunitati* c=creaaza_coada(c);
        oportunitatile_din_piata(s1,s2,s3,c);
        afisare_coada(s1,s2,s3,c,argc, argv);
    }
    //task3
    if (strstr(argv[1], "11") || strstr(argv[1], "12") || strstr(argv[1], "13") || strstr(argv[1], "14") || strstr(argv[1], "15"))
    {
       afisare_oglindit(argc ,argv);
    }
    //task4
     if (strstr(argv[1], "16") || strstr(argv[1], "17") || strstr(argv[1], "18") || strstr(argv[1], "19") || strstr(argv[1], "20"))
    {
       probabilitati(argc ,argv);
    }
    //bonus
    // argc > 1 se asigura ca utilizatorul a scris ceva după numele programului
    if (argc > 1 && strstr(argv[1], "bonus")) 
{
   int nr_de_zile = 0;
   double * preturi = get_open_prices("GOOGL", "1d", "1mo", &nr_de_zile);
   if(preturi != NULL && nr_de_zile > 0)
   {
        double maxim = preturi[0];
        double minim = preturi[0];
        for (int i = 1 ; i < nr_de_zile ;i++)
        {
            if (preturi[i] > maxim) 
            {
                maxim = preturi[i];
            }
            if (preturi[i] < minim) 
            {
                minim = preturi[i];
            }
        }
        printf("Pretul maxim GOOGL: %f\n", maxim);
        printf("Pretul minim GOOGL: %f\n", minim);
        free(preturi);
   }
}
    return 0;

}