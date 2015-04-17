//RunCGoL.c


int runCGoL(struct Solution *solution, int solutionWidth, int solutionHeight, int fitnessSpecifier, struct CGoL *cgol, int visabilityModifier){
	//reset board
	resetBoard((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	
	//insert seed into the center of the board
	int seedTooLarge;
	seedTooLarge = loadSeed((solution -> seed), solutionWidth, solutionHeight, (cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	if(seedTooLarge == 0) return seedTooLarge; //Temp fix
	
	//Play the game
	for((cgol -> currentStep) = 0; (cgol -> currentStep) < (cgol -> maxStep); (cgol -> currentStep)++){
		//Print step information
		if(visabilityModifier == 1){
			printf("\ncurrentStep: %d\n", (cgol -> currentStep));
			printf("\nmaxStep: %d\n", (cgol -> maxStep));
		}
		
		//Print the board
		if(visabilityModifier == 1){
			printBoard(cgol, 1);
			sleep(1);
		}
		
		//Determine the next state of the game
		setFutureBoardState((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
		
		//Update the game to its next state
		updateBoardState((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight));
	}
	
	//Print the board
	if(visabilityModifier == 1){
		printBoard(cgol, 1);
		sleep(1);
	}
	
	//DetermineFitness
	(solution -> fitness) = getFitness((cgol -> board), (cgol -> boardWidth), (cgol -> boardHeight), fitnessSpecifier);
	
	return 1;
}