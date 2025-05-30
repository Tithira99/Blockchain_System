#include <stdio.h>
#include <stdlib.h>

#include "Block.h"

typedef struct BlockNode {
    Block block;
    struct BlockNode* next;
} BlockNode;


BlockNode* createGenesisNode();
BlockNode* addBlock(BlockNode* lastNode, char* data, nonceList* list);
int isChainValid(BlockNode* head, nonceList* list);