#ifndef __KNAPSACK__
#define __KNAPSACK__

#include "population.h"

struct {
    int *objectValues;
    int *objectWeights;
    int maxWeight;
    int numberOfObjects;
    Population *population;
} knapsack;

typedef struct knapsack Knapsack;

Knapsack *NewKnapsackProblem(int *objectValues, int *objectWeights, int maxWeight, int numberOfObjects, Population *pop);

Individual *Solve(Knapsack *instance);

#endif