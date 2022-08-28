#include <stdio.h>
#include <stdlib.h>
#include "population.h"

Population *NewPopulation(int populationSize, int geneSize) {
    Population *pop = (Population *) malloc(sizeof(Population));
    pop->individuals = (Individual **) malloc(populationSize * sizeof(Individual*));
    pop->numberOfIndividuals = populationSize;

    for (int i = 0; i < populationSize; i++) {
        Individual *ind = NewIndividual(geneSize);
        pop->individuals[i] = ind;
    }

    return pop;
}

Population *Selection(Population *pop, int k) {
    
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