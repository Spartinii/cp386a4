// Github ID: Spartinii
// Github Repo: https://github.com/Spartinii/cp386a4

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// Globals
#define MAX_RESOURCES 100
#define MAX_CUSTOMERS 100
#define FNAME "sample4_in.txt"
#define CHAR_BUFFER 100
#define LINE_MAX 100

// Variables
int maximum[MAX_CUSTOMERS][MAX_RESOURCES];
int customer_count = 0;
int available[MAX_RESOURCES];
int need[MAX_CUSTOMERS][MAX_RESOURCES];
int resources_count = 0;
int allocated[MAX_CUSTOMERS][MAX_RESOURCES];
int customer_order[MAX_CUSTOMERS];

pthread_mutex_t lockResources;
pthread_cond_t condition;

// Methods
void releaseResources();
int bankersAlgo();
void requestResources();
void start();
int initMaxMatrice();
void status();
void runProgram();
void update();

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

	// bank customers
	customer_count = initMaxMatrice();
	printf("Number of Customers: %d \n", customer_count);


	// print available resources
    printf("Currently Available resources:\n");
	resources_count = argc - 1;
	for(int i = 0; i < resources_count; i++){
        available[i] = atoi(argv[i + 1]);
		printf("%d ", available[i]);
    }

	// print maximum resources
	printf("\nMaximum resources from file:\n");
	for(int i = 0; i < customer_count; i++){
		for (int j = 0; j<resources_count; j++){
			printf("%d ", maximum[i][j]);
		}
		printf("\n");
    }

    // Program Start
    start();

    // free resources
    // free(resources_count));
    //     for(int i=0; i<customer_count; i++) {
    //          free(allocated[i]);
    //          free(need[i]);
    //          free(maximum[i]);
	// 	        
    //     }
    
}

int initMaxMatrice(){

	FILE *file_pointer = fopen("./sample4_in.txt","r");

	if (file_pointer == NULL){
		printf("file not found");
		return 0;
	}

	char str[CHAR_BUFFER];
    char *fp_array[LINE_MAX];

    while(!feof(file_pointer)){
        if(fgets(str, CHAR_BUFFER, file_pointer) != NULL){
            fp_array[customer_count] = malloc(sizeof(str) * sizeof(char));
            strcpy(fp_array[customer_count], str);
            customer_count++;
        }
    }
	for (int i = 0; i < customer_count; i++) {
		char *str = NULL;
		str = strtok(fp_array[i], ",");
		
		int j = 0;
		while (str != NULL) {
            maximum[i][j] = atoi(str);
			str = strtok(NULL, ",");
            j++;
		}
	}

    return customer_count;
}

// Bank Required Functions

void start(){
    char command[CHAR_BUFFER];
    while(1){
        printf("Enter Command: ");
        scanf("%s", command);
        
        if(strcmp(command, "Exit") == 0){
            break;
        } else if(strcmp(command, "Status") == 0){
            status();
        } else if(strcmp(command, "Run") == 0){
            runProgram();
        } else if(strcmp(command, "RQ") == 0){
            requestResources();
        } else if(strcmp(command, "RL") == 0){
            releaseResources();
        }

    }
}

void status(){
	// function to output status of matrices with one call

	// available resources
	printf("Available Resources: \n");

	for(int index_i = 0; index_i< resources_count; index_i++){
		printf("%d, ", available[index_i]);
	}
	printf("\n");

	// Maximum matrice
	printf("Maximum Resources: \n");
	
	for(int index_i = 0; index_i< customer_count; index_i++){
		for (int index_j = 0; index_j < resources_count; index_j++){
			printf("%d ", maximum[index_i][index_j]);
		}
		printf("\n");
	}
	
	// Allocated matrice
	printf("Allocated Resources:\n");
    for(int index_i = 0; index_i < customer_count; ++index_i){
        for(int index_j = 0; index_j < resources_count; ++index_j){
            printf("%d ",allocated[index_i][index_j]);
        }
        printf("\n");
    }    

	// Need matrice
    printf("Need Resources:\n");
    for(int index_i = 0; index_i < customer_count; ++index_i){
        for(int index_j = 0; index_j < resources_count; ++index_j){
            printf("%d ",need[index_i][index_j]);
        }
        printf("\n");
    }    

}

