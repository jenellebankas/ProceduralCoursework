#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

int DATACOUNT = 0;
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
        DATACOUNT++;
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
        DATACOUNT++;
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
        DATACOUNT++;
    }
    
    // Free the duplicated string
    free(inputCopy);
}

// Function to add values to the array 
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
       
    }

    GLOBALCOUNT = counter;

    // checks if the file has the correct data 
    if (DATACOUNT % 3 != 0) {
        printf("Invalid File!\n");
        return 1;
    }
    
    printf("Data sorted and written to FitnessData_2023.csv.tsv\n");

    fclose(file);
    return 0;
}

// Function to sort values 
int sortingArray() {

    char tempStoreDate[11];
    char tempStoreTime[6];
    int tempStoreSteps;
    int swapped = 0;
    int count, count2;

    // bubble sort algorithm to sort thorugh the data 
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
        
        // boolean to check if the value has already been swapped 
        if (swapped == 0) {
            break;
        }      
    }
}

// to transfer data into the new tab separated file 
int sortedNewFile() {

    // filename for opening the new file
    char filename[] = "./FitnessData_2023.csv.tsv";
    int count;

    // opening the new file
    FILE *file = fopen(filename, "a");

    // writes the data to the file 
    for (count = 0; count < GLOBALCOUNT; count++) {
        fprintf(file, "%s\t%s\t%d\n", fitness[count].date, fitness[count].time, fitness[count].steps);
    }
}

int main() {

    // creates a variable to check if the array could be created 
    int addingData;

    printf("Please enter a filename: ");
    scanf("%s", filename); 

    addingData = addToArray();

    // checks function to add all the data runs without faults 
    if (addingData == 1){
        return 1;
    }

    // sorts and formats the new file
    sortingArray();
    sortedNewFile();
    return 0;
}