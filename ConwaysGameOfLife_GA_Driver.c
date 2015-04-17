//hammDrewFinalProj.c
#include "ProjectFilesHeaders.h"
#include "ProjectFilesSources.c"
time_t t;

int debugMode = 0;

void test_FileCharacterOutput(FILE *fp);
void test_FileNamesFromBaseFile(char *settingsFileName, char *seedFileName);
void test_StructValuesInitialized(struct Settings *settings, struct CGoL *cgol, struct GA *ga);

const int MAX_FILE_NAME = 100;
const int MAX_VIEW_WIDTH = 100;
const int MAX_VIEW_HEIGHT = 50;

const char defaultFileName[] = "Saved_Default.txt";


int main(int argc, char* argv[])
{
	//Random attribute
	srand((unsigned) time(&t));
	
	//File attributes
	FILE *fp;
	char *settingsFileName;
	char *seedFileName;
	
	
	//================================================================
	//Evaluate command line arguments and open the relevant file
	switch(argc){
		case 1:
			fp = fopen(defaultFileName, "r");
			break;
		case 2:
			fp = fopen(argv[1], "r");
			break;
		default:
			printf("Error in argument count\nUsage: %s <Saved_File>", argv[0]);
			printf("\nargc = %d", argc);
			exit(2);
	}
	//================================================================
	//Test the file for containing characters
	if(debugMode) test_FileCharacterOutput(fp);


	//================================================================
	//Read from the base file to get the names of the secondary files
	settingsFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	seedFileName = (char*)calloc(MAX_FILE_NAME, sizeof(char));
	fscanf(fp, "%s %s", settingsFileName, seedFileName);
	fclose(fp);
	//================================================================

	
	//================================================================
	//Ensure that the file names have valid lengths
	if((sizeof(settingsFileName) == 0 || sizeof(seedFileName) == 0)){
		printf("Invalid file input.");
        exit(2);
    } else if(sizeof(settingsFileName) == 50 || sizeof(seedFileName) == 50){
		printf("File names too large.");
        exit(2);
	}
	//================================================================
	//Test that the file names were read correctly
	if(debugMode) test_FileNamesFromBaseFile(settingsFileName, seedFileName);
	

	//================================================================
	//Intro Message
	printf("\nFile: \t%s\nTitle: \t%s\nBy: \t%s\nDate: \t%s\nClass: \t%s\n\n", argv[0], "Final Project", "Drew Hamm", "03/18/2015", "CS 133c");
	printf("This program is designed from Conway's Game of Life.(CGoL)\n");
	printf("In addition, a Genetic Algorithm(GA) is used to find optimal seeds.\n");
	printf("Options are provided to change the game environment as well as the behaviour of the GA.\n\n");
	
	printf("Hit enter to begin...\n");
	while(getchar() != '\n');
	//================================================================
	
	
	//================================================================
	//Create structs
	struct Settings settings;
	struct CGoL cgol;
	struct GA ga;
	
	//Open settings file
	fp = fopen(settingsFileName, "r");
	rewind(fp);
	


	//Initialize structs values
	//Settings
	fscanf (fp, "%d", &settings.viewWidth);
	fscanf (fp, "%d", &settings.viewHeight);
	strcpy(settings.settingsFileName, settingsFileName);
	strcpy(settings.seedFileName, seedFileName);
	//CGoL
	cgol.currentStep = 0;
	fscanf (fp, "%d", &cgol.maxStep);
	fscanf (fp, "%d", &cgol.boardWidth);
	fscanf (fp, "%d", &cgol.boardHeight);
	//GA
	ga.currentSolution = 0;
	fscanf (fp, "%d", &ga.maxSolution);
	fscanf (fp, "%d", &ga.solutionWidth);
	fscanf (fp, "%d", &ga.solutionHeight);
	ga.currentGeneration = 0;
	fscanf (fp, "%d", &ga.maxGeneration);
	fscanf (fp, "%d", &ga.mutationRate);
	fscanf (fp, "%d", &ga.fitnessSpecifier);
	fscanf (fp, "%d", &ga.selectionSpecifier);
	fscanf (fp, "%d", &ga.crossoverSpecifier);
	fclose(fp);
	


	printf("\nBefore initialize board\n");
	//Initialize cgol.board
	cgol.board = cgol_initializeBoard(cgol.boardWidth, cgol.boardHeight);
	
	printf("\nBefore initialize best seed\n");
	//Initialize ga.bestSolution
	ga.bestSolution.fitness = 0;
	ga.bestSolution = *ga_initializeBestSolution(ga.solutionWidth, ga.solutionHeight, settings.seedFileName);

	printf("\nBefore initialize pop\n");
	//Initialize ga.population
	ga.population = ga_initializePopulation(ga.maxSolution, ga.solutionWidth, ga.solutionHeight);
	

	//================================================================
	//Check if each struct was initialized correctly
	if(debugMode) {
		test_StructValuesInitialized(&settings, &cgol, &ga);
		test_CGoLBoardInitialized(&cgol);
		test_GASolutionsInitiallized(&ga);
	}
	
	//================================================================
	//For readability I moved this to Run.c
	//I have a new debugMode this function which is currently included in run.c
	run(&settings, &cgol, &ga);
	//================================================================
	
	
	
	//================================================================
	//Exit Message
	printf("\n\nThis concludes the program.\n");
	//================================================================
	
	
	//================================================================
	//File output
	//Not sure if I need this at this point...
	//================================================================
	return 0;
}

