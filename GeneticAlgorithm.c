//GeneticAlgorithm.c


struct Solution* ga_initializeBestSolution(int solutionWidth, int solutionHeight, char *seedFileName){
	printf("\nIn ga_initializeBestSolution\n");
	printf("Width: %d\nHeight: %d\n", solutionWidth, solutionHeight);

	struct Solution *solution = (struct Solution*)malloc(sizeof(struct Solution));
	solution -> seed = (int**)calloc(solutionHeight, sizeof(int));
	int h, w;

	for(h = 0; h < solutionHeight; h++){
		solution -> seed[h] = (int*)calloc(solutionWidth, sizeof(int));
	}
	solution -> fitness = 0;

	FILE *fp;
	int ch;
	printf("\nseedFileName: %s\n", seedFileName);
    fp = fopen(seedFileName, "r");
    printf("\nfopen!!!\n");
    h = w = 0;




   	 while ((ch = fgetc(fp)) != EOF)
    {
    	if(h==solutionHeight) break;
    	switch(ch){
			case '0':
				printf("0");
				w++;
				break;
			case '1':
				printf("1");
				solution -> seed[h][w] = 1;
				w++;
				break;
			case '\n':
				printf("\n");
				h++;
				w = 0;
				break;
			default:
				//printf("What is c: %c", ch);
				printf("_");
		}
    }
 
    if (ferror(fp))
        printf("I/O error when reading");
    else if (feof(fp))
        printf("End of file reached successfully");

	printf("\nfclose?\n");
	fclose(fp);
	printf("\nfclose done\n");
   return solution;	
}

struct Solution* ga_initializePopulation(int maxSolution, int solutionWidth, int solutionHeight){
	struct Solution *population = (struct Solution*)calloc(maxSolution, sizeof(struct Solution));
	int p;
	
	for(p = 0; p < maxSolution; p++){
		population[p] = *ga_initializeSolution(solutionWidth, solutionHeight);
	}
	
	
	return population;
	
}

void ga_freePopulation(struct Solution *population, int maxSolution, int solutionHeight){
	int p, h;
	for(p = 0; p < maxSolution; p++){
		for(h = 0; h < solutionHeight; h++){
			free(population[p].seed[h]);
		}
		free(population[p].seed);
	}
	free(population);
}

struct Solution* ga_initializeSolution(int solutionWidth, int solutionHeight){
	struct Solution *solution = (struct Solution*)malloc(sizeof(struct Solution));
	solution -> seed = (int**)calloc(solutionHeight, sizeof(int));
	
	int h;
	for(h = 0; h < solutionHeight; h++){
		solution -> seed[h] = (int*)calloc(solutionWidth, sizeof(int));
	}
	solution -> fitness = 0;
	
	return solution;
}

void ga_freeSolution(struct Solution *solution, int solutionHeight){
	int  h;
	for(h = 0; h < solutionHeight; h++){
		free((solution -> seed)[h]);
	}
	free(solution -> seed);
}

struct Solution* copySolution(struct Solution *solution, int solutionWidth, int solutionHeight){
	struct Solution *newSolution = ga_initializeSolution(solutionWidth, solutionHeight);
	int h, w;
	for(h = 0; h < solutionHeight; h++){
		for(w = 0; w < solutionWidth; w++){
			//This needs to return the value not a pointer
			(newSolution -> seed)[h][w] = (solution -> seed)[h][w];
		}
	}
	(newSolution -> fitness) = (solution -> fitness);
	return newSolution;
}

int changePopSize(int *attribute){
	requestNewValueForAttribute("Population size", *attribute, MIN_POPULATION, MAX_POPULATION);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_POPULATION, MAX_POPULATION);
	return changed;
}

