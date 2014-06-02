# Filename: Makefile (for hw3)
# Author: <CS305 STUDENT WRITE NAME HERE>  
# Created by: Tanya L. Crenshaw
# Date created: 2/09/2014
#
CC = gcc
SRCS = main.c list.c workorder.c
OBJS = main.o list.o workorder.o

# Compile the hw3 executable from a list of object files.  If none of
# the object files has changed, make will report 'hw3 is up to date.'
hw3:	$(OBJS)
	$(CC) -o hw3 $(OBJS)

# A rule to create a .o file for each .c file found in this directory.
%.o:	%.c
	$(CC) -c -o $@ $<

# A rule to clean up the directory of all object files and executable
# file.
clean:
	rm -f hw3
	rm -f *~
	rm -f $(OBJS)

