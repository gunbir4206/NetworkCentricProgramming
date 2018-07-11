#include "fileManager.h"
int isRegularFile(const char* path) //Check if it is a regular file
{	
	struct stat buf;
    	stat(path, &buf);
	return S_ISREG(buf.st_mode);
}
int Exists(const char* path) //Check the location for the existence of the file
{
	int find = 0;
	if(isRegularFile(path))
	{	
		FILE* fp = fopen(path, "r");
		if(fp != NULL)
		{
			find = 1;
		}
		fclose(fp);	
	}
	return find;
}
long int bufferSize(FILE* fp) //Buffer using std
{
	long int bsize = 0;
	fseek(fp, 0, SEEK_END); //size of file
	bsize = ftell(fp);
	rewind(fp);
	return bsize;
}
long int bufferSizeSYS(int fd) //Buffer using system call
{
	long int bsize = 0;
	bsize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return bsize;
}
char *fileToStringSTDIO(const char *path) // Coverts a file located with a given path into a string so that the contents can be worked with without the user needing to do extra work using standard I/O. */
{
	char* string = calloc(1, sizeof(char *));
	int ch = 0;
	int index = 0;
	if(isRegularFile(path))
	{
		FILE* fp = fopen(path, "r");
		if(fp != NULL)
		{
			string = calloc(bufferSize(fp), sizeof(char *));
			while((ch = fgetc(fp)) != EOF)
			{
				if((char) ch != '\n' || (char) ch != '\t' || (char) ch != '\v' || (char) ch != '\f')
				{
					string[index] = (char) ch;
					index++;
				}
				else
				{
					string[index] = ' ';
					index++;
				}
			}
		}
		fclose(fp);
	}
	return string;
}
char* fileToStringSYSTEM(const char* path)
{
	char* string = calloc(1, sizeof(char *));
	char* ch = calloc(1, sizeof(char *));
	int index = 0;
	int fd;
	if(isRegularFile(path))
	{
		fd = open(path, O_RDONLY);
		if(fd != -1)
		{
			string = calloc(bufferSizeSYS(fd), sizeof(char *));
			while(read(fd, ch, 1) != 0)
			{
				if(ch[0] != '\n' || ch[0] != '\t' || ch[0] != '\v' || ch[0] != '\f')
				{
					string[index] = ch[0];
					index++;
				}
				else
				{
					string[index] = ' ';
					index++;
				}
			}
		}
		close(fd);
	}
	free(ch);
	return string;
}
