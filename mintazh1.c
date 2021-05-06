#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<time.h>
#include<math.h>

struct CP
{
    unsigned int x,y,z;
}centerp;

typedef struct leggomb
{
    struct CP kozeppont;
    unsigned int r;
    pid_t pid;
}lufi;

struct leggomb generate()
{
    
    srand(time(NULL));
    struct leggomb retval;
    struct CP kozeppont;
    kozeppont.x = rand()%101;
    kozeppont.y = rand()%101;
    kozeppont.z = rand()%101;
    retval.kozeppont = kozeppont;
    retval.r= rand()%101;
    retval.pid = getpid();
    return retval;
}

void printballoon(lufi balloon)
{
    printf("x: %i y: %i  z: %i , r: %i, pid: %i \n", balloon.kozeppont.x, balloon.kozeppont.y,balloon.kozeppont.z,balloon.r,balloon.pid);
}

int tartalmazzae(lufi b1, lufi b2)
{
    int c1c2 = pow(sqrt(b1.kozeppont.x - b2.kozeppont.x), 2+(2*(b1.kozeppont.y-b2.kozeppont.y)));
    printf("%i",c1c2);
    if(c1c2 == b1.r + b2.r)
    {
        kill(b1.pid,SIGUSR1);
        kill(b2.pid,SIGUSR1);
    }
    else if(c1c2 < (b1.r + b2.r))
    {
        kill(b1.pid,SIGUSR1);
        kill(b2.pid,SIGUSR1);
    }
    else return 0;
}



void sig_handler()
{
    printf("sugar csokken a felere!");
}

int main() 
{
    signal(SIGUSR1,sig_handler);
    int pipe1[2];
    pipe(pipe1);
    int pipe2[2];
    pipe(pipe2);
    int pipe3[2];
    pipe(pipe3);
    pid_t balloon1 = fork();
    if(balloon1 == 0) // 1-es lufi
    {
        signal(SIGUSR1,sig_handler);
        lufi balloon1 = generate();
        //printballoon(balloon1);
        close(pipe1[0]);
        write(pipe1[1],&balloon1,sizeof(balloon1));
        close(pipe1[1]);
    }
    pid_t balloon2 = fork();
    if(balloon2 == 0) // 2-es lufi
    {
        signal(SIGUSR1,sig_handler);
        lufi balloon2 = generate();
        //printballoon(balloon2);
        close(pipe2[0]);
        write(pipe2[1],&balloon2,sizeof(balloon2));
        close(pipe2[1]);
    } 
    pid_t balloon3 = fork();
    if(balloon3==0) // 3-as lufi
    {
        signal(SIGUSR1,sig_handler);
        lufi balloon3 = generate();
        //printballoon(balloon3);
        close(pipe3[0]);
        write(pipe3[1],&balloon3,sizeof(balloon3));
        close(pipe3[1]);
    }
    if(balloon1 > 0 && balloon2 > 0 && balloon3 > 0) // parent
    {
        wait(NULL); // wait for the others
        close(pipe1[1]);
        close(pipe2[1]);
        close(pipe3[1]);
        lufi b1,b2,b3;
        read(pipe1[0],&b1,sizeof(b1));
        read(pipe2[0],&b2,sizeof(b2));
        read(pipe3[0],&b3,sizeof(b3));
        printballoon(b1);
        printballoon(b2);
        printballoon(b3);        
        tartalmazzae(b1,b2);
        tartalmazzae(b1,b3);
        tartalmazzae(b2,b3);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe3[0]);
    }

    return 0; 
}