/*  Minos Stavrakakis - csd4120
    HY255 - Assignment3
    symtable.h */

#include<stdio.h>
#include<stddef.h>

typedef struct SymTable * SymTable_T;

/*  Description: Returns a new, empty SymTable_T
    Parameters: void
    Returns: SymTable_T
    PreConditions: -
    PostConditions: new SymTable_T returned
    */
SymTable_T SymTable_new(void);


/*  Description: Free memory alocated for SymTable_T and its'
	contents
    Parameters: SymTable_T oSymTable
    Returns: void
    PreConditions: oSymTable != NULL
    PostConditions: memory allocated for oSymTable freed
    */
void SymTable_free(SymTable_T oSymTable);


/*  Description: Returns the number of bindings contained in a
	SymTable_T object
    Parameters: SymTable_T oSymTable
    Returns: unsigned int
    PreConditions: oSymTable != NULL
    PostConditions: num of bindings returned
    */
unsigned int SymTable_getLength(SymTable_T oSymTable);


/*  Description: Checks if a binding w pcKey exists in oSymTable, if
				 not adds a new binding. Returns 1 if binding added
				 successfully, 0 otherwise.
    Parameters: SymTable_T oSymTable, const char *pcKey,
                const void *pvValue
    Returns: int
    PreConditions: oSymTable != NULL, pcKey != NULL
    PostConditions: appropriate int value returned
    */
int SymTable_put(SymTable_T oSymTable, const char *pcKey,
                          const void *pvValue);


/*  Description: Removes a binding that contains pcKey from SymTable_T.
				 Returns 1 if successful, 0 otherwise.
    Parameters: SymTable_T oSymTable, const char *pcKey
    Returns: int
    PreConditions: oSymTable != NULL, pcKey != NULL
    PostConditions: aprropriate int value returned
    */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);


/*  Description: Search SymTable for binding with given key. Return 1
				 if successful, 0 otherwise.
    Parameters: SymTable_T oSymTable, const char *pcKey
    Returns: int
    PreConditions: oSymTable != NULL, pcKey != NULL
    PostConditions: aprropriate int value returned
    */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);


/*  Description: Returns a new, empty SymTable_T
    Parameters: void
    Returns: SymTable_T
    PreConditions: oSymTable != NULL, pcKey != NULL
    PostConditions: new SymTable_T returned
    */
void* SymTable_get(SymTable_T oSymTable, const char *pcKey);


/*  Description: Applies pfApply to every binding in oSymTable
    Parameters: SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra)
    Returns: void
    PreConditions: oSymTable != NULL, pcKey != NULL
    PostConditions:
    */
void SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue,
                                   void *pvExtra),
                   const void *pvExtra);


/*================*/
/* Prints SymTable : For testing Purposes */
void SymTable_Print(SymTable_T oSymTable);
