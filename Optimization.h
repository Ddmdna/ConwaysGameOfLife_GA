//Optimization.h


void mutatePopulation(struct Solution *population, int maxSolution, int solutionWidth, int solutionHeight, int mutationRate);
int bitMutationCheck(int mutationRate);
void sortPopulationByFitness(struct Solution *population, int maxSolution);

int runCGoL(struct Solution *solution, int solutionWidth, int solutionHeight, int fitnessSpecifier, struct CGoL *cgol, int visabilityModifier);