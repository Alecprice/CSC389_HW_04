#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

#define SIZE 1000

int main()
{
   int p1[2], p2[2], bytes;
    char buffer[SIZE];
    pid_t pid;

    if ( pipe(p1) < 0 )
        return 1;
    if ( pipe(p2) < 0 )
        return 1;

     /* Create a message */
     printf("Please input a character string: ");

     //scanf("%[^\n]s", buffer);
	fgets(buffer, SIZE, stdin);

   /* Fork a child process */
   pid = fork();
  
    if ( pid == 0 )
    {       
        close(p1[1]);
      
       int i = 0;
       char buffer[SIZE];
       read(p1[0], buffer, SIZE);
       bytes = strlen(buffer);
       printf("Child: Read the message from the Pipe1: ");
       puts(buffer);
        while( i < bytes )
        {
           if( isupper( buffer[i] ) )
               buffer[i] = tolower( buffer[i] );
           else if( islower( buffer[i] ) )
               buffer[i] = toupper( buffer[i] );
           i++;
       }
       close(p1[0]);
       close(p2[0]);
      
       printf("Child: Write the modified message to the Pipe2.");
        write(p2[1], buffer, strlen(buffer)+1 );
        close(p2[1]);
   }
    else
    {
       close(p1[0]);
       puts("Parent: Write the message to the Pipe1.");
        write(p1[1], buffer, strlen(buffer)+1);
        close(p1[1]);
      
        while( wait(NULL) > 0);
        close(p2[1]);
        read(p2[0], buffer, SIZE);
      
        printf("\nParent: Read the message from the Pipe2: ");
        puts(buffer);
        close(p2[0]);
    }
    return 0;
}