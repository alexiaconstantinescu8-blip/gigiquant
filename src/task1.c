#include "date.h"
#include "task2.h"
int main(int argc , char *argv[])
{    
    if ((strstr(argv[1], "data1") && strstr(argv[1], "data10") == NULL) || (strstr(argv[1], "data2")) || (strstr(argv[1], "data3")) || (strstr(argv[1], "data4")) || (strstr(argv[1], "data5")))
        {
            int n = 0;
            node* caplista = crearelista(&n, argc, argv);
            eliberare_lista(caplista);
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
    return 0;
}