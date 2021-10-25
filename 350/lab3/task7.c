#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<string.h> // String functions
#include<stdbool.h> // bool alias

int myAtoI(char* num) {
	// Subtract the ASCII 0 from each digit and then multiply by each
	// decimal place to get out number back
	int i, result = 0;
	bool isNum = true; 
	bool isNegative = false;

	for (i = 0; num[i] != '\0'; i++) {
		// Check to see if they input a negative number
		if (num[i] == '-' && i == 0) {
			isNegative = true;
			continue;
		}

		if (num[i] < '0' || num[i] > '9') {
			// If invalid, isNum will be false
			isNum = false;
			break;
		}
		result = result * 10 + num[i] - '0';
	}
	if (isNegative) {
		result *= -1;
	}

	// return -0 -> This will be handled in the calling process
	if (!isNum) {
		return -0;
	}                     return result;
	return result;
}

void printSum(int argc, char** argv) {
	// Declare the counter and initialize the sum
	int i, j, sum = -1, check;
	bool isFirstRealNum = true;
	// Loop through the strings and the chars
	for (i = 1; i < argc; i++) {
		// Need to check if the argument is a valid integer
		if ((check = myAtoI(argv[i])) != -0) {
			if (isFirstRealNum) {
				isFirstRealNum = false;
				sum = 0;
			}
			sum += check;
		}
	}

	if (isFirstRealNum) {
		puts("*** There is not at least one integer on the command line. ***");
	} else {
		printf("Sum: %d\n", sum);
	}
}


int main(int argc, char** argv) {

	// Make sure the argument count is correct
	if (argc < 2) {
		puts("*** Invalid # of args ***");
		return 1; // Return because the number of arguments was incorrect
	}

	// Print the sum of the digits of the argument
	printSum(argc, argv);

	return 0;
}
