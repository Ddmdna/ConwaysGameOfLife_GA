//Run.c


void run(struct Settings *settings, struct CGoL *cgol, struct GA *ga){
	//Create GenericMenu structs
	struct Menu main_Menu;
	struct Menu menu_GA;
	struct Menu menu_CGoL;
	
	//Initialize mainMenu
	main_Menu.numberOfFunctions = 6;
	main_Menu.menuName = "Main Menu";
	main_Menu.functionDescriptions = (char *[]){ "GA Settings Menu", "CGoL Settings Menu", 
	"Run Optimization", "Observe CGoL with Best Seed", "Save Best Seed", "Exit"
	};
	//if(debugRun) test_InitializeMain_Menu();
	
	
	//Initialize menu_GA
	menu_GA.numberOfFunctions = 9;
	menu_GA.menuName = "GA Settings Menu";
	menu_GA.functionDescriptions = (char *[]){ "Set Population Size", "Set Solution Width", 
	"Set Solution Height", "Set Max Generation", "Set Mutation Rate", "Set Fitness Specifier", 
	"Set Selection Specifier", "Set Crossover Specifier", "Exit"
	};
	//if(debugRun) test_InitializeMenu_GA);
	
	
	//Initialize menu_CGoL
	menu_CGoL.numberOfFunctions = 4;
	menu_CGoL.menuName = "CGoL Settings Menu";
	menu_CGoL.functionDescriptions = (char *[]){ "Set Board Width", "Set Board Height", 
	"Set Max Step", "Exit"
	};
	//if(debugRun) test_InitializeMenu_CGoL();
	
	
	//Loop through mainMenu until exitCondition is returned
	int index;
	do{
		index = mainMenu(&main_Menu);
		switch(index){
			case 0:
				//Loop through menu_GA until exitCondition is returned
				//This functions includes IO which enables the user to access
				//and change the values of "ga" attributes
				while(settingsMenu_GA(&menu_GA, ga) != EXIT_CONDITION);
				if(debugRun) test_PrintGASimpleAttributes(ga);
				break;
			case 1:
				//Loop through menu_CGoL until exitCondition is returned
				//This functions includes IO which enables the user to access
				//and change the values of "cgol" attributes
				while(settingsMenu_CGoL(&menu_CGoL, cgol) != EXIT_CONDITION);
				if(debugRun) test_PrintCGoLSimpleAttributes(cgol);
				break;
			case 2:
				//Loop through each solution in population through each generation
				//This functions includes simple output as it progresses
				//Returns true if currentGeneration < maxGeneration
				printf("\nStarting optimization\n");
				ga -> currentGeneration = 0;
				while(optimization(ga, cgol));
				printf("\nFinished optimization\n");
				break;
			case 3:
				//observeBestSeed(ga, cgol)
				printf("\nStarting To watch the bestSolution\n");
				runCGoL(&(ga -> bestSolution), (ga -> solutionWidth), (ga -> solutionHeight), (ga -> fitnessSpecifier), cgol, 1);
				printf("\nFinished bestSolution\n");
				break;
			case 4:
				//saveBestSeed(ga)
				break;
			case 5:
				//exit
				index = EXIT_CONDITION;
				break;
			default:
				index = SKIP_CONDITION;
				printf("\nInvalid input\n");
				break;
		}
	}
	while(index != EXIT_CONDITION);
}

int mainMenu(struct Menu *menu){
	int index = -2;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	return index;
}

