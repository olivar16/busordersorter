/* Filename: list.c
 * Author:Paul Ryan Olivar
 *
 * Description: This file contains a full implementation of a
 *               linked-list.
 */
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


/* Function: initialize()
 *
 * Initialize a linked-list header block with size = 0 and
 * a NULL pointer to the linked list.
 *
 * CS305 students are responsible for implementing this function.
 *
 */
int initialize(ListHeader ** elPtr) {

  //allocate memory for a new ListHeader
  ListHeader*initHeader = (malloc(sizeof(ListHeader)));  

  //if pointer passed in is null, free the memory allocated memory to prevent memory leak
if (elPtr ==NULL){
  free(initHeader);
    return INITIALIZE_FAILURE;
  }
  else if (*elPtr==NULL){
    //if new list hasn't been initialized yet, do so here
     initHeader->size = 0;
     initHeader->head = NULL;
     //initialize parameter to initHeader
    *elPtr = initHeader;
       
  }


  return INITIALIZE_SUCCESS;
}

/* Function: priorityInsert() 
 * 
 * Perform a prioritized insert.  The priority for insertion is as
 * follows:
 *
 *    1. Hybrid electric buses are the highest priority.
 *    2. New buses are the second highest priority.
 *    3. All other buses have equal priority.
 *    4. Ties should be broken using the orderno field.
 * 
 *
 */
int priorityInsert(WorkOrder * newOrder, ListHeader * el)
{

  //check if either parameter passed in is NULL
  if ( (newOrder==NULL) || (el==NULL)){
    return INSERT_FAILURE;
  }

  //create ListNodes that will be adjacent to each other as we sort through the list
  ListNode*prevNode = NULL;
  ListNode*currentNode =NULL;

  //allocate memory to a new order
  ListNode * newNode = malloc(sizeof(ListNode));
  newNode->item = newOrder;
  newNode->next = NULL;
 

  // If there are no nodes in the list yet, set the first node to given work order
if (el->head == NULL){
    el->head = newNode;
    (el->size)+=1;
    return INSERT_SUCCESS;  
 }

//set prevNode to start of the list
 prevNode = el->head;   
 currentNode = prevNode->next;

   
 //if there is just one node in the list
if ((el->size) == 1){
      if ( isHigherPriority(newNode->item, prevNode->item) == 1){
	//if newNode has higher priority than prevNode, put it in front

newNode->next = prevNode;
	el->head = newNode;
	(el->size)+=1;
return INSERT_SUCCESS;
      }
      else{

	prevNode->next = newNode;
	(el->size)+=1;
	return INSERT_SUCCESS;
      }
 }
 //if there are two nodes in the list
 else if ((el->size)==2){
   if (isHigherPriority(newNode->item, prevNode->item) == 1){
    el->head = newNode;
     newNode->next = prevNode;
     (el->size)+=1;
     return INSERT_SUCCESS;
   }
   else if ( isHigherPriority(newNode->item, currentNode->item)==1 ){
     newNode->next = currentNode;
     prevNode->next = newNode;
     (el->size)+=1; 
return INSERT_SUCCESS;
   }
   else{
     currentNode->next = newNode;
     (el->size)+=1;
     return INSERT_SUCCESS;
   }

 }

     
    
//else do the regular routine
//iteratively compare every node on the list
 int ctr = 0;  
    while ( currentNode!=NULL){

      //check first node      
if ( ctr==0){

	if ( isHigherPriority(newNode->item, prevNode->item) == 1){
	  newNode->next = prevNode;
	  el->head = newNode;
	  (el->size)+=1;
	  return INSERT_SUCCESS;
	}
	ctr++;
      }

      //compare newNode and currentNode for priority status
      if ((isHigherPriority(newNode->item, currentNode->item))==1){
	//if true, put newNode at the front of currentNode
	newNode->next = currentNode;
prevNode->next = newNode;
	(el->size)+=1;
	return INSERT_SUCCESS;
      }
     
      
      //iterate to the next node
      prevNode = prevNode->next;
      currentNode = currentNode->next;

    }
    prevNode->next = newNode;    
    (el->size)+=1; //increment list size 
   return INSERT_SUCCESS;
}




 


