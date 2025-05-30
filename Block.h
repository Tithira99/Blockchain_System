#include <time.h>
#include <string.h>
#include <stdio.h>
#include "nonceList.h"

#define HASH_SIZE 65
typedef struct block {
    int index;
    time_t timestamp;
    char data[256];
    char previousHash[HASH_SIZE];
    char hash[HASH_SIZE];
} Block;

// function prototypes (forward declaration)
Block createGenesisBlock();
Block createBlock(Block previousBlock, char* data, nonceList* list);
int isBlockValid(Block newBlock, Block previousBlock,nonceList* list);
