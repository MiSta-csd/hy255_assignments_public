/*  Minos Stavrakakis - csd4120
    HY255 - Assignment3
    symtablelist.c */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "symtable.h"



typedef struct binding {
	void *value;
	char *key;
	struct binding *next;
} bind;

struct SymTable {
	unsigned int numOfBinds;
	bind *head;
};




SymTable_T SymTable_new(void)
{
	SymTable_T table;
	table = (SymTable_T) malloc(sizeof(struct SymTable));
	table->numOfBinds = 0U;
	table->head = NULL;

	return table;
}


void SymTable_free(SymTable_T oSymTable)
{
	bind *temp1;
	bind *temp2;
	assert(oSymTable);
	temp1 = oSymTable->head;
	while(temp1!=NULL){
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2->key);
		free(temp2);
	}
	oSymTable->numOfBinds = 0U;
	oSymTable->head=NULL;
	oSymTable = NULL;
	free(oSymTable);
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

	assert(oSymTable);
	assert(pcKey);

	temp1 = oSymTable->head;

	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key))
			return 0;
		temp1 = temp1->next;
	}

	temp1 = malloc(sizeof(bind));
	assert(temp1);
	temp1->key = malloc((strlen(pcKey)+1)*sizeof(char));
	assert(temp1->key);
	temp1->key = strdup(pcKey);
	temp1->value = (void*)pvValue;
	temp1->next = oSymTable->head;

	oSymTable->head = temp1;
	oSymTable->numOfBinds++;
	return 1;
}


int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
	bind *temp1;
	bind *temp2;

	assert(oSymTable);
	assert(pcKey);

	temp1 = oSymTable->head;

	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key)){
			temp2->next = temp1->next;
			free(temp1->key);
			free(temp1);
			oSymTable->numOfBinds--;
			return 1;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}

    return 0;
}


int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
	bind *temp1;

	assert(oSymTable);
	assert(pcKey);

	temp1 = oSymTable->head;

	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key))
			return 1;
		temp1 = temp1->next;
	}
	return 0;
}


void* SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
	bind *temp1;
	assert(oSymTable);
	assert(pcKey);

	temp1 = oSymTable->head;

	while(temp1!=NULL){
		if(!strcmp(pcKey,temp1->key))
			return temp1->value;
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
	assert(oSymTable);
	assert(pfApply);
	temp1 = oSymTable->head;

	while(temp1!=NULL){
		pfApply(temp1->key, temp1->value,(void*)pvExtra);
		temp1 = temp1->next;
	}
	return;
}

/*-----------------------*/
/* Implementation for testing purposes */
void SymTable_Print(SymTable_T oSymTable)
{
    bind *temp1;
    assert(oSymTable);
	temp1 = oSymTable->head;

    while (temp1 != NULL){
        printf("key: %s\t\tvalue: %d \n",
               temp1->key, (int)temp1->value);
        temp1 = temp1->next;
    }
}
