//ConwaysGameOfLife.h


struct CGoL{
	int currentStep;
	int maxStep;
	int boardWidth;
	int boardHeight;
	int **board;
};

int** cgol_initializeBoard(int boardWidth, int boardHeight);
void cgol_freeBoard(int **board, int boardHeight);
int changeBoardWidth(int *attribute);
int changeBoardHeight(int *attribute);
int changeMaxStep(int *attribute);
void printBoard(struct CGoL *cgol, int visabilityModifier);
void test_CGoLBoardInitialized(struct CGoL *cgol);
void test_PrintCGoLSimpleAttributes(struct CGoL *cgol);
void resetBoard(int **board, int boardWidth, int boardHeight);
int loadSeed(int **seed, int solutionWidth, int solutionHeight, int **board, int boardWidth, int boardHeight);
int getFutureState(int currentState, int sumLive);
int getFutureCenterState(int **board, int startH, int startW);
void setFutureBoardState(int **board, int boardWidth, int boardHeight);
void updateBoardState(int **board, int boardWidth, int boardHeight);
int getFitness(int **board, int boardWidth, int boardHeight, int fitnessSpecifier);