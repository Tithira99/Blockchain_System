#include "Block.h"

#include "sha256.h"

void simpleHash(char* input, char output[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE - 1; i++) {
        output[i] = 0;
    }
    for (int i = 0; input[i] != '\0'; i++) {
        output[i % (HASH_SIZE - 1)] ^= input[i];
    }
    output[HASH_SIZE - 1] = '\0'; // null-terminate the hash
}

Block createGenesisBlock() {
    Block genesis = { 0 }; // init all fields to zero
    genesis.index = 0;
    strcpy_s(genesis.previousHash, sizeof(genesis.previousHash), "0");
    genesis.timestamp = time(NULL);
    strcpy_s(genesis.data, sizeof(genesis.data), "Genesis Block");
    char temp[1024] = { 0 }; // init to zero
    sprintf_s(temp, sizeof(temp), "%d%s%lld%s", genesis.index, genesis.previousHash, (long long)genesis.timestamp, genesis.data);
    sha256_hex(temp, strlen(temp), genesis.hash);
    return genesis;
}

Block createBlock(Block previousBlock, char* data, nonceList* list) {
    Block newBlock = { 0 };
    newBlock.index = previousBlock.index + 1;
    strcpy_s(newBlock.previousHash, sizeof(newBlock.previousHash), previousBlock.hash);
    newBlock.timestamp = time(NULL);
    strcpy_s(newBlock.data, sizeof(newBlock.data), data);
    char temp[1024] = { 0 };
    int nonce=0;
    int check =1;
    char pattern[4]="000";
    while(check=1){
        sprintf_s(temp, sizeof(temp), "%d%s%lld%s%d", newBlock.index, newBlock.previousHash, (long long)newBlock.timestamp, newBlock.data,nonce);
        
        sha256_hex(temp, strlen(temp), newBlock.hash);
        if(strncmp(newBlock.hash, pattern, strlen(pattern))==0){
            int available=0;
            for(int i=0;i<list->lastelement;i++){//checking whether the nonce is already used
                if(list->elements[i]==nonce){
                    available=1;
                    break;
                }
            }
            if(available==0){//if the nonce is not used earlier, then it is used by the current hash
                list->elements[list->lastelement]=nonce;
                list->lastelement++;
                return newBlock;
            }
        }
        nonce++;
    }
    
    return newBlock;
}

int isBlockValid(Block newBlock, Block previousBlock,nonceList* list) {
    if (newBlock.index != previousBlock.index + 1) {
        return 0;
    }
    if (strcmp(newBlock.previousHash, previousBlock.hash) != 0) {
        return 0;
    }
    char recalculatedHash[HASH_SIZE] = { 0 };
    char temp[1024] = { 0 };
    
    sprintf_s(temp, sizeof(temp), "%d%s%lld%s%d", newBlock.index, newBlock.previousHash, (long long)newBlock.timestamp, newBlock.data,list->elements[--list->lastelement]);
    
    sha256_hex(temp, strlen(temp), recalculatedHash);
    if (strcmp(recalculatedHash, newBlock.hash) != 0) {
        return 0;
    }
    return 1;
}