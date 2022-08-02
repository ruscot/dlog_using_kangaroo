#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZEATTACK 1048576

struct DataItem {
   unsigned __int128 exponent_value;   
   unsigned __int128 hashKey;
   struct DataItem *next;
};

struct DataItem* tameKangaroo[SIZEATTACK]; 
struct DataItem* wildKangaroo[SIZEATTACK]; 

uint32_t modulo = (1<<20)-1;

int hashCode(unsigned __int128 key) {
   return key & modulo;
}

void freeTameKangarooTable() {
    int i;
    struct DataItem* currentItem;
    struct DataItem* saveCurrentItem;
    for(i = 0; i < SIZEATTACK; i++){
        currentItem = tameKangaroo[i];
        while(currentItem != NULL){
            saveCurrentItem = currentItem->next;
            free(currentItem);
            currentItem = saveCurrentItem;
        }
    }
}

void freeWildKangarooTable() {
    int i;
    struct DataItem* currentItem;
    struct DataItem* saveCurrentItem;
    for(i = 0; i < SIZEATTACK; i++){
        currentItem = wildKangaroo[i];
        while(currentItem != NULL){
            saveCurrentItem = currentItem->next;
            free(currentItem);
            currentItem = saveCurrentItem;
        }
    }
}

int searchTameKangarooTable(unsigned __int128 key, unsigned __int128 *exponent) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   struct DataItem* currentItem = tameKangaroo[hashIndex];
   while(currentItem != NULL) {
	
      if(currentItem->hashKey == key) {
         printf("In search tame %llx\n",*exponent);
         *exponent = currentItem->exponent_value;
         printf("In search tame new exponent %llx\n",*exponent);
         return 1;
      } 
			
      currentItem = currentItem->next;
   }
	
   return 0;        
}

int searchWildKangarooTable(unsigned __int128 key, unsigned __int128 *exponent) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   struct DataItem* currentItem = wildKangaroo[hashIndex];
   while(currentItem != NULL) {
	
      if(currentItem->hashKey == key) {
         printf("In search wild %llx\n",*exponent);
         *exponent = currentItem->exponent_value;
         printf("In search wild new exponent %llx\n",*exponent);
         return 1;
      } 
			
      currentItem = currentItem->next;
   }
	
   return 0;        
}

void insertTameKangarooTable(unsigned __int128 key, unsigned __int128 exponent) {
   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->exponent_value = exponent;
   item->hashKey = key;

   //get the hash 
   int hashIndex = hashCode(key);
   item->next = tameKangaroo[hashIndex];
   tameKangaroo[hashIndex] = item;
}

void insertWildKangarooTable(unsigned __int128 key, unsigned __int128 exponent) {
   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   item->exponent_value = exponent;
   item->hashKey = key;

   //get the hash 
   int hashIndex = hashCode(key);
   item->next = wildKangaroo[hashIndex];
   wildKangaroo[hashIndex] = item;
}
