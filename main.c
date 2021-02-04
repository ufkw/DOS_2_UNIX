#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
    char * command = malloc(10*sizeof(char));
    char * arg1 = malloc(500*sizeof(char));
    char * arg2 = malloc(500*sizeof(char));

    memset(command, '\0', sizeof(command));
    memset(arg1, '\0', sizeof(arg1));
    memset(arg2, '\0', sizeof(arg2));

    // char * arg1 = NULL;
    // char * arg2 = NULL;

    char * input = malloc(sizeof(command) + sizeof(arg1) + sizeof(arg2));
    memset(input, '\0', sizeof(input));
    while(1)
    {
        //get input
        scanf("%s", input);
        
        // run infinitely



        if(input[0] != '\0')
        {
            //if input exists
            int pid = fork();    //create child thread

            if(pid == 0)
            {
                //child process


                //tokenize input into command, arg1, arg2
                char * token;
                token = strtok(input, " ");
                

                int count = 0;

                while(token != NULL)
                {
                    if(count == 0)
                    {
                        strcpy(command, token);
                    }
                    else if(count == 1)
                    {
                        strcpy(arg1, token);
                    }
                    else if(count == 2)
                    {
                        strcpy(arg2, token);
                    }

                    printf( "token: %s\n", token );
                    token = strtok(NULL, " ");
                    count++;
                }

                printf("command: %s\n", command);
                printf("arg1: %s\n", arg1);
                printf("arg2: %s\n", arg2);


                //new thread converts and executes command
                if(command[0] == 'c' && command[1] == 'd')          //cd to cd
                {
                    memset(command, '\0', sizeof(command));
                    command = "cd";
                    execlp("/bin/cd", "cd", arg1);


                }
                else if(strcmp(command, "dir") == 0) 
                {
                    memset(command, '\0', sizeof(command));
                    command = "ls";

                    execlp("/bin/ls", "ls", NULL);
                }
                else if(strcmp(command, "type") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    command = "cat";
                }
                else if(strcmp(command, "del") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    command = "rm";
                }
                else if(strcmp(command, "ren") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    command = "mv";
                }
                else if(strcmp(command, "copy") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    command = "cp";   
   
                }
                // else if(strcmp(command, 0x03) == 0)
                // {
                //     //ToWrite ctrl-c to exit
                //     printf("ctrl-c");
                //     exit(0);
                // }
                else 
                {
                    //command not recognized
                    strcat(command, " is not recognized as an internal or external command, operable program or batch file." );
                    printf(command);
                    
                }



                // if(arg1[0] != '\0')
                // {
                //     strcat(command, " ");
                //     strcat(command, arg1);
                // }
                
                // if(arg2[0] != '\0')
                // {
                //     strcat(command, " ");
                //     strcat(command, arg2);
                // }

                // printf("running: %s", command);

                // exec(command, arg1, arg2);
                
            }
            else
            {
                // parent process
                wait(NULL);
                printf("Child complete");
            }
        }

        

    }

    return(0);
}


