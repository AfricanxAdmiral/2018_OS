#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid){
        printf("Main process id : %d.\n", getpid());
        wait(NULL);
    }
    else{
        printf("Fork1, I'm the child %d, my parent is %d.\n", getpid(), getppid());
        pid = fork();
        if(pid) wait(NULL);
        else printf("Fork2, I'm the child %d, my parent is %d.\n", getpid(), getppid());
    }
    pid = fork();
    if(pid) wait(NULL);
    else printf("Fork3, I'm the child %d, my parent is %d.\n", getpid(), getppid());
    return 0;
}