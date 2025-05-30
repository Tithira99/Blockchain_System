#include "BlockNode.h"

BlockNode* createGenesisNode() {
    BlockNode* genesisNode = (BlockNode*)malloc(sizeof(BlockNode));
    if (genesisNode == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    genesisNode->block = createGenesisBlock();
    genesisNode->next = NULL;
    return genesisNode;
}

BlockNode* addBlock(BlockNode* lastNode, char* data, nonceList* list) {
    Block newBlock = createBlock(lastNode->block, data, list);
    if (isBlockValid(newBlock, lastNode->block, list)) {
        BlockNode* newNode = (BlockNode*)malloc(sizeof(BlockNode));
        if (newNode == NULL) {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }
        newNode->block = newBlock;
        newNode->next = NULL;
        lastNode->next = newNode;
        return newNode;
    }
    else {
        fprintf(stderr, "Invalid block!\n");
        return NULL;
    }
}

int isChainValid(BlockNode* head, nonceList* list) {
    BlockNode* current = head;
    while (current && current->next) {
        if (!isBlockValid(current->next->block, current->block, list)) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}