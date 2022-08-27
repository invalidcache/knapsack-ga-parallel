#include <stdio.h>
#include "individual.h"

int main(int argc, char const *argv[])
{
    Individual *ind = NewIndividual(4);
    String(ind);
    return 0;
}
