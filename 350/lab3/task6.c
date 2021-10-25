#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFFER_SIZE 1

int main(int argc, char** argv)
{
	char buf[BUFFER_SIZE];
	char fd1[] = "foo";
	char fd2[] = "foorev";
	int nread;

	int in = open(fd1, O_RDONLY);
	if (in == -1)
	{
		puts("Error opening read file");
		return 1;
	}

	umask(0);
	int out = open(fd2, O_WRONLY|O_CREAT, 0760);
	if(out == -1)
	{
		puts("Error opening output file");
		close(in);
		close(out);
		return 2;
	}
	int done = 0;
	int offset = 0;
	int length = 0;
	while((nread = pread(in, buf, BUFFER_SIZE, offset) > 0) && done == 0)
	{
		length++;
		offset++;
	}
	length--;
	offset = 0;
	while((nread = pread(in, buf, BUFFER_SIZE, offset) > 0) && done == 0)
	{
		if(pwrite(out, buf, nread, length-offset) == -1)
		{
			printf("Write error in file\n");
			return 3;
		}
		offset += 1;
	}
	close(in);
	close(out);
	if(nread == -1)
	{
		printf("Read error");
		return 4;
	}
	return 0;
}
