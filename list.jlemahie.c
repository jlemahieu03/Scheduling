// jdh CS3010 Fall 2024

#include <stdio.h>
#include <stdlib.h>
#include "list.jhibbele.h"

//--------------------------------------------------------------------------

int insertItem(ListNode **theList, void *item, ComparisonFunction compare) {
  ListNode *newNode, *currNode, *prevNode;

  newNode = (ListNode *) malloc(sizeof(ListNode));
  newNode->data = item;
  newNode->next = NULL;

  if (*theList == NULL) {
    *theList = newNode;
    return 0;
  }

  currNode = *theList;
  prevNode = NULL;
  int done = 0;
  while ( ! done ) {
    if (currNode == NULL)
      done = 1;
    else {
      if (compare(item, currNode->data) < 0)
        done = 1;
    }
    if ( ! done ) {
      prevNode = currNode;
      currNode = currNode->next;
    }
  }

  newNode->next = currNode;
  if (prevNode != NULL)
    prevNode->next = newNode;
  else
    *theList = newNode;

  return 0;
} // insertItem()

//--------------------------------------------------------------------------

void *removeItem(ListNode **theList, void *item, ComparisonFunction compare) {
  ListNode *curr, *prev;
  int done = 0;

  curr = *theList;
  prev = NULL;

  while ( curr != NULL && ! done ) {
    if ( compare(item, curr->data) == 0 ) {
      done = 1;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  if (curr == NULL)
    return NULL;

  void *rtnval;
  if (prev != NULL) {
    prev->next = curr->next;
    rtnval = curr->data;
    free(curr);
  } else {
    *theList = curr->next;
    rtnval = curr->data;
    free(curr);
  }

  return rtnval;
} // removeItem()

//--------------------------------------------------------------------------

void *findItem(ListNode *theList, void *item, ComparisonFunction compare) {
  ListNode *curr;
  int done = 0;

  curr = theList;

  while ( curr != NULL && ! done ) {
    if ( compare(item, curr->data) == 0 ) {
      done = 1;
    } else {
      curr = curr->next;
    }
  }

  if (curr == NULL)
    return NULL;
  else
    return curr->data;
} // findItem()

//--------------------------------------------------------------------------

int printList(ListNode *theList, PrintFunction print) {
  ListNode *currNode;
  currNode = theList;
  while (currNode != NULL) {
    print(currNode->data);
    currNode = currNode->next;
  }

  return 0;
}

//--------------------------------------------------------------------------

void *removeNthItem(ListNode **theList, int pos) {
  ListNode *prev, *curr;

  if (*theList == NULL)
    return NULL;

  int idx = 0;
  curr = *theList;
  prev = NULL;
  while (curr != NULL && idx < pos) {
    prev = curr;
    curr = curr->next;
    idx = idx + 1;
  }

  if (curr == NULL)
    return NULL;

  if (pos == 0)
    *theList = curr->next;
  else
    prev->next = curr->next;

  void *data = curr->data;
  free(curr);
  return data;
}

//--------------------------------------------------------------------------

void *findNthItem(ListNode **theList, int pos) {
  ListNode *prev, *curr;

  if (*theList == NULL)
    return NULL;

  int idx = 0;
  curr = *theList;
  prev = NULL;
  while (curr != NULL && idx < pos) {
    curr = curr->next;
    idx = idx + 1;
  }

  if (curr == NULL)
    return NULL;

  return curr->data;
}
