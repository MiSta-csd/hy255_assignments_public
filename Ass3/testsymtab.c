#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"


/*=================*/
/* Implementation for testing purposes */
void pfApply(const char *pcKey, void *pvValue, void *pvExtra)
{
	printf("\npfApply called for key: %s \n", pcKey);
	printf("pfApply returned (_)_)IIIID \n");
}
/*=================*/

int main(void)
{
	SymTable_T oSymTable;
    char pcKey1[10] = "Vasilis";
    char pcKey2[10] = "Chris";
    char pcKey3[10] = "Anestis";
    char pcKey4[10] = "Bebis";
    char pcKey5[10] = "Eyterpi";
	int i1=313, i2=181, i3=456, i4=223;
	int boo = 9, malcolm;

	oSymTable = SymTable_new();

    printf("%d\n",SymTable_getLength(oSymTable));

    SymTable_put(oSymTable, pcKey1,(void*) i1);
    SymTable_put(oSymTable, pcKey2,(void*) i2);
    SymTable_put(oSymTable, pcKey3,(void*) i3);
    SymTable_put(oSymTable, pcKey4,(void*) i4);

    SymTable_Print(oSymTable);
    printf("\n\n");
    SymTable_remove(oSymTable, pcKey1);
    SymTable_put(oSymTable, pcKey1,(void*) i1);

    boo = SymTable_contains(oSymTable, pcKey5);
    printf("\nboo = %d\n\n", boo);
    /*SymTable_free(oSymTable);*/

    SymTable_Print(oSymTable);

    printf("\n\n");
    malcolm = (int)SymTable_get(oSymTable, pcKey3);
    printf("malcolm = %d", malcolm);

    printf("\n\n");
    printf("%d\n",SymTable_getLength(oSymTable));

    printf("\n\n");
    SymTable_map(oSymTable, pfApply, (void*) i2);

    SymTable_free(oSymTable);

	return 0;
}
