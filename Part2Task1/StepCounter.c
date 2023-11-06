#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// array of FITNESS_DATA structs
FITNESS_DATA fitness[100];

// global variable for the filename 
char filename[];

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

// functions to calculate results for options

   
int presentOptions() {

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
    printf("Enter Choice: \n");
    scanf("%s", choice);

    if (choice != "A" || "B" || "C" || "D" || "E" || "F" || "Q") {
        printf("Incorrect input, try again!");
    } else {
        // switch for the user once their option has been inputted 
        switch (choice) { 

            case "A":
                printf("Input filename: \n");
                scanf("%s", filename);
                FILE *openFile(filename,"r");
                totalRecords();
                addToArray();
                break;

            case "B":
                printf("Total records: %d\n", GLOBALCOUNT);
                break;

            case "C": 
                fewestSteps();
                break;

            case "D":
                largestSteps();
                break;

            case "E":
                meanStepCount();
                break;

            case "F":
                longestPeriodCheck();
                break;

            case "Q":
                EXIT = 1;
                break;
            }     
        }
    }  
}


FILE *openFile(char filename[], char mode[]) {

    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        printf("Error: Could not find or open the file.\n");
        exit(1);
    }
    return file;
}

int addToArray() {

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
    }

    fclose(file);
    return 0;
}

int totalRecords() {

    int counter = 0;

    while (fgets(line, buffer_size, file)) { 
        counter++;
    }

    COUNT = counter;
    return 0;
}

void fewestSteps() {
    
    //count variable declared for the function
    int count = 0;
    int fewest = 99999999;
    char fewestDate[];
    char fewestTime[];
    

    for (count = 0; count < GLOBALCOUNT - 1, count++) {
        if (fitness[count].steps < fewest) {
            fewestDate = fitness[count].date;
            fewestTime = fitness[count].time;
        }
    }
    
    printf("Fewest steps: %s %s\n", fewestDate, fewestTime);
    
}

void largestSteps() {
    
    int count;
    int largest = 0;
    char largestDate[];
    char largestTime[];
    

    for (count = 0; count < GLOBALCOUNT - 1, count++) {
        if (fitness[count].steps > largest) {
            largestDate = fitness[count].date;
            largestTime = fitness[count].time;
        }
    }
    
    printf("Largest steps: %s %s\n", largestDate, largestTime);

}

int meanStepCount() {

    int total = 0;
    float mean = 0.0;

    for (count = 0; count < GLOBALCOUNT; count++) {
        total += fitness[count].steps;
    }

    mean = total / GLOBALCOUNT;

    printf("Mean step count: %d\n", mean);
    return 0;
}

int longestPeriodCheck() {

    int count;
    int count2;
    int periodLength = 0;
    char periodStartDate[];
    char periodStartTime[];
    char periodEndDate[];
    char periodEndTime[];

    for (count = 0; count < GLOBALCOUNT; count++) {
        periodStartDate = fitness[count].date;
        periodStartTime = fitness[count].time;
        
        // continue statement taken from: https://www.geeksforgeeks.org/continue-in-c/
        if (fitness[count].steps < 500) {
            continue;
        } else {
            for (count2 = count; count2 < GLOBALCOUNT; count2++) {
                if (fitness[count].steps > 500) {
                    continue;
                } else { 
                    periodEndDate = fitness[count2].date;
                    periodEndTime = fitness[count2].time;
                }
            }
        }
    } 

    printf("Longest period start: %s %s\n", periodStartDate, periodStartTime);
    printf("Longest period end; %s %s\n", periodEndDate, periodEndTime); 

    return 0;  
}

// complete the main function
int main() {
    
    while (EXIT == 0) {
        presentOptions();
    }
    return 0;
}