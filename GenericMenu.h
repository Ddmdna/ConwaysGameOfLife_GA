//GenericMenu.h


struct Menu{
	int numberOfFunctions;
	char *menuName;
	char **functionDescriptions;
};

void outputMenu(struct Menu *menu);