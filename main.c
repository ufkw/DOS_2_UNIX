#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void) 
{
    // char * command = malloc(10*sizeof(char));
    // char * arg1 = malloc(500*sizeof(char));
    // char * arg2 = malloc(500*sizeof(char));

    char command[10];
    char arg1[200];
    char arg2[200];


    

    // char * arg1 = NULL;
    // char * arg2 = NULL;

    char input[500];//* input = malloc(sizeof(command) + sizeof(arg1) + sizeof(arg2));
    char input_cpy[500];
    while(1)
    {
        memset(command, '\0', sizeof(command));
        memset(arg1, '\0', sizeof(arg1));
        memset(arg2, '\0', sizeof(arg2));    
        memset(input, '\0', sizeof(input));
        memset(input_cpy, '\0', sizeof(input));
        //get input
        fgets(input, 501, stdin);
    //    scanf("%s", input);
        const char check[] = "\n";
        int len = strcspn(input, check);
    //    printf("len = |%d|\n");
        strncpy(input_cpy,input, len);
        printf("input_cpy = |%s|\n", input_cpy);
    //    input = strtok(input, "\n");
        // run infinitely



        if(input_cpy[0] != '\0')
        {
            //if input exists
            int pid = fork();    //create child thread

            char cwd[256];
            
            if(getcwd(cwd,sizeof(cwd)) == NULL)
            {
                //error
                
            }


            if(pid == 0)
            {
                //child process
                printf("in child process\n");


                //tokenize input into command, arg1, arg2
                // char * tmp = malloc(sizeof(input));
                // memset(tmp, '\0', sizeof(tmp));
                // strcpy(tmp, input);

           //     printf("input_cpy = |%s|\n", input_cpy);

                const char delim[2] = " ";
                char * token = strtok(input_cpy, delim);
                strcpy(command, token);
                // printf("1.command: |%s|\n", command);
                // printf("2.token |%s|\n", token);
                int count = 0;

                while(token != NULL)
                {
                    if(count == 1)
                    {
                        strcpy(arg1, token);
                    }
                    else if(count == 2)
                    {
                        strcpy(arg2, token);
                    }

                //    printf("count: %d\n", count);
                //    printf( "token: %s\n", token );
                    count++;
                    
                    token = strtok(NULL, delim);
                    // strcpy(tmp, input);
                    // token = strtok(tmp, delim);
                 //   printf( "next token: %s\n", token );
                    
                    
                }

                // printf("command: %s\n", command);
                // printf("arg1: %s\n", arg1);
                // printf("arg2: %s\n", arg2);



                //new thread converts and executes command
                if(command[0] == 'c' && command[1] == 'd')          //cd to cd
                {
                    printf("executing cd\n");
                    //memset(command, '\0', sizeof(command));
                    //strcpy(command, "cd");
                    //execlp("/bin/cd", command, arg1, arg2, NULL);

                    


                    if(arg1[0] == '.' && arg1[1] == '.' && arg1[2] == '\0')
                    {
                        //need to cut off cwd text after last "/"

                        //find last "/"
                        int length = strlen(cwd);

                        int i = length;
                        while(cwd[i] != '/')
                        {
                            i--;
                        }

                        cwd[i] = '\0';
                        chdir(cwd);
                        //trim cwd
                    }
                    else if(strstr(arg1, cwd) == NULL)
                    {
                        //arg1 does not contain the cwd
                        //need to append /arg1 to cwd
                        strcat(cwd, "/");
                        strcat(cwd, arg1);
                        chdir(cwd);

                    }
                    else
                    {
                        //arg1 is sufficient
                        chdir(arg1);
                    }


                    
          
                    printf("[%s]$ ", cwd);

                }
                else if(strcmp(command, "dir") == 0) 
                {
                    //works
                    memset(command, '\0', sizeof(command));
                    strcpy(command, "ls");

                    //execlp("/bin/ls", "ls", NULL);

                    strcat(command," ");
                    strcat(command, arg1);
                    strcat(command," ");
                    strcat(command, arg2);
                    system(command);
                }
                else if(strcmp(command, "type") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    strcpy(command,"cat");

                    strcat(command," ");
                    strcat(command, arg1);
                    strcat(command," ");
                    strcat(command, arg2);
                    system(command);
                }
                else if(strcmp(command, "del") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    strcpy(command,"rm");
                    strcat(command," ");
                    strcat(command, arg1);
                    strcat(command," ");
                    strcat(command, arg2);
                    system(command);
                   
                }
                else if(strcmp(command, "ren") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    strcpy(command,"mv");
                }
                else if(strcmp(command, "copy") == 0)
                {
                    memset(command, '\0', sizeof(command));
                    strcpy(command,"cp"); 
   
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
                printf("[%s]$ ", cwd);
                //printf("Child complete\n");
            }
        }

        

    }

    return(0);
}


