#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_handling.h" // Selbstgeschriebene Headerfile -> Muss mit geliefert werden

/// @brief Datenstruktur für Startdatum, Enddatum und Geburtsdatum
struct Date {
    char day[3]; 
    char month[3]; 
    char year[5];
};

/// @brief Studentenstruktur mit einer doppelt verketteten Liste (prevoius ,next)
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

/// @brief Sucht den Prevoius Student um ihn alphabetisch in die Liste zu sortieren
struct student* findPrevForInsertion(struct student* sNew, struct student* s1) 
{    
    struct student *current = s1;
    if (strcmp(current->first_name, sNew->first_name) > 0) 
    {
        return NULL;
    }

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

/// @brief Zählt die Anzahl an vorhandenen Studenten in der Liste
/// @param s1 
/// @return Anzahl der Sudenten 
int countStudents(struct student *s1) {
    int count = 0;
    struct student *current = s1;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;  
}

/// @brief Öffnet ein Formular für die Eingabe der Studenteninformationen. Durch Q wird das Formular geschlosssen
/// @param sNew 
/// @return 
int inputStudent(struct student* sNew) {
    int checkString = 0; // Validierung der Stringeingaben
    int checkDate = 0; // Validierung der Datumseingaben
    int whichDate = 0; // Validierung der Datumslogik

    // Eingabeaufforderung für den Benutzer
    printf("----------------- <1> Studenten hinzufuegen <1> -----------------");

    int c; //Buffer clearen
    while ((c = getchar()) != '\n' && c != EOF);

    // Vorname
    do {
        printf("\n(Zum Abbrechen: q)\nWie lautet der Vorname?: ");

        fgets(sNew->first_name, sizeof(sNew->first_name), stdin);
        sNew->first_name[strcspn(sNew->first_name, "\n")] = '\0';
        sNew->first_name[0] = toupper(sNew->first_name[0]);
        if (strcmp(sNew->first_name, "Q") == 0) {
            return 0;
        }
        checkString = checkInputString(sNew->first_name);
        if (checkString) {
            printf("\n***Eingabe ungueltig: Es sind nur Buchstaben und keine Sonderzeichen erlaubt***\n");
        }
    } while (checkString);  

    // Nachname
    do {
        printf("\n(Zum Abbrechen: q)\nWie lautet der Nachname?: ");
        fgets(sNew->last_name, sizeof(sNew->last_name), stdin);
        sNew->last_name[0] = toupper(sNew->last_name[0]);
        sNew->last_name[strcspn(sNew->last_name, "\n")] = '\0';
        if (strcmp(sNew->last_name, "Q") == 0) {
            return 0;
        }
        checkString = checkInputString(sNew->last_name);
        if (checkString) {
            printf("\n***Eingabe ungueltig: Es sind nur Buchstaben und keine Sonderzeichen erlaubt***\n");
        }
    } while (checkString);  

    // Studiengang
    do {
        printf("\n(Zum Abbrechen: q)\nWelches Studienfach wird belegt?: ");
        fgets(sNew->course, sizeof(sNew->course), stdin);
        sNew->course[0] = toupper(sNew->course[0]);
        sNew->course[strcspn(sNew->course, "\n")] = '\0';
        if (strcmp(sNew->course, "Q") == 0) {
            return 0;
        }
        checkString = checkInputString(sNew->course);
        if (checkString) {
            printf("\n***Eingabe ungueltig: Es sind nur Buchstaben und keine Sonderzeichen erlaubt***\n");
        }
    } while (checkString);  

    // Geburtsdatum
    do {
        printf("\n(Zum Abbrechen: q)\nWie lautet das Geburtsdatum? (TT.MM.JJJJ): ");
        scanf("%2s.%2s.%4s", sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);
        if (strcmp(sNew->birthday.day, "q") == 0) {
            return 0;
        }
        checkDate = checkInputDate(sNew->birthday.day, sNew->birthday.month, sNew->birthday.year, whichDate, NULL, NULL, NULL);
        if (checkDate == 0) {
            printf("\n***Geburtsdatum ist ungueltig***\n");
        }
    } while (checkDate == 0); 

    // Startdatum
    whichDate = 2;
    do {
        printf("\n(Zum Abbrechen: q)\nGeben Sie das Startdatum ein (TT.MM.JJJJ): ");
        scanf("%2s.%2s.%4s", sNew->start.day, sNew->start.month, sNew->start.year);
        if (strcmp(sNew->start.day, "q") == 0) {
            return 0;  //Hab abbruch mittendrin eingebaut
        }
        checkDate = checkInputDate(sNew->start.day, sNew->start.month, sNew->start.year, whichDate, sNew->birthday.day, sNew->birthday.month, sNew->birthday.year);
        if (checkDate == 0) {
            printf("\n***Startdatum ist ungueltig***\n");
        }
    } while (checkDate == 0);  

    // Enddatum
    whichDate = 1;
    do {
        printf("\n(Zum Abbrechen: q)\nGeben Sie das Enddatum ein (TT.MM.JJJJ): ");
        scanf("%2s.%2s.%4s", sNew->end.day, sNew->end.month, sNew->end.year);
        if (strcmp(sNew->end.day, "q") == 0) {
            return 0;
        }
        checkDate = checkInputDate(sNew->end.day, sNew->end.month, sNew->end.year, whichDate, sNew->start.day, sNew->start.month, sNew->start.year);
        if (checkDate == 0) {
            printf("\n***Enddatum ist ungueltig***\n");
        }
    } while (checkDate == 0); 

    printf("\n***Neuen Studenten erfolgreich hinzugefuegt***\n");
    return 1;
}


/// @brief Sucht die maximale Studentennummer und gibt sie zurück
/// @param s1 
/// @return maximale Studentennummer
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

/// @brief Löscht einen Studenten auf Basis seiner generierten Matrikelnummer. 
/// @param student_number 
/// @param s1 
void deleteStudent(int student_number, struct student **s1) {
    struct student *current = *s1;

    // Die Liste ist leer
    if (current == NULL) {
        printf("\n***Keine Studenten in der Liste***\n");
        return;
    }

    while (current != NULL) {
        if (current->student_number == student_number) {
            // Das löschende Element ist Kopf der Liste
            if (current == *s1) {
                *s1 = current->next;
                if (*s1 != NULL) {
                    (*s1)->previous = NULL;
                }
            // Das löschende Element ist am Ende oder in der Mitte der Liste
            } else {
                if (current->previous != NULL) {
                    current->previous->next = current->next;
                }
                if (current->next != NULL) {
                    current->next->previous = current->previous;
                }
            }
            free(current);
            printf("\n***Studenten erfolgreich geloescht***\n");
            return;
        }
        current = current->next;
    }
    printf("\n***Matrikelnummer nicht gefunden***\n");
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

    if (inputStudent(sNew) == 0) {
        printf("\n***Eingabe wurde vom Benutzer abgebrochen, daher wurde kein Student hinzugefuegt***\n");
        free(sNew);  // Input abgebrochen
        return; 
    }
    

    if (*s1 == NULL) 
    {
        sNew->student_number = 10000001;
        sNew->previous = NULL;
        sNew->next = NULL;
        *s1 = sNew;
    } else 
    {
       struct student *prev = findPrevForInsertion(sNew, *s1);
if (prev == NULL) 
{
    // Neuer Student wird zum neuen Kopf der Liste
    sNew->next = *s1; 
    sNew->previous = NULL; 

    
    (*s1)->previous = sNew; 
    *s1 = sNew; // s1 bleibt der Kopf de Liste
} 
else 
{
    // Neuer Student wird in die Liste eingefügt (nicht am Anfang)
    sNew->next = prev->next;
    sNew->previous = prev;

    if (prev->next != NULL) 
    {
        prev->next->previous = sNew; 
    }

    prev->next = sNew; 
}

int max = findMaxStudentNumber(*s1);

if (sNew->student_number == 99999999)
{
    free(sNew);
    printf("***Das System ist voll, neuer Student konnte nicht gespeichert werden***");
    return;
}else sNew->student_number = max + 1; // Matrikelnummer um 1 erhöhen

    }
}

/// @brief Gibt alle Studenten der Liste alphabetisch aus
/// @param s1 
void printAllStudents(struct student *s1) {
    printf("---------------- <3> Alle Studenten anzeigen <3> ----------------");
    if(s1 == NULL) // Wenn die Liste leer ist
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
        printf("\nMatrikelnr.:\t%d",s1->student_number);
        if(s1->next == NULL)  /* Leerzeile wird nach letztem Student geprintet*/
        {
            printf("\n");
        }
        if(s1->next != NULL)   /* Wenn nur ein Student vorhanden ist, wird diese Linie nicht ausgegeben, sie ist nur Trenner zw. Student x und Student x+1*/
        {
        printf("\n---------------------------");
        }
        else{
            break;
        }

        s1 = s1->next;
    
    }
}

