#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "individual.h"
#include "population.h"
#include "knapsack.h"
#include "../global.h"
#include "file_util.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    ProblemInfo *info = GetProblemInfoFromFile("../teste.txt");
    
    Population *initalPopulation = NewPopulation(POPULATION_SIZE, info->numberOfObjects, info->objectValues);
    Knapsack *instance = NewKnapsackProblem(info->objectValues, info->objectWeights, info->knapsackMaxWeight, info->numberOfObjects, initalPopulation);
    Individual *bestIndividual = Solver(instance, GENERATIONS, TOURNMENT_PARTICIPANTS, MUTATION_RATE, CROSSOVER_RATE);

    IndividualString(bestIndividual);

    DeleteIndividual(bestIndividual);
    DeleteKnapsackProblem(instance);
    DeletePopulation(initalPopulation);
    
    return 0;
}
