#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    char day[2];
    char month[2];
    char year[4];
};

struct student
{
    char first_name[50];
    char last_name[50];
    char course[100];
    int student_number;
    struct Date birthday;
    struct Date start;
    struct Date end;
    struct student *previous;
    struct student *next;
};

struct student* findPrevForInsertion(struct student* sNew, struct student* s1)
{
    struct student *current; //= malloc(sizeof(student));
    
    if((current = malloc(sizeof(struct student))) == NULL) {
          fprintf(stderr,"Kein Speicherplatz fuer das letzte Element\n");
      }

    
    while (current->next != NULL) {
        // Wenn der Vorname alphabetisch zwischen `current` und `current->next` liegt     
        if(strcmp(current->next->first_name, sNew->first_name ) > 0 ) {
            return current; // Rueckgabe des Vorgaengers
        }
        current = current->next; // Weiter zum naechsten Knoten
    }

    return current;
}

int countStudents(struct student* s1)
{
    struct student *pointer = s1; 
    int counter = 1;
    while(pointer->next != NULL){
        counter += 1;
        pointer = pointer->next;
    }
    return counter;
}

/// @brief Generiert eine einzigartige achtstellige Matrikelnummer, die ab 10000001 aufzählt
/// @param s1 
/// @return next_student_number
int generateID(struct student* s1)
{
    struct student* ptr = s1;
    while(ptr->next != NULL)
    {
        if(ptr->next == NULL) return ptr->student_number += 1;
        else ptr = ptr->next;
    }
}

/// @brief Legt einen neuen Studenten an und fügt diesen in die verkettete Liste hinzu.
/// @param sNew 
void inputStudent(struct student* sNew)
{
    char first_name[50];
    char last_name[50];
    char course[100];
    char geburtstag[10];
    char startdatum[10];
    char enddatum[10];

    do{
        printf("### WELCOME TO DHBW MANNHEIM ###");
        printf("\nWie lautet der Vorname?: ");
        fgets(first_name, 50, stdin); //sNew->first_name
        //int first_name_ok = checkInputString(first_name);
        printf("\nWie lautet der Nachname?: ");
        fgets(last_name, 50, stdin); //sNew->last_name
        printf("\nWelches Studienfach wird belegt?: ");
        fgets(course, 100, stdin); //sNew->course
        printf("\nWie lautet das Geburtsdatum? Form:TT.MM.YYYY ");
        fgets(geburtstag, 10, stdin);
        //fscanf(geburtstag,"%2s.%2s.%4s", sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);
        printf("\nGeben Sie das Startdatum ein: ");
        fgets(startdatum, 10, stdin);
        //fscanf(startdatum,"%2s.%2s.%4s", sNew->start.day, sNew->start.month, sNew->start.year);
        printf("\nGeben Sie das Enddatum ein: ");
        fgets(enddatum, 10, stdin);
        //fscanf(enddatum,"%2s.%2s.%4s", sNew->end.day, sNew->end.month, sNew->end.year);
    } while(0);
}

int checkInputString(char *string){
    while (*string != '\0') {
        if (*string>=0 || *string<=9) return 0;
        else string++;
    }
    return 1;
}

/// @brief Fügt einen Studenten in die verketteten Liste hinzu
/// @param s1 
void addStudent(struct student* s1)
{
    struct student *sNew;
    inputStudent(sNew);

    // einfügen eines Studenten zur Liste
    //wenn Liste leer
    if(s1 == NULL){

        if((s1 = malloc(sizeof(struct student))) == NULL) {
         fprintf(stderr, "Kein Speicherplatz vorhanden für anfang\n");
         return;
        }
        
        sNew->student_number = 10000001;
        s1 = &sNew;
        s1->previous = NULL;
        s1->next = NULL; 
           
    }else{
        //wenn mind. ein Student in der Liste ist
        sNew->previous = findPrevForInsertion(sNew, s1); // sNew kriegt Vorgänger zugeordnet
        sNew->next = sNew->previous->next;   // sNew kriegt Nachfolger zugeordnet
        sNew->previous->next = sNew;         // der Vorgänger kriegt sNew als Nachfolger
        if (sNew->next != NULL)
        {
            sNew->next->previous = sNew;         // Der Nachfolger kriegt sNew als Vorgänger
        }
    }
}
void printStudent(int student_number, struct student* s1)
{
        // Print all information
        struct student *current = s1;
        

}

void printAllStudents(struct student *s1)
{
    // prints all students alphabetically
    for(; s1 != NULL; s1 = s1 -> next){
        printf("\nVorname: \t%50s", s1->first_name);
        printf("\nNachname: \t%50s", s1->last_name);
        printf("\nStudienfach: \t%50s", s1->course);
        printf("\nGeburtsdatum: \t%50s", s1->birthday);
        printf("\nStartdatum: \t%50s", s1->start);
        printf("\nEnddatum ein: \t%50s", s1->end);
    }
}

void deleteStudent(int student_number, struct student *s1)
{
    // Delete Student
    while (s1 != NULL) // Gehe Liste durch
    {
        if(s1->student_number == student_number) {
            s1->previous = s1->next; 
            free(s1); // Unsicher
            }// Wenn student_number identisch -> setze den prevoious zum next (löschen)
        else printf("Student wurde nicht gefunden");
        s1 = s1->next; 
    }
    
}

void interfaceSwitch(int choice){
    int student_number;
    switch (choice)
    {
    case 1:
        //addStudent();
        break;
    case 2:
        //printStudent()
        break;
    case 3:
        //printAllStudents();
        break;
    case 4:
        printf("Welchen Studenten wollen Sie loeschen? (Matrikelnummer): \t");
        scanf("%d", student_number);
        //deleteStudent(student_number);
        break;
    default:
        printf("Eingabe ist invalide. Bitte erneut eingeben!");
        break;
    }
}

void interface()
{
    int choice;
    printf("### WELCOME ###");
    do{
        printf("Studenten hinzufuegen\t<1>");
        printf("Bestimmten Studenten anzeigen\t<2>");
        printf("Alle Studenten anzeigen\t<3>");
        printf("Studenten loeschen\t<4>");
        scanf("%d", &choice);
        interfaceSwitch(choice);   
    }while(choice != 'x' || 'X');
}

int read() 
{
    FILE *spr = fopen("Studenten_saved.csv", "r");   // spr = student pointer read
    char buffer[255];

    if(spr == NULL) 
    {
        return 0; // Datei nicht gefunden, keine Fehlermeldung
    }

    else 
    {
        while(fgets(buffer, 255, spr) != NULL) 
        {
            printf("%s", buffer); // hier muss dann die Datei ausgelesen werden und in die Student pointer Liste integriert werden
        }
    }

    fclose(spr);
}

int save()             /* AUSGABE NUR ALS TEXT IM MOMENT */
{
    printf("### Bitte warten...\tProgramm wird beendet ###");

    FILE *sps = fopen("Studenten_saved.csv", "a"); /*Aktuell: Parameter a für Falls eine Datei mit dem angegebenen Namen nicht existiert, wird sie neu angelegt. Falls eine Datei mit dem angegebenen Namen existiert, wird der neue Inhalt am Ende der Datei angefügt.*/
    
    if (sps == NULL)    /*sps = student pointer save*/
    {  
        return 0;
    }

    else 
    { 
        fprintf(sps, "TEST1");
        printf("Datei wurde gespeichert!\n"); /* MUSS RAUS */
    }
    
    fclose(sps);
}   

int main()
{
    read();        
    struct student *s1 = NULL;
    interface();
    save();
    return 0;
}