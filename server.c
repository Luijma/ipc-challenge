#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "data_structure.h"

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE (sizeof(SharedMemory))

void printDataStructure(const DataStructure *data) {
    const char* enumStrings[] = {"type1", "type2", "type3"};
    printf("int: %d, float: %.2f, string: %s, enum: %s\n",
           data->intValue, data->floatValue, data->stringValue, enumStrings[data->enumValue]);
}

int main() {
    // Create + map shared memory
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Access Shared memory
    SharedMemory* sharedMemory = (SharedMemory*)ptr;

    // Initialize Semaphores
    if (sem_init(&sharedMemory->sem_client, 1, 1) == -1) {
        perror("sem_init sem_client");
        exit(1);
    }
    if (sem_init(&sharedMemory->sem_server, 1, 0) == -1) {
        perror("sem_init sem_server");
        exit(1);
    }

    for (int i = 0; i < 10; ++i) {
        if (sem_wait(&sharedMemory->sem_server) == -1) {
            perror("sem_wait sem_server");
            exit(1);
        }

        printDataStructure(&sharedMemory->data[i]);

        if (sem_post(&sharedMemory->sem_client) == -1) {
            perror("sem_post sem_client");
            exit(1);
        }
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);
    shm_unlink(SHARED_MEMORY_NAME);

    return 0;
}

~                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
~                               