void runProgram(){
    if(bankersAlgo() == 1){
        printf("Safe Sequence is:");
        for(int index_i = 0; index_i < customer_count; ++index_i){
            printf(" %d",customer_order[index_i]);
        }
        printf("\n");
        for(int index_i = 0; index_i < customer_count; ++index_i){
            printf("--> Customer/Thread %d\n", customer_order[index_i]);
            printf("    Allocated resources:");
            for(int k = 0;k < resources_count; ++k){
                printf(" %d",allocated[customer_order[index_i]][k]);
            }
            printf("\n");
            printf("    Needed:");
            for(int k = 0; k < resources_count; ++k){
                printf(" %d",maximum[customer_order[index_i]][k] - allocated[customer_order[index_i]][k]);
            }
            printf("\n");
            printf("    Available:");
            for(int k = 0; k < resources_count; ++k){
                printf(" %d",available[k]);
            }
            printf("\n");
            
            // Thread create, need to implement
            // pthread_t processes[customer_count];
            // pthread_attr_t attr;
            // pthread_attr_init(&attr);

            printf("    Thread has started\n");

            // Thread Join, need to implement
            printf("    Thread has finished\n");

            // Thread release, need to implement
            printf("    Thread is releasing resources\n");


            for(int k = 0; k < resources_count; ++k){
                available[k] += allocated[customer_order[index_i]][k];
            }
            printf("    New Available:");
            for(int k = 0; k < resources_count; ++k){
                printf(" %d",available[k]);
            }
            printf("\n");
        }
    }        
}

void requestResources(){
	int index;
    int request_count[resources_count];
    scanf("%d", &index);
    for(int i = 0; i < resources_count; ++i){
        int resource_count;
        scanf("%d", &resource_count);
        allocated[index][i] = allocated[index][i] + resource_count;
        available[i] = available[i] - resource_count;
        request_count[i] = resource_count;
    }
    update();
    if(bankersAlgo() == 1){
        printf("State is safe, and request is satisfied\n");
    } else {
        printf("State is not safe, request is not satisfied\n");
        for(int i = 0; i < resources_count; ++i){
            available[i] += request_count[i];
            allocated[index][i] -= request_count[i];
        }
        update();
    }
}

void releaseResources(){
	int index;
    scanf("%d",&index);
    for(int i = 0; i < resources_count; ++i){
        int count;
        scanf("%d", &count);
        allocated[index][i] = allocated[index][i] - count;
        available[i] = available[i] + count;
    }           
    update();

    printf("Resources Released \n") ;
}

void update(){
	for(int index_i = 0; index_i < customer_count; ++index_i){
        for(int index_j = 0; index_j < resources_count; ++index_j){
            need[index_i][index_j] = maximum[index_i][index_j] - allocated[index_i][index_j];
        }
    }
}

int bankersAlgo(){

	int work_max[MAX_RESOURCES] = {0};
	int finish_max[MAX_CUSTOMERS] = {0};
	int count = 0;

	for(int index_i = 0; index_i < MAX_RESOURCES; ++index_i){
        work_max[index_i] = available[index_i];
    }

	while(1){
        int is_valid = 0;
        for(int i = 0; i < customer_count; ++i){
            if(finish_max[i] == 1 ){
                continue;
            }
            int required_reources = 1;
            for(int j = 0; j < resources_count; ++j){
                if(need[i][j] > work_max[j]){
                    required_reources = 0;
                    break;
                }
            }
            if(required_reources == 1){
                for(int m = 0; m < resources_count; ++m){
                    work_max[m]+= allocated[i][m];
                }
                finish_max[i] = 1;
                customer_order[count] = i;
                count++;
                is_valid = 1;
                break;
            }
        }        
        if(is_valid == 0){
            return 0;
        }
        if(count == customer_count){
            return 1;
        }
    }
    return 0;
}
