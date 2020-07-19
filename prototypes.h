#include <stdio.h>
#include <string.h>#include <stdlib.h>

#define FILENAME ".\\contacts.bin"
#define TEMPFILE "tempfile"

//#define RED     "\x1b[31m"
//#define GREEN   "\x1b[32m"
//#define YELLOW  "\x1b[33m"
//#define BLUE    "\x1b[34m"
//#define MAGENTA "\x1b[35m"
//#define CYAN    "\x1b[36m"
//#define RESET   "\x1b[0m"
//#define WHITE   "\x1b[37m"

//#define LGRAY		"\x1b[90m"
//#define LRED		"\x1b[91m"	
//#define LGREEN	"\x1b[92m"	
//#define LYELLOW	"\x1b[93m"	
//#define LBLUE		"\x1b[94m"	
//#define LMAGENTA	"\x1b[95m"	
//#define LCYAN		"\x1b[96m"	
//#define LWHITE	"\x1b[97m"	


typedef struct mystruct {
	char name[25];
	char surname[25];
	char number[25];
	char address[25];
	char email[25];
	char zip[25];
} contact;

typedef enum mynumber { zero } number;

void askfordetails(contact*);
void add();
void searchEditDelete();
void list();
void nofitems();
void printThis(contact*);
void copyFile();
void sort();
void exportme();