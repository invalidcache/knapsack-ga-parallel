#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "individual.h"
#include "population.h"
#include "global.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));


    int objectValues[GENESIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int objectWeights[GENESIZE] = {12, 13, 3, 11, 41, 2, 51, 1, 10, 1};
    // int maxWeight = 1;
    // float fitness1, fitness2;
    // Individual *ind = NewIndividual(GENESIZE);
    // IndividualString(ind);
    
    // Individual *ind2 = NewIndividual(GENESIZE);
    // IndividualString(ind2);
    
    // fitness1 = CalculateFitness(ind, objectValues);
    // fitness2 = CalculateFitness(ind2, objectValues);

    // printf("Fitness 1: %.2f | Fitness 2: %.2f\n", fitness1, fitness2);

    // Individual *ind3_cross = CrossOver(ind, ind2);
    // IndividualString(ind3_cross);

    // Individual *repairedIndividual = Repair(ind, objectWeights, maxWeight);
    // IndividualString(repairedIndividual);

    Population *pop = NewPopulation(4, GENESIZE, objectValues);
    Population *newPop = Selection(pop, 2, objectValues);
    PopulationString(pop);
    PopulationString(newPop);

    DeletePopulation(pop);
    DeletePopulation(newPop);
    return 0;
}
