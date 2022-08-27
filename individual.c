#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "individual.h"


char *convertGeneToString(Individual *ind) {
    int geneSize = ind->geneSize;
    char *string = (char *) malloc(sizeof(char)*geneSize);

    for (int i = 0; i < geneSize; i++) {
        string[i] = '0' + ind->genes[i];
    }

    return string;
}


Individual *NewIndividual(int geneSize) {
    Individual *newIndividual = (Individual *) malloc(sizeof(Individual));
    newIndividual->genes = (int *) malloc(geneSize * sizeof(int));
    newIndividual->geneSize = geneSize;
    srand(time(NULL));
    for (int i = 0; i < geneSize; i++) {
        newIndividual->genes[i] = rand() % 2;
    }
    return newIndividual;
}

void String(Individual *ind) {
    if (ind == NULL) {
        printf("NULL");
        return;
    }
    printf("Individual{\n"
    "\tgeneSize: %d\n"
    "\tgenes: %s\n"
    "\tfitness: %.2f\n"
    "}", ind->geneSize, convertGeneToString(ind), ind->fitness);
}
