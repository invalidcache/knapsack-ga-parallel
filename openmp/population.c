#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <omp.h>
#include "population.h"

Population *NewPopulation(int populationSize, int geneSize, int* objectValues) {
    Population *pop = (Population *) malloc(sizeof(Population));
    pop->individuals = (Individual **) malloc(populationSize * sizeof(Individual*));
    pop->numberOfIndividuals = populationSize;
    pop->numberOfGenes = geneSize;

    // #pragma omp omp_set_num_threads(3) parallel for
    for (int i = 0; i < populationSize; i++) {
        #ifdef DEBUG_PARALLEL
            int threadId = omp_get_thread_num();
            printf("On %s thread %d executing index %d\n", __func__, threadId, i);
        #endif
        Individual *ind = NewIndividual(geneSize);
        pop->individuals[i] = ind;
        pop->individuals[i]->fitness = CalculateFitness(pop->individuals[i], objectValues);
    }

    return pop;
}

void DeletePopulation(Population *pop){
    for (int i = 0; i < pop->numberOfIndividuals; i++) {
        DeleteIndividual(pop->individuals[i]);
        pop->individuals[i] = NULL;
    }
    free(pop->individuals);
    pop->individuals = NULL;
    free(pop);
    pop = NULL;
}

void copyIndividual(Individual *destination, Individual *source) {
    if (destination == NULL || source == NULL) {
        printf("destination or source is NULL on %s\n", __func__);
        return;
    }
    destination->fitness = source->fitness;
    memcpy(destination->genes, source->genes, sizeof(int)*source->geneSize);
    destination->geneSize = source->geneSize; 
}

Population *Selection(Population *pop, int num_participants, int* objectValues) {
    int best_tournament_fitness = INT_MIN;
    int curr_fitness;
    int best_tournament_index = -1;
    int selected_individual_index;

    Population *new_pop = NewPopulation(pop->numberOfIndividuals, pop->numberOfGenes, objectValues);
    
    for (int i = 0; i < pop->numberOfIndividuals; i++) {
        best_tournament_fitness = INT_MIN;
        best_tournament_index = -1;
        #ifdef DEBUG
        printf("Start Tournament\n");
        #endif
        // #pragma omp omp_set_num_threads(3) parallel for 
        for (int j = 0; j < num_participants; j++) {
            selected_individual_index = rand()%pop->numberOfIndividuals;
            #ifdef DEBUG
            printf("Choosen index: %d\n", selected_individual_index);
            #endif
            curr_fitness = pop->individuals[selected_individual_index]->fitness;
            if (curr_fitness > best_tournament_fitness) {
                best_tournament_fitness = curr_fitness;
                best_tournament_index = selected_individual_index;
            }
        }
        #ifdef DEBUG
        printf("End Tournament\n");
        #endif
        copyIndividual(new_pop->individuals[i], pop->individuals[best_tournament_index]);
    }

    return new_pop;
}

float GetBestFitness(Population *pop) {
    float currFitness = INT_MIN;
    for (int i=0; i < pop->numberOfIndividuals; i++) {
        if (pop->individuals[i]->fitness > currFitness) {
            currFitness = pop->individuals[i]->fitness;
        }
    }
    return currFitness;
}

float GetAvgFitness(Population *pop) {
    float acumulateFitness = 0;
    for (int i=0; i < pop->numberOfIndividuals; i++) {
        acumulateFitness += pop->individuals[i]->fitness;
    }
    return acumulateFitness/pop->numberOfIndividuals;
}

Individual *GetBestIndividual(Population *pop) {
    float currFitness = INT_MIN;
    Individual *ind = NULL;
    for (int i=0; i < pop->numberOfIndividuals; i++) {
        if (pop->individuals[i]->fitness > currFitness) {
            currFitness = pop->individuals[i]->fitness;
            ind = pop->individuals[i];
        }
    }
    return ind;
}

void PopulationString(Population *pop) {
    if (pop == NULL) {
        printf("Population is NULL on %s\n", __func__);
        return;
    }

    printf("Population{\n"
    "\tIndividuals:\n");
    for (int i = 0; i < pop->numberOfIndividuals; i++) {
        IndividualString(pop->individuals[i]);
    }
    printf("\tnumberOfIndividuals: %d\n", pop->numberOfIndividuals);
    printf("}\n");
}