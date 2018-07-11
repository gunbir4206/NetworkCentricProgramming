#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fileManager.h"

int main(int argc, char** argv)
{
	int count = 0;		//count of occurence of substring in the string
	int length = 0;		//file length
	int lengthOarg;	    //argument lenght
	int position = 0; 	//position within the string
	int curr = 1;		//Current position in argv
	int maxLength;  	//max length for stop searching
	int isSet = 0;		//Holds whether or not the flag is set
	int t = 0;			//needed for counting
	char* buff;			//Buffer 
	char* fileString;	//store file contents
	
	
	//clock_t start, end;	//start = clock(); used for evaulating execution time
	if (argc == 1)
	{
		fprintf(stderr, "%s: No arguments provided \n", argv[0]);
		return 0;
	}
	if (argc == 2 && strcmp("-s", argv[curr]) == 0)
	{
		fprintf(stderr, "%s: No file or arguments provided\n", argv[0]);
		return 0;
	}
	else if (strcmp("-s", argv[curr]) == 0)
	{
		isSet = 1;
	}
	if (argc == 2 && isSet == 0)
	{
		fprintf(stderr, "%s: No arguments provided\n", argv[0]);
		return 0;
	}
	if (isSet == 1)
	{
		if (Exists(argv[curr + 1]) == 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return 0;
		}
	}
	else
	{
		if (Exists(argv[curr]) == 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", argv[0]);
			return 0;
		}
	}
	if (argc == 3 && isSet == 1)
	{
		fprintf(stderr, "%s: You must enter something to be found\n", argv[0]);
		return 0;
	}
	if(isSet == 0)  //flag position
	{
		fileString = fileToStringSTDIO(argv[curr]); //standard I/O call
		if(strlen(fileString) == 0)					//Chech file for content
		{
			fprintf(stderr, "File is empty, no appropriate actions can be taken!\n");
			return 0;
		}
		curr++;
	}
	else
	{
		fileString = fileToStringSYSTEM(argv[curr + 1]); //system call
		if(strlen(fileString) == 0)						 //check file for content
		{
			fprintf(stderr, "File is empty, no appropriate actions can be taken!\n");
			return 0;
		}
		curr = curr + 2;
	}
	length = strlen(fileString) - 1; //lenght of the argument
	
	//Grab each argument one at a time
	while(curr < argc)
	{
		lengthOarg = strlen(argv[curr]);
		maxLength = length - lengthOarg;
		if(lengthOarg > length) //incase the length of argument is greater than that of string length
		{
			fprintf(stderr, "0\n");
			curr++;
			count = 0; //reinitialize
			position = 0;
			continue;
		}
		buff = calloc(0,lengthOarg*sizeof(char)); //create buffer
		while(position <= maxLength)// find number of occurence
		{
			for(t = 0; t < lengthOarg; t++) //next substring
			{	
				buff[t] = fileString[position+t];
			}
			if(strcmp(buff, argv[curr]) == 0)
			{
				count++;
			}
			position++;
		}
		fprintf(stdout, "%d\n", count);
		free(buff);
		curr++;
		count = 0; //reinitialize
		position = 0;
	}
	//end = clock();//printf("Execution time: %fs\n", (double) (end-start)/CLOCKS_PER_SEC); // used to find the execution time
	return 0;
}
