#ifndef __POPULATION__
#define __POPULATION__

#include "individual.h"

struct population {
    Individual **individuals;
    int numberOfIndividuals;
};

typedef struct population Population;

Population *NewPopulation(int populationSize, int geneSize);

Population *Selection(Population *pop, int k);

void PopulationString(Population *pop);


#endif