/*
 * Function: isHigherPriority
 *  
 * Given two pointers to WorkOrders, return 1 if the first is higher priority
 * and 0 otherwise.
 *
 * CS305 may choose to implement this function to assist with
 * implementing priorityInsert().
 */
int isHigherPriority(WorkOrder * first, WorkOrder * second)
{
  //get order numbers 
  int firstNum = atoi(first->orderno);
  int secondNum = atoi(second->orderno);

  //New order is Hybrid Electric
  if(isHybridElectric(first) == 1){
    if (isHybridElectric(second) == 1){
      //allocate priority based on order number     
if( firstNum > secondNum){
	return 0;
 }
      else{
	return 1;}
    }

    return 1;

  }

  //New order is part of new fleet
  if (isNewFleet(first) == 1){
    if(isNewFleet(second) == 1){
      if ( firstNum > secondNum){
	return 0;
      }
      return 1;
    }
    else if (isHybridElectric(second)==1){
      return 0;
    }
    else{
      return 1;
    }

  }

  //New order is neither Hybrid nor new  
  if ( (isHybridElectric(second)==1) || (isNewFleet(second)==1)){
   
    return 0;
  }
  //if comparing to another bus of last priority, compare their order numbers
if(firstNum>secondNum){
return 0;
  }
  return 1;

}





/* Function: mergeSortHelper()
 *
 * Perform the mergeSort algorithm on the linked list pointed to by
 * head.  Sort the linked list lexicographically according to the
 * model field of the workorder.
 * 
 * CS305 students are responsible for implementing this function.
 */
ListNode * mergeSortHelper(ListNode * head)
{
  //check if parameter is NULL
  if ( head == NULL){
    return head;
  }
  
ListNode * headCopy = head;
int size = 0;
//get size of list
 while( headCopy!=NULL){
   size++;
   headCopy = headCopy->next;
 }

 if ( size==1){
   return head;
 }

 //split list into two
 ListNode*middle = head->next;
 ListNode*prev = head;
 int i = 0;
 while ((middle!=NULL) && (i<((size/2)-1))){
       middle = middle->next;
       prev = prev->next;
       i++;
     }
     prev->next = NULL;
     //middle is pointed at beginning of second 2nd half
     //prev is pointed at ending of first half

     return merge(mergeSortHelper(head), mergeSortHelper(middle));
}

/* Function: freeList
 * 
 * Free all memory allocated for the linked list, including the linked
 * list header block.
 *
 * CS305 students are responsible for implementing this function.
 */
void freeList(ListHeader ** el)
{
  //check if pointer is null
  if (el==NULL){
    return;
  }

  ListHeader*List=*el;

  int size = (*el)->size;
  int i = 0;
 
  ListNode*currNode = (*el)->head;
  free(*el);
for ( i = 0; i< size; i++){
    free(currNode);
    currNode=currNode->next;
  }



  return;
}


/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */

/* Function: printList()
 *
 * Print the linked list pointed to by the Linked List header block
 * pointer, el.
 * 
 * IMPORTANT! CS305 Students SHOULD NOT alter this function.  It's
 * already done for you.
 */
void printList(ListHeader * el)
{
  int i = 0;
  ListNode * current = NULL;
  
  if(el == NULL)
    {
      printf("uninitialized list\n");
      return;
    }

  if(el->size == 0)
    {
      printf("empty list\n");
      return;
    }

  current = (el->head);

  printf("   There are %d items in the list:\n   ", el->size);

  while(current != NULL) {
      printf("%s ", current->item->orderno);
      current = current->next;
    }

  printf("\n");

  return;
}


/* Function: mergeSort()
 * 
 * Instead students must implement mergeSortHelper and allow this
 * function to set the result of mergeSortHelper in the Linked List
 * header block.
 */
void mergeSort(ListHeader * el)
{


    el->head = mergeSortHelper(el->head);
}


ListNode*merge(ListNode*left, ListNode*right){
  ListNode*head = NULL;
 

  if (left==NULL){
    return right;
  }

  if ( right==NULL){
    return left;
  }


 int leftNum = atoi(left->item->orderno);
  int rightNum = atoi(right->item->orderno);

    if ( leftNum < rightNum){

      head = left;
      head->next = merge(left->next, right);
    }

    else{
      head = right;
      head ->next = merge (left, right->next);

    }
    return head;
 

}
