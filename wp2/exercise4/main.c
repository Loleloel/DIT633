// File: main.c

/*
wp2 - exercise 4
John Dickson, Oliver Hansson, Sebastian Vingård Larsson
2026-02-10
group: 27
Submission code: 450999
*/

#include <stdio.h> //scanf and printf
#include <string.h> //strcmp

typedef struct { // person structure
    char firstname[20]; // first name
    char famname[20]; // family name
    char pers_number[13]; // personal number
} PERSON; 

#define FILENAME "persons.bin"  // binary not text so we write raw structs

//function prototypes
PERSON input_record(void); // input a new record
void write_new_file(PERSON *inrecord); // write a new file
void printfile(void); // print the file
void search_by_firstname(char *name); // search by first name
void search_by_famname(char *name); // search by family name
void append_file(PERSON *inrecord); // append a record to the file

//------------------------------------------------------------------------------------------------

int main(void) 
{
    PERSON ppost; // current record
    int choice; // choice from the menu

    while (1) { // while the program is running
        printf("\n1. Create new file\n2. Add person\n3. Search\n4. Print all\n5. Exit\nChoice: "); // print the menu
        if (scanf("%d", &choice) != 1) { // if the input is not an integer
            while (getchar() != '\n');  // clear the bad input so we don't loop forever
            continue; // skip to the next iteration of the loop
        }

        switch (choice) { // switch statement to handle the choice
            case 1: { // create a new file
                PERSON dummy = {"", "", ""};  // assignment said first record is a dummy
                write_new_file(&dummy); // write the dummy record to the file
                puts("New file created.");
                break;
            }
            case 2: { // add a person
                FILE *check = fopen(FILENAME, "rb");
                if (!check) {
                    puts("The file doesn't exist.");
                    break;
                }
                fclose(check);
                ppost = input_record(); // input the record
                append_file(&ppost); // append the record to the file
                puts("Added.");
                break;
            }
            case 3: { // search for a person
                char name[20]; // name to search for
                int by_first; // search by first name or family name

                puts("Search by 1=first name 2=family name: "); // prompt the user to enter the search type
                scanf("%d", &by_first); // scan the search type
                puts("Name: ");
                scanf("%19s", name); // scan the name

                if (by_first == 1) // if the search type is first name
                    search_by_firstname(name); // search by first name
                else
                    search_by_famname(name); // search by family name
                break;
            }
            case 4: // print all records
                printfile(); // print all records
                break;
            case 5: // exit the program
                return 0; // return 0 to indicate success
            default: // invalid choice
                puts("Invalid choice.");
        }
    }
}


PERSON input_record(void) { // input a new record
    PERSON p; // current record
    puts("First name: "); // prompt the user to enter the first name
    scanf("%19s", p.firstname);  // 19 so we leave room for \0 in [20]
    puts("Family name: "); // prompt the user to enter the family name
    scanf("%19s", p.famname); // scan the family name
    puts("Pers number (yyyymmddnnnn): "); // prompt the user to enter the personal number
    scanf("%12s", p.pers_number);  // 12 for pers_number[13]
    return p; // return the record
}

void write_new_file(PERSON *inrecord) { // write a new file so
    FILE *file = fopen(FILENAME, "wb");  // wb overwrites any existing file
    if (!file) { // if the file does not exist
        puts("Could not create file.");
        return;
    }
    fwrite(inrecord, sizeof(PERSON), 1, file); // write the record to the file
    fclose(file); // close the file
}

void append_file(PERSON *inrecord) { // append a record to the file
    FILE *f = fopen(FILENAME, "ab");  // ab = append so we add to the end
    if (!f) { // if the file does not exist
        puts("Could not open file. Create it first (option 1).");
        return;
    }
    fwrite(inrecord, sizeof(PERSON), 1, f); // write the record to the file
    fclose(f); // close the file
}


void printfile(void) { // print all records 
    FILE *f = fopen(FILENAME, "rb"); // rb = read binary
    if (!f) { // if the file does not exist
        puts("File does not exist.");
        return;
    }
    PERSON p; // current record
    int count = 0; // counter for the records
    while (fread(&p, sizeof(PERSON), 1, f) == 1) { // read the record from the file
        if (p.firstname[0] == '\0' && p.famname[0] == '\0') // if the record is a dummy
            continue;  // skip the dummy record
        printf("%s %s %s\n", p.firstname, p.famname, p.pers_number); // print the record
        count++; // increment the counter
    }
    fclose(f); // close the file
    if (count == 0) // if there are no records
        puts("(empty)");
}

void search_by_firstname(char *name) { // search by first name
    FILE *f = fopen(FILENAME, "rb"); // rb = read binary
    if (!f) { // if the file does not exist
        puts("File does not exist.");
        return;
    }
    PERSON p; // current record
    int found = 0; // counter for the found records
    while (fread(&p, sizeof(PERSON), 1, f) == 1) { // read the record from the file
        int match = (strcmp(p.firstname, name) == 0);
        if (match) { // if the first name matches the search name
            printf("%s %s %s\n", p.firstname, p.famname, p.pers_number); // print the record
            found = 1; // set the found flag to 1
        }
    }
    fclose(f); // close the file
    if (!found) // if no matches were found
        puts("No match.");
}

void search_by_famname(char *name) { // search by family name
    FILE *f = fopen(FILENAME, "rb"); // rb = read binary
    if (!f) { // if the file does not exist
        puts("File does not exist.");
        return;
    }
    PERSON rec; // current record
    int found = 0; // counter for the found records
    while (fread(&rec, sizeof(PERSON), 1, f) == 1) { // read the record from the file
        if (strcmp(rec.famname, name) == 0) { // if the family name matches the search name
            printf("%s %s %s\n", rec.firstname, rec.famname, rec.pers_number); // print the record
            found = 1; // set the found flag to 1
        }
    }
    fclose(f); // close the file
    if (!found) // if no matches were found
        puts("No match.");
}


