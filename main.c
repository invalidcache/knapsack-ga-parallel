#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "individual.h"
#include "population.h"
#include "knapsack.h"
#include "global.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int objectValues[NUMBER_OF_OBJECTS] = {55, 10, 47, 5, 4, 50, 8, 61, 85, 87};
    int objectWeights[NUMBER_OF_OBJECTS] = {95, 4, 60, 32, 23, 72, 80, 62, 65, 46};
    
    Population *initalPopulation = NewPopulation(POPULATION_SIZE, GENESIZE, objectValues);
    Knapsack *instance = NewKnapsackProblem(objectValues, objectWeights, PROBLEM_MAX_WEIGHT, NUMBER_OF_OBJECTS, initalPopulation);
    Individual *bestIndividual = Solver(instance, GENERATIONS, TOURNMENT_PARTICIPANTS, MUTATION_RATE);

    IndividualString(bestIndividual);

    DeleteIndividual(bestIndividual);
    DeleteKnapsackProblem(instance);
    DeletePopulation(initalPopulation);
    
    return 0;
}
