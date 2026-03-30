#include "date.h"

int main(int argc,char *argv[])
{   
    
    int n = 0;
    node* caplista = crearelista(&n, argc, argv);
    eliberare_lista(caplista);
    return 0;
}