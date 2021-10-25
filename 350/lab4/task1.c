#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library 
#include<string.h> // String functions
#include<fcntl.h> // open()
#include<unistd.h> // read(), write()
#include<stdbool.h> // bool alias
#include<sys/stat.h> // umask()




int myAtoI(char* num, int buffSize) {
	// Subtract the ASCII 0 from each digit and then multiply by each
	// decimal place to get out number back
	int i, result = 0;
	for (i = 0; i < buffSize; i++) {
		result = result * 10 + num[i] - '0';
	}
	return result;
}


int main(int argc, char** argv) {

	// Create buffer

	if (argc != 3) {
		puts("*** Invalid # of arguments ***");
		return 1; // Returning because the # of arguments passed is invalid
	}


	int infd;
	// Output file descriptor
	int outfd;

	infd = open(argv[1], O_RDONLY);
	// Check to make sure the file opened correctly
	if (infd == -1) {
		puts("*** Error opening the first file ***");
		return 2; // Returning because there was an error opening the first file
	}


	outfd = open(argv[2], O_CREAT | O_WRONLY, 0666);
	// Check to make sure the file was created/opened correctly
	if (outfd == -1) {
		puts("*** Error opening/creating the second file ***");
		close(infd);
		return 3; // Returning because there was an error opening/reading the second file
	}


	// Create the read buffer
	char readBuff[1];
	// Create the number buffer
	char numBuff[3];
	// Zero out the buffer
	memset(numBuff, 0, 3);
	// Create endline buffer
	char endlineBuff[] = {'\n'};
	// Create the write buff
	char writeBuff[1];
	// Read byte
	int nbyte;
	// numbuff counter
	int counter = 0;
	// Temp conversion int

	int temp; 


	while ((nbyte = read(infd, readBuff, 1)) > 0) {
		if (readBuff[0] == ' ') {
			// Convert the buffer to an integer
			temp = myAtoI(numBuff, counter); 
			// Convert the integer to a char
			writeBuff[0] = (char)temp; 
			// Write that char to a file
			if (write(outfd, writeBuff, 1) != 1) {
				puts("*** Write Error ***");
				close(infd);
				close(outfd);                                                                                                                     
				return 4; // Returning because there was an error writing to the file
			}
			memset(numBuff, 0, 3);
			counter = 0;

		} else if (readBuff[0] == '\n') {
			if (write(outfd, endlineBuff, 1) != 1) {
				puts("*** Write error ***");
				close(infd);
				close(outfd);
				return 5; // Returning because there was a write error
			}
		} else {
			numBuff[counter++] = readBuff[0];
		}
	}
	if (nbyte == -1) {
		puts("*** Read error ***");
		close(infd);
		close(outfd);
		return 6; // Returning because there was a read error
	}

	// Close the files
	close(infd);
	close(outfd);

	return 0;

}
