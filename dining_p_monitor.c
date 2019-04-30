#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

//!Number of philosophers
#define NPHILO 5
//!Helps to cope with ASCII
#define ASCII 48
//!Used for the think-loop in think() as a really large number
#define THINK_LOOP 100000000
//!Used for the eat-loop in eat() as a really large number
#define EAT_LOOP 500000000
//!For Keyboard-Input
#define KEYKOMBO 3

//!this is how the stick IDs match the philosophers on the right side
#define RIGHT(philoID) ((philoID+1)%NPHILO)
//!this is how the stick IDs match the philosophers on the left side
#define LEFT(philoID) philoID

//!this is how neighbours are defined at a round table - right side
#define RIGHTNEIGHB(philoID) ((philoID == NPHILO-1)? 0 : philoID+1)
//!this is how neighbours are defined at a round table - left side
#define LEFTNEIGHB(philoID) ((philoID == 0)? NPHILO-1 : philoID-1)

//!boolean variables true and false
typedef enum {
    FALSE = 0,
    TRUE = 1
} Bool;

//!definition of the states of the philosophers
typedef enum {
    THINK = 0,
    HUNGRY = 1,
    EAT = 2
} State;

//!definition of the states of the sticks
typedef enum {
    FREE = 0,
    IN_USE = 1
} Sticks;

//!states of the N philosophers
State philoStates[NPHILO];
//!states of the N sticks
Sticks stickStates[NPHILO];

//!mutual exclusion with pthreads
pthread_mutex_t mutex;
//!condition variables with pthreads - one for every philosopher
pthread_cond_t cond[NPHILO];
//!semaphors with pthreads - one for every philosopher
sem_t semaphore[NPHILO];
//!philoIDs
int tmp[NPHILO];               

//!For keyboard input
char keyinput[KEYKOMBO];
//!For transmitting b, u or p to the philosophers
char listen[NPHILO];

// declaration to get an overview
void *philo(void *arg);
void think(int philoID);
void eat(int philoID);
void get_sticks(int philoID);
void put_sticks(int philoID);
void disp_philo_states();
char convertStates(State philoState);
void checkForB(int philoID);

void
get_sticks(int philoID)
{

    //lock and display states
    pthread_mutex_lock(&mutex);
    disp_philo_states();

    // when he tries to get the sticks he's obviously hungry
    philoStates[philoID] = HUNGRY;

    while(stickStates[LEFT(philoID)] == IN_USE
          || stickStates[RIGHT(philoID)] == IN_USE) {
        pthread_cond_wait(&cond[philoID], &mutex);
    }

    // mark philosopher as eating and stick as in use
    philoStates[philoID] = EAT;
    stickStates[LEFT(philoID)] = IN_USE;
    stickStates[RIGHT(philoID)] = IN_USE;

	//unlock the mutex
    pthread_mutex_unlock(&mutex);
}


void
put_sticks(int philoID)
{

    // again, lock and display states
    pthread_mutex_lock(&mutex);
    disp_philo_states();

    // lets go of his sticks
    stickStates[LEFT(philoID)] = FREE;
    stickStates[RIGHT(philoID)] = FREE;

    // goes back to thinking
    philoStates[philoID] = THINK;

    // nudges his philosopher buddies next to him
    pthread_cond_signal(&cond[LEFTNEIGHB(philoID)]);
    pthread_cond_signal(&cond[RIGHTNEIGHB(philoID)]);

    pthread_mutex_unlock(&mutex);
}


void
disp_philo_states()
{
    int i;

    // go through them and look if there's an error
    for(i = 0; i < NPHILO; i++) {
        if(philoStates[i] == EAT
           && (philoStates[LEFTNEIGHB(i)] == EAT
               || philoStates[RIGHTNEIGHB(i)] == EAT)) {
            printf("OUPS! Something went wrong...\n\n");
            break;
        }
    }

    // display anyway to see what might be wrong or actual states
    for(i = 0; i < NPHILO; i++) {
        printf("%d%c ", i, convertStates(philoStates[i]));
    }
    printf("\n\n");
}


char
convertStates(State philoState)
{
    if(philoState == EAT) {
        return 'E';
    }
    else if(philoState == THINK) {
        return 'T';
    }
    else {
        return 'H';
    }
    return '-'; // error
}

int
main(void)
{
    pthread_t philoThreadIDs[NPHILO];
    int i;
    int err;
    int res[NPHILO];

//init stuff
    for(i = 0; i < NPHILO; i++) {
        philoStates[i] = THINK;
        stickStates[i] = FREE;
        err = pthread_cond_init(&cond[i], NULL);
        assert(!err);
        sem_init(&semaphore[i], 0, 0);
    }
    pthread_mutex_init(&mutex, NULL);

// start threads
    for(i = 0; i < NPHILO; i++) {
        res[i] =
            pthread_create(&philoThreadIDs[i], NULL, philo, &tmp[i]);
        tmp[i] = i;

        if(res[i] != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }

// keyboard input
    while(TRUE) {
        fgets(keyinput, KEYKOMBO, stdin);

        if(keyinput[0] == 'q' || keyinput[0] == 'Q') {

        printf("Quitting...\n");
	    
	    printf("Unblocking all philos\n");
	    for(i = 0; i < NPHILO; i++) {
	      listen[i] = 'q';
	      sem_post(&semaphore[keyinput[0]-ASCII]);
	    }
        for(i = 0; i < NPHILO; i++) {
        	printf("Thread %d joined\n", i);
			pthread_cond_signal(&cond[i]);
            pthread_join(philoThreadIDs[i], NULL);
            }
            
        printf("Destroying the rest...\n");
        for(i = 0; i < NPHILO; i++) {
			pthread_cond_destroy(&cond[i]);
            sem_destroy(&semaphore[i]);
	    }
        pthread_mutex_destroy(&mutex);
        
	    printf("Exiting...\n");
        pthread_exit(NULL);
        exit(EXIT_FAILURE);    // programm stops here
        }
        else if(keyinput[0] >= '0' && keyinput[0] < NPHILO + ASCII) {
            if(keyinput[1] == 'b') {
                printf("Blocking Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = keyinput[1];
            }
            else if(keyinput[1] == 'u') {
                printf("Unblocking Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = 'u';
                sem_post(&semaphore[keyinput[0] - ASCII]);
            }
            else if(keyinput[1] == 'p') {
                printf("Proceeding Philo Nr. %d\n", keyinput[0] - ASCII);
                listen[keyinput[0] - ASCII] = 'p';
            }
        }
    }

    return 0;
}       // main


void *
philo(void *pID)
{

    int *philoID = pID;
    int running = 1;            // init

    printf("philospher %d just awoke\n", *philoID);

    while(running) {

        checkForB(*philoID);

        think(*philoID);

        checkForB(*philoID);

        get_sticks(*philoID);

        eat(*philoID);

        checkForB(*philoID);

        put_sticks(*philoID);

        if(listen[*philoID] == 'q' || listen[*philoID] == 'Q') {
            running = 0;
        }
    }
    return NULL;
}




void
think(int philoID)
{
    int i;

    for(i = 0; i < THINK_LOOP; i++) {
        if(listen[philoID] == 'p') {
            listen[philoID] = 'd';
            break;
        }
    }
}


void
eat(int philoID)
{
    int i;
    for(i = 0; i < EAT_LOOP; i++) {
        if(listen[philoID] == 'p') {
            listen[philoID] = 'd';
            break;
        }
    }
}


void
checkForB(int philoID)
{
    if(listen[philoID] == 'b') {
        sem_wait(&semaphore[philoID]);
    }
}


