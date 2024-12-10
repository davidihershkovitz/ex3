/******************
Name: Davidi Hershkovitz
ID: 214165417
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};

// Clear the buffer
void clearInputBuffer() {
    // Use scanf to discard the rest of the line until a newline
    scanf("%*[^\n]"); // Discards everything up to the newline
    scanf("%*c");     // Discards the newline character itself
}


// Initialize the cube to -1
void initializeCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                cube[day][brand][type] = -1;
            }
        }
    }
}

// Function that will receive data from the user for each day
void enterDataForBrandDaily(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int brand;

    if (scanf("%d", &brand) != 1) {
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    if (brand < 0 || brand >= NUM_OF_BRANDS) {
        return;
    }
    if (days[brand] >= DAYS_IN_YEAR) {
        return;
    }

    for (int type = 0; type < NUM_OF_TYPES; type++) {
        if (scanf("%d", &cube[days[brand]][brand][type]) != 1) {
            clearInputBuffer();
            return;
        }
    }
    clearInputBuffer();
    days[brand]++;

    printf("Data entered successfully for brand %s.\n", brands[brand]);
}

// Populate the day of sales for all brands
void populateDayOfSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int completedBrands[NUM_OF_BRANDS] = {0};

    while (1) {
        int remaining = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (days[i] < DAYS_IN_YEAR && !completedBrands[i]) {
                remaining = 1;
                break;
            }
        }
        if (!remaining) break;

        int brand;
        if (scanf("%d", &brand) != 1) {
            clearInputBuffer();
            continue;
        }

        if (brand < 0 || brand >= NUM_OF_BRANDS || completedBrands[brand] || days[brand] >= DAYS_IN_YEAR) {
            clearInputBuffer();
            continue;
        }

        for (int type = 0; type < NUM_OF_TYPES; type++) {
            if (scanf("%d", &cube[days[brand]][brand][type]) != 1) {
                clearInputBuffer();
                break;
            }
        }
        clearInputBuffer();
        completedBrands[brand] = 1;
    }

    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (days[i] < DAYS_IN_YEAR) {
            days[i]++;
        }
    }
}

// Function to print the name by index
void printNameByIndex(const char names[][15], int index, int size) {
    if (index >= 0 && index < size) {
        printf("%s", names[index]);
    }
}

// Provide daily stats for a specific day
void provideDailyStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int day;

    while (1) {
        if (scanf("%d", &day) == 1 && day > 0 && day <= DAYS_IN_YEAR) {
            int hasData = 0;
            for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
                if (days[brand] >= day && cube[day-1][brand][0] != -1) {
                    hasData = 1;
                    break;
                }
            }

            if (!hasData) {
                clearInputBuffer();
                continue;
            }

            int totalSales = 0;
            int brandSales[NUM_OF_BRANDS] = {0};
            int typeSales[NUM_OF_TYPES] = {0};

            for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
                for (int type = 0; type < NUM_OF_TYPES; type++) {
                    if (cube[day-1][brand][type] != -1) {
                        int sales = cube[day-1][brand][type];
                        totalSales += sales;
                        brandSales[brand] += sales;
                        typeSales[type] += sales;
                    }
                }
            }

            int maxBrandSales = 0, maxTypeSales = 0;
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                if (brandSales[i] > maxBrandSales) {
                    maxBrandSales = brandSales[i];
                }
            }
            for (int i = 0; i < NUM_OF_TYPES; i++) {
                if (typeSales[i] > maxTypeSales) {
                    maxTypeSales = typeSales[i];
                }
            }

            printf("In day number %d:\n", day);
            printf("The sales total was %d\n", totalSales);
            printf("The best sold brand with %d sales was ", maxBrandSales);
            for (int i = 0; i < NUM_OF_BRANDS; i++) {
                if (brandSales[i] == maxBrandSales) {
                    printf("%s ", brands[i]);
                }
            }
            printf("\n");

            printf("The best sold type with %d sales was ", maxTypeSales);
            for (int i = 0; i < NUM_OF_TYPES; i++) {
                if (typeSales[i] == maxTypeSales) {
                    printf("%s ", types[i]);
                }
            }
            printf("\n");

            break;
        } else {
            clearInputBuffer();
        }
    }
}

// Function to print all sales data for all days in the desired format
void printAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    printf("*****************************************\n");

    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf("Sales for %s:\n", brands[brand]);

        for (int day = 0; day < days[brand]; day++) {
            if (cube[day][brand][0] != -1) {
                printf("Day %d- ", day + 1);
                for (int type = 0; type < NUM_OF_TYPES; type++) {
                    printf("%s: %d ", types[type], cube[day][brand][type]);
                }
                printf("\n");
            } else {
                printf("Day %d- SUV: 0 Sedan: 0 Coupe: 0 GT: 0\n", day + 1);
            }
        }
    }

    printf("*****************************************\n");
}

void provideOverallInsights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int totalSalesForBrand[NUM_OF_BRANDS] = {0};
    int totalSalesForType[NUM_OF_TYPES] = {0};
    int totalSalesPerDay[DAYS_IN_YEAR] = {0};

    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int day = 0; day < days[brand]; day++) {
            if (cube[day][brand][0] != -1) {
                for (int type = 0; type < NUM_OF_TYPES; type++) {
                    int sales = cube[day][brand][type];
                    totalSalesForBrand[brand] += sales;
                    totalSalesForType[type] += sales;
                    totalSalesPerDay[day] += sales;
                }
            }
        }
    }

    int bestBrandIndex = 0;
    for (int i = 1; i < NUM_OF_BRANDS; i++) {
        if (totalSalesForBrand[i] > totalSalesForBrand[bestBrandIndex]) {
            bestBrandIndex = i;
        }
    }

    int bestTypeIndex = 0;
    for (int i = 1; i < NUM_OF_TYPES; i++) {
        if (totalSalesForType[i] > totalSalesForType[bestTypeIndex]) {
            bestTypeIndex = i;
        }
    }

    int bestDayIndex = 0;
    for (int i = 1; i < DAYS_IN_YEAR; i++) {
        if (totalSalesPerDay[i] > totalSalesPerDay[bestDayIndex]) {
            bestDayIndex = i;
        }
    }

    printf("The best-selling brand overall is %s: %d$\n", brands[bestBrandIndex], totalSalesForBrand[bestBrandIndex]);
    printf("The best-selling type of car is %s: %d$\n", types[bestTypeIndex], totalSalesForType[bestTypeIndex]);
    printf("The most profitable day was day number %d: %d$\n", bestDayIndex + 1, totalSalesPerDay[bestDayIndex]);
}

// Function to calculate the delta for a given brand
double calculateDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int days[NUM_OF_BRANDS]) {
    int totalDelta = 0;
    int validDays = 0;

    for (int day = 1; day < days[brand]; day++) {
        int previousDaySales = 0;
        int currentDaySales = 0;

        for (int type = 0; type < NUM_OF_TYPES; type++) {
            if (cube[day - 1][brand][type] != -1) {
                previousDaySales += cube[day - 1][brand][type];
            }
        }

        for (int type = 0; type < NUM_OF_TYPES; type++) {
            if (cube[day][brand][type] != -1) {
                currentDaySales += cube[day][brand][type];
            }
        }

        if (previousDaySales > 0 && currentDaySales > 0) {
            totalDelta += currentDaySales - previousDaySales;
            validDays++;
        }
    }

    if (validDays > 0) {
        return (double)totalDelta / validDays;
    }

    return 0.0;
}

// Function to provide average delta metrics (Task 6)
void provideAverageDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        double delta = calculateDelta(cube, brand, days);
        printf("Brand: %s, Average Delta: %.6f\n", brands[brand], delta);
    }
}

void printMenu() {
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    int isRunning = 1;

    initializeCube(cube);

    while (isRunning) {
        printMenu();

        // Read user input and handle invalid input
        if (scanf("%d", &choice) != 1) { // Read integer input
            clearInputBuffer();         // Discard invalid input
            printf("Invalid input. Please enter a number.\n");
            continue;                   // Retry on invalid input
        }
        clearInputBuffer();             // Discard trailing characters after the number

        // Process the choice
        switch (choice) {
        case addOne:
            enterDataForBrandDaily(cube, days);
            break;
        case addAll:
            populateDayOfSales(cube, days);
            break;
        case stats:
            provideDailyStats(cube, days);
            break;
        case print:
            printAllData(cube, days);
            break;
        case insights:
            provideOverallInsights(cube, days);
            break;
        case deltas:
            provideAverageDeltaMetrics(cube, days);
            break;
        case done:
            printf("Goodbye!\n");
            isRunning = 0;             // Exit the loop
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}




