#include <stdio.h>
#include <stdlib.h>
#include "individual.h"
#include "population.h"
#include "knapsack.h"

Knapsack *NewKnapsackProblem(int *objectValues, int *objectWeights, int maxWeight, int numberOfObjects, Population *pop) {
    Knapsack *instance = (Knapsack *) malloc(sizeof(Knapsack));
    instance->maxWeight = maxWeight;
    instance->numberOfObjects = numberOfObjects;
    instance->objectValues = objectValues;
    instance->objectWeights = objectWeights;
    instance->population = pop;
    return instance;
}

void DeleteKnapsackProblem(Knapsack *instance) {
    free(instance->objectValues);
    free(instance->objectWeights);
    free(instance);
    instance = NULL;
}

Individual *Solver(Knapsack *instance, int numberOfGenerations, int tournamentParticipants, float mutationRate, float crossoverRate) {
    Population *pop = instance->population;
    Population *selectedPop;

    if (pop == NULL) {
        printf("Population is NULL\n");
        return NULL;
    }

    if (instance == NULL) {
        printf("Instance is NULL\n");
        return NULL;
    }
    
    // PopulationString(pop);

    // Repair
    printf("Starting first repair\n");
    for (int i=0; i < pop->numberOfIndividuals; i++) {
        pop->individuals[i] = Repair(pop->individuals[i], instance->objectWeights, instance->maxWeight);
    }
 
    // PopulationString(pop);

    printf("Starting first Firness\n");
    // Get Fitness
    for (int i=0; i < pop->numberOfIndividuals; i++) {
        pop->individuals[i]->fitness = CalculateFitness(pop->individuals[i], instance->objectValues);
    }

    printf("Starting first Generation\n");
    for (int i=0; i < numberOfGenerations; i++) {
        Individual *bestIndividual = NewIndividual(pop->numberOfGenes);
        copyIndividual(bestIndividual, GetBestIndividual(pop));
        
        printf("Generation: %d/%d | Best Fitness: %.2f | Avg Fitness: %.2f\n", i+1, numberOfGenerations, GetBestFitness(pop), GetAvgFitness(pop));
        
        // Selection
        selectedPop = Selection(pop, tournamentParticipants, instance->objectValues);

        // Cross Over
        for (int j=0; j<pop->numberOfIndividuals; j++) {
            int randomIntegerPart = rand() % 1000;
            float floatRandomPart = randomIntegerPart / 1000;
            if (floatRandomPart < crossoverRate) {
                Individual *indAddrs = pop->individuals[j];
                pop->individuals[j] = CrossOver(pop->individuals[j], selectedPop->individuals[j]);
                free(indAddrs);
            }
        } 

        // Mutation
        for (int j=0; j<pop->numberOfIndividuals; j++) {
            pop->individuals[j] = Mutation(pop->individuals[j], mutationRate);
        } 

        // Repair
        for (int j=0; j < pop->numberOfIndividuals; j++) {
            pop->individuals[j] = Repair(pop->individuals[j], instance->objectWeights, instance->maxWeight);
        }

        // Get Fitness
        for (int j=0; j < pop->numberOfIndividuals; j++) {
            pop->individuals[j]->fitness = CalculateFitness(pop->individuals[j], instance->objectValues);
        }

        copyIndividual(pop->individuals[rand()%pop->numberOfIndividuals], bestIndividual);

        free(selectedPop);
    }

    return GetBestIndividual(pop);
}
