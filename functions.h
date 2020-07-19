#include "prototypes.h"

/*Asking the user to fill in the contact information*/
void askfordetails(contact *newContact) {

	printf("\x1b[97m""First Name:");
	scanf("%25[^\n]s",  newContact->name);
	getchar();
	printf("Last Name:");
	scanf("%25[^\n]s",  newContact->surname);
	getchar();
	printf("Number:");
	scanf("%25[^\n]s",  newContact->number);
	getchar();
	printf("Address:");
	scanf("%25[^\n]s",  newContact->address);
	getchar();
	printf("ZIP:");
	scanf("%25[^\n]s" , newContact->zip);
	getchar();
	printf("Email:");
	scanf("%25[^\n]s",  newContact->email);
	printf("\x1b[0m");
	getchar();
}
//======================================================================================================

/*Add a contact*/
void add() {
	char choice;
	FILE *fp;
	fp = fopen(FILENAME, "ab");

	/*checking whether opening the file was unsuccessfull*/
	if ( fp== NULL) {
		fprintf(stderr, "ERROR opening " FILENAME);
		return 1;
	}

	do {
		system("cls");

		contact *newContact = (contact*)malloc(1 * sizeof(contact));

		askfordetails(newContact);

		fwrite(newContact, sizeof(contact), 1, fp);

		free(newContact);

		printf("Enter Y if you want to add again\nAnything else to exit...\n");

		scanf("%c", &choice);
		getchar();
	} while (choice=='Y' || choice=='y');
	system("cls");
	fclose(fp);

}
//======================================================================================================

/*Search+Edit+Delete*/
void searchEditDelete() {

	short selection;

	contact *Contact = (contact*)malloc(1 * sizeof(contact));

	FILE *fp = fopen(FILENAME, "r+b");

	if (fp == NULL) {
		fprintf(stderr, "ERROR opening " FILENAME);
		exit(1);
	}

	system("cls");

	puts("\x1b[95m""Search by:\n""\x1b[0m");
	printf( "\x1b[36m""1)" "\x1b[97m" " Name\n"     "\x1b[0m"
			"\x1b[36m""2)" "\x1b[97m" " Last Name\n""\x1b[0m"
			"\x1b[36m""3)" "\x1b[97m" " Number\n"   "\x1b[0m"
			"\x1b[36m""4)" "\x1b[97m" " Address\n"  "\x1b[0m"
			"\x1b[36m""5)" "\x1b[97m" " Email\n"    "\x1b[0m"
			"\x1b[36m""6)" "\x1b[97m" " ZIP\n"      "\x1b[0m"
			"\x1b[36m""7)" "\x1b[97m" " ALL\n"      "\x1b[0m"
			"\x1b[36m""0)" "\x1b[97m" " Exit\n"     "\x1b[0m");
	do {
		scanf("%hd", &selection);
		getchar();
		if (selection < 0 || selection >= 8)
			printf("\x1b[31m" "Wrong input, select again:\n""\x1b[0m");
	} while (selection < 0 || selection >= 8);
	
	system("cls");

	if (selection == 0) return;

	char search[25];//keyword to search

	printf("\x1b[95m""Enter keyword to search:\n""\x1b[0m");
	scanf("%25[^\n]s", search);
	getchar();

	short found=0;//number of contacts found by search
	contact *remember[20];//to remember the contact in case user wants to edit

		/*search by first name*/
		if (selection == 1) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->name) == 0)
				{
					printf("\x1b[96m" "#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found-1] = *Contact;
					printThis(Contact);
				}
			}		

		/*search by last name*/
		if (selection == 2) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->surname) == 0)
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found - 1] = *Contact;
					printThis(Contact);
				}
			}
		
		/*search by number*/
		if (selection == 3) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->number) == 0)
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found - 1] = *Contact;
					printThis(Contact);
				}
			}
		
		/*searh by address*/
		if (selection == 4) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->address) == 0)
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found - 1] = *Contact;
					printThis(Contact);
				}
			}		

		/*search by email*/
		if (selection == 5) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->email) == 0)
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found - 1] = *Contact;
					printThis(Contact);
				}
			}

		/*search by zip*/
		if (selection == 6) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (_stricmp(search, Contact->zip) == 0)
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found - 1] = *Contact;
					printThis(Contact);
				}
			}
		
		/*search by all*/
		if (selection == 7) 
			while (fread(Contact, sizeof(contact), 1, fp)) {
				if (!_stricmp(search, Contact->name)   || !_stricmp(search, Contact->surname) || 
					!_stricmp(search, Contact->number) || !_stricmp(search, Contact->address) ||
					!_stricmp(search, Contact->email)  || !_stricmp(search, Contact->zip))
				{
					printf("\x1b[96m""#%hd ""\x1b[0m", ++found);
					remember[found - 1] = malloc(sizeof(contact));
					*remember[found-1] = *Contact;
					printThis(Contact);
				}
			}
		
	printf("\x1b[92m" "%hd contact(s) found\n" "\x1b[0m", found);

