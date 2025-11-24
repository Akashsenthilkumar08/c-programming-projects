#include <stdio.h>

int main() {
    int month, year;
    int day, i, j;

    char *months[] = {
        "January",
		 "February",
		  "March",
		   "April", 
		   "May",
		    "June",
        "July",
		 "August",
		  "September",
		   "October", 
		   "November",
		    "December"
    };

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("Enter month (1-12): ");
    scanf("%d", &month);

    printf("Enter year: ");
    scanf("%d", &year);

    if (month < 1 || month > 12) {
        printf("Invalid month!\n");
    }

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        days[1] = 29;
    else
        days[1] = 28;

    printf("\n ------------ %s %d ------------\n", months[month-1], year);

    for (i = 0; i < day; i++) {
        printf("   ");
    }


    for (j = 1; j <= days[month - 1]; j++) {

        if (day == 0)
            printf("\033[31m%4d\033[0m ", j); 
        else
            printf("%4d ", j);

        day++;

        if (day > 6) {
            day = 0;
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}

