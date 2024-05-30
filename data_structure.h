#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <semaphore.h>

typedef enum { type1, type2, type3 } DataType;

typedef struct {
    int intValue;
    float floatValue;
    char stringValue[100];
    DataType enumValue;
} DataStructure;

typedef struct {
    DataStructure data[10];
    sem_t sem_client;  
    sem_t sem_server; 
} SharedMemory;

#endif // DATA_STRUCTURE_H