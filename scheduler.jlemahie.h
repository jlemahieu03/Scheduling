//
// Created by James on 11/9/2024.
//

#ifndef SCHEDULING_SCHEDULER_JLEMAHIE_H
#define SCHEDULING_SCHEDULER_JLEMAHIE_H

typedef enum {
    RUNNING_STATE,
    READY_STATE,
    NOT_SUBMITTED_STATE
    } TaskState;

typedef struct {
    int id; // unique ID for this task
    int burstTime; // total time that this task will run
    int submitTime; // the time at which this task is submitted
    int startTime; // the time that this task started
    int endTime; // the time that this task ended
    int totalWaitTime; // the total time that this task has waited
    TaskState taskState; // this task’s state
    } Task;

void firstComeFirstServe(Task *tasks[], Task *runningTask, int numItems);

void shortestJobFirst(Task *tasks[], Task *runningTask, int numItems);

int firstComeFirstServeCompare(Task *task1, Task *task2);

int shortestJobFirstCompare(Task *task1, Task *task2);

int removeCompare(Task *task1, Task *task2);


#endif //SCHEDULING_SCHEDULER_JLEMAHIE_H
