#Compiler to be used
CC = gcc

#flags for compilation
CFLAGS = -Wall -std=c99 -pedantic -g -Werror

#Final object
OUTPUT = ./p05

#More output objects
#OUTPUT1 = 
#OUTPUT2 =
#....

#Object files to be archived
LIBOBJ = ./p05.o ./fileManager.o

#Name of archive
LIBTOKEN = ./libtoken.a

#Make it so it performs both as 'make' (default case) as it does for 'make all' (make all case).
default: $(OUTPUT)
all: default

#Create object (.o) file for all source files (.c). gcc -flags -c something.c -o something.o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Create the archive with all the archive files.
$(LIBTOKEN): $(LIBOBJ)
	ar rc $(LIBTOKEN) $(LIBOBJ)

#Creates output executable that contains the defined archive
$(OUTPUT): $(LIBTOKEN)
	$(CC) $(CFLAGS) $(LIBTOKEN) -o $@
	make clean

#Clean up all onject files and swp files and archives. Call by self with 'make clean'
clean:
	rm -f *.o *~
	rm -f $(LIBTOKEN)
