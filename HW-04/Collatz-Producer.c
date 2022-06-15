#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
/* The size (in bytes) of shared-memory object */
const int SIZE = 4096;

/* The name of shared-memory object */
const char *Obj = "ShareMemory";

/* The shared-memory file descriptor */
int shared_memory_fd;

/* The pointer to shared-memory object */
void *ptr;

/* Create the shared-memory object */
shared_memory_fd = shm_open(Obj, O_CREAT | O_RDWR, 0666);

/* Configure the size of the shared-memory object */
ftruncate(shared_memory_fd, SIZE);

if (argc < 2 || argc > 2) {
        printf("Two arguments expected - program name and positive integer.\n");
        exit(1);
    }
else if (argc == 2)
{
if (atoi(argv[1]) <= 0)
{
printf ("Input must be a positive integer\n");
return 0;
}
ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);

if (ptr == MAP_FAILED)
    {
      printf("Map failed\n");
        return -1;
    }

  int term = atoi(argv[1]);
sprintf(ptr, " %d", term);

 int n = term;    
   int count=1;   
   
   while(n!=0)  
   {  
       n=n/10;  
       count++;  
   }  

ptr += count;

while(term > 1)
{
    if(term % 2 == 0){ //for even numbers
      term = term / 2;

sprintf(ptr, ", %d", term);
int n = term;    
   int count=2;   
   
   while(n!=0)  
   {  
       n=n/10;  
       count++;  
   }  


ptr += count;
     
    }
    else
{

       term = term * 3 + 1;

sprintf(ptr, ", %d", term);
int n = term;    
   int count=2;   
   
   while(n!=0)  
   {  
       n=n/10;  
       count++;  
   }  


ptr += count;      
    }
 }

    printf("\nProducer : Writing the sequence to the shared memory is done! \n");
     return 0;
}

}

