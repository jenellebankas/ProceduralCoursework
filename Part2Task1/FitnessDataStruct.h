#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

//REMEMEBER TO DECLARE ALL OTHER FUNCTIONS
FILE *openFile(char filename[], char mode[]);
// this is a doxygen comment - you'll see more of these in COMP1921 :)
// taken from sessin code
/**
 * @brief Opens the specified file
 *
 * @param filename the path to the file to be opened.
 * @param mode the mode ( r/w/a | + )
 * @return the opened file pointer
 */



int presentOptions();
int totalRecords();
int addToArray();
void fewestSteps();
void largestSteps();
int meanStepCount();
int longestPeriodCheck();


#endif // FITNESS_DATA_STRUCT_H
