#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Check leap year
int isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Days in month
int daysInMonth(int month, int year) {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    return 31;
}

// Day of week: 0 = Sunday
int dayOfWeek(int year, int month, int day) {
    static int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};
    if (month < 3) year -= 1;
    return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}

// Check special day
int isSpecial(int month, int day) {
    switch(month) {
        case 1: return (day == 1 || day == 26);
        case 2: return (day == 14);
        case 3: return (day == 8 || day == 22);
        case 4: return (day == 1 || day == 22);
        case 5: return (day == 1);
        case 6: return (day == 5 || day == 21);
        case 7: return (day == 4 || day == 29);
        case 8: return (day == 15 || day == 29);
        case 9: return (day == 5 || day == 15);
        case 10: return (day == 2 || day == 31);
        case 11: return (day == 14 || day == 30);
        case 12: return (day == 25 || day == 31);
    }
    return 0;
}

// Print special days
void printSpecialDays(int month) {
    printf("\nSpecial Days:\n");
    switch(month) {
        case 1:
            printf(" - \033[36mJan 1: New Year Day\033[0m\n");
            printf(" - \033[36mJan 26: Republic Day (India)\033[0m\n");
            break;
        case 2:
            printf(" - \033[36mFeb 14: Valentines Day\033[0m\n");
            break;
        case 3:
            printf(" - \033[36mMar 8: International Women’s Day\033[0m\n");
            printf(" - \033[36mMar 22: World Water Day\033[0m\n");
            break;
        case 4:
            printf(" - \033[36mApr 1: April Fools Day\033[0m\n");
            printf(" - \033[36mApr 22: Earth Day\033[0m\n");
            break;
        case 5:
            printf(" - \033[36mMay 1: International Labour Day\033[0m\n");
            printf(" - \033[36mMother’s Day (2nd Sunday)\033[0m\n");
            break;
        case 6:
            printf(" - \033[36mJun 5: World Environment Day\033[0m\n");
            printf(" - \033[36mJun 21: International Yoga Day\033[0m\n");
            break;
        case 7:
            printf(" - \033[36mJul 4: Doctors Day (India)\033[0m\n");
            printf(" - \033[36mJul 29: International Tiger Day\033[0m\n");
            break;
        case 8:
            printf(" - \033[36mAug 15: Independence Day (India)\033[0m\n");
            printf(" - \033[36mAug 29: National Sports Day\033[0m\n");
            break;
        case 9:
            printf(" - \033[36mSep 5: Teachers Day (India)\033[0m\n");
            printf(" - \033[36mSep 15: Engineers Day\033[0m\n");
            break;
        case 10:
            printf(" - \033[36mOct 2: Gandhi Jayanti (India)\033[0m\n");
            printf(" - \033[36mOct 31: National Unity Day\033[0m\n");
            break;
        case 11:
            printf(" - \033[36mNov 14: Childrens Day (India)\033[0m\n");
            printf(" - \033[36mNov 30: Computer Security Day\033[0m\n");
            break;
        case 12:
            printf(" - \033[36mDec 25: Christmas\033[0m\n");
            printf(" - \033[36mDec 31: New Years Eve\033[0m\n");
            break;
    }
}

// Strict Y/N input function with stay/leave
char getYesNoStayLeave() {
    char line[100];
    while (1) {
        if (!fgets(line, sizeof(line), stdin)) continue;
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strlen(line) == 1) {
            if (line[0] == 'y' || line[0] == 'Y') return 'y';
            if (line[0] == 'n' || line[0] == 'N') return 'n';
        }
        printf("Invalid choice! Enter only y or n: ");
    }
}

// Print calendar
void printCalendar(int month, int year) {
    const char *months[] = {"","January","February","March","April","May","June",
                            "July","August","September","October","November","December"};

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int today_day = tm.tm_mday;
    int today_month = tm.tm_mon + 1;
    int today_year = tm.tm_year + 1900;

    printf("\n     %s %d\n", months[month], year);
    printf(" Su Mo Tu We Th Fr Sa\n");

    int start = dayOfWeek(year, month, 1);
    int dim = daysInMonth(month, year);

    int i, day;
    for (i = 0; i < start; i++) printf("   ");

    for (day = 1; day <= dim; day++) {
        int weekDay = (start + day - 1) % 7;

        if (day == today_day && month == today_month && year == today_year)
            printf("\033[43;30m%3d\033[0m", day);  // Today = yellow background
        else if (weekDay == 0)
            printf("\033[31m%3d\033[0m", day);     // Sunday = red
        else if (isSpecial(month, day))
            printf("\033[36m%3d\033[0m", day);     // Special day = cyan
        else
            printf("%3d", day);

        if (weekDay == 6) printf("\n");
    }

    printf("\n");
    printSpecialDays(month);
    printf("\n");
}

// Main
int main() {
    int month, year;
    char line[100];
    char choice, leaveChoice;

    printf("Calendar Application With Special Days & Colors\n");
    printf("----------------------------------------------\n");

    while (1) {
        // Month input
        while (1) {
            printf("Enter month (1-12): ");
            if (!fgets(line, sizeof(line), stdin)) continue;
            if (sscanf(line, "%d", &month) != 1) {
                printf("Invalid input. Enter only numbers.\n");
                continue;
            }
            if (month >= 1 && month <= 12) break;

            printf("Invalid month! Do you want to try again? (y/n): ");
            choice = getYesNoStayLeave();
            if (choice == 'n') {
                printf("Do you want to leave or stay? (l/s): ");
                while (1) {
                    if (!fgets(line, sizeof(line), stdin)) continue;
                    line[strcspn(line, "\n")] = 0;
                    if (strlen(line) == 1) {
                        if (line[0] == 's' || line[0] == 'S') break; // stay
                        if (line[0] == 'l' || line[0] == 'L') {
                            printf("Are you sure you want to leave? (y/n): ");
                            leaveChoice = getYesNoStayLeave();
                            if (leaveChoice == 'y') { printf("Goodbye!\n"); return 0; }
                            else break; // stay
                        }
                    }
                    printf("Invalid choice! Enter l (leave) or s (stay): ");
                }
            }
        }

        // Year input
        while (1) {
            printf("Enter year (e.g., 2025): ");
            if (!fgets(line, sizeof(line), stdin)) continue;
            if (sscanf(line, "%d", &year) != 1) {
                printf("Invalid input. Enter only numbers.\n");
                continue;
            }
            break;
        }

        printCalendar(month, year);

        // Ask if user wants another month
        printf("Do you want to check another month? (y/n): ");
        choice = getYesNoStayLeave();
        if (choice == 'n') {
            printf("Do you want to leave or stay? (l/s): ");
            while (1) {
                if (!fgets(line, sizeof(line), stdin)) continue;
                line[strcspn(line, "\n")] = 0;
                if (strlen(line) == 1) {
                    if (line[0] == 's' || line[0] == 'S') break; // stay
                    if (line[0] == 'l' || line[0] == 'L') {
                        printf("Are you sure you want to leave? (y/n): ");
                        leaveChoice = getYesNoStayLeave();
                        if (leaveChoice == 'y') { printf("Goodbye!\n"); return 0; }
                        else break; // stay
                    }
                }
                printf("Invalid choice! Enter l (leave) or s (stay): ");
            }
        }
    }

    return 0;
}

