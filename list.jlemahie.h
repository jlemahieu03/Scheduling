// jdh CS 3010 Fall 2024

typedef struct ListNodeStruct {
  void *data;
  struct ListNodeStruct *next;
} ListNode;

typedef int (* ComparisonFunction)(void *, void *);
typedef void (* PrintFunction)(void *);

int insertItem(ListNode **theList, void *item, ComparisonFunction compare);

void *findItem(ListNode *theList, void *item, ComparisonFunction compare);

void *removeItem(ListNode **theList, void *item, ComparisonFunction compare);

void *removeNthItem(ListNode **theList, int pos);

void *findNthItem(ListNode **theList, int pos);

int printList(ListNode *theList, PrintFunction print);
