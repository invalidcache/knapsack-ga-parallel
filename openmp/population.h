#ifndef __POPULATION__
#define __POPULATION__

#include "individual.h"

struct population {
    Individual **individuals;
    int numberOfIndividuals;
    int numberOfGenes; // Number of genes that each individual have
};

typedef struct population Population;

Population *NewPopulation(int populationSize, int geneSize, int* objectValues);

void DeletePopulation(Population *pop);

Population *Selection(Population *pop, int num_participants, int* objectValues);

float GetBestFitness(Population *pop);

float GetAvgFitness(Population *pop);

void copyIndividual(Individual *destination, Individual *source);

Individual *GetBestIndividual(Population *pop);

void PopulationString(Population *pop);


#endif