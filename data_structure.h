#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

typedef enum { type1, type2, type3 } DataType;

typedef struct {
    int intValue;
    float floatValue;
    char stringValue[100];
    DataType enumValue;
} DataStructure;

#endif // DATA_STRUCTURE_H
