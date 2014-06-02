/* Filename: workorder.h
 * Created by: Paul Ryan Olivar
 * Date created: 2/09/2014
 *
 *
 * Description: This file contains the type definitions necessary to
 *              implement a work order data type.  A work order
 *              describes the fleet number, manufacturer, model,
 *              and problem description for a particular bus or 
 *              train in the tri-met fleet that requires maintenance
 *              or repair.
 *
 *
 *       Thank you.
 */

#ifndef __WORKORDER_H__
#define __WORKORDER_H__

#define MAXLINE 200
#define MAXLENGTH 100

// A particular WorkOrder for a bus consists of five fields:
struct WorkOrderTag {
  char * orderno;       // The assigned order number.
  char * fleetno;       // The fleet number of the bus to be fixed.
  char * manufacturer;  // The manufacturer of the bus to be fixed.
  char * model;         // The model of the bus to be fixed.
  char * description;   // A description of the problem.
};

// Define a type, WorkOrder, to be synonymous with the above struct.
typedef struct WorkOrderTag WorkOrder;

// Function prototypes.  See description of functions in workorder.c.
int allocateWorkOrders(const char * filename, WorkOrder ** w);
void printWorkOrder(WorkOrder * w);
void printWorkOrders(WorkOrder * w, int number);
int isHybridElectric(WorkOrder * w);
int isNewFleet(WorkOrder * w);
int isB5Biodiesel(WorkOrder * w);
void freeWorkOrders(WorkOrder ** w, int number);
#endif
