#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv)
{
    int m1 = 0;                 //guess number for parent process.
    int m2 = 0;                 //answer for child process.

    m1 = *argv[1] - '0';
    m2 = *argv[2] - '0';

    const char *name_of_shm = "SHM";
    const int SIZE = 4096;
    int shared_int;
    shared_int = shm_open(name_of_shm,O_CREAT|O_RDWR, 0666);
    ftruncate(shared_int,SIZE);

    int *ptr = (int *)mmap(0,SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shared_int,0);
    *ptr = 0;
    
    pid_t s_pid = fork();

    if(s_pid == -1)
    {
        perror ( "fork" );
        exit(EXIT_FAILURE);
    }

    else if (s_pid > 0)         //Parent Process
    {
        int PidOfChild = s_pid;
        int Parent_pid = getpid();
        std::cout<<"[ "<<Parent_pid<<" Parent ] : Child process id "<<PidOfChild<<" has created."<<endl;

        int &sharing_value = *ptr;

        vector<int> GuessedNum;
        GuessedNum.clear();

        int count = 0;

        srand(m1);

        while(true)
        {
            if(sharing_value < 0)
            {
                if(sharing_value == -1)
                {
                    int guessingNum = 0;
                    bool NumFound = false;
                    do{
                        guessingNum = rand()% 20 + 1;

                        for(int i = 0;i < GuessedNum.size();i++)
                        {
                            if(guessingNum == GuessedNum.at(i))
                            {
                                NumFound = true;
                                break;
                            }
                        }

                    }while(NumFound == true);

                    GuessedNum.push_back(guessingNum);

                    std::cout<<"[ "<<Parent_pid<<" Parent ] : Guess "<<guessingNum<<endl;
                    
                    sharing_value = guessingNum;
                }
                else if(sharing_value == -2)            //Right answer
                {
                    sharing_value = 77;
                    break;
                }
                else if(sharing_value == -3)
                {
                    sharing_value = 77;
                    break;
                }
                
            }
        }

        while (true)
        {
            if(sharing_value !=77)
            {
                cout<<"[ "<<Parent_pid<<" Parent ] : Answer: "<<sharing_value<<endl;
                break;
            }
        }
    }

    else                        //Child Process
    {
        int Child_pid = getpid();
        int &sharing_value = *ptr;

        int count = 0;

        srand(m2);

        int answer = rand()%20 + 1;
        sharing_value = -1;

        while(true)
        {
            if(sharing_value > 0)
            {
                count++;
                if(sharing_value != answer)
                {
                    if(count == 5)
                    {
                        std::cout<<"[ "<<Child_pid<<" Child ] : Missed, you lose."<<endl;
                        sharing_value = -3;
                        break;
                    }
                    else
                    {
                        std::cout<<"[ "<<Child_pid<<" Child ] : Missed."<<endl;
                        sharing_value = -1;
                    }
                }

                else
                {
                    std::cout<<"[ "<<Child_pid<<" Child ] : Correct, you win."<<endl;
                    sharing_value = -2;
                    break;
                }
            }
            
        }
        while(true)
        {
            if(sharing_value == 77)
            {
                sharing_value = answer;
                break;
            }
        }

        return 0;
    }

    //Unlink shm
    munmap(ptr,SIZE);
    shm_unlink(name_of_shm);

    return 0;
}