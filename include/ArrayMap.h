/**********************************************************
 * @author Vicky Mohammad
 * Copyright 2018, Vicky Mohammad, All rights reserved.
 * https://github.com/vicmoh/DynamicStringAPI
 **********************************************************/

// guard
#ifndef _ARRAY_MAP_H_
#define _ARRAY_MAP_H_

// include libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <stdarg.h>

/**********************************************************
 * function definition
 **********************************************************/

// 20 param preprocessor
#define ARGS_SEQUENCE(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,N,...) N
#define ARGS(...) ARGS_SEQUENCE(\
__VA_ARGS__, 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)\
// for in like javascript
#define for_in( x , object ) for(int x = 0; x < ( object->length ) ; x++)
// functions
#define array_addMultiple( obj, ...) array_addMultipleData(obj, ARGS(__VA_ARGS__), __VA_ARGS__)
// garbage collector 
#define MEM_START _GARBAGE_COLLECTOR_ = new_Array(garabage_freeFunction)
#define MEM( var ) array_add(_GARBAGE_COLLECTOR_, var)
#define MEM_ADD(...) array_addMultipleData( _GARBAGE_COLLECTOR_ , ARGS(__VA_ARGS__), __VA_ARGS__)
#define MEM_END array_free(_GARBAGE_COLLECTOR_)
#define M( var ) MEM_ADD( var )

/**********************************************************
 * array class
 **********************************************************/

typedef struct{
    void* data;
    char tag[256];
}ArrayIndex;

typedef struct ArrayClass{
    unsigned int length;
    ArrayIndex* index;
    void (*deleteFunction)(void* toBeFreed);
    // methods
    void (*add)(struct ArrayClass*, void* toBeAdded);
    void* (*getIndexOf)(struct ArrayClass* object, int theIndex);
    void (*removeIndexOf)(struct ArrayClass* object, int theIndex);
    void (*destroy)(void* object);
}Array;

Array* _GARBAGE_COLLECTOR_;

// construtor
Array* new_Array(void (*deleteFunction)(void* toBeFreed));
// getter and setter
void array_add(Array* object, void* toBeAdded);
void* array_getIndexOf(Array* object, int index);
void array_removeIndexOf(Array* object, int index);
// free
void array_free(void* ArrayObjectToBeFreed);

/**********************************************************
 * map class
 **********************************************************/

typedef struct MapDataClass{
    void* data;
    char key[256];
    struct MapDataClass* next;
}MapData;

typedef struct MapClass{
    unsigned int tableSize;
    MapData** table;
    void (*deleteFunction)(void*);
    Array* list;
    unsigned int length;
    // func
    void (*add)(struct MapClass* object, char* key, void* dataToBeAdded);
    void* (*get)(struct MapClass* object, char* key);
    void (*destroy)(void* mapToBeFreed);
}Map;

// constructor
Map* new_Map(unsigned int tableSize, void (*deleteFunction)(void* deleteFunction));
MapData* map_initData(char* key, void* data);
// getter and setter
void map_add(Map* object, char* key, void* dataToBeAdded);
void array_addMultipleData(Array* object, unsigned int numOfArg, ... );
void* map_get(Map* object, char* key);
// funtions
unsigned long map_hashDJB(const char* string, unsigned int tableSize);
int map_isPrime(const int toBeChecked);
int map_nextPrime(int number);
// free function
void map_free(void* toBeFreed);
void map_freeMapData(void* toBeFreed);
void garabage_freeFunction(void* toBeDeleted);

#endif