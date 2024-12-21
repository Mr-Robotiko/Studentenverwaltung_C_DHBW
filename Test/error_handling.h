#include <ctype.h>

// Überprüft, ob der String nur gültige Zeichen (Buchstaben) enthält
int checkInputString(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i])) {
            return 1; // Ungültiger String
        }
    }
    return 0; // Gültiger String
}

int checkInputDate(char *day, char *month, char *year, int endDate) {
    int intDay = atoi(day);
    int intMonth = atoi(month);
    int intYear = atoi(year);

    // Überprüfe gültigen Bereich des Jahres
    if ((intYear < 1980 || intYear > 2024) && endDate == 0) return 0;

    // Überprüft Enddatum
    if((intYear <=2024 || intYear >= 2028) && endDate == 1) return 0;

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

    return 1; // Datum ist gültig
}
