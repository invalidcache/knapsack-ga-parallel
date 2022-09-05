#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "individual.h"
#include "../global.h"


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
    for (int i = 0; i < geneSize; i++) {
        newIndividual->genes[i] = rand() % 2;
    }
    return newIndividual;
}

void DeleteIndividual(Individual *ind) {
    free(ind->genes);
    ind->genes = NULL;
    free(ind);
    ind = NULL;
}

void IndividualString(Individual *ind) {
    if (ind == NULL) {
        printf("NULL");
        return;
    }
    printf("Individual{\n"
    "\tgeneSize: %d\n"
    "\tgenes: %s\n"
    "\tfitness: %.2f\n"
    "}\n", ind->geneSize, convertGeneToString(ind), ind->fitness);
}


Individual *Mutation(Individual *ind, float mutationRate) {
    if (ind == NULL) {
        printf("ERROR: Individual NULL on function %s\n", __func__);
        return NULL;
    }

    for (int i = 0; i < ind->geneSize; i++) {
        int randomIntegerPart = rand() % 1000;
        float floatRandomPart = (float) randomIntegerPart / (float) 1000;
        if (floatRandomPart < mutationRate) {
            #ifdef DEBUG
            printf("Flipping bit on individual.\n");
            printf("Before: %s\n", convertGeneToString(ind));
            #endif
            ind->genes[i] = ind->genes[i] == 0 ? 1 : 0;
            #ifdef DEBUG
            printf("After: %s\n", convertGeneToString(ind));
            #endif
        }
    }

    return ind;
}

float CalculateFitness(Individual *ind, int* objectValues) {
    if (ind == NULL) {
        printf("ERROR: Individual NULL on function %s\n", __func__);
        return 0.0;
    }

    int geneSize = ind->geneSize;
    int sum = 0;

    for (int i = 0; i < geneSize; i++) {
        sum += ind->genes[i]*objectValues[i];
    }

    ind->fitness = sum;

    return sum;
}

Individual *CrossOver(Individual *ind1, Individual *ind2) {
    if (ind1 == NULL) {
        printf("ERROR: Individual1 NULL on function %s\n", __func__);
        return NULL;
    }

    if (ind2 == NULL) {
        printf("ERROR: Individual2 NULL on function %s\n", __func__);
        return NULL;
    }

    int geneSize = ind1->geneSize;
    int sep = rand() % geneSize;
    Individual *newIndividual = NewIndividual(geneSize);

    #ifdef DEBUG
        printf("Separation index: %d\n", sep);
    #endif

    for (int i = 0; i <= sep; i++) {
        newIndividual->genes[i] = ind1->genes[i];
    }

    for (int i = sep+1; i < geneSize; i++) {
        newIndividual->genes[i] = ind2->genes[i];
    }

    return newIndividual;
}

Individual *Repair(Individual *ind, int* objectWeights, int knapsackWeightMax) {
    if (ind == NULL) {
        printf("ERROR: Individual NULL on function %s\n", __func__);
        return NULL;
    }
    int currentWeight;
    while (TRUE) {
        currentWeight = 0;
        for (int i = 0; i < ind->geneSize; i++) {
            currentWeight += (ind->genes[i] * objectWeights[i]);
        }

        if (currentWeight <= knapsackWeightMax) {
            break;
        }

        int geneIndex = rand() % ind->geneSize;
        #ifdef DEBUG
        printf("Excluding index: %d\n", geneIndex);
        #endif
        ind->genes[geneIndex] = ind->genes[geneIndex] == 0 ? 0 : 0;
    }
    return ind;
}