#ifndef __FILE_UTIL__
#define __FILE_UTIL__

typedef struct problemInfo{
    int numberOfObjects;
    int knapsackMaxWeight;
    int *objectValues;
    int *objectWeights;
} ProblemInfo;

ProblemInfo *GetProblemInfoFromFile(char *path);

#endif