#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <ctime>
#include <mutex>
#include <vector>
#include <sys/syscall.h>
#include <unistd.h>
#define gettid() syscall(SYS_gettid)

using namespace std;

mutex Global_mutex;

time_t START_TIME, END_TIME;

struct ThreadUnit
{
    pid_t ID = 0;
    int num = 0;
    int value = 0;
    int result = 0;
};

int CountDigit(int num)
{
    int d = 0;
    while (num > 0)
    {
        d++;
        num /= 10;
    }
    return d;
}

int Lucas(int n)
{
    switch(n)
    {
        case 0:
            return 2;
        case 1:
            return 1;
        default:
            return Lucas(n - 1) + Lucas(n - 2);
    }
}

void* ThreadFunc(void* input)
{
    time_t CALCULATION_START, CALCULATION_END;
    CALCULATION_START = clock();

    ThreadUnit* ThisUnit = (ThreadUnit*)input;
    ThisUnit->ID = gettid();
    ThisUnit->result = Lucas(ThisUnit->value);

    int result_digit = 0;
    result_digit = CountDigit(ThisUnit->result);

    CALCULATION_END = clock();

    Global_mutex.lock();
    cout<<"[Child "<<ThisUnit->num<<" tid = "<<ThisUnit->ID<<" ] L( "<<ThisUnit->value <<" ) has "<<result_digit<<" digit(s), calculation lasts "<<(CALCULATION_END - CALCULATION_START)<<"ms."<<endl;
    Global_mutex.unlock();

    return NULL;

}

int main(int argc, char** argv)
{
    START_TIME = clock();
    int a_size = argc - 1;

    ThreadUnit data[a_size];
    for(int i = 0; i < a_size; i++)
    {
        data[i].value = atoi(argv[i + 1]);
        data[i].num = i;
    }
    
    pthread_t pth[a_size];

    for(int i = 0;i < a_size; i++)
    {
        pthread_create(&pth[i], NULL , ThreadFunc , &data[i]);
        do
        {
            continue;
        } while (data[i].ID == 0);


        Global_mutex.lock();
        cout<<"[Main]Thread ID of L("<<data[i].value<<") : "<<data[i].ID<<"."<<endl;
        Global_mutex.unlock();
    }

    for(int i = 0; i < a_size; i++)
    {
        pthread_join(pth[i],NULL);
    }

    for(int i = 0; i < a_size; i++)
    {
        Global_mutex.lock();
        cout<<"[Main] L("<<data[i].value<<") = "<<data[i].result<<"."<<endl;
        Global_mutex.unlock();
    }
    END_TIME = clock();
    cout<<"Program execution lasts "<<(END_TIME - START_TIME)<<"ms."<<endl;
    return 0;
}