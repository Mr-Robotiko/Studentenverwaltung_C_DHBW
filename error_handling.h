#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Überprüft, ob der String nur gültige Zeichen (Buchstaben) enthält
int checkInputString(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i]) && input[i] != ' ' && input[i]!= '-') {
            return 1; // Ungültiger String
        }
    }
    return 0; // Gültiger String
}

int is18YearsOld(int intDay, int intMonth, int intYear) {
    // Hole das aktuelle Datum
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    // Berechne das Alter
    int age = currentDate.tm_year + 1900 - intYear;

    // Prüfe, ob der Geburtstag in diesem Jahr noch nicht war
    if (currentDate.tm_mon + 1 < intMonth || 
        (currentDate.tm_mon + 1 == intMonth && currentDate.tm_mday < intDay)) {
        age--;
    }

    // Rückgabe: 1, wenn die Person 18 Jahre oder älter ist, sonst 0
    return age >= 18;
}

int checkInputDate(char *day, char *month, char *year, int whichDate, char *compareday, char *comparemonth, char *compareyear) {
    int intDay = atoi(day);
    int intMonth = atoi(month);
    int intYear = atoi(year);



    if (whichDate == 0)
    {
       if (is18YearsOld(intDay, intMonth, intYear) == 0) {
            return 0; 
        }
    }
    
    // Überprüfe gültigen Bereich des Geburtsjahres
    if ((intYear < 1960 || intYear > 2024) && whichDate == 0) return 0;

    // Überprüfe gültigen Bereich des Startjahres
    if ((intYear < 1980 || intYear > 2024) && whichDate == 2) return 0;

   // Überprüfe gültigen Bereich des Endjahres
    if((intYear <=2024 || intYear >= 2028) && whichDate == 1) return 0;

    // Überprüfe gültigen Bereich des Monats
    if (intMonth < 1 || intMonth > 12) return 0;

    // Überprüfe gültigen Bereich des Tages
    if (intDay < 1) return 0;

    // Anzahl der Tage in den jeweiligen Monaten
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Berücksichtige Schaltjahr
    if ((intYear % 4 == 0 && intYear % 100 != 0) || (intYear % 400 == 0)) {
        daysInMonth[1] = 29; // Februar hat 29 Tage in Schaltjahren
    }

    // Überprüfe gültigen Bereich des Tages in Bezug auf den Monat
    if (intDay > daysInMonth[intMonth - 1]) return 0;

    //Überprüft Geburtsdatum < Startdatum

    if (whichDate == 2) {
    int compareDay = atoi(compareday);
    int compareMonth = atoi(comparemonth);
    int compareYear = atoi(compareyear);

     if (intYear < compareYear) {
        return 0;
    }
    if (intYear == compareYear) {
        if (intMonth < compareMonth) {
            return 0; 
        }
        if (intMonth == compareMonth) {
    
            if (intDay < compareDay) {
                return 0; 
            }
        }
    }
} 
    // Überprüft Startdatum < Enddatum
    if (whichDate == 1) {
    int compareDay = atoi(compareday);
    int compareMonth = atoi(comparemonth);
    int compareYear = atoi(compareyear);

    // Vergleiche Jahr, Monat und Tag für Enddatum vs. Startdatum
     if (intYear < compareYear) {
        return 0;
    }
    if (intYear == compareYear) {
        if (intMonth < compareMonth) {
            return 0; 
        }
        if (intMonth == compareMonth) {
    
            if (intDay < compareDay) {
                return 0; 
            }
        }
    }
} 


    return 1; // Datum ist gültig
}
