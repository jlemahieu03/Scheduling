//
// Created by James on 11/9/2024.
//
#include "list.jlemahie.c"
#include <stdlib.h>
#include <stdbool.h>
#include "scheduler.jlemahie.h"


int main() {
    //declaring and setting running task to null
    Task *runningTask = NULL;

    //creating all tasks and adding to array
    Task *T1 = malloc(sizeof(Task));
    T1->id = 0;
    T1->burstTime = 6;
    T1->submitTime = 0;

    Task *T2 = malloc(sizeof(Task));
    T2->id = 1;
    T2->burstTime = 8;
    T2->submitTime = 2;

    Task *T3 = malloc(sizeof(Task));
    T3->id = 2;
    T3->burstTime = 7;
    T3->submitTime = 4;

    Task *T4 = malloc(sizeof(Task));
    T4->id = 3;
    T4->burstTime = 3;
    T4->submitTime = 8;

    Task *tasks[] = {T1, T2, T3, T4};

    int numItems;
    numItems = sizeof(tasks) / sizeof(Task *);

    firstComeFirstServe(tasks, runningTask, numItems);
    shortestJobFirst(tasks, runningTask, numItems);

    free(T1);
    free(T2);
    free(T3);
    free(T4);
    return 0;
}

void firstComeFirstServe(Task *tasks[], Task *runningTask, int numItems){
    int i;
    int currentTime = 0;
    int totalWaitTime = 0;
    bool done = false;
    bool tasksNotLeftBehind = true;
    ListNode *ready = NULL;

    //setting all task states to not submitted
    for (i = 0; i < numItems; ++i){
        tasks[i]->taskState = NOT_SUBMITTED_STATE;
    }

    //setting current time to 0

    //doing scheduling
    while (!done){
        //for each item in list check if current time equals their submit time
        //if task does equal submit time then the task is inserted into te ready queue and\
        //it is put into the ready state
        for (i = 0; i < numItems; ++i){

            if (currentTime == tasks[i]->submitTime) {
                insertItem(&ready, tasks[i], (ComparisonFunction) firstComeFirstServeCompare);
                tasks[i]->taskState = READY_STATE;
            }
        }

        if (runningTask == NULL){
            if (ready != NULL){
                Task *Front = ready->data;
                runningTask = Front;
                tasks[Front->id]->taskState = RUNNING_STATE;
                tasks[Front->id]->startTime = currentTime;
                removeItem(&ready, Front, (ComparisonFunction) removeCompare);
            }
        }

        if (runningTask != NULL){
            if ((runningTask->burstTime + runningTask->startTime) == currentTime){
                tasks[runningTask->id]->endTime = currentTime;
                tasks[runningTask->id]->totalWaitTime = tasks[runningTask->id]->startTime - tasks[runningTask->id]->submitTime;
                runningTask = NULL;
                if (ready != NULL){
                    Task *Front = ready->data;
                    runningTask = Front;
                    tasks[Front->id]->taskState = RUNNING_STATE;
                    tasks[Front->id]->startTime = currentTime;
                    removeItem(&ready, Front, (ComparisonFunction) removeCompare);
                }
            }

        }

        tasksNotLeftBehind = true;
        for (i = 0; i < numItems; ++i){
            if (tasks[i]->taskState == NOT_SUBMITTED_STATE){
                tasksNotLeftBehind = false;
            }
        }


        if(runningTask == NULL && ready == NULL && tasksNotLeftBehind){
            done = true;
        }

        currentTime = currentTime + 1;
    }
    for (i = 0; i < numItems; ++i){
        totalWaitTime = totalWaitTime + tasks[i]->totalWaitTime;
    }

    for (i = 0; i < numItems; ++i) {
        printf("T%d %4d %4d %4d %4d %4d\n", i+1,tasks[i]->burstTime, tasks[i]->submitTime, tasks[i]->startTime, tasks[i]->endTime, tasks[i]->totalWaitTime);
    }
    printf("total wait time = %d\n", totalWaitTime);
}

void shortestJobFirst(Task *tasks[], Task *runningTask, int numItems) {
    int i;
    int currentTime = 0;
    int totalWaitTime = 0;
    bool done = false;
    bool tasksNotLeftBehind = true;
    ListNode *ready = NULL;

    //setting all task states to not submitted
    for (i = 0; i < numItems; ++i) {
        tasks[i]->taskState = NOT_SUBMITTED_STATE;
    }

    //setting current time to 0

    //doing scheduling
    while (!done) {
        //for each item in list check if current time equals their submit time
        //if task does equal submit time then the task is inserted into te ready queue and\
        //it is put into the ready state
        for (i = 0; i < numItems; ++i) {

            if (currentTime == tasks[i]->submitTime) {
                insertItem(&ready, tasks[i], (ComparisonFunction) shortestJobFirstCompare);
                tasks[i]->taskState = READY_STATE;
            }
        }

        if (runningTask == NULL) {
            if (ready != NULL) {
                Task *Front = ready->data;
                runningTask = Front;
                tasks[Front->id]->taskState = RUNNING_STATE;
                tasks[Front->id]->startTime = currentTime;
                removeItem(&ready, Front, (ComparisonFunction) removeCompare);
            }
        }

        if (runningTask != NULL) {
            if ((runningTask->burstTime + runningTask->startTime) == currentTime) {
                tasks[runningTask->id]->endTime = currentTime;
                tasks[runningTask->id]->totalWaitTime =
                        tasks[runningTask->id]->startTime - tasks[runningTask->id]->submitTime;
                runningTask = NULL;
                if (ready != NULL) {
                    Task *Front = ready->data;
                    runningTask = Front;
                    tasks[Front->id]->taskState = RUNNING_STATE;
                    tasks[Front->id]->startTime = currentTime;
                    removeItem(&ready, Front, (ComparisonFunction) removeCompare);
                }
            }

        }

        tasksNotLeftBehind = true;
        for (i = 0; i < numItems; ++i) {
            if (tasks[i]->taskState == NOT_SUBMITTED_STATE) {
                tasksNotLeftBehind = false;
            }
        }


        if (runningTask == NULL && ready == NULL && tasksNotLeftBehind) {
            done = true;
        }

        currentTime = currentTime + 1;
    }
    for (i = 0; i < numItems; ++i) {
        totalWaitTime = totalWaitTime + tasks[i]->totalWaitTime;
    }

    for (i = 0; i < numItems; ++i) {
        printf("T%d %4d %4d %4d %4d %4d\n", i+1,tasks[i]->burstTime, tasks[i]->submitTime, tasks[i]->startTime, tasks[i]->endTime, tasks[i]->totalWaitTime);
    }
    printf("total wait time = %d\n", totalWaitTime);
}


int firstComeFirstServeCompare(Task *task1, Task *task2){
    return 1;
}

int shortestJobFirstCompare(Task *task1, Task *task2){
    if (task1 == NULL || task2 == NULL){
        printf("One of the Tasks given were a null pointer. Cannot compare Tasks.\n");
        return -3;
    }

    //comparing burst time and returning correct value
    if (task1->burstTime < task2->burstTime){
        return -1;
    } else if (task1->burstTime == task2->burstTime){
        return 0;
    } else {
        return 1;
    }
}

int removeCompare(Task *task1, Task *task2) {
    return 0;
}
