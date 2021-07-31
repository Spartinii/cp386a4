#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<unistd.h>
#include<pthread.h>
#include <semaphore.h>

// Github ID: Spartinii
// Github Repo: https://github.com/Spartinii/cp386a4



// Bank methods
void status();
void addCustomer(int threadNum, int maxDemand[]);
bool requestResources(int threadNum, int request[]);
void releaseResources(int threadNum, int release[]);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

	int i;
    char *value;

    for(i = 1; i < argc; i++) {
        // The integers given is read as (char *)
        value = argv[i];
        printf("Command line index: %d value: %s in ascii: %d\n", i, value, *value);	
    }

	int a[5] = {1,2,3,4,5};

	// Function tests
	addCustomer(5, a);
	bool b = requestResources(5, a);
	printf("Bool Result: %d\n", b);
	releaseResources(5, a);
	status();

}


// Bank Methods
void addCustomer(int threadNum, int maxDemand[]){
	printf("TADA %d", threadNum);

	printf("WOO %d", maxDemand[0]);
	printf("\n");
}

bool requestResources(int threadNum, int request[]){
	printf("requested resources at %d, %d\n", threadNum, request[0]);
	return true;
}

void releaseResources(int threadNum, int release[]){
	printf("requested resources at %d, %d\n", threadNum, release[0]);
}

void status(){
	// prints status of all threads in memory
	printf("Current Status %d, %d, %d, %d\n", 0, 0, 0, 0);
}

