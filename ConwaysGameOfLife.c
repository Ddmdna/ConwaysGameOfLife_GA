//ConwaysGameOfLife.c


//Initialize and return a two dimensional array to be used as the board for the CGoL struct
int** cgol_initializeBoard(int boardWidth, int boardHeight){
	int **board = (int**)calloc(boardHeight, sizeof(int));
	int h;
	for(h = 0; h < boardHeight; h++){
		board[h] = (int*)calloc(boardWidth, sizeof(int));
	}
	return board;
}


void cgol_freeBoard(int **board, int boardHeight){
	int h;
	for(h = 0; h < boardHeight; h++){
		free(board[h]);
	}
	free(board);
}

void resetBoard(int **board, int boardWidth, int boardHeight){
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			board[h][w] = 0;
		}
	}
}

int loadSeed(int **seed, int solutionWidth, int solutionHeight, int **board, int boardWidth, int boardHeight){
	//Check to see if the seed can fit
	if(solutionWidth >= boardWidth || solutionHeight >= boardHeight) return 0;
	
	//Determine initial coordinates
	int startH = ((boardHeight-solutionHeight)/2);
	int startW = ((boardWidth-solutionWidth)/2);
	int h, w;
	for(h = 0; h < solutionHeight; h++ ){
		for(w = 0; w < solutionWidth; w++){
			board[startH+h][startW+w] = seed[h][w];
		}
	}
	return 1;
}


//void requestNewValueForAttribute(char* attributeName, int currentValue, int min, int max);

int changeBoardWidth(int *attribute){
	requestNewValueForAttribute("Board width", *attribute, MIN_BOARD_WIDTH, MAX_BOARD_WIDTH);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_BOARD_WIDTH, MAX_BOARD_WIDTH);
	return changed;
}

int changeBoardHeight(int *attribute){
	requestNewValueForAttribute("Board height", *attribute, MIN_BOARD_HEIGHT, MAX_BOARD_HEIGHT);
	int changed = getPositiveChangedIntInRange(attribute, 5, MIN_BOARD_HEIGHT, MAX_BOARD_HEIGHT);
	return changed;
}

int changeMaxStep(int *attribute){
	requestNewValueForAttribute("Max step", *attribute, MIN_STEP, MAX_STEP);
	int changed = getPositiveChangedIntInRange(attribute, 6, MIN_STEP, MAX_STEP);
	return changed;
}

void printBoard(struct CGoL *cgol, int visabilityModifier){
	int h, w;
	if(visabilityModifier == 1) printSpacedCharLine('=', (cgol -> boardWidth));
	else printf("\n");
	for(h = 0; h < (cgol -> boardHeight); h++){
		for(w = 0; w < (cgol -> boardWidth); w++){
			if(visabilityModifier == 1){
				if((cgol -> board[h][w]) == 0) printf(" ");
				else printf("%d", (cgol -> board[h][w]));
			}else{
				printf("%d", (cgol -> board[h][w]));
			}
		}
		printf("\n");
	}
	if(visabilityModifier == 1) printSpacedCharLine('=', (cgol -> boardWidth));
	else printf("\n");
}

int getFutureState(int currentState, int sumLive){
	int futureState = 0;
	if(currentState == LIVING){
		if(sumLive < 2 || sumLive > 3){
			futureState = DEAD_NEXT_TURN;
		}else{
			futureState = LIVING;
		}
	}
	else if(currentState == NONLIVING){
		if(sumLive == 3) {
			futureState = BORN_NEXT_TURN;
		}
	}

	return futureState;
}

int getFutureCenterState(int **board, int startH, int startW){
	int sumLive = 0;
	int h, w;
	for(h = (startH-1); h < (startH+2); h++){
		for(w = (startW-1); w < (startW+2); w++){
			if( (board[h][w] == (LIVING)) || (board[h][w] == (DEAD_NEXT_TURN)) ){
				sumLive++;
			}
		}
	}
	if(board[startH][startW] == LIVING) sumLive--;

	int futureState = getFutureState((board[startH][startW]), sumLive);
	return futureState;
}

void setFutureBoardState(int **board, int boardWidth, int boardHeight){
	int h, w;
	//Check the center with a two space gap, will add edge and corner cases later
	//Problem if my board is too small
	for(h = 2; h < (boardHeight - 2); h++){
		for(w = 2; w < (boardWidth - 2); w++){
			(board[h][w]) = getFutureCenterState(board, h, w);
		}
	}
}

void updateBoardState(int **board, int boardWidth, int boardHeight){
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			if(board[h][w] == DEAD_NEXT_TURN){
				(board[h][w]) = NONLIVING;
			}
			else if(board[h][w] == BORN_NEXT_TURN){
				(board[h][w]) = LIVING;
			}
		}
	}
}

int getFitness(int **board, int boardWidth, int boardHeight, int fitnessSpecifier){
	int sumFitness = 0;
	int h, w;
	for(h = 0; h < boardHeight; h++){
		for(w = 0; w < boardWidth; w++){
			if(board[h][w] == LIVING) sumFitness++;
		}
	}
	return sumFitness;
}

void test_CGoLBoardInitialized(struct CGoL *cgol){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_CGoLBoardInitialized\n\n");
	printBoard(cgol, 0);
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_PrintCGoLSimpleAttributes(struct CGoL *cgol){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_PrintCGoLSimpleAttributes\n\n");
	printf("currentStep: %d\n", (cgol -> currentStep));
	printf("maxStep: %d\n", (cgol -> maxStep));
	printf("boardWidth: %d\n", (cgol -> boardWidth));
	printf("boardHeight: %d\n", (cgol -> boardHeight));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}