//======================================================================================================

	/*proceed to options if the contact is found*/
	int option = 0;
	if (found) {
		printf("\x1b[95m""\nSelect an option:\n""\x1b[0m");
		printf("1) Edit  2) Delete  0) Menu\n");
		do {
			scanf("%d", &option);
			if (option > 2 || option < 0)
				printf("\x1b[31m" "Wrong input, select again:\n" "\x1b[0m");
			if (option == 0) {
				system("cls");
				return;
			}
		} while (option > 2 || option < 0);
	}
	else {
		fclose(fp);
		return;
	}

	fseek(fp, 0, SEEK_SET);

	/*editing*/
	contact editthis;//needed for edit + delete
	FILE *tempfile = fopen(TEMPFILE, "wb");//needed for edit + delete
	if (tempfile == NULL) {
		fprintf(stderr, "Error opening " FILENAME);
		exit(1);
	}
	if (option == 1) { 
		if(found==1) editthis = *remember[0];
		else {
			printf("\x1b[95m""Enter the # of the contact to edit:\n""\x1b[0m");
			short id;
			do {
				scanf("%hd", &id);
				if (id > found || id <= 0)
					printf("Please select a number till %d:\n", found);
			} while (id > found || id <= 0);

			editthis = *remember[id - 1];
		}
		/*copying all contacts to the temp file except the edit*/
		while (fread(Contact, sizeof(contact), 1, fp))
			if (strcmp(editthis.number, Contact->number)) 
				fwrite(Contact, sizeof(contact), 1, tempfile);

		//eladi
		printf("\x1b[95m""\nEdit:\n""\x1b[0m"
			"\x1b[36m""\n1)" "\x1b[97m" " Name\n""\x1b[0m"
			"\x1b[36m""2)" "\x1b[97m" " Last Name\n""\x1b[0m"
			"\x1b[36m""3)" "\x1b[97m" " Number\n""\x1b[0m"
			"\x1b[36m""4)" "\x1b[97m" " Address\n""\x1b[0m"
			"\x1b[36m""5)" "\x1b[97m" " ZIP\n""\x1b[0m"
			"\x1b[36m""6)" "\x1b[97m" " Email\n\n""\x1b[0m");

		short editwhat;
		do {
			scanf("%hd", &editwhat);

			if (editwhat > 6 || editwhat < 1)
				printf("\x1b[31m" "Wrong input, enter again:\n" "\x1b[0m");

		} while (editwhat > 6 || editwhat < 1);
		char newstr[25];

		switch (editwhat) {
		case 1:
			printf("\x1b[97m""Enter new name: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.name, newstr);
			break;
		case 2:
			printf("Enter new last name: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.surname, newstr);
			break;
		case 3:
			printf("Enter new number: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.number, newstr);
			break;
		case 4:
			printf("Enter new address: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.address, newstr);
			break;
		case 5:
			printf("Enter new zip: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.zip, newstr);
			break;
		case 6:
			printf("Enter new email: ");
			getchar();
			scanf("%25[^\n]s", newstr);
			strcpy(editthis.email, newstr);
			break;
		}

		fwrite(&editthis, sizeof(contact), 1, tempfile);

		system("cls");
		printf("\x1b[92m" "Contact was successfully edited\n" "\x1b[0m""\x1b[0m");

	}
//======================================================================================================

	/*Deleting a contact*/
	if (option == 2) {
		if (found == 1) editthis = *remember[0];
		else {
			printf("Enter the " "\x1b[36m" "#" "\x1b[0m" " of the contact to " "\x1b[31m" "delete" "\x1b[0m"":\n");
			short id;
			do {
				scanf("%hd", &id);
				if (id > found || id<1)
					printf("Please select a number till %d", found);
			} while (id > found || id < 1);
			editthis = *remember[id - 1];
		}
		/*copying all contacts to the temp file*/
		while (fread(Contact, sizeof(contact), 1, fp))
			if (strcmp(editthis.number, Contact->number))
				fwrite(Contact, sizeof(contact), 1, tempfile);

		system("cls");
		printf("\x1b[92m"	"Contact was successfully deleted\n""\x1b[0m");

	}
	number count=zero;
	for (; count < found; count++)
		free(remember[count]);

	free(Contact);
	fclose(tempfile);
	fclose(fp);
	copyFile();

}
//======================================================================================================

/*Listing all contacts*/
void list() {
	contact *cotactPointer = malloc(1 * sizeof(contact));
	FILE *fp = fopen(FILENAME, "rb");// <---
	if (fp == NULL) {
		fprintf(stderr, "ERROR opening " FILENAME);
		exit(1);
	}
	while (fread(cotactPointer, sizeof(contact), 1, fp)) {
		for (int i = 0; i < 30; printf("\x1b[93m" "=" "\x1b[0m"), i++);
		printf("\nName: %s\n"
			"Last Name: %s\n"
			"Number: %s\n"
			"Address: %s\n"
			"ZIP: %s\n"
			"Email: %s\n\n", cotactPointer->name, cotactPointer->surname, cotactPointer->number,
			cotactPointer->address, cotactPointer->zip, cotactPointer->email);
	}
	free(cotactPointer);
	fclose(fp);
}
//======================================================================================================

/*Show total number of contacts*/
void nofitems() {
	FILE *fp= fopen(FILENAME, "rb");
	if (fp == NULL) {
		fprintf(stderr, "ERROR opening " FILENAME);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	printf("Number of contacts: %.0lf\n", ftell(fp)*1.0/sizeof(contact));
	fclose(fp);
}
//======================================================================================================

/*Printing a contact*/
void printThis(contact * Contact) {
	for (int i = 0; i < 30; printf("\x1b[93m" "=" "\x1b[0m") , i++);
	printf("\nName: %s\n"
		"Last Name: %s\n"
		"Number: %s\n"
		"Address: %s\n"
		"ZIP: %s\n"
		"Email: %s\n\n", Contact->name, Contact->surname, Contact->number,
		Contact->address, Contact->zip, Contact->email);
}
//======================================================================================================

/*Copying contents of temp file to main file*/
void copyFile() {
	FILE *OriginalFile = fopen(TEMPFILE, "rb");
	FILE *CopiedFile = fopen(FILENAME, "wb");
	if (OriginalFile == NULL) {
		fprintf(stderr, "ERROR opening "TEMPFILE);
		exit(1);
	}
	if (CopiedFile == NULL) {
		fprintf(stderr, "ERROR creating "FILENAME);
		exit(1);
	}
	int gc;

	while ((gc = fgetc(OriginalFile)) != EOF)
		fputc(gc, CopiedFile);

	fclose(OriginalFile);
	fclose(CopiedFile);
	remove(TEMPFILE);
}
//======================================================================================================

/*Sorting contacs ascending or descending by member*/
void sort() {
	FILE* fp = fopen(FILENAME, "rb");
	if (fp == NULL) {
		fprintf(stderr,"ERROR opening "FILENAME);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	int N = ftell(fp)/sizeof(contact);

	fseek(fp, 0, SEEK_SET);

	contact **all = (contact**)malloc(N*sizeof(contact));

	int i = -1;
	do {
		i++;
		all[i] = malloc(sizeof(contact));

	} while (fread(all[i], sizeof(contact), 1, fp));

	//qsort(*all, N, sizeof(contact), compare);

	printf("\x1b[95m""Sort by:\n""\x1b[0m"
		"\x1b[36m""\n1)" "\x1b[97m" " Name\n""\x1b[0m"
		"\x1b[36m""2)" "\x1b[97m" " Last Name\n""\x1b[0m"
		"\x1b[36m""3)" "\x1b[97m" " Number\n""\x1b[0m"
		"\x1b[36m""4)" "\x1b[97m" " Address\n""\x1b[0m"
		"\x1b[36m""5)" "\x1b[97m" " ZIP\n""\x1b[0m"
		"\x1b[36m""6)" "\x1b[97m" " Email\n\n""\x1b[0m");


	short sortby;
	do {
		scanf("%hd", &sortby);

		if (sortby > 6 || sortby < 1)
			printf("\x1b[31m" "Wrong input, enter again:\n" "\x1b[0m");
	} while (sortby > 6 || sortby < 1);

	printf("Enter 1 for ascending and -1 for descending order\n");

	short asdec;
	do {
		scanf("%hd", &asdec);
		if (asdec !=1 && asdec !=-1)
			printf("\x1b[31m" "Wrong input, enter again:\n" "\x1b[0m");

	} while (asdec != 1 && asdec != -1);

	/*sort by name*/
	if(sortby==1)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++) 
				if(asdec*strcmp((*all[i]).name, (*all[j]).name) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	/*sort by last name*/
	if (sortby == 2)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if(asdec*strcmp((*all[i]).surname, (*all[j]).surname) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	/*sort by number*/
	if (sortby == 3)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if(asdec*strcmp((*all[i]).number, (*all[j]).number) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	/*sort by address*/
	if (sortby == 4)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if(asdec*strcmp((*all[i]).address, (*all[j]).address) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	/*sort by zip*/
	if (sortby == 5)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if(asdec*strcmp((*all[i]).zip, (*all[j]).zip) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	/*sort by email*/
	if (sortby == 6)
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j < N; j++)
				if(asdec*strcmp((*all[i]).email, (*all[j]).email) < 0) {
					contact temp = *all[i];
					*all[i] = *all[j];
					*all[j] = temp;
				}

	for (int i = 0; i < N ; i++)
		printThis(all[i]);

	for (int i = 0; i < N; i++)
		free(all[i]);

	free(all);
	fclose(fp);
}
//======================================================================================================

/*Export all contacts to export.txt file*/
void exportme() {
	FILE *fp = fopen(FILENAME, "rb");
	FILE *exportit = fopen("export.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "ERROR cannot open " FILENAME);
		exit(1);
	}

	if (exportit == NULL) {
		fprintf(stderr, "ERROR cannot create export.txt");
		exit(1);
	}

	contact* c=(contact*)malloc(1 * sizeof(contact));

	number count = zero;

	while (fread(c, sizeof(contact), 1, fp)) {
		fprintf(exportit, "Name: %s\n",c->name);
		fprintf(exportit, "Last name: %s\n", c->surname);
		fprintf(exportit, "Number: %s\n", c->number);
		fprintf(exportit, "Address: %s\n", c->address);
		fprintf(exportit, "Email: %s\n", c->email);
		fprintf(exportit, "ZIP: %s\n\n", c->zip);
		count++;
	}

	free(c);
	fclose(fp);
	fclose(exportit);
	printf("\x1b[92m" "%d" "\x1b[0m"" contact(s) were successfully exported\n",count);
}
//======================================================================================================
