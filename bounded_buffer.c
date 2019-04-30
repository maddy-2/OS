//bounded buffer

#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int empty;
int full = 0;
int noOfItemsCurrentlyInBuffer = 0;
int wait(int s)
{
    return (s - 1);
}
int signal(int s)
{
    return (s + 1);
}
void producer()
{
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    noOfItemsCurrentlyInBuffer++;
    printf("Producer has produced the item:%d", noOfItemsCurrentlyInBuffer);
    mutex = signal(mutex);
}
void consumer()
{
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("Consumer has consumed the item:%d", noOfItemsCurrentlyInBuffer);
    noOfItemsCurrentlyInBuffer--;
    mutex = signal(mutex);
}
void main()
{
    int n;
    printf("  Enter the Buffer Size:\n");
    scanf("%d", &n);
    empty = n;
    int choice;
    while (1)
    {
        printf("\n*************Options*************\n1.Producer\n2.Consumer\n3.Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            if ((mutex == 1) && (empty != 0))
                producer();
            else
            {
                printf("Buffer is full!");
            }
            break;
        case 2:
            if ((mutex == 1) && (full != 0))
                consumer();
            else
            {
                printf("Buffer is empty!");
            }
            break;
        case 3:
            exit(0);
            break;
        }
    }
}
