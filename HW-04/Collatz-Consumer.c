#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{

	/* The size (in bytes) of shared-memory object */
	const int SIZE = 4096;

	/* The name of shared-memory object */
	const char *Obj = "ShareMemory";

	/* The shared-memory file descriptor */
	int shared_memory_fd;

	/* The pointer to shared-memory object */
	void *ptr;

	/* Open the shared-memory object */
	shared_memory_fd = shm_open(Obj, O_RDONLY, 0666);

	if (shared_memory_fd == -1) 
	{
		printf("Shared memory failed\n");
		exit(-1);
	}

	/* Map the shared-memory object in the address space of the process */
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shared_memory_fd, 0);

	if (ptr == MAP_FAILED) 
	{
		printf("Map failed\n");
		exit(-1);
	}

	/* Read from the shared-memory object */
	printf("Consumer : The output sequence is:  %s\n", (char *)ptr);

	/* Remove the shared-memory object */
	if (shm_unlink(Obj) == -1) 
	{
		printf("\nError removing %s\n", Obj);
		exit(-1);
	}

	return 0;
}
