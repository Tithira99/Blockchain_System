#include "BlockNode.h"
#include "sha256.h"
#include <string.h>
#include <stdio.h>
int main() {
    BlockNode* blockchain = createGenesisNode();
    printf("Genesis Block has been created with hash: %s\n\n", blockchain->block.hash);

    BlockNode* lastNode = blockchain;
    char data[256];
    int blockchainLength = 1; // genesis block = 1
    nonceList list;
    list.lastelement=0;
    while (1) {
        printf("Enter new-block data ('exit' to stop): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0; // Remove newline character

        // condition --> exit
        if (strcmp(data, "exit") == 0) {
            break;
        }

        //Info --> new block
        lastNode = addBlock(lastNode, data, &list);
        if (lastNode != NULL) {
            blockchainLength++;
            printf("\nBlock added with new hash: %s\n", lastNode->block.hash);
            printf("\nNew block index: %d\n", lastNode->block.index);
            printf("New block prev hash: %s\n", lastNode->block.previousHash);
            printf("New block data: %s\n", lastNode->block.data);
            printf("\nCurrent blockchain length: %d\n\n", blockchainLength);
        }
        else {
            fprintf(stderr, "Failed to add new block.\n");
        }
    }

    if (isChainValid(blockchain,&list)) {
        printf("The blockchain is valid.\n");
    }
    else {
        printf("The blockchain is invalid!\n");
    }

    // Free --> allocated memory
    BlockNode* current = blockchain;
    while (current) {
        BlockNode* toFree = current;
        current = current->next;
        free(toFree);
    }

    printf("Blockchain program exited.\n");
    return 0;
}