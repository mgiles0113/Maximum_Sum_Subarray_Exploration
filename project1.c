#include <stdio.h>
#include <string.h>

/******************************************************************************
 * Function Name: writeArray
 * Parameters:
 *     - outputFile: file to write array
 *     - array: values to be written
 *     - arrayCount: number of values in array 
 *****************************************************************************/
void writeArray(FILE * outputFile, int array[512], int arrayCount) {
	int i = 0;			// loop iteration
	/* 
     * read through each value of array and write to ouput file. Each value is
     * separated by white space and the array is terminated by newline
    */
	for (i = 0; i < arrayCount; i++) {
		fprintf(outputFile, "%i ", array[i]);
	}
	fprintf(outputFile, "\n");
}

/******************************************************************************
 * Function Name: mssEnumeration
 * Parameters:
 *
 *****************************************************************************/
void mssEnumeration(FILE * outputFile, int inputArray[512], int inputCount) {
	fprintf(outputFile, "\nALGORITHM 1: MSS ENUMERATION\n");
	fprintf(outputFile, "Max Sum: \n");
	fprintf(outputFile, "Output Array: \n");
}

/******************************************************************************
 * Function Name: mssBetterEnumeration
 * Parameters:
 *
 *****************************************************************************/
void mssBetterEnumeration(FILE * outputFile,
                          int inputArray[512],
                          int inputCount) {
	fprintf(outputFile, "\nALGORITHM 2: MSS BETTER ENUMERATION\n");
	fprintf(outputFile, "Max Sum: \n");
	fprintf(outputFile, "Output Array: \n");

}

/******************************************************************************
 * Function Name: mssDivideAndConquer
 * Parameters:
 *
 *****************************************************************************/
void mssDivideAndConquer(FILE * outputFile,
                         int inputArray[512],
                         int inputCount) {
	fprintf(outputFile, "\nALGORITHM 3: MSS DIVIDE AND CONQUER\n");
	fprintf(outputFile, "Max Sum: \n");
	fprintf(outputFile, "Output Array: \n");
}

/******************************************************************************
 * Function Name: mssLinearTime
 * Parameters:
 *
 *****************************************************************************/
void mssLinearTime(FILE * outputFile, int inputArray[512], int inputCount) {
	fprintf(outputFile, "\nALGORITHM 4: MSS LINEAR TIME\n");
	fprintf(outputFile, "Max Sum: \n");
	fprintf(outputFile, "Output Array: \n");	
}

int main() {
	FILE *inputFile,				// file with input arrays to be processed
         *outputFile;				// file used to produce results
	int inputArray[512],			// array of integers sent to algorithms
        inputCount = 0,				// number of integers in the input array
        intValue = -1,				// individual input integer for input array
		i = 0;						// loop iteration
	char c,							// individual read character from file
         stringArray[512],			// individual array from file as string
         stringValue[512];			// individual value from array as string

	// files used for reading and writing
	inputFile = fopen("MSS_TestProblems-1.txt", "r");
	outputFile = fopen("MSS_Results.txt", "w");

	/* 
     * read each character of input file, isolate individual input arrays and
     * process the arrays through each MSS algorithm. This process also removes
     * unnecessary values such as square brackets, new lines, and white space
    */
	while ((c = getc(inputFile)) != EOF) {
		// identifies end of individual array
		if (c == ']') {
			// read through array string, separating individual values
			for (i = 0; i < strlen(stringArray); i++) {
				// comma identifies the completion of an array value
				if (stringArray[i] == ',') {
					// convert string to integer for and store in input array
					intValue = atoi(stringValue);
					inputArray[inputCount] = intValue;
					inputCount = inputCount + 1;
					memset(stringValue, 0, strlen(stringValue));
				} else {
					// add character to value string
					stringValue[strlen(stringValue)] = stringArray[i];
				}
			}
			// convert final value to integer and store in input array
			intValue = atoi(stringValue);
			inputArray[inputCount] = intValue;
			inputCount = inputCount + 1;

			// output formatting for ease of reading
			fprintf(outputFile, "\n----------------------------------------------------\n");
			fprintf(outputFile, "\nINPUT ARRAY:\n");
			writeArray(outputFile, inputArray, inputCount);

			// process input array through each of the four algorithms
			mssEnumeration(outputFile, inputArray, inputCount);
			mssBetterEnumeration(outputFile, inputArray, inputCount);
			mssDivideAndConquer(outputFile, inputArray, inputCount);
			mssLinearTime(outputFile, inputArray, inputCount);

			// reset processing attributes to prepare for next input array
			inputCount = 0;
			memset(stringValue, 0, strlen(stringValue));
			memset(stringArray, 0, strlen(stringArray));
			memset(inputArray, 0, 512);
		} else if (c != '[' && c != ' ' && c != '\n') {
			// add character to input string
			stringArray[strlen(stringArray)] = c;
		}
	}


	fclose(inputFile);
	fclose(outputFile);

	return 0;
}
