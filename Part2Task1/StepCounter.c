#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// array of FITNESS_DATA structs
FITNESS_DATA fitness[100];

// global variable for the filename 
char filename[10000];

// to be accessed by multiple functions
int GLOBALCOUNT = 0;
int EXIT = 0;


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);
}

// function to handle menu and call correct functions
int optionOperations() {

    char choice[2];

    // to print the options available 
    printf("Menu Options:\n");
    printf("A: Specify the filename to be imported\n");
    printf("B: Display the total number of records in the file\n");
    printf("C: Find the date and time of the timeslot with the fewest steps\n");
    printf("D: Find the date and time of the timeslot with the largest number of steps\n");
    printf("E: Find the mean step count of all the records in the file\n");
    printf("F: Find the longest continuous period where the step count is above 500 steps\n");
    printf("Q: Quit\n");
    printf("Enter Choice: ");
    scanf("%s", choice);


    // switch for the user once their option has been inputted 
    switch (choice[0]) { 

        case 'A':
            printf("Input filename: ");
            scanf("%s", filename);
            addToArray();
            break;

        case 'B':
            printf("Total records: %d\n", GLOBALCOUNT);
            break;

        case 'C': 
            fewestSteps();
            break;

        case 'D':
            largestSteps();
            break;

        case 'E':
            meanStepCount();
            break;

        case 'F':
            longestPeriodCheck();
            break;

        case 'Q':
            EXIT = 1;
            break;

        default:
            printf("Incorrect input, try again!\n");
            optionOperations();
            break;
    }  
}

// functions to calculate results for options
// function to add values to the fitness array
int addToArray() {

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not find or open the file.\n");
        EXIT = 1;
    }

    // variables needed 
    int buffer_size = 250;
    char line[buffer_size];
    int counter = 0;
    int count;

    // declaring variables needed to temp store 
    char date[11];
    char time[6];
    char steps[100000];

    // to read each line
    while (fgets(line, buffer_size, file)) {   
        // sorting the data in the file
        tokeniseRecord(line, ",", date, time, steps);

        // copy the info into the array
        strcpy(fitness[counter].date, date);
        strcpy(fitness[counter].time, time);
        fitness[counter].steps = atoi(steps);  
        counter++;
    }

    GLOBALCOUNT = counter;
    printf("File successfully loaded.\n");

    fclose(file);
    return 0;
}

// function to calculate the fewest number of steps walked
void fewestSteps() {
    
    //count variable declared for the function
    int count = 0;
    int fewest = 99999999;
    char fewestDate[11];
    char fewestTime[6];
    

    for (count = 0; count < GLOBALCOUNT; count++) {
        if (fitness[count].steps < fewest) {
            strcpy(fewestDate,fitness[count].date);
            strcpy(fewestTime,fitness[count].time);
            fewest = fitness[count].steps;
        }
    }  
    printf("Fewest steps: %s %s\n", fewestDate, fewestTime);  
}

// function to calculate the largest number of steps walked
void largestSteps() {
    
    int count;
    int largest = 0;
    char largestDate[11];
    char largestTime[6];
    

    for (count = 0; count < GLOBALCOUNT; count++) {
        if (fitness[count].steps > largest) {
            strcpy(largestDate, fitness[count].date);
            strcpy(largestTime, fitness[count].time);
            largest = fitness[count].steps;
        }
    }
    
    printf("Largest steps: %s %s\n", largestDate, largestTime);

}

// function to calculate the mean number of steps
int meanStepCount() {

    int total = 0;
    int mean = 0;
    int count;

    for (count = 0; count < GLOBALCOUNT; count++) {
        total += fitness[count].steps;
    }

    mean = total / GLOBALCOUNT;

    printf("Mean step count: %d\n", mean);
    return 0;
}

// function to calculate the longest period
int longestPeriodCheck() {

    int count;
    int count2 = 0;
    int maxPeriodLength = 0;
    int currentPeriodLength = 0;
    char periodStartDate[11];
    char periodStartTime[6];
    char periodEndDate[11];
    char periodEndTime[6];
    
   

    while (count < GLOBALCOUNT) {
        if (fitness[count].steps > 500) {
            while (fitness[count2].steps > 500) {
                currentPeriodLength += 1;
                count2++;
            }
            if (currentPeriodLength > maxPeriodLength) {
                maxPeriodLength = currentPeriodLength;
                currentPeriodLength = 0; 
                strcpy(periodStartDate, fitness[count].date);
                strcpy(periodStartTime, fitness[count].time);
                strcpy(periodEndDate, fitness[count2 - 1].date);
                strcpy(periodEndTime, fitness[count2 - 1].time);
                break; 
            }
        }
    count++;
    }
    printf("Longest period start: %s %s\n", periodStartDate, periodStartTime);
    printf("Longest period end: %s %s\n", periodEndDate, periodEndTime); 

    return 0;  
}


// calls the menu operations function and enables it to be called until exited 
int main() {

    while (EXIT == 0) {
        optionOperations();
    }
    return 0;
}