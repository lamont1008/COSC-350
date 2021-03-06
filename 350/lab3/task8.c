#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library 
#include<string.h> // String functions
#include<fcntl.h> // open()
#include<unistd.h> // read(), write()
#include<stdbool.h> // bool alias
#include<sys/stat.h> // umask()


#define BUFFER_SIZE 1

int myAtoItoA(char num, char* buffer) {
	// Subtract the ASCII 0 from each digit and then multiply by each
	// decimal place to get out number back
	int asciiInt = 0;
	asciiInt = num - '\0';
	int numDigits;
	if (asciiInt >= 100) {
		numDigits = 3;
	} else if (asciiInt >= 10) {
		numDigits = 2;
	} else {
		numDigits = 1;
	}

	int i = numDigits - 1;
	while (asciiInt != 0) {
		buffer[i--] = asciiInt % 10 + '0';
		asciiInt /= 10;
	}
	return numDigits;
}


int main(int argc, char** argv) {

	// Create buffer
	char buff[BUFFER_SIZE];
	// Create full path buffer
	char fullpath[120]; // Large in case of abnormally long path
	// For home variable
	char* homedir;

	if (argc != 3) {
		puts("*** Invalid # of arguments ***");
		return 1; // Returning because the # of arguments passed is invalid
	}


	strcpy(fullpath, argv[1]);

	// Open the first file as READ ONLY
	int readfd = open(fullpath, O_RDONLY);
	// Check if the file opened correctly
	if (readfd == -1) {
		puts("*** Read error ***");
		return 3; // Returning because there was a read error
	}

	umask(0);

	int writefd = open(argv[2], O_WRONLY | O_CREAT, 0666);
	// Check if the file opened correctly
	if (writefd == -1) {
		puts("*** Write error ***");
		close(readfd);
		return 4; // Returning because there was a write error
	}

	int nbyte;
	// Create a char buffer that can be filled when converting the int to ascii
	char fillBuff[3];
	int numDigits;
	//             // Need a buffer to write a space after every ascii number written to the file
	char spaceBuff[] = {' '};


	while((nbyte = read(readfd, buff, BUFFER_SIZE)) > 0) {
		if (buff[0] == '\n') {
			if (write(writefd, buff, BUFFER_SIZE) != nbyte) {
				puts("*** Write error ***");
				close(readfd);
				close(writefd);
				return 5; // Returning because there was a write error in the loop
			}
			continue;
		}
		numDigits = myAtoItoA(buff[0], fillBuff);
		if (write(writefd, fillBuff, numDigits) != numDigits) {
			puts("*** Write error ***");
			close(readfd);
			close(writefd);
			return 6; // Returning because there was a write error in the loop
		}

		if (write(writefd, spaceBuff, 1) != 1) {
			puts("*** Write error ***");
			close(readfd);
			close(writefd);
			return 7; // Returning because there was a write error in the loop
		}
	}

	if (nbyte < 0) {
		puts("*** Read error ***");
		close(readfd);
		close(writefd);
		return 6; // Returning because there was a read error in the loop
	}

	// Close the file descriptors
	close(readfd);
	close(writefd);

	return 0;
}

