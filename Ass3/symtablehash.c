/*  Minos Stavrakakis - csd4120
    HY255 - Assignment3
    symtablehash.c */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "symtable.h"

#define SIZE 509
#define HASH_MULTIPLIER 65599



typedef struct binding {
	void *value;
	char *key;
	struct binding *next;
} bind;

struct SymTable {
	unsigned int numOfBinds;
	bind *btable[SIZE];
};

/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  return uiHash % (SIZE);
}


SymTable_T SymTable_new(void)
{
	SymTable_T table;
	unsigned int i;
	table = (SymTable_T) malloc(sizeof(struct SymTable));
	assert(table);
	table->numOfBinds = 0U;
	for(i=0U;i<SIZE;i++)
		table->btable[i] = NULL;

	return table;
}


void SymTable_free(SymTable_T oSymTable)
{
	unsigned int i;
	bind *temp1;
	bind *temp2;
	assert(oSymTable);

	for(i=0U;i<SIZE;i++){
		if(oSymTable->btable[i]!=NULL){
			temp1 = oSymTable->btable[i];
			while(temp1!=NULL){
				temp2 = temp1;
				temp1 = temp1->next;
				free(temp2->key);
				free(temp2);
			}
		}
	}
	oSymTable->numOfBinds = 0U;
	free(oSymTable);
	return;
}


unsigned int SymTable_getLength(SymTable_T oSymTable)
{
	assert(oSymTable);
	return oSymTable->numOfBinds;
}


int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                 		const void *pvValue)
{
	bind *temp1;
	bind *temp2;
	unsigned int i=0U;
	assert(oSymTable);
	assert(pcKey);

	if(SymTable_contains(oSymTable, pcKey)){
		return 0;
	}

	temp1 = (bind*) malloc(sizeof(bind));
	assert(temp1);

	temp1->key = (char*) malloc((strlen(pcKey)+1)*sizeof(char));
	assert(temp1->key);

	temp1->key = strdup(pcKey);
	temp1->value = (void*)pvValue;

	i = SymTable_hash(pcKey);
	temp2 = oSymTable->btable[i];
	if(oSymTable->btable[i]!=NULL){
		temp1->next = temp2;
		oSymTable->btable[i] = temp1;
	} else {
		temp1->next = NULL;
		oSymTable->btable[i] = temp1;
	}
	oSymTable->numOfBinds++;
	return 1;
}


int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
	bind *temp1;
	bind *temp2;
	unsigned int i;

	assert(oSymTable);
	assert(pcKey);

	i = SymTable_hash(pcKey);
	temp1 = oSymTable->btable[i];
	while(temp1!=NULL){
		temp2 = temp1;
		temp1 = temp1->next;
		if(!strcmp(pcKey,temp2->key)){
			free(temp2->key);
			free(temp2);
			oSymTable->btable[i]=temp1;
			oSymTable->numOfBinds--;
			return 1;
		}
		if(!strcmp(pcKey,temp1->key)){
			temp2->next = temp1->next;
			free(temp1->key);
			free(temp1);
			oSymTable->numOfBinds--;
			return 1;
		}

	}
	return 0;
}


int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
	unsigned int i;
	bind *temp1;

	assert(oSymTable);
	assert(pcKey);

	i = SymTable_hash(pcKey);
	temp1 = oSymTable->btable[i];
	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key))
				return 1;
		temp1 = temp1->next;
	}
	return 0;
}


void* SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
	unsigned int i;
	bind *temp1;

	assert(oSymTable);
	assert(pcKey);

	i = SymTable_hash(pcKey);
	temp1 = oSymTable->btable[i];

	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key))
			return (void*)temp1->value;
		temp1 = temp1->next;
	}

	return NULL;
}

/*=================*/
/* Implementation for testing purposes */
/*
void pfApply(const char *pcKey, void *pvValue, void *pvExtra)
{
	printf("pfApply called for key: %s \n", pcKey);
	printf("pfApply returned (_)_)IIIID \n");
}
*/
/*=================*/

void  SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra)
{
	bind *temp1;
	unsigned int i;

	assert(oSymTable);
	assert(pfApply);

	for(i=0U;i<SIZE;i++){
		if(oSymTable->btable[i]!=NULL){
			temp1 = oSymTable->btable[i];
			while(temp1!=NULL){
				pfApply(temp1->key, temp1->value,(void*)pvExtra);
				temp1 = temp1->next;
			}
		}
	}
	return;
}

/*-----------------------*/
/* Implementation for testing purposes */
void SymTable_Print(SymTable_T oSymTable)
{
    bind *temp1;
    unsigned int i;
    assert(oSymTable);

	for(i=0U;i<SIZE;i++){
		if(oSymTable->btable[i]!=NULL){
            temp1 = oSymTable->btable[i];
            while (temp1 != NULL){
                printf("key: %s\t\tvalue: %d \n",
                        temp1->key, (int)temp1->value);
                temp1 = temp1->next;
            }
		}
	}
}
