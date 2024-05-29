#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "data_structure.h"

#define SHARED_MEMORY_NAME "/my_shared_memory"
#define SHARED_MEMORY_SIZE (sizeof(DataStructure) * 10)

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

    // Map memory to address space
    void* ptr = mmap(0, SHARED_MEMORY_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Access the data structures in shared memory
    DataStructure* dataArray = (DataStructure*)ptr;

    for (int i = 0; i < 10; ++i) {
        DataStructure data;
        data.intValue = i;
        data.floatValue = i * 1.1f;
        snprintf(data.stringValue, sizeof(data.stringValue), "String%d", i);
        data.enumValue = (DataType)(i % 3);
        dataArray[i] = data;

        // Debug
/*        printf("Written: int: %d, float: %.2f, string: %s, enum: %d\n",
               data.intValue, data.floatValue, data.stringValue, data.enumValue); */
    }

    // Cleanup
    munmap(ptr, SHARED_MEMORY_SIZE);
    close(shm_fd);

    return 0;
}
