#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "data_structure.h"

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE (sizeof(SharedMemory))

int main() {
    // Create and set up shared memory mapping + size
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // create pointer to shared memory
    SharedMemory* sharedMemory = (SharedMemory*)ptr;

    // Write data to shared memory
    for (int i = 0; i < 10; ++i) {
        if (sem_wait(&sharedMemory->sem_client) == -1) {
            perror("sem_wait sem_client");
            exit(1);
        }

        DataStructure data;
        data.intValue = i;
        data.floatValue = i * 1.1f;
        snprintf(data.stringValue, sizeof(data.stringValue), "String%d", i);
        data.enumValue = (DataType)(i % 3);
        sharedMemory->data[i] = data;

        // Print debug information
        //printf("Client: Written int: %d, float: %.2f, string: %s, enum: %d\n",
        //       data.intValue, data.floatValue, data.stringValue, data.enumValue);

        if (sem_post(&sharedMemory->sem_server) == -1) {
            perror("sem_post sem_server");
            exit(1);
        }
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);

    return 0;
}
~      