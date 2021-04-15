#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

int max;
int m, b;
sem_t e;
sem_t f;
int in = 0;
int out = 0;
int *buffer;
pthread_mutex_t mx;

void *pro(void *pno)
{
    int j;
    for (int i = 0; i < b; i++)
    {
        j = rand() % 100;
        sem_wait(&e);
        pthread_mutex_lock(&mx);
        buffer[in] = j;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % b;
        pthread_mutex_unlock(&mx);
        sem_post(&f);
    }
}
void *con(void *cno)
{
    for (int i = 0; i < b; i++)
    {
        sem_wait(&f);
        pthread_mutex_lock(&mx);
        int j = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", *((int *)cno), j, out);
        out = (out + 1) % b;
        pthread_mutex_unlock(&mx);
        sem_post(&e);
    }
}

void main()
{
    pthread_t *p, *c;
    int rn, wn, *n;
    pthread_mutex_init(&mx, NULL);
    printf("(19BIT0292)Enter the size of the buffer: ");
    scanf("%d", &b);
    buffer = (int *)malloc(sizeof(int) * b);
    sem_init(&e, 0, b);
    sem_init(&f, 0, 0);
    printf("Enter the number of producers: ");
    scanf("%d", &rn);
    p = (pthread_t *)malloc(sizeof(pthread_t) * rn);
    printf("Enter the number of consumers: ");
    scanf("%d", &wn);
    c = (pthread_t *)malloc(sizeof(pthread_t) * wn);
    for (int i = 0; i < rn; i++)
    {
        n = malloc(sizeof(int));
        *n = i + 1;
        pthread_create(&p[i], NULL, pro, n);
        n = NULL;
    }
    for (int i = 0; i < wn; i++)
    {
        n = malloc(sizeof(int));
        *n = i + 1;
        pthread_create(&c[i], NULL, con, n);
        n = NULL;
    }

    for (int i = 0; i < rn; i++)
        pthread_join(p[i], NULL);
    for (int i = 0; i < wn; i++)
        pthread_join(c[i], NULL);

    pthread_mutex_destroy(&mx);
    sem_destroy(&e);
    sem_destroy(&f);
}