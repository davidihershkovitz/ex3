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
void clearInputBuffer()
{
    char clear;
    while (scanf("%c", &clear) == 1 && clear != '\n');
}

// Initialize the cube to -1
void initializeCube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
    for (int day = 0; day < DAYS_IN_YEAR; day++)
    {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
        {
            for (int type = 0; type < NUM_OF_TYPES; type++)
            {
                cube[day][brand][type] = -1;
            }
        }
    }
}
// inserting data for the cube for each brand and for each type
void populateDayOfSales(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    int completedBrands[NUM_OF_BRANDS] = {0}; // Tracks which brands are completed

    while (1)
    {
        // Check for remaining brands
        int remaining = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            if (days[i] < DAYS_IN_YEAR && !completedBrands[i])
            {
                remaining = 1;
                break;
            }
        }
        if (!remaining)
        {
            break; // Exit if no brands are left
        }
        // Print brands that still need data
        printf("No data for brands");
        for (int i = 0; i < NUM_OF_BRANDS; i++)
        {
            if (!completedBrands[i])
            {
                printf(" %s", brands[i]);
            }
        }
        printf("\nPlease complete the data\n");

        int brand;
        // Read the brand index
        if (scanf("%d", &brand) != 1)
        {
            clearInputBuffer(); // Clear invalid input
            printf("This brand is not valid\n");
            continue;
        }
        // make sure tha the index of the brand is correct
        if (brand < 0 || brand >= NUM_OF_BRANDS || completedBrands[brand] || days[brand] >= DAYS_IN_YEAR)
        {
            printf("This brand is not valid\n");
            clearInputBuffer(); // Ensure leftover input is discarded
            continue; // Skip invalid or completed brand
        }
        // Input sales data for the brand
        for (int type = 0; type < NUM_OF_TYPES; type++)
        {
            if (scanf("%d", &cube[days[brand]][brand][type]) != 1)
            {
                clearInputBuffer(); // Clear invalid input
                break;
            }
        }
        // Mark the brand as completed
        completedBrands[brand] = 1;
    }
    // To make sure to update the day
    for (int i = 0; i < NUM_OF_BRANDS; i++)
    {
        if (days[i] < DAYS_IN_YEAR)
        {
            days[i]++; // Move to the next day for the brand
        }
    }
}
// Provide daily stats for a specific day
void provideDailyStats(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS]) {
    int day;

    while (1) {
        printf("What day would you like to analyze?\n");

        if (scanf("%d", &day) != 1) {
            clearInputBuffer(); // Clear invalid input
            printf("Please enter a valid day.\n");
            continue; // Re-prompt the user
        }

        if (day <= 0 || day > DAYS_IN_YEAR) {
            printf("Please enter a valid day.\n");
            continue; // Re-prompt the user
        }

        int hasData = 0;
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            if (days[brand] >= day && cube[day - 1][brand][0] != -1) {
                hasData = 1;
                break;
            }
        }
        if (!hasData) {
            printf("Please enter a valid day.\n");
            continue; // Re-prompt the user
        }

        int totalSales = 0;
        int brandSales[NUM_OF_BRANDS] = {0};
        int typeSales[NUM_OF_TYPES] = {0};

        // Calculate total sales and sales by brand and type
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                if (cube[day - 1][brand][type] != -1) {
                    int sales = cube[day - 1][brand][type];
                    totalSales += sales;
                    brandSales[brand] += sales;
                    typeSales[type] += sales;
                }
            }
        }

        // Find the brand with the maximum sales (lower index on ties)
        int maxBrandIndex = -1, maxBrandSales = 0;
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (brandSales[i] > maxBrandSales ||
               (brandSales[i] == maxBrandSales && maxBrandIndex == -1)) {
                maxBrandSales = brandSales[i];
                maxBrandIndex = i;
            }
        }

        // Find the type with the maximum sales (lower index on ties)
        int maxTypeIndex = -1, maxTypeSales = 0;
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            if (typeSales[i] > maxTypeSales ||
               (typeSales[i] == maxTypeSales && maxTypeIndex == -1)) {
                maxTypeSales = typeSales[i];
                maxTypeIndex = i;
            }
        }

        // Print results
        printf("In day number %d:\n", day);
        printf("The sales total was %d\n", totalSales);
        printf("The best sold brand with %d sales was %s\n", maxBrandSales, brands[maxBrandIndex]);
        printf("The best sold type with %d sales was %s\n", maxTypeSales, types[maxTypeIndex]);

        break;
    }
}
// Function to print all sales data for all the days that are in the cube at the moment
void printAllData(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{

    printf("*****************************************\n");

    // Loop through all brands
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
    {
        printf("Sales for %s:\n", brands[brand]);

        // Loop through all days, but only print days that are within the range of data
        for (int day = 0; day < days[brand]; day++)
        {
            // Check if there's data for the current day for the current brand
            if (cube[day][brand][0] != -1)
            {
                // Checking if data exists
                printf("Day %d- ", day + 1);
                for (int type = 0; type < NUM_OF_TYPES; type++)
                {
                    printf("%s: %d ", types[type], cube[day][brand][type]);
                }
                printf("\n");
            }
            else
            {
                // If no data exists, print "Day [x]- SUV: 0 Sedan: 0 Coupe: 0 GT: 0"
                printf("Day %d- SUV: 0 Sedan: 0 Coupe: 0 GT: 0\n", day + 1);
            }
        }
    }

    // Print the ending border with stars
    printf("*****************************************\n");
}
// provide insights about the sales so far
void provideOverallInsights(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    int totalSalesForBrand[NUM_OF_BRANDS] = {0}; // Total sales for each brand
    int totalSalesForType[NUM_OF_TYPES] = {0}; // Total sales for each car type
    int totalSalesPerDay[DAYS_IN_YEAR] = {0}; // Total sales for each day

    // Calculate total sales for each brand, type, and day
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
    {
        for (int day = 0; day < days[brand]; day++)
        {
            // Loop until the last day for each brand
            if (cube[day][brand][0] != -1)
            {
                // If there is data for the day
                for (int type = 0; type < NUM_OF_TYPES; type++)
                {
                    int sales = cube[day][brand][type];
                    totalSalesForBrand[brand] += sales;
                    totalSalesForType[type] += sales;
                    totalSalesPerDay[day] += sales;
                }
            }
        }
    }
    // Find the best-selling brand
    int bestBrandIndex = 0;
    for (int i = 1; i < NUM_OF_BRANDS; i++)
    {
        if (totalSalesForBrand[i] > totalSalesForBrand[bestBrandIndex])
        {
            bestBrandIndex = i;
        }
    }
    // Find the best-selling type of car
    int bestTypeIndex = 0;
    for (int i = 1; i < NUM_OF_TYPES; i++)
    {
        if (totalSalesForType[i] > totalSalesForType[bestTypeIndex])
        {
            bestTypeIndex = i;
        }
    }
    // Find the most profitable day
    int bestDayIndex = 0;
    for (int i = 1; i < DAYS_IN_YEAR; i++)
    {
        if (totalSalesPerDay[i] > totalSalesPerDay[bestDayIndex])
        {
            bestDayIndex = i;
        }
    }
    // Print insights
    printf("The best-selling brand overall is %s: %d$\n", brands[bestBrandIndex], totalSalesForBrand[bestBrandIndex]);
    printf("The best-selling type of car is %s: %d$\n", types[bestTypeIndex], totalSalesForType[bestTypeIndex]);
    printf("The most profitable day was day number %d: %d$\n", bestDayIndex + 1, totalSalesPerDay[bestDayIndex]);
}

// Function to calculate the delta for a given brand
double calculateDelta(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int brand, int days[NUM_OF_BRANDS])
{
    int totalDelta = 0;
    int validDays = 0; // Count days with sales data

    // Loop through all the days for the given brand
    for (int day = 1; day < days[brand]; day++)
    {
        int previousDaySales = 0;
        int currentDaySales = 0;

        // Calculate the total sales for the previous day
        for (int type = 0; type < NUM_OF_TYPES; type++)
        {
            if (cube[day - 1][brand][type] != -1)
            {
                // Check if there's data for the previous day
                previousDaySales += cube[day - 1][brand][type];
            }
        }
        // Calculate the total sales for the current day
        for (int type = 0; type < NUM_OF_TYPES; type++)
        {
            if (cube[day][brand][type] != -1)
            {
                // Check if there's data for the current day
                currentDaySales += cube[day][brand][type];
            }
        }

        // If there was data for both days, calculate the delta
        if (previousDaySales > 0 && currentDaySales > 0)
        {
            totalDelta += currentDaySales - previousDaySales;
            validDays++;
        }
    }
    // If there are valid days, return the average delta
    if (validDays > 0)
    {
        return (double)totalDelta / validDays;
    }

    // If there are not enough valid data, return 0
    return 0.0;
}

// Function to provide average delta metrics
void provideAverageDeltaMetrics(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int days[NUM_OF_BRANDS])
{
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++)
    {
        // Call the calculateDelta function to get the delta for this brand
        double delta = calculateDelta(cube, brand, days);

        // Print the result for each brand
        printf("Brand: %s, Average Delta: %.6f\n", brands[brand], delta);
    }
}
void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
        "1.Enter Daily Data For A Brand\n"
        "2.Populate A Day Of Sales For All Brands\n"
        "3.Provide Daily Stats\n"
        "4.Print All Data\n"
        "5.Provide Overall (simple) Insights\n"
        "6.Provide Average Delta Metrics\n"
        "7.exit\n");
}

int main()
{
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    int isRunning = 1; // Flag to control the loop

    // Initialize the cube
    initializeCube(cube);

    while (isRunning)
    {

        printMenu();

        // Read input from the user
        if (scanf("%d", &choice) != 1)
        {
            clearInputBuffer();
            printf("Invalid input\n");
            continue; // Skip to the next iteration
        }


        switch (choice)
        {
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
            isRunning = 0; // Set flag to stop the loop
            break;
        default:
            printf("Invalid input\n");
            clearInputBuffer();
        }
    }
    return 0;
}