#include <stdio.h>
#include <pthread.h>
void *h(void *p)
{
    while (1)
        printf("\nH");
    return NULL;
}
void I()
{
    while (1)
        printf("\nI");
}
void main()
{
    pthread_t a;
    pthread_create(&a, NULL, h, NULL);
    I();
}