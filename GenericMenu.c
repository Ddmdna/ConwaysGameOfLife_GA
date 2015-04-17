//GenericMenu.c


void outputMenu(struct Menu *menu){
	int i;
	printf("\n%s", menu -> menuName);
	for(i = 0; i < menu -> numberOfFunctions; i++){
		printf("\n(%d): %s", i, menu -> functionDescriptions[i]);
	}
	printf("\nSelection a function between (0-%d): ", menu -> numberOfFunctions -1);
}