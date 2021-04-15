#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t wrt;
pthread_mutex_t mutex;
int cnt = 1;
int numreader = 0;

void *wr(void *wno)
{
    sem_wait(&wrt);
    cnt = cnt * 2;
    printf("Writer %d modified count to %d\n", (*((int *)wno)), cnt);
    sem_post(&wrt);
}
void *rd(void *rno)
{
    pthread_mutex_lock(&mutex);
    numreader++;
    if (numreader == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader %d: read count as %d\n", *((int *)rno), cnt);
    pthread_mutex_lock(&mutex);
    numreader--;
    if (numreader == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

void main()
{
    pthread_t *r, *w;
    int rn, wn, *n;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    printf("Enter the number of readers: ");
    scanf("%d", &rn);
    r = (pthread_t *)malloc(sizeof(pthread_t) * rn);
    printf("Enter the number of writers: ");
    scanf("%d", &wn);
    w = (pthread_t *)malloc(sizeof(pthread_t) * wn);
    for (int i = 0; i < rn; i++)
    {
        n = malloc(sizeof(int));
        *n = i + 1;
        pthread_create(&r[i], NULL, (void *)rd, (void *)n);
    }
    for (int i = 0; i < wn; i++)
    {
        n = malloc(sizeof(int));
        *n = i + 1;
        pthread_create(&w[i], NULL, (void *)wr, (void *)n);
    }

    for (int i = 0; i < rn; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < wn; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
}