/// @brief Printlayout für die Ausgabe eines einzelnen Studenten
/// @param s1 
void printSingleStudentInformation(struct student *s1){
    printf("\nVorname:\t%s", s1->first_name);
    printf("\nNachname:\t%s", s1->last_name);
    printf("\nStudienfach:\t%s", s1->course);
    printf("\nGeburtsdatum:\t%s.%s.%s", s1->birthday.day, s1->birthday.month, s1->birthday.year);
    printf("\nStartdatum:\t%s.%s.%s", s1->start.day, s1->start.month, s1->start.year);
    printf("\nEnddatum:\t%s.%s.%s", s1->end.day, s1->end.month, s1->end.year);
    printf("\nMatrikelnr.:\t%d",s1->student_number);
}

/// @brief Gibt die Information eines einzelnen Studenten auf Baiss seiner Matrikrlnummer wieder
/// @param student_number 
/// @param s1 
void printStudent(int student_number, struct student* s1)
{
    int found = 0; // Wenn Student nicht gefunden
    struct student* current = s1;

    // Liste ist leet
    if (current == NULL) {
        printf("\n***Keine Studenten in der Liste***\n");
        return;
    }
    
    if(current->student_number == student_number) {
        printSingleStudentInformation(s1);
        found = 1;
    }

    while(current->next != NULL){
        if(current->next->student_number == student_number) {
            printSingleStudentInformation(current->next);
            found = 1;
        };
        current = current->next;
    }
    if(found == 0) printf("\n***Matrikelnummer nicht gefunden***\n");
}

