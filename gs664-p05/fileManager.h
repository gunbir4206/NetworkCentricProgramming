#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

int isRegularFile(const char *path); //Returns 1 for a regular file and 0 for not a regular file
int Exists(const char *path);        //Returns 1 if file exists and 0 if it doesn't
long int bufferSize(FILE* fp);  //determines the number of characters in a file
char *fileToStringSTDIO(const char *path);// fileToString will take in a pointer to a FILE and will construct a single array out of the contents of the file.
char *fileToStringSYSTEM(const char *path); //fileToString will take in a pointer to a FILE and will construct a single array out of the contents of the file.
#endif
