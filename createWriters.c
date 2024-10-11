#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <assert.h>
#include <time.h>
#include "MallocCheck.h"

// Prototypes
void ForkWRITER(char *SegmentID_String);

int main(void)
{
    int sleepsecs, SegmentID;
    srand(time(NULL)); // intialize random number generator

    printf("Please enter the shared memory segment's ID: ");
    scanf("%d", &SegmentID);

    // Memory allocation for the Shared ID string
    char *SegmentID_String = malloc(10 * sizeof(char));
    MallocCheck(SegmentID_String);

    // Convert the shared ID into string form
    sprintf(SegmentID_String, "%d", SegmentID);

    for (int i = 0; i < 10; i++)
    {   
        sleepsecs = rand() % 10;
        printf("Sleeping for %d secs...\n", sleepsecs);
        sleep(sleepsecs);

        printf("Forking a writer (#%d)...\n", i);
        ForkWRITER(SegmentID_String);
    }
    
    return 0;
}

void ForkWRITER(char *SegmentID_String)
{
    pid_t ForkValue;

    ForkValue = fork();

    if (ForkValue != 0) // I am the parent
    {
        // wait(ForkValue);
    }
    else if (ForkValue == 0) // I am the child
    {
        execlp("./write", "./write", "-f", "./SampleData4Proj3/accounts50.bin", "-l", "25", "-d", "5", "-s", SegmentID_String, "-v", "-10" ,(char *)NULL);
    }
    else // Error
    {
        perror("Forking a Writer");
    }
}