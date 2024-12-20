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