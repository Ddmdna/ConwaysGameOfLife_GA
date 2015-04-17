//GeneticAlgorithm.h


struct Solution{
	int fitness;
	int **seed;
};


struct GA{
	int currentSolution;
	int maxSolution;
	int solutionWidth;
	int solutionHeight;
	int currentGeneration;
	int maxGeneration;
	int mutationRate;
	int fitnessSpecifier;
	int selectionSpecifier;
	int crossoverSpecifier;
	struct Solution bestSolution;
	struct Solution *population;
};


struct Solution* ga_initializeBestSolution(int solutionWidth, int solutionHeight, char *seedFileName);
struct Solution* ga_initializePopulation(int maxSolution, int solutionWidth, int solutionHeight);
void ga_freePopulation(struct Solution *population, int maxSolution, int solutionHeight);
struct Solution* ga_initializeSolution(int solutionWidth, int solutionHeight);
void ga_freeSolution(struct Solution *solution, int solutionHeight);
struct Solution* copySolution(struct Solution *solution, int solutionWidth, int solutionHeight);
int changePopSize(int *attribute);
int changeSolutionWidth(int *attribute);
int changeSolutionHeight(int *attribute);
int changeMaxGeneration(int *attribute);
int changeMutationRate(int *attribute);
int changeFitnessSpecifier(int *attribute);
int changeSelectionSpecifier(int *attribute);
int changeCrossoverSpecifier(int *attribute);
void test_GASolutionsInitiallized(struct GA *ga);
void test_PrintGASimpleAttributes(struct GA *ga);
void printSolution(struct Solution *solution, int solutionHeight, int solutionWidth, int lineModifier);
int selection_Roulette(struct Solution *population, int maxSolution);
struct Solution* crossover(struct Solution *parentA, struct Solution *parentB, int solutionWidth, int solutionHeight);