#include "functions.h"

int main(int argc, char * argv[]) {

	int option;
	//printf("%d |%s|\n",argc, argv[1]);
	if (argc == 2) {

		if (!strcmp(argv[1], "add")) add();
		else if (!strcmp(argv[1], "list")) list();// ???
		else if (!strcmp(argv[1], "n")) nofitems();
		else if (!strcmp(argv[1], "help")) printf("add - add contact\n"
			"n - show number of contacts\n"
			"list - show all contacts\n"
			"help - get info\n");
		else printf("Wrong input, type help for info");
	}
	else if (argc > 2) printf("Wrong input, type help for info\n");
	else
		do {
			printf("\x1b[95m" "\nSelect an option:\n\n" "\x1b[0m");

			printf("\x1b[36m""1)" "\x1b[97m" " Add new contact\n""\x1b[0m"
				"\x1b[36m" "2)" "\x1b[97m" " Search\n""\x1b[0m"
				"\x1b[36m" "3)" "\x1b[97m" " List all\n""\x1b[0m"
				"\x1b[36m" "4)" "\x1b[97m" " NO of contacts\n""\x1b[0m"
				"\x1b[36m" "5)" "\x1b[97m" " Sort\n""\x1b[0m"
				"\x1b[36m" "6)" "\x1b[97m" " Export\n"
				"\x1b[36m" "0)" "\x1b[97m" " Exit\n\n");

			scanf("%d", &option);

			system("cls");

			switch (option) {
			case 0:
				printf("\x1b[90m""Exiting...""\x1b[0m");
				continue;
			case 1:
				getchar();
				add();
				break;

			case 2:
				searchEditDelete();
				break;

			case 3:
				list();
				break;

			case 4:
				nofitems();
				break;

			case 5:
				sort();
				break;
			case 6:
				exportme();
				break;

			default:
				printf("\x1b[31m""Wrong input\n""\x1b[0m");
			}
		} while (option != 0);
}

