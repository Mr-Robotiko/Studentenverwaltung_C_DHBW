#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date {
    char day[3]; 
    char month[3]; 
    char year[5];
};

struct student {
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
    struct student *current = s1;

    while (current->next != NULL) 
    {
        if (strcmp(current->next->first_name, sNew->first_name) > 0) 
        {
            return current;
        }
        current = current->next;
    }

    return current;
}

int checkInputString(char *string) 
{
    while (*string != '\0') {
        if (*string >= '0' && *string <= '9') return 1;
        string++;
    }
    return 0;
}
// Muss vervollständigt werde
int checkInputDate(char *day, char *month, char *year)
{
    int intDay = atoi(day);
    int intMont = atoi(month);
    int intYear = atoi(year);

    if((intDay > 0 && intDay <= 32) && (intMont > 0 && intMont <= 12) && (intYear > 1980 && intYear <= 2024)) return 1;
    else return 0;
}

void inputStudent(struct student* sNew) 
{
    int checkString = 0;
    int checkDate = 0;
    do{
        printf("----------------- <1> Studenten hinzufuegen <1> -----------------");
        printf("\nWie lautet der Vorname?: ");
        scanf("%49s", sNew->first_name);
        int checkFirstName = checkInputString(sNew->first_name);

        printf("\nWie lautet der Nachname?: ");
        scanf("%49s", sNew->last_name);
        int checkLastName = checkInputString(sNew->last_name);

        printf("\nWelches Studienfach wird belegt?: ");
        scanf("%99s", sNew->course);
        int checkCourse = checkInputString(sNew->course);

        printf("\nWie lautet das Geburtsdatum? (TT.MM.YYYY): ");
        scanf("%2s.%2s.%4s", sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);
        int chekBirthday = checkInputDate(sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);

        printf("\nGeben Sie das Startdatum ein (TT.MM.YYYY): ");
        scanf("%2s.%2s.%4s", sNew->start.day, sNew->start.month, sNew->start.year);
        int checkStart = checkInputDate(sNew->start.day, sNew->start.month, sNew->start.year);
        
        printf("\nGeben Sie das Enddatum ein (TT.MM.YYYY): ");
        scanf("%2s.%2s.%4s", sNew->end.day, sNew->end.month, sNew->end.year);
        int checkEnd = checkInputDate(sNew->end.day, sNew->end.month, sNew->end.year);

        checkString = checkFirstName || checkLastName || checkCourse; // Checkt, ob Nummern im String sind
        //checkDate = chekBirthday || checkStart || checkEnd; // Checkt, ob Datum in Eingabe ist
        if(checkString) printf("\n***Eingabe ungueltig***\n");
        else printf("\n***Neuen Studenten erfolgreich hinzugefuegt***\n"); 
        
    }while(checkString); // Neue Eingabe wenn nicht Valide
}

/// @brief Sucht die maximale Studentennummer und gibt sie zurück
/// @param s1 
/// @return next_student_number
int findMaxStudentNumber(struct student* s1)
{
    struct student* current = s1;
    int max = current->student_number;
    while(current->next != NULL)
    {
        if(current->student_number > max) max = current->student_number;
        current = current->next;
    } 
    if(current->next == NULL && current->student_number > max) max = current->student_number;
    return max;
}

/// @brief Fügt ein Student in die verkettete Liste ein
/// @param s1 
void addStudent(struct student** s1) {
    struct student *sNew = malloc(sizeof(struct student));
    if (sNew == NULL) 
    {
        fprintf(stderr, "\n***Kein Speicherplatz fuer neuen Studenten vorhanden***\n");
        return;
    }

    inputStudent(sNew);

    if (*s1 == NULL) 
    {
        sNew->student_number = 10000001;
        sNew->previous = NULL;
        sNew->next = NULL;
        *s1 = sNew;
    } else 
    {
        struct student *prev = findPrevForInsertion(sNew, *s1);
        sNew->next = prev->next;
        sNew->previous = prev;
        int max = findMaxStudentNumber(*s1);
        if (prev->next != NULL) 
        {
            prev->next->previous = sNew;
        }
        // Muss noch bearbeitet werden
        sNew->student_number = max +1;
        prev->next = sNew;
    }
}

/// @brief Gibt alle Studenten der Liste alphabetisch aus
/// @param s1 
void printAllStudents(struct student *s1) {
    printf("---------------- <3> Alle Studenten anzeigen <3> ----------------");
    if(s1 == NULL)                          /* Gibt es ueberhaupt schon einen eingefuegten Studenten?*/
    {
        printf("\n***Aktuell wurde noch kein Student hinzugefuegt***\n");
    }
    while (s1 != NULL) {

        printf("\nVorname:\t%s", s1->first_name);
        printf("\nNachname:\t%s", s1->last_name);
        printf("\nStudienfach:\t%s", s1->course);
        printf("\nGeburtsdatum:\t%s.%s.%s", s1->birthday.day, s1->birthday.month, s1->birthday.year);
        printf("\nStartdatum:\t%s.%s.%s", s1->start.day, s1->start.month, s1->start.year);
        printf("\nEnddatum:\t%s.%s.%s", s1->end.day, s1->end.month, s1->end.year);
        printf("\nMatrikelnummmer:%d",s1->student_number);
        if(s1->next == NULL)                    /* Leerzeile wird nach letztem Student geprintet*/
        {
            printf("\n");
        }
        if(s1->next != NULL)                            /* Wenn nur ein Student vorhanden ist, wird diese Linie nicht ausgegeben, sie ist nur Trenner zw. Student x und Student x+1*/
        {
        printf("\n---------------------------");
        }
        else{
            break;
        }

        s1 = s1->next;
    
    }
}

void interfaceSwitch(int choice, struct student **s1) {
    int student_number;

    switch (choice) {
    case '1':
        addStudent(s1);
        break;
    case '2':
        //printStudent()
        break;
    case '3':
        printAllStudents(*s1);
        break;
    case '4':
        printf("------------------- <4> Studenten loeschen <4> -------------------");
        printf("\nWelchen Studenten moechten Sie loeschen (Matrikelnummer): ");
        scanf("%d", &student_number);
        //deleteStudent(student_number, s1);
        printf("\n***Studenten erfolgreich aus dem System geloescht***\n");
        break;
    case 'x':
        printf("\n---------- <x> Programm wird beendet. Bitte warten. <x> ----------\n");
        break;
    case 'X': 
        printf("\n---------- <X> Programm wird beendet. Bitte warten. <X> ----------\n");
        break;
    default:
        printf("\n-------- <?> Eingabe ungueltig. Auswahl bitte erneut. <?> -------\n");
        break;
    }
}

void interface(struct student **s1) {
    char choice;
    
    while (choice != 'x' && choice != 'X'){
        printf("\n------------------------ Aktions-Auswahl ------------------------");
        printf("\n                          Zum Beenden: X                         \n");
        printf("\nStudenten hinzufuegen <1>\t");
        printf("Bestimmten Studenten anzeigen <2>\t\n");
        printf("\nAlle Studenten anzeigen <3>\t");
        printf("Studenten loeschen <4>\t\n");
        printf("\nIhre Auswahl: ");
        scanf(" %c", &choice);
        interfaceSwitch(choice, s1);
    }
}

int main() {
    struct student *s1 = NULL;
    interface(&s1);
    return 0;
}