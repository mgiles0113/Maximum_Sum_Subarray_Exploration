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
 *   and ending index of the subarray. Each of the four algorithms are
 *   described in greater detail in their corresponding function descriptions.
 *   Detailed function input is located in the input section of each function.
 *
 * Input: 
 *   The primary input for this program is a file containing square bracket
 *   delimited arrays with comma delimited integer values. The values are
 *   parsed through reading the file, parsing the integers, placing them into
 *   an array, and providing the array to each of the four algorithms for
 *   processing.  *
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
 *   Divide and Conquer -
 *     In addition to pseduocode from "Introduction to Algorithms" by Cormen,
 *     Leiserson, Clifford, and Stein, I used the code on this post to serve
 *       - http://www.geeksforgeeks.org/divide-and-conquer-maximum-sum-subarray
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>


const int testing = 1;

/******************************************************************************
 * Function Name: writeArray
 * Description:
 *   This function takes an array of integers and writes the
 *   array's contents to a specified output file.
 * Input:
 *   - outputFile: file to write array
 *   - array: values to be written
 *   - arrayCount: number of values in array
 * Output: 
 *   - Writes the contents of each value of the array to the specified
 *     output file.
 *****************************************************************************/
void writeArray(FILE * outputFile, int array[512], int arrayCount) {
    int i = 0;    // loop iteration
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
 * Function Name: max2
 * Description: This function takes two integers and returns the larger of the
 * two.
 *****************************************************************************/
int max2(int a, int b) {
	return (a > b)? a : b;
}

/******************************************************************************
 * Function Name: max3
 * Description: This function takes three integers and returns the larger of 
 * the three.
 *****************************************************************************/
int max3(int a, int b, int c) {
	return max2(max2(a, b), c);
}

/******************************************************************************
 * Function Name: mssEnumeration
 * Description: This function takes an array of positive and negative integers
 *   and calculates the maximum sum of a subarray of the array. It then writes
 *   the results to a specified output file. This function represents an
 *   iterative 
 * Input:
 *   - outputFile: file to write the results of the function
 *   - inputArray: array of integers to be used to calculate maximum sum
 *       and indices for the maximum subarray.
 *   - inputCount: number of actual values in array for ease of iteration.
 * Output:
 *   All output is directed to the output file specified. The content is the
 *   value of the maximum sum as well as the array contents of the input
 *   array's maximum sum subarray.
 *****************************************************************************/
void mssEnumeration(FILE * outputFile, int inputArray[512], int inputCount) {
    int i = 0,                      // loop iteration
        j = 0,                      // loop iteration
        maxSubarray[inputCount],    // subarray with maximum sum
        maxSum = inputArray[0],     // sum of max subarray values
        tmpSum = -1,                // used to hold temporary sum values
        startIndex = 0,            // start index of best subarray
        endIndex = 0;              // end index of best subarray

    maxSum = inputArray[0];         // base case of the initial sum
	clock_t begin = clock();	
    /*
     * loop through each element in the array, comparing the values at i and
     * j, tracking the maximum sum until the end of the array.
    */
    for (i = 0; i < inputCount; i++) {
        // initial value for each iteration is the value at i
        tmpSum = inputArray[i];
        // loop until the end of available values
        for (j = i + 1; j < inputCount; j++) {
            // add to temporary sum the value at j
            tmpSum = tmpSum + inputArray[j];
            // store new max sum if the temp value is larger
            if (tmpSum > maxSum) {
                maxSum = tmpSum;
                startIndex = i;
                endIndex = j;
            }
        }
    }
	clock_t end = clock();

    /* 
     * print the name of the algorithm/function, maximum sum, and the contents
     * of the maximum sum subarray
    */
    fprintf(outputFile, "\nALGORITHM 1: MSS ENUMERATION\n");
    fprintf(outputFile, "Max Sum: %i\n", maxSum);
	if (!testing) {
		fprintf(outputFile, "\nINPUT ARRAY:\n");
		writeArray(outputFile, inputArray, inputCount);
	    fprintf(outputFile, "Output Array: \n");
   		for (i = startIndex; i <= endIndex; i++) {
       		fprintf(outputFile, "%i ", inputArray[i]);
    	}
	}
	fprintf(outputFile, "Running Time: %lf\n", (double)(end - begin)/ CLOCKS_PER_SEC);
}

/******************************************************************************
 * Function Name: mssBetterEnumeration
 * Parameters:
 *
 *****************************************************************************/
void mssBetterEnumeration(FILE * outputFile,
                          int inputArray[512],
                          int inputCount) {

	int maxSubsetSum, currentSum = 0;
	int startSubset, stopSubset = 0;
	int i, j;
	clock_t begin = clock();	
	for (i = 0; i < inputCount; i++){
		currentSum = 0;
		for (j = i; j < inputCount; j++){
			currentSum += inputArray[j];
			if (currentSum > maxSubsetSum)
			{
				maxSubsetSum = currentSum;
				startSubset = i;
				stopSubset = j;
			}
		}	
	}
	clock_t end = clock();	
	fprintf(outputFile, "\nALGORITHM 2: MSS BETTER ENUMERATION\n");
	fprintf(outputFile, "Max Sum: %i\n", maxSubsetSum);
	if (!testing) {
		fprintf(outputFile, "\nINPUT ARRAY:\n");
		writeArray(outputFile, inputArray, inputCount);
		fprintf(outputFile, "Output Array: \n");
    	for (i = startSubset; i <= stopSubset; i++) {
        	 fprintf(outputFile, "%i ", inputArray[i]);
    	}
	}
	fprintf(outputFile, "Running Time: %lf\n", (double)(end - begin)/ CLOCKS_PER_SEC);
}

/******************************************************************************
 * Function Name: mssDivideAndConquer
 * Parameters:
 *
 *****************************************************************************/
void mssDivideAndConquer(FILE * outputFile,
                         int inputArray[512],
                         int inputCount) {
	int maxSum = -1;
	clock_t begin = clock();
	maxSum = maxSubArraySum(inputArray, 0, inputCount - 1);
	clock_t end = clock();

	fprintf(outputFile, "\nALGORITHM 3: MSS DIVIDE AND CONQUER\n");
	fprintf(outputFile, "Max Sum: %i\n", maxSum);
	if (!testing) {
		fprintf(outputFile, "\nINPUT ARRAY:\n");
		writeArray(outputFile, inputArray, inputCount);
		fprintf(outputFile, "Output Array: \n");
	}
	fprintf(outputFile, "Running Time: %lf\n", (double)(end - begin)/ CLOCKS_PER_SEC);
}

int maxCrossingSum(int arr[], int l, int m, int h) {
	int sum = 0;
	int left_sum = INT_MIN;
	int i = 0;
	for (i = m; i >= l; i--) {
		sum = sum + arr[i];
		if (sum > left_sum) {
			left_sum = sum;
		}
	}

	sum = 0;
	int right_sum = INT_MIN;
	for (i = m + 1; i <= h; i++) {
		sum = sum + arr[i];
		if (sum > right_sum) {
			right_sum = sum;
		}
	}

	return left_sum + right_sum;
}

int maxSubArraySum(int arr[], int l, int h) {
	if (l == h) {
		return arr[l];
	}
	int m = (l + h)/2;

	return max3(maxSubArraySum(arr, l, m),
			   maxSubArraySum(arr, m + 1, h),
			   maxCrossingSum(arr, l, m, h));
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
	clock_t begin = clock();
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
	clock_t end = clock();
	fprintf(outputFile, "\nALGORITHM 4: MSS LINEAR TIME\n");
	fprintf(outputFile, "Max Sum: %i\n", maxSoFar);
	if (!testing) {
		fprintf(outputFile, "\nINPUT ARRAY:\n");
		writeArray(outputFile, inputArray, inputCount);
		fprintf(outputFile, "Output Array: \n");	
		for (i = bestStartIndexSoFar; i <= bestEndIndexSoFar; i++) {
			fprintf(outputFile, "%i ", inputArray[i]);
		}
	}
	fprintf(outputFile, "Running Time: %lf\n", (double)(end - begin)/ CLOCKS_PER_SEC);
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
	time_t t;
	srand((unsigned) time(&t));

	// files used for reading and writing
	inputFile = fopen("MSS_Problems.txt", "r");
	outputFile = fopen("MSS_Results.txt", "w");

	/* 
     * read each character of input file, isolate individual input arrays and
     * process the arrays through each MSS algorithm. This process also removes
     * unnecessary values such as square brackets, new lines, and white space
    */
/*
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


	*/
	inputCount = 1750000;
	int testArray[inputCount],
   	    randInt = 0,
       	signCheck = 0,
		j = 0;

	fprintf(outputFile, "\nInput Size: %i\n", inputCount);
	for (i = 0; i < 10; i++) {
		for (j = 0; j < inputCount; j++) {
			randInt = rand() % 100;
			signCheck = rand();
			if (signCheck % 2 == 0) {
				randInt = randInt * -1;
			}
			testArray[j] = randInt;
		}
		
		fprintf(outputFile, "Test Instance: %i\n", i + 1);
		// process input array through each of the four algorithms
		//mssEnumeration(outputFile, testArray, inputCount);
		//mssBetterEnumeration(outputFile, testArray, inputCount);
		mssDivideAndConquer(outputFile, testArray, inputCount);
		//mssLinearTime(outputFile, testArray, inputCount);
	}
	fclose(inputFile);
	fclose(outputFile);
	
	return 0;
}
