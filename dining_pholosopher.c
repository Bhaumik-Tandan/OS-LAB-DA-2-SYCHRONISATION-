#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

int n;

int *s;

sem_t mutex;
sem_t *S;

void test(int phnum)
{
    if (s[phnum] == 1 && s[(phnum + 4) % n] != 0 && s[(phnum + 1) % n] != 0)
    {
        s[phnum] = 0;

        printf("Philosopher %d takes fork %d and %d\n",
               phnum + 1, phnum + 1, (phnum + 4) % n + 1);

        printf("Philosopher %d is eating\n", phnum + 1);

        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum)
{

    sem_wait(&mutex);

    s[phnum] = 1;

    test(phnum);

    sem_post(&mutex);

    sem_wait(&S[phnum]);
}
void put_fork(int phnum)
{

    sem_wait(&mutex);

    s[phnum] = 2;

    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, (phnum + 4) % n + 1, phnum + 1);
    printf("Philosopher %d has finished eating and now thinking again\n", phnum + 1);

    test((phnum + 4) % n);
    test((phnum + 1) % n);

    sem_post(&mutex);
}

void *philospher(void *num)
{

    int *i = num;

    take_fork(*i);

    put_fork(*i);
}

int main()
{

    int i, *p;
    printf("(19BIT0292)Enter  the total number of philosophers: ");
    scanf("%d", &n);
    pthread_t thread_id[n];
    S = malloc(sizeof(sem_t) * n);
    s = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        p[i] = i;
    sem_init(&mutex, 0, 1);

    for (i = 0; i < n; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < n; i++)
    {
        p = malloc(sizeof(int));
        *p = i + 1;
        pthread_create(&thread_id[i], NULL,
                       philospher, p);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < n; i++)
        pthread_join(thread_id[i], NULL);
}