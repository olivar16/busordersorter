/* Filename: workorder.c
 * Created by: Paul Ryan Olivar
 * Date created: 2/15/2014
 *
 * Description: This file contains the functions necessary to
 *              allocate, print, and assess a work order data type.  A
 *              work order describes the fleet number, manufacturer,
 *              model, and problem description for a particular bus in
 *              the tri-met fleet that requires maintenance or repair.
 *
 *       Thank you.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "workorder.h"


/* Function: isHybridElectric() 
 * Parameters: 1. w: A pointer to a workorder.
 *
 * Description: This function returns 1 (or true) if a bus model
 *              contained in a work order is hybrid electric and 0 (or
 *              false) otherwise.
 */
int isHybridElectric(WorkOrder * w)
{

  if (w == NULL)
    return -1;

  if(strncmp(w->model, "BRT(HE)", 8) == 0)
    return 1;

  return 0;
}


/* Function: isNewFleet()
 * Parameters: 1. w: A pointer to a workorder.
 * 
 * Description: This function returns 1 (or true) if a bus model
 *              contained in a work order is from the newest set of
 *              buses in the Tri-Met fleet and 0 (or false) otherwise.
 */
int isNewFleet(WorkOrder * w)
{
  if (w == NULL)
    return -1;

  int fleetNumber = atoi(w->fleetno);

  if (fleetNumber > 3100)
    return 1;

  return 0;
}


/* Function: isB5Biodiesel()
 * Parameters: 1. w: a pointer to a workorder.
 * 
 * Description: This function returns 1 (or true) if a bus model
 *              contained in a work order is a diesel bus and 0 (or
 *              false) otherwise.
 */
int isB5Biodiesel(WorkOrder * w)
{
  if (w == NULL)
    return -1;

  if(strncmp(w->model, "D40LF", 10) == 0)
    return 1;

  if(strncmp(w->model, "D40LFR", 10) == 0)
    return 1;

  return 0;
}

/* Function: allocateWorkOrders()
 * Parameters: 1. filename: the name of a file to be parsed.
 *             2. wPtr: The address of a pointer to a workorder.
 * 
 * Description: This function opens a file named "filename", reads
 *              each work order in the file, and stores it in memory
 *              pointed to by the contents of w.  It returns the total
 *              number of work orders allocated.
 */
int allocateWorkOrders(const char * filename, WorkOrder ** wPtr)
{
  FILE * ifp;
  char inputArray[MAXLENGTH];
  char * c = inputArray;
  int lineCount = 0;
  int i, j;

  char line[MAXLINE];
  char ** temp = NULL;
  char * thisWord = NULL;

  if((ifp = fopen(filename, "r")) == NULL)
    {
      return 0;
    }

  // Open the file and count the number of lines in the file
  // to determine how large the array should be.
  while(fgets(line, MAXLINE, ifp) != NULL)
    {
      lineCount++;
    }

  // The number of lines is known.  Allocate a contiguous block
  // of memory to store the work order array.
  *wPtr = malloc(lineCount * sizeof(WorkOrder));

  close(ifp);

  ifp = fopen(filename, "r");
  fseek(ifp, 0, SEEK_SET);

  temp = (char **) *wPtr;

  // Since the format and the number of lines of the file is known
  // execute this loop "lineCount" number of times:
  for (i = 0; i < lineCount; i++)
    {
      
      // Read the first four words, allocate space for each one, and add its 
      // pointer to the array of character pointers which comprise the 
      // work order list.
      for(j = 0; j < 4; j++) {
	if (fscanf(ifp, "%s", c) == 1)
	  {

	    // Allocate space for this word.
	    thisWord = malloc((int)strlen(c));

	    // Copy the word to the array.
	    strncpy(thisWord, c, (int)strlen(c));
	    *temp = thisWord;

	    temp++;
	  }  
      }

      // Read th rest of the line and store it in the last entry.
      fgets(line, MAXLINE, ifp);
     
      // Allocate space for this word.
      thisWord = malloc((int)strlen(line));

      // Copy the word to the array.
      strncpy(thisWord, line, (int)strlen(line));
      *temp = thisWord;

      temp++;
    }

  close(ifp);

  return lineCount;
}


/* Function: printWorkOrder()
 * Parameters: 1. w: a pointer to a work order.
 *
 * Description: Pretty-print the contents of the individual work order
 *              data structure.
 */
void printWorkOrder(WorkOrder * w)
{
  printf("+---------------------------------------------------------------------+\n");
  printf("|  #%2d. | Fleet No. %s. | Model: %s. | Mfr: %s.\n", atoi(w->orderno), w->fleetno, w->model, w->manufacturer);
  printf("|       | Problem description: %s", w->description);
  printf("+---------------------------------------------------------------------+\n");
}

/* Function: printWorkOrders()
 * Parameters: 1. w: a pointer to a work order.
 *             2. number: the total number of work orders to be printed.
 *
 * Description:  This function prints a 'number' total of work orders
 *               to the console using the printWorkOrder() function,
 *               starting from the first work order and ending at the
 *               'number'th workorder.
 */
void printWorkOrders(WorkOrder * w, int number)
{
  int i;

  // Print all the work orders.
  for(i = 0; i < number; i++)
    {
      printWorkOrder(w);
      w++;
    }

  printf("Line %d reached", __LINE__);
}


/* Function: freeWorkOrders()
 * Parameters: 1. wPtr: the address of a pointer to an array of work orders.
 *             2. number: the total number of work orders to be freed.
 *
 * Description: This function frees all memory allocated to the array
 *              of work orders.
 */
void freeWorkOrders(WorkOrder ** wPtr, int number)
{
  int i = 0;
  WorkOrder * w = *wPtr;

  for(i=0; i < number; i++)
    {
      free(w->orderno);
      free(w->fleetno);
      free(w->manufacturer);
      free(w->model);
      free(w->description);
      w++;
    }

  free(*wPtr);

  *wPtr=NULL;  // Avoid the dangling pointer!

  return;
}