/// @brief Die Interfacelogik zusammen mit dem Interface der Menüpunkte
/// @param choice 
/// @param s1 
void interfaceSwitch(int choice, struct student **s1) {
    int student_number = 0;

    switch (choice) {
    case '1':
        addStudent(s1);
        break;
    case '2':
        printf("------------------- <2> Studenten anzeigen <2> -------------------");
        printf("\nWelchen Studenten moechten Sie angezeigt bekommen? (Matrikelnummer): ");
        scanf("%d", &student_number);
        printStudent(student_number, *s1);
        break;
    case '3':
        printAllStudents(*s1);
        break;
    case '4':
        printf("------------------- <4> Studenten loeschen <4> -------------------");
        printf("\nWelchen Studenten moechten Sie loeschen? (Matrikelnummer): ");
        scanf("%d", &student_number);
        deleteStudent(student_number, s1);
        break;
     case '5': 
        printf("--------------- <5> Anzahl aktueller Studenten <5> ---------------");
        printf("\nAktuell gespeicherte Studenten: %d\n", countStudents(*s1));
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

/// @brief Ausgebe des Interfaces 
/// @param choice 
/// @param s1 
void interface(struct student **s1) {
    char choice;
    
    while (choice != 'x' && choice != 'X'){
        printf("\n------------------------ Aktions-Auswahl ------------------------");
        printf("\n                          Zum Beenden: X                         \n");
        printf("\nStudenten hinzufuegen <1>\t");
        printf("Bestimmten Studenten anzeigen <2>\t\n");
        printf("\nAlle Studenten anzeigen <3>\t");
        printf("Studenten loeschen <4>\t\n");
        printf("\nAnzahl der Studenten anzeigen <5>\n");
        printf("\nIhre Auswahl: ");
        scanf(" %c", &choice);
        interfaceSwitch(choice, s1);
    }
}

/// @brief Sichert die Element der Liste in einer CSV Datei
/// @param s1 
void save(struct student *s1) {
    FILE *file = fopen("students.csv", "w");
    
    if (file == NULL) {
        return;
    }
    

    fprintf(file, "Matrikelnummer,Vorname,Nachname,Studienfach,Geburtsdatum,Startdatum,Enddatum\n");
    

    while (s1 != NULL) {
        fprintf(file, "%d;%s;%s;%s;%s.%s.%s;%s.%s.%s;%s.%s.%s\n",
                s1->student_number,
                s1->first_name,
                s1->last_name,
                s1->course,
                s1->birthday.day, s1->birthday.month, s1->birthday.year,
                s1->start.day, s1->start.month, s1->start.year,
                s1->end.day, s1->end.month, s1->end.year);
        s1 = s1->next;
    }
    
    fclose(file);
}

/// @brief Liest die Element der CSV Datei und schreibt sie in die Liste
/// @param s1 
void read(struct student **s1) {
    FILE *file = fopen("students.csv", "r");
    if (file == NULL) return; 

    char line[256];
    
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        struct student *sNew = malloc(sizeof(struct student));
        if (sNew == NULL) { fclose(file); return; } // Speicherprobleme, Abbruch

        // Sieht schwer aus aber Trennt nur den String am ";" auf und begrenzt die Anzahl wieviel einglesen wird 
        sscanf(line, "%d;%49[^;];%49[^;];%99[^;];%2[^.].%2[^.].%4[^;];%2[^.].%2[^.].%4[^;];%2[^.].%2[^.].%4[^\n]",
               &sNew->student_number,
               sNew->first_name, sNew->last_name, sNew->course,
               sNew->birthday.day, sNew->birthday.month, sNew->birthday.year,
               sNew->start.day, sNew->start.month, sNew->start.year,
               sNew->end.day, sNew->end.month, sNew->end.year);

 
        sNew->next = NULL;
        sNew->previous = NULL;

        // In Liste einfügen
          if (*s1 == NULL) {
            *s1 = sNew;
        } else {
            // Student hinten einfügen, da alles sortiert in CSV
            struct student *current = *s1;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = sNew;
            sNew->previous = current;
        }
    }

    fclose(file);
}

/// @brief Befreit den Speicherplatz von allen Studenten
/// @param s1 
void freeAllStudents(struct student *s1) {
    while (s1 != NULL) {
        struct student *temp = s1;
        s1 = s1->next;
        free(temp);
    }
}

int main() {
    struct student *s1 = NULL;
    read(&s1); // Alle studenten spawnen
    interface(&s1);
    save(s1); //schnell speichern nicht das unsere schönen Studenten verloren gehen
    freeAllStudents(s1);
    return 0;
}
