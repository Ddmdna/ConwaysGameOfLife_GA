//Optimization.c


int optimization(struct GA *ga, struct CGoL *cgol){
	printf("\nIn optimization\n");
	printf("\ncurrentGeneration: %d\n", (ga -> currentGeneration) + 1);
	printf("\nmaxGeneration: %d\n", ga -> maxGeneration);
	
	int again = 0;
	
	//Mutate initial population
	if((ga -> currentGeneration) == 0){
		printf("\nBest Solution at start\n");
		printSolution(&(ga -> bestSolution), (ga -> solutionHeight), (ga -> solutionWidth), 0);
		printf("\nWith a fitness of: (%d)\n",(ga -> bestSolution.fitness));
		sleep(1);
		mutatePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight), INITIAL_MUTATION_RATE);
	}
	int p;
	
	//Run each solution through CGoL to determine their fitness
	//Don't show the board...
	int seedTooLarge;
	int i;
	for(i = 0; i < (ga -> maxSolution); i++){
		seedTooLarge = runCGoL(&(ga -> population[i]), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> fitnessSpecifier), cgol, 0);
		if(seedTooLarge == 0) return seedTooLarge; //Temp fix
	}
	
	//Sort population by fitness
	sortPopulationByFitness((ga -> population), (ga -> maxSolution));
	
	//Allocate memory for a new blank population for the next generation
	struct Solution *newPopulation = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
	
	//For each new solution perform the following by working with the last population
	//Selection and Crossover
	for(i = 0; i < (ga -> maxSolution); i++){
		int parentA, parentB;
		//Selection to find each parent
		parentA = selection_Roulette((ga -> population), (ga -> maxSolution));
		parentB = selection_Roulette((ga -> population), (ga -> maxSolution));
		//perform crossover at different parts for each line
		(newPopulation)[i] = *crossover(&(ga -> population[parentA]), &(ga -> population[parentB]), (ga -> solutionWidth), (ga -> solutionHeight));
	}
	
	//For each solution in the new population
	//Mutation
	mutatePopulation(newPopulation, (ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> mutationRate));
	
	//Determine to continue or set the bestSeed and finish
	if((ga -> currentGeneration) < ((ga -> maxGeneration)-1)){
		again = 1;
	}else{
		//Testing past bestSolution vs current leading solution
		if(ga -> bestSolution.fitness < ga -> population[(ga -> maxSolution) - 1].fitness){
			printf("\nga -> bestSolution.fitness < ga -> population[0].fitness\n");
			//free the old bestSolution
			ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
			//Copy values and return a new solution
			(ga -> bestSolution) = *copySolution(&((ga -> population)[(ga -> maxSolution) - 1]), (ga -> solutionWidth), (ga -> solutionHeight));
		}
		
		printf("\nBest Solution at finish\n");
		printSolution(&(ga -> bestSolution), (ga -> solutionHeight), (ga -> solutionWidth), 0);
		printf("\nWith a fitness of: (%d)\n",(ga -> bestSolution.fitness));
		sleep(1);
	}
	
	//Free memory from the old population
	ga_freePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionHeight));
	
	//Set ga.population to point to the new population
	(ga -> population) = newPopulation;
	
	//Advance currentGeneration
	(ga -> currentGeneration)++; 
	
	return again;
}

void mutatePopulation(struct Solution *population, int maxSolution, int solutionWidth, int solutionHeight, int mutationRate){
	int h, w, p;
	for(p = 0; p < maxSolution; p++){
		for(h = 0; h < solutionHeight; h++){
			for(w = 0; w < solutionWidth; w++){
				if(bitMutationCheck(mutationRate)){
					if(population[p].seed[h][w]){
						population[p].seed[h][w] = 0;
					} else{
						population[p].seed[h][w] = 1;
					}
				}
			}
		}
	}
}

//Larger seeds will have higher mutation rates...
//Might want to adjust this later
int bitMutationCheck(int mutationRate){
	int result = 0;
	//prepare for random values by multiplying mutationRate by 10 in hopes of a better dispersal of values
	mutationRate*=10;
	int randValue = rand();
	if((randValue % (MAX_MUTATION_RATE*10)) <= mutationRate) result = 1;
	return result;
}

//Grabbed a selection sort from:
//http://www.codebeach.com/2008/09/sorting-algorithms-in-c.html
void sortPopulationByFitness(struct Solution *population, int maxSolution){
	struct Solution temp;
	int i;
    for (i = 0; i < (maxSolution - 1); ++i)
    {
        int j, min;
        min = i;
        for (j = i+1; j < maxSolution; ++j)
        {
			if(population[j].fitness < population[min].fitness)
				min = j;
        }

        temp = population[i];
        population[i] = population[min];
        population[min] = temp;
	}
}