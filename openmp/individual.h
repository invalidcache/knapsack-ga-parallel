#ifndef __INDIVIDUAL__
#define __INDIVIDUAL__

struct individual {
    int geneSize;
    int *genes;
    float fitness;
};

typedef struct individual Individual;

/*
* NewIndividual initializes and returns
* one individual with gene of geneSize
*/
Individual *NewIndividual(int geneSize);

void DeleteIndividual(Individual *ind);

/*
* CalculateFitness gets one individual ind
* and calculate its fitness
*/
float CalculateFitness(Individual *ind, int* objectValues);

/*
* CrossOver makes the crossover between two
* individuals and returns a new individual
*/
Individual *CrossOver(Individual *ind1, Individual *ind2);

/*
* Mutation changes randomly some genes of ind
* and returns the indivual generated by it
*/
Individual *Mutation(Individual *ind, float mutationRate);

Individual *Repair(Individual *ind, int* objectWeights, int knapsackWeightMax);

/*
* IndividualString prints the information about one individual
*/
void IndividualString(Individual *ind);




#endif