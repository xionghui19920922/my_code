#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#define THREAD_NUM 5

pthread_mutex_t myMutex;

int number = 1;

void * funA(void * str)
{

    pthread_mutex_lock(&myMutex);

    cout<<number<<" + 1 = "<< number + 1 <<endl;
    number++;
    pthread_mutex_unlock(&myMutex);

    pthread_exit(str);
}

int main()
{
    pthread_t threaIndex[5];
    int valueIndex[] = {1,2,3,4,5};

    pthread_attr_t myAttr;
    pthread_attr_init(&myAttr);

    pthread_attr_setdetachstate(&myAttr, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&myMutex, NULL);

    for(int i = 0; i < THREAD_NUM; i++)
    {
        // sleep(1);
        int ret = pthread_create(&threaIndex[i], &myAttr, funA, (void*)(&valueIndex[i]));
        if(ret != 0)
        {
            cout << "create thread error" <<endl;
        }
    }
    pthread_attr_destroy(&myAttr);
    void * state;

    for(int i = 0; i < THREAD_NUM; i++)
    {
        int ret = pthread_join(threaIndex[i], &state);
        if (ret != 0)
        {
            cout << "join error!" << endl;
        }
        // cout << *((int*)state) << endl;
    }

    pthread_mutex_destroy(&myMutex);
}
