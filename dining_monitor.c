//dining philosopher using monitor

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>
#define NPHILO 5

#define ASCII 48

#define THINK_LOOP 100000000

#define EAT_LOOP 500000000

#define KEYKOMBO 3


#define RIGHT(philoID) ((philoID+1)%NPHILO)

#define LEFT(philoID) philoID


#define RIGHTNEIGHB(philoID) ((philoID == NPHILO-1)? 0 : philoID+1)

#define LEFTNEIGHB(philoID) ((philoID == 0)? NPHILO-1 : philoID-1)


typedef enum {
    FALSE = 0,
    TRUE = 1
} Bool;


typedef enum {
    THINK = 0,
    HUNGRY = 1,
    EAT = 2
} State;


typedef enum {
    FREE = 0,
    IN_USE = 1
} Sticks;


State philoStates[NPHILO];

Sticks stickStates[NPHILO];


pthread_mutex_t mutex;

pthread_cond_t cond[NPHILO];

sem_t semaphore[NPHILO];

int tmp[NPHILO];               


char keyinput[KEYKOMBO];

char listen[NPHILO];


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

  
    pthread_mutex_lock(&mutex);
    disp_philo_states();

    
    philoStates[philoID] = HUNGRY;

    while(stickStates[LEFT(philoID)] == IN_USE
          || stickStates[RIGHT(philoID)] == IN_USE) {
        pthread_cond_wait(&cond[philoID], &mutex);
    }

    
    philoStates[philoID] = EAT;
    stickStates[LEFT(philoID)] = IN_USE;
    stickStates[RIGHT(philoID)] = IN_USE;

	
    pthread_mutex_unlock(&mutex);
}


void
put_sticks(int philoID)
{

    
    pthread_mutex_lock(&mutex);
    disp_philo_states();

   
    stickStates[LEFT(philoID)] = FREE;
    stickStates[RIGHT(philoID)] = FREE;

    
    philoStates[philoID] = THINK;

    
    pthread_cond_signal(&cond[LEFTNEIGHB(philoID)]);
    pthread_cond_signal(&cond[RIGHTNEIGHB(philoID)]);

    pthread_mutex_unlock(&mutex);
}


void
disp_philo_states()
{
    int i;

    
    for(i = 0; i < NPHILO; i++) {
        if(philoStates[i] == EAT
           && (philoStates[LEFTNEIGHB(i)] == EAT
               || philoStates[RIGHTNEIGHB(i)] == EAT)) {
            printf("OUPS! Something went wrong...\n\n");
            break;
        }
    }

    
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
    return '-';
}

int
main(void)
{
    pthread_t philoThreadIDs[NPHILO];
    int i;
    int err;
    int res[NPHILO];


    for(i = 0; i < NPHILO; i++) {
        philoStates[i] = THINK;
        stickStates[i] = FREE;
        err = pthread_cond_init(&cond[i], NULL);
        assert(!err);
        sem_init(&semaphore[i], 0, 0);
    }
    pthread_mutex_init(&mutex, NULL);


    for(i = 0; i < NPHILO; i++) {
        res[i] =
            pthread_create(&philoThreadIDs[i], NULL, philo, &tmp[i]);
        tmp[i] = i;

        if(res[i] != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }


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
        exit(EXIT_FAILURE);   
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
    int running = 1;            

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


