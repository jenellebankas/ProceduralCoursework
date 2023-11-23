#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

int GLOBALCOUNT = 0;
// array of FITNESS_DATA structs
FITNESS_DATA fitness[100];

char filename[100000];

// Function to tokenize a record
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

int addToArray() {


    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: Could not find or open the file.\n");
        return 1;
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

        if (fitness[counter].date == NULL || fitness[counter].time == NULL || fitness[counter].steps == 0) {
            printf("Invalid File.\n");
            return 1;
        }
    }

    GLOBALCOUNT = counter;
    printf("File successfully loaded.\n");

    fclose(file);
    return 0;
}

int sortingArray() {

    char tempStoreDate[11];
    char tempStoreTime[6];
    int tempStoreSteps;
    int swapped = 0;
    int count, count2;

    for (count = 0; count < GLOBALCOUNT - 1; count++) {
        swapped = 0;
        for (count2 = 0; count2 < GLOBALCOUNT - 1; count2++) {

            if (fitness[count].steps > fitness[count2].steps) {

            strcpy(tempStoreDate, fitness[count].date);
            strcpy(tempStoreTime, fitness[count].time);
            tempStoreSteps = fitness[count].steps;
            
            strcpy(fitness[count].date, fitness[count2].date);
            strcpy(fitness[count].time, fitness[count2].time);
            fitness[count].steps = fitness[count2].steps;
           
            strcpy(fitness[count2].date,tempStoreDate);
            strcpy(fitness[count2].time,tempStoreTime);
            fitness[count2].steps = tempStoreSteps;

            swapped = 1;
            
            }
        }
        
        if (swapped == 0) {
            break;
        }      
    }
}

int sortedNewFile() {

    char filename[] = "FitnessData_2023.csv.tsv";
    int count;

    FILE *file = fopen(filename, "a");

    for (count = 0; count < GLOBALCOUNT; count++) {
        fprintf(file, "%s\t%s\t%d\n", fitness[count].date, fitness[count].time, fitness[count].steps);
    }
}

int main() {

    int addingData;

    printf("Please enter a filename: ");
    scanf("%s", filename); 

    addingData = addToArray();

    if (addingData == 1) {
        return 1;
    }
    sortingArray();
    sortedNewFile();
    return 0;
}