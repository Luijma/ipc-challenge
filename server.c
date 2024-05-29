#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "data_structure.h"

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE (sizeof(DataStructure) * 10)

void printDataStructure(const DataStructure *data) {
    const char* enumStrings[] = {"type1", "type2", "type3"};
    printf("int: %d, float: %.2f, string: %s, enum: %s\n",
           data->intValue, data->floatValue, data->stringValue, enumStrings[data->enumValue]);
}

int main() {
    // Create shared memory
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Set the size
    if (ftruncate(shm_fd, SHARED_MEMORY_SIZE) == -1) {
        perror("ftruncate");
        exit(1);
    }

    // Map shared memory
    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Access the data
    DataStructure* dataArray = (DataStructure*)ptr;

    for (int i = 0; i < 10; ++i) {
        printDataStructure(&dataArray[i]);
        sleep(1);
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);
    shm_unlink(SHARED_MEMORY_NAME); // Unlink to delete shared memory

    return 0;
}