int changeSolutionWidth(int *attribute){
	requestNewValueForAttribute("Solution width", *attribute, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	int changed = getPositiveChangedIntInRange(attribute, 4, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	return changed;
}

int changeSolutionHeight(int *attribute){
	requestNewValueForAttribute("Solution height", *attribute, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	int changed = getPositiveChangedIntInRange(attribute, 4, MIN_SOLUTION_SIZE, MAX_SOLUTION_SIZE);
	return changed;
}

int changeMaxGeneration(int *attribute){
	requestNewValueForAttribute("Max generation", *attribute, MIN_GENERATION, MAX_GENERATION);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_GENERATION, MAX_GENERATION);
	return changed;
}

int changeMutationRate(int *attribute){
	requestNewValueForAttribute("Mutation rate", *attribute, MIN_MUTATION_RATE, MAX_MUTATION_RATE);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_MUTATION_RATE, MAX_MUTATION_RATE);
	return changed;
}

int changeFitnessSpecifier(int *attribute){
	requestNewValueForAttribute("Fitness specifier", *attribute, MIN_FITNESS_SPECIFIER, MAX_FITNESS_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_FITNESS_SPECIFIER, MAX_FITNESS_SPECIFIER);
	return changed;
}

int changeSelectionSpecifier(int *attribute){
	requestNewValueForAttribute("Selection specifier", *attribute, MIN_SELECTION_SPECIFIER, MAX_SELECTION_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_SELECTION_SPECIFIER, MAX_SELECTION_SPECIFIER);
	return changed;
}

int changeCrossoverSpecifier(int *attribute){
	requestNewValueForAttribute("Crossover specifier", *attribute, MIN_CROSSOVER_SPECIFIER, MAX_CROSSOVER_SPECIFIER);
	int changed = getPositiveChangedIntInRange(attribute, 3, MIN_CROSSOVER_SPECIFIER, MAX_CROSSOVER_SPECIFIER);
	return changed;
}


void test_GASolutionsInitiallized(struct GA *ga){
	int p, h, w;
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_GASolutionsInitiallized\n\n");
	printf("ga.bestSolution:\n");
	for(h = 0; h < ga -> solutionHeight; h++){
		for(w = 0; w < ga -> solutionWidth; w++){
			printf("%d", ga -> bestSolution.seed[h][w]);
		}
		printf("\n");
	}
	printf("\n");
	
	int randVal = rand();
	randVal %= ( (ga -> maxSolution) - 1);
	randVal++;
	int testing[3] = {0, randVal, (ga -> maxSolution) - 1};
	for(p = 0; p < 3; p++){
		printf("ga.population[%d]:\n", testing[p]);
		for(h = 0; h < ga -> solutionHeight; h++){
			for(w = 0; w < ga -> solutionWidth; w++){
				printf("%d", ga -> population[testing[p]].seed[h][w]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_PrintGASimpleAttributes(struct GA *ga){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_PrintGASimpleAttributes\n\n");
	printf("currentSolution: %d\n", (ga -> currentSolution));
	printf("maxSolution: %d\n", (ga -> maxSolution));
	printf("solutionWidth: %d\n", (ga -> solutionWidth));
	printf("solutionHeight: %d\n", (ga -> solutionHeight));
	printf("currentGeneration: %d\n", (ga -> currentGeneration));
	printf("maxGeneration: %d\n", (ga -> maxGeneration));
	printf("mutationRate: %d\n", (ga -> mutationRate));
	printf("fitnessSpecifier: %d\n", (ga -> fitnessSpecifier));
	printf("selectionSpecifier: %d\n", (ga -> selectionSpecifier));
	printf("crossoverSpecifier: %d\n", (ga -> crossoverSpecifier));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void printSolution(struct Solution *solution, int solutionHeight, int solutionWidth, int lineModifier){
	if(lineModifier) printSpacedCharLine('=', TEST_LINE_MAX);
	int h, w;
	for(h = 0; h < solutionHeight; h++){
		for(w = 0; w < solutionWidth; w++){
			printf("%d", solution -> seed[h][w]);
		}
		printf("\n");
	}
	if(lineModifier) printSpacedCharLine('=', TEST_LINE_MAX);
}

int selection_Roulette(struct Solution *population, int maxSolution){
	int fitnessSum = 0;
	int p;
	for(p = 0; p < maxSolution; p++){
		fitnessSum += population[p].fitness;
	}
	int randNum = rand() % (fitnessSum + 1);
	
	p = 0;
	while(p<(maxSolution-1)){
		randNum -= population[p].fitness;
		if(randNum <= 0) break;
		p++;
	}
	return p;
}

struct Solution* crossover(struct Solution *parentA, struct Solution *parentB, int solutionWidth, int solutionHeight){
	struct Solution *child = ga_initializeSolution(solutionWidth, solutionHeight);
	int h, w;
	//For each row
	for(h = 0; h < solutionHeight; h++){
		//Select a point to swap at
		int swapPoint = rand() % (solutionWidth + 1);
		for(w = 0; w < solutionWidth; w++){
			if(w < swapPoint){
				(child -> seed)[h][w] = (parentA -> seed)[h][w];
			}else{
				(child -> seed)[h][w] = (parentB -> seed)[h][w];
			}
		}
	}
	
	return child;
}