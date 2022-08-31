#ifndef __KNAPSACK__
#define __KNAPSACK__

#include "population.h"

struct knapsack {
    int *objectValues;
    int *objectWeights;
    int maxWeight;
    int numberOfObjects;
    Population *population;
};

typedef struct knapsack Knapsack;

Knapsack *NewKnapsackProblem(int *objectValues, int *objectWeights, int maxWeight, int numberOfObjects, Population *pop);

void DeleteKnapsackProblem(Knapsack *instance);

Individual *Solver(Knapsack *instance, int numberOfGenerations, int tournamentParticipants, float mutationRate);

#endif