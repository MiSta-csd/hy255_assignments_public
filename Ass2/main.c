/*  Minos Stavrakakis - csd4120
    HY255 - Assignment2
    main.c */

#include <stdlib.h>
#include "mystring.h"
#include <string.h>
#include <stddef.h>







int main()
{
    char ex1[10]= "awesome";
    char ex2[30]= "Yoan ";
    //char *ex2;
    char ex3[10]= "wes";
    char ex4[16]= "awesomebebe";
    char greeting[] = "Hello";
    char* ptr1;
    size_t cnt;
    int i;

    //assert(sizeof(ex1)>sizeof(ex2));
    cnt = ms_length(ex1);
    //ms_copy(ex2,ex1);
    //ms_ncopy(ex2,ex1,3);;
    //ms_concat(ex2,ex1);
    //ms_nconcat(ex2,ex1,3);
    //i = ms_compare(ex2,ex1);
    i = ms_ncompare(ex1,ex4,10);
    ptr1 = ms_search(ex1,ex3);

    printf("Hello world!\n");
    printf("\n\nSize of str: %d\n\n", cnt);
    printf("%s\n", ex2);
    printf("%d\n", i);
    printf("%s\n", ptr1);
    printf("%d\n",sizeof(ex2));
    printf("%d\n",sizeof(greeting));
    return 0;
}
