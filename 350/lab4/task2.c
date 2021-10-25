#include <stdio.h> // Standard I/O
#include <stdlib.h> // Standard Library
#include <fcntl.h> // open()
#include <unistd.h> // lseek(), read()
#include <string.h> // String functions
#include <ctype.h> // isdigit()
#include <stdbool.h> // bool alias


#define BUFFER_SIZE 81

int convIntToStr(char* str, int x) {
	sprintf(str, "%d\n", x);
	return (strlen(str));
}


int myAtoI(char* num) {
	// Subtract the ASCII 0 from each digit and then multiply by each
	// decimal place to get out number back
	int i, result = 0;
	bool isNum = true, isNegative = false;
	for (i = 0; num[i] != '\0'; i++) {
		result = result * 10 + num[i] - '0';
	}
	return result;
}

int main(int argc, char** argv) {

	// Check to see if argument # is correct
	if (argc != 2) {
		puts("*** Invalid # of arguments ***");
		return 1; // Returning because the # of arguments is incorrect
	}


	int infd;
	// Create the number buffer
	char numBuff[BUFFER_SIZE];
	// Create the read-in buffer
	char readBuff[BUFFER_SIZE];
	// Make sure there are no weird errors
	memset(readBuff, 0, BUFFER_SIZE);




	infd = open(argv[1], O_RDONLY);
	if (infd == -1) {
		puts("*** Error opening the file ***");
		return 2; // Returning because there was an error opening the file
	}




	int nbyte;
	// Read in up to 80 chars in the file
	if ((nbyte = read(infd, readBuff, BUFFER_SIZE)) == -1) {
		puts("*** Read error ***");
		close(infd);
		return 3; // Returning because there was a read error
	}






	int counter = 0;
	int i; // Variable counter
	for (i = 0; readBuff[i] != '\0'; i++) {
		// Using isdigit to check if the char is a digit or not
		if (isdigit(readBuff[i])) {
			// Enter into the numBuff string and increment the outer counter
			numBuff[counter] = readBuff[i];
			counter++;
		}
	}
	numBuff[counter] = '\0'; // Append the null terminator to the end
	counter++;



	printf("String found: %s\n", numBuff);

	// Now convert the string to an integer
	int converted = myAtoI(numBuff);

	// Add 10 to the integer
	converted += 10;

	// Create a new buffer to hold the integer that will be converted
	// to a string
	char newStringBuff[BUFFER_SIZE];
	// Convert the ingeger to a string and get the length of it back
	int lengthOfNSB = convIntToStr(newStringBuff, converted);

	// Use a system call to write the string to standard output
	write(1, newStringBuff, lengthOfNSB);

	// Close the file descriptor
	close(infd);

	return 0;
}
