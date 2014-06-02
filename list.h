/* Filename: list.h
 * Author: Paul Ryan Olivar
 * Date created: 2/09/2014
 *
 * Description: This file contains the interface for a linked list
 *              data type.  The list contains elements of type
 *              WorkOrder, as defined in workorder.h.
 */

#include "workorder.h"

#ifndef __LIST_H__
#define __LIST_H__

// Constants to use as return values from initialize()
#define INITIALIZE_SUCCESS 0
#define INITIALIZE_FAILURE -1

// Constants to use as return values from insert()
#define INSERT_SUCCESS 0
#define INSERT_FAILURE -1



/* Define the structure for a List node and a linked list header node.
 */
typedef struct ListNodeTag {
  WorkOrder * item;          // The pointer to the WorkOrder for this list item.
  struct ListNodeTag * next; // The pointer to the next node in the list. 
} ListNode;


typedef struct ListHeaderTag {
  int size;                // The current number of elements in this list
  ListNode * head;         // A pointer to the first element in this list.
} ListHeader;


/* Function prototypes for the list data type.
 */
int initialize(ListHeader ** elPtr);
int priorityInsert(WorkOrder * w, ListHeader * el);
int isHigherPriority(WorkOrder * first, WorkOrder * second);
void printList(ListHeader * el);
void mergeSort(ListHeader * el);
ListNode * mergeSortHelper(ListNode * head);
ListNode*merge(ListNode*left, ListNode*right);
#endif