void test_FileCharacterOutput(FILE *fp){
	int c;
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileCharacterOutput\n\n");
	while(1){
		c = fgetc(fp);
		if(feof(fp)){
			break;
		}
		if(c != '\r') printf("[%c]", c);
   }
   printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
   rewind(fp);
}

void test_FileNamesFromBaseFile(char *settingsFileName, char *seedFileName){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_FileNamesFromBaseFile\n\n");
	printf("Settings File Name: \"%s\"\nSeed File Name: \"%s\"\n", settingsFileName, seedFileName);
	printf("strlen(settingsFileName): %d\nstrlen(seedFileName): %d", strlen(settingsFileName), strlen(seedFileName));
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}

void test_StructValuesInitialized(struct Settings *settings, struct CGoL *cgol, struct GA *ga){
	printSpacedCharLine(START_CHAR, TEST_LINE_MAX);
	printf("test_settingStructInit\n\n");
	printf("settingsFileName: %s", settings -> settingsFileName);
	printf("\nseedFileName: %s", settings -> seedFileName);
	printf("\nviewWidth: %d", settings -> viewWidth);
	printf("\nviewHeight: %d", settings -> viewHeight);
	
	printf("\n\ncurrentStep: %d", cgol -> currentStep);
	printf("\nmaxStep: %d", cgol -> maxStep);
	printf("\nboardWidth: %d", cgol -> boardWidth);
	printf("\nboardHeight: %d", cgol -> boardHeight);
	
	printf("\n\ncurrentSolution: %d", ga -> currentSolution);
	printf("\nmaxSolution: %d", ga -> maxSolution);
	printf("\nsolutionWidth: %d", ga -> solutionWidth);
	printf("\nsolutionHeight: %d", ga -> solutionHeight);
	printf("\ncurrentGeneration: %d", ga -> currentGeneration);
	printf("\nmaxGeneration: %d", ga -> maxGeneration);
	printf("\nmutationRate: %d", ga -> mutationRate);
	printf("\nfitnessSpecifier: %d", ga -> fitnessSpecifier);
	printf("\nselectionSpecifier: %d", ga -> selectionSpecifier);
	printf("\ncrossoverSpecifier: %d", ga -> crossoverSpecifier);
	printSpacedCharLine(END_CHAR, TEST_LINE_MAX);
}