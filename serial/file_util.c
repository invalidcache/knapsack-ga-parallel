#include <stdio.h>
#include <stdlib.h>
#include "file_util.h"


ProblemInfo *GetProblemInfoFromFile(char *path) {
    FILE *fptr;
    fptr = fopen(path, "rt");

    ProblemInfo *info = (ProblemInfo *) malloc(sizeof(ProblemInfo));
    int numberOfObjects, knapsackWeight;

    fscanf(fptr, "%d %d\n", &numberOfObjects, &knapsackWeight);

    int *objectValues = (int *)malloc(numberOfObjects * sizeof(int));
    int *objectWeights = (int *)malloc(numberOfObjects * sizeof(int));

    for (int i = 0; i < numberOfObjects; i++) {
        fscanf(fptr, "%d %d\n", &objectValues[i], &objectWeights[i]);
    }

    info->knapsackMaxWeight = knapsackWeight;
    info->numberOfObjects   = numberOfObjects;
    info->objectValues      = objectValues;
    info->objectWeights     = objectWeights;

    // for (int i = 0; i < numberOfObjects; i++) {
    //     printf("Values: %d, Weights: %d\n", objectValues[i], objectWeights[i]);
    // }
    fclose(fptr);

    return info;
}

