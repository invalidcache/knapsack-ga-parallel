#ifndef __POPULATION__
#define __POPULATION__

#include "individual.h"

struct population {
    Individual *individuals;
    int numberOfIndividuals;
};

typedef struct population Population;

Population *NewPopulation(int populationSize);

Population *Selection(Population *pop);

void PopulationString(Population *pop);


#endif