#include<stdio.h> // Standard I/O
#include<stdlib.h> // Standard library
#include<unistd.h> // read(), write(), lseek()
#include<fcntl.h> // open()
#include<sys/stat.h> // umask()


#define BUFFER_SIZE 1


int main(void) {


	// Create the input file descriptor variable
	int infd;
	// Create the output file descriptor variable
	int outfd;
	// Create the buffer
	char buff[BUFFER_SIZE];


	//Create the string that stores the name of the input file
	char inFileName[] = "./foo";
	// Create the string that stores the name of the output file
	char outFileName[] = "./foorev";


	infd = open(inFileName, O_RDONLY);
	// Check for error
	if (infd == -1) {
		puts("*** error opening input file ***");
		return 1; // Return because input file did not open correctly
	}

	umask(0);



	outfd = open(outFileName, O_CREAT | O_WRONLY, 0760);
	// Check for error
	if (outfd == -1) {
		puts("*** error opening or creating the output file ***");
		close(infd);
		return 2; // Return because output file did not create/open correctly
	}


	int revcounter = -1;
	// Byte check
	int nbyte;



	int filesize = lseek(infd, 0, SEEK_END);
	// Start the cursor at the end of the file
	lseek(infd, revcounter, SEEK_END);
	while((nbyte = read(infd, buff, BUFFER_SIZE)) > 0) {
		if (write(outfd, buff, BUFFER_SIZE) != nbyte) {
			puts("*** error writing to file ***");
			close(infd);
			close(outfd);
			return 3; // Return because the write did not work 
		}
		if ((revcounter*-1) == filesize) {
			break;
		}
		revcounter--;
		lseek(infd, revcounter, SEEK_END);
	}
	if (nbyte < 0) {
		puts("*** error reading from file ***");
		close(infd);                                                                     
		close(outfd);                                                                                                                                                           
  		return 4;
} // Return because the read did not work
		// Close the files
		close(infd);
		close(outfd);
		return 0;
	}

