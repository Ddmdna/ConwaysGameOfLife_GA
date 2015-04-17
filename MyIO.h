//MyIO.h


void printSpacedCharLine(char character, int numberOfTimes);
int getPositiveIntInRange(int bufferSize, int min, int max);
int getPositiveChangedIntInRange(int *currentValue, int bufferSize, int min, int max);
void requestNewValueForAttribute(char* attributeName, int currentValue, int min, int max);