/******************************************************************************
 * Author(s):
 *   Mark Giles
 *   Ryan Fleming
 * File Name: project1.c
 * Date Created: 10/14/2016
 * Last Modified: 10/14/2016
 * Description:
 *   This program is self-contained (no extended header files) and
 *   provides a mechanism to compare various algorithms used to calculate the 
 *   maximum sum of a subarray given an array of integers. Each algorithm takes
 *   as a parameter an input array of positive and/or negative integers,
 *   calculates the maximum sum of a subarray as well as tracks the starting
 *   and ending index of the subarray.
 *
 * Input: 
 *   The primary input for this program is a file containing square bracket
 *   delimited arrays with comma delimited integer values. The values are
 *   parsed through reading the file, parsing the integers, placing them into
 *   an array, and providing the array to each of the four algorithms for
 *   processing. Each of the four algorithms are described in greater detail
 *   in their corresponding function descriptions. Detailed function input is
 *   located in the input section of each function.
 *
 * Output:
 *   All output for this program is directed to a file in the current working
 *   directory called MSS_Results.txt. Detailed function output is located in
 *   the output section of each function.
 *
 * References:
 *   Kadane's Algorithm - 
 *     I researched methods for providing algorithm 4, depicted below in the
 *     function called:
 *       mssLinearTime(FILE * outputFile, int inputArray[512], int inputCount)
 *     Various results were found surrounding this popular program, and I used
 *     elements learned from the following two web sites to create the function
 *       - https://en.wikipedia.org/wiki/Maximum_subarray_problem
 *       - http://stackoverflow.com/questions/7943903/maximum-subarray-of-an-array-with-integers
 *****************************************************************************/

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
	int i = 0,                      // loop iteration
        j = 0,                      // loop iteration
        maxSubarray[inputCount],    // subarray with maximum sum
        maxSum = inputArray[0],     // sum of max subarray values
        tmpSum = -1,                // used to hold temporary sum values
		startIndex = -1,            // start index of best subarray
        endIndex = -1;              // end index of best subarray

	maxSum = inputArray[0];
	for (i = 0; i < inputCount; i++) {
		tmpSum = inputArray[i];
		for (j = i + 1; j < inputCount; j++) {
			tmpSum = tmpSum + inputArray[j];
			if (tmpSum > maxSum) {
				maxSum = tmpSum;
				startIndex = i;
				endIndex = j;
			}
		}
	}

	fprintf(outputFile, "\nALGORITHM 1: MSS ENUMERATION\n");
	fprintf(outputFile, "Max Sum: %i\n", maxSum);
	fprintf(outputFile, "Output Array: \n");
	for (i = startIndex; i <= endIndex; i++) {
		fprintf(outputFile, "%i ", inputArray[i]);
	}
	fprintf(outputFile, "\n");

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
	int i = 0,                    // loop iteration
        maxSoFar = 0,             // max tracking at each iteration
        maxHere = 0,              // max at current iteration of loop
        currentValue = 0,         // calculates value of current iteration
        maxBeginning = 0,         // max at beginning of iteration
        bestStartIndexSoFar = 0,  // start index of current max subarray
        bestEndIndexSoFar = 0,    // end index of current max subarray
        bestStartIndexHere = 0;   // current start index for max subarray

    for (i = 0; i < inputCount; i++) {
        currentValue = maxHere + inputArray[i];
        if (currentValue > 0) {
            if (maxHere == 0) {
                bestStartIndexHere = i;
            }
            maxHere = currentValue;
		} else {
            maxHere = 0;
        }

        if (maxHere > maxSoFar) {
            maxSoFar = maxHere;
            bestEndIndexSoFar = i;
            bestStartIndexSoFar = bestStartIndexHere;
		}
    }

	fprintf(outputFile, "\nALGORITHM 4: MSS LINEAR TIME\n");
	fprintf(outputFile, "Max Sum: %i\n", maxSoFar);
	fprintf(outputFile, "Output Array: \n");	
	for (i = bestStartIndexSoFar; i <= bestEndIndexSoFar; i++) {
		fprintf(outputFile, "%i ", inputArray[i]);
	}
	fprintf(outputFile, "\n");
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
