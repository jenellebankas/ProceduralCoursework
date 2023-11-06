#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// array of FITNESS_DATA structs
    FITNESS_DATA fitness[100];
 // declaring variables needed to temp store 
    char DATE[11];
    char TIME[6];
    char STEPS[100000];

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




// Complete the main function
int main() {

    // variables needed 
    int buffer_size = 250;
    char line[buffer_size];
    int counter = 0;
    int count;

    char filename[] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");

    // to read each line
    while (fgets(line, buffer_size, file)) {   
        // sorting the data in the file
        tokeniseRecord(line, ",", DATE, TIME, STEPS);
        
        // copy the info into the array
        strcpy(fitness[counter].date, DATE);
        strcpy(fitness[counter].time, TIME);
        fitness[counter].steps = atoi(STEPS);
        counter++;
        
    }


    switch c { 

        case "A":
            printf("Input filename: \n");
            scanf("%s", filename);
            break;
        case "B":
            printf("Total records: \n")
            break;
        case "C":
            printf("Fewest steps: \n")
            break;
        case "D":
            printf("largest steps: \n")
            break;
        case "E":
            printf("mean step count: \n")
            break;
        case "F":
            printf("Longest period start: \n")
            printf("Longest perod end: \n")
            break;
        case "Q":
            break;
    }     
}


