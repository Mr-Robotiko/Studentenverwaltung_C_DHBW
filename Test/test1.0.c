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

struct student* findPrevForInsertion(struct student* sNew, struct student* s1) {
    struct student *current = s1;

    while (current->next != NULL) {
        if (strcmp(current->next->first_name, sNew->first_name) > 0) {
            return current;
        }
        current = current->next;
    }

    return current;
}

void inputStudent(struct student* sNew) {
    printf("----------------- <1> Studenten hinzufuegen <1> -----------------");
    printf("\nWie lautet der Vorname?: ");
    scanf("%49s", sNew->first_name);
    printf("\nWie lautet der Nachname?: ");
    scanf("%49s", sNew->last_name);
    printf("\nWelches Studienfach wird belegt?: ");
    scanf("%99s", sNew->course);
    printf("\nWie lautet das Geburtsdatum? (TT.MM.YYYY): ");
    scanf("%2s.%2s.%4s", sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);
    printf("\nGeben Sie das Startdatum ein (TT.MM.YYYY): ");
    scanf("%2s.%2s.%4s", sNew->start.day, sNew->start.month, sNew->start.year);
    printf("\nGeben Sie das Enddatum ein (TT.MM.YYYY): ");
    scanf("%2s.%2s.%4s", sNew->end.day, sNew->end.month, sNew->end.year);
    printf("\n***Neuen Studenten erfolgreich hinzugefuegt***\n");
}

/// @brief 
/// @param s1 
void addStudent(struct student** s1) {
    struct student *sNew = malloc(sizeof(struct student));
    if (sNew == NULL) {
        fprintf(stderr, "Kein Speicherplatz für neuen Studenten vorhanden!\n");
        return;
    }

    inputStudent(sNew);

    if (*s1 == NULL) {
        sNew->student_number = 10000001;
        sNew->previous = NULL;
        sNew->next = NULL;
        *s1 = sNew;
    } else {
        struct student *prev = findPrevForInsertion(sNew, *s1);
        sNew->next = prev->next;
        sNew->previous = prev;
        if (prev->next != NULL) {
            prev->next->previous = sNew;
        }
        prev->next = sNew;
    }
}

/// @brief Gibt alle Studenten der Liste alphabetisch aus
/// @param s1 
void printAllStudents(struct student *s1) {
    printf("---------------- <3> Alle Studenten anzeigen <3> ----------------");
    if(s1 == NULL)                          /* Gibt es überhaupt schon einen eingefügten Studenten?*/
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

int checkInputString(char *string) {
    while (*string != '\0') {
        if (*string >= '0' && *string <= '9') return 0;
        string++;
    }
    return 1;
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
        printf("-------------------- <4> Studenten loeschen <4> --------------------");
        printf("\nWelchen Studenten möchten Sie loeschen (Matrikelnummer): ");
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