int settingsMenu_GA(struct Menu *menu, struct GA *ga){
	int index = -1;
	int oldMaxSolution;
	int oldSolutionHeight;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	switch(index){
		case 0:
			//Update maxSolution
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			oldMaxSolution = (ga -> maxSolution);
			if(changePopSize(&(ga -> maxSolution))){
				ga_freePopulation((ga -> population), oldMaxSolution, (ga -> solutionHeight));
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nPopulation max changed to (%d)\n", (ga -> maxSolution));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 1:
			//Update solutionWidth
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			if(changeSolutionWidth(&(ga -> solutionWidth))){
				ga_freePopulation((ga -> population), (ga -> maxSolution), (ga -> solutionHeight));
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nSolution width changed to (%d)\n", (ga -> solutionWidth));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), (ga -> solutionHeight));
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 2:
			//Update solutionHeight
			//If successful, free population and allocate a new population in its place
			//using the updated attributes
			oldSolutionHeight = (ga -> solutionHeight);
			if(changeSolutionHeight(&(ga -> solutionHeight))){
				ga_freePopulation((ga -> population), (ga -> maxSolution), oldSolutionHeight);
				(ga -> population) = ga_initializePopulation((ga -> maxSolution), (ga -> solutionWidth), (ga -> solutionHeight));
				printf("\nSolution height changed to (%d)\n", (ga -> solutionHeight));
				//Also Change bestSolution...
				ga_freeSolution(&(ga -> bestSolution), oldSolutionHeight);
				(ga -> bestSolution) = *ga_initializeSolution((ga -> solutionWidth), (ga -> solutionHeight));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 3:
			//Update maxGeneration
			if(changeMaxGeneration(&(ga -> maxGeneration))){
				printf("\nMax generation changed to (%d)\n", (ga -> maxGeneration));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 4:
			//Update mutationRate
			if(changeMutationRate(&(ga -> mutationRate))){
				printf("\nMutation rate changed to (%d)\n", (ga -> mutationRate));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 5:
			if(changeFitnessSpecifier(&(ga -> fitnessSpecifier))){
				printf("\nFitness specifier changed to (%d)\n", (ga -> fitnessSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 6:
			if(changeSelectionSpecifier(&(ga -> selectionSpecifier))){
				printf("\nSelection specifier changed to (%d)\n", (ga -> selectionSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 7:
			if(changeCrossoverSpecifier(&(ga -> crossoverSpecifier))){
				printf("\nCrossover specifier changed to (%d)\n", (ga -> crossoverSpecifier));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 8:
			index = EXIT_CONDITION;
			break;
		default:
			index = SKIP_CONDITION;
			printf("\nInvalid input\n");
			break;
	}
	return index;
}

int settingsMenu_CGoL(struct Menu *menu, struct CGoL *cgol){
	int index = -1;
	int oldBoardHeight;
	outputMenu(menu);
	index = getPositiveIntInRange(3, 0, menu -> numberOfFunctions);
	switch(index){
		case 0:
			//Update boardWidth
			//If successful, free board and allocate a new board in its place
			//using the updated attributes
			if(changeBoardWidth(&(cgol -> boardWidth))){
				cgol_freeBoard((cgol -> board), (cgol -> boardHeight));
				(cgol -> board) = cgol_initializeBoard((cgol -> boardWidth), (cgol -> boardHeight));
				printf("\nBoard width changed to (%d)\n", (cgol -> boardWidth));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 1:
			//Update boardHeight
			//If successful, free board and allocate a new board in its place
			//using the updated attributes
			oldBoardHeight = (cgol -> boardHeight);
			if(changeBoardHeight(&(cgol -> boardHeight))){
				cgol_freeBoard((cgol -> board), oldBoardHeight);
				(cgol -> board) = cgol_initializeBoard((cgol -> boardWidth), (cgol -> boardHeight));
				printf("\nBoard width changed to (%d)\n", (cgol -> boardWidth));
			}else{
				printf("\nInvalid input\n");
			}
			break;
		case 2:
			//Update maxStep
			if(changeMaxStep(&(cgol -> maxStep))){
				printf("\nMax step changed to (%d)\n", (cgol -> maxStep));
			} else{
				printf("\nInvalid input\n");
			}
			break;
		case 3:
			index = EXIT_CONDITION;
			break;
		default:
			index = SKIP_CONDITION;
			printf("\nInvalid input\n");
			break;
	}
	return index;
}