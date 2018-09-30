#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void)
{
        char arg[MAX_LINE/2+1]; /*command line arguments*/
        int should_run = 1; /*flag to determine when to exit program*/

        while(should_run){
                printf("osh>");
                fflush(stdout);

                /**
                * your code!
                * After reading user input, the step are:
                * (1) fork a child process using fork()
                * (2) the child process will invoke execvp()
                * (3) if command included &, parent will invoke wait()
                */

                // Read in the command
                read(STDIN_FILENO, arg, MAX_LINE);
                
                // Save the command into char *argv[] to fit the second argument of execvp
                char *args = strtok(arg, "\n");
                args = strtok(args, " ");
                if(!strcmp("exit", args)) should_run = 0;
                char *params[10];
                for(int i = 0; i < 10; i++){ 
                    params[i] = (char *)malloc(sizeof(char) * 80);
                }
                int count = 0; // To set the last element of params for fitting execvp
                int background = 0; // Set to 1 if & in argument
                for(; args != NULL; count++){
                    if(!strcmp("&", args)){
                        background = 1;
                        count--;
                    }
                    else strcpy(params[count],args);
                    args = strtok(NULL, " ");
                }
                params[count] = NULL;

                // Execute the shell program
                pid_t pid;
                if(!background) while(wait(NULL) != -1); // For spec asked to reap all zombie process if not background
                pid = fork();
                if(!pid) execvp(params[0], params);
                else if(!background) wait(NULL);
        }
        return 0;
}


