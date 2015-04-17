//MyIO.c


void printSpacedCharLine(char character, int numberOfTimes){
	printf("\n");
	int i;
	for(i = 0; i < numberOfTimes; i++){
		printf("%c", character);
	}
	printf("\n");
}

int getPositiveIntInRange(int bufferSize, int min, int max){
	int result = -1;
	char *buffer = (char*)calloc(bufferSize, sizeof(char));

	fgets(buffer, bufferSize, stdin);
	int check = sscanf(buffer, "%d", &result);

	if(strlen(buffer) == (bufferSize-1) && buffer[bufferSize-2] != '\n'){
		result = INVALID_INPUT;
		while(getchar() != '\n');
	}
	
	//Checks for lack of integers
	if(check != VALID_INPUT)
		result = INVALID_INPUT;
	
	//Checks for a result out of range
	if(result < min || result > max)
		result = INVALID_INPUT;

	free(buffer);
	return result;
}

int getPositiveChangedIntInRange(int *currentValue, int bufferSize, int min, int max){
	int check;
	int result = getPositiveIntInRange(bufferSize, min, max);
	
	if(result == INVALID_INPUT || result == *currentValue){
		check = UNCHANGED;
	} else{
		*currentValue = result;
		check = CHANGED;
	}
	return check;
}

void requestNewValueForAttribute(char* attributeName, int currentValue, int min, int max){
	printf("\n%s is currently set to (%d)\n", attributeName, currentValue);
	printf("Enter a value in the range (%d-%d): ", min, max);
}