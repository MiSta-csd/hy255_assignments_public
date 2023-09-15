/*  Minos Stavrakakis - csd4120
    HY255 - Assignment2
    mystring_ars.c */

#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "mystring.h"



/* Return the length of string pcStr.
   It is a checked runtime error for pcStr to be NULL. */
size_t ms_length(const char pcStr[])
{
    size_t uiLength= 0U;
    assert(pcStr != NULL);
    while (pcStr[uiLength] != '\0')
        uiLength++;
    return uiLength;
}

/*  Description: Copy string strSrc to string strDest and return a pointer to
    strDest
    Parameters: char strDest[], const char strSrc[]
    Returns: char*
    PreConditions: strDest != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_copy(char strDest[], const char strSrc[])
{
    size_t i = 0U;
    assert(strSrc);
    while((strDest[i] = strSrc[i]) != '\0')
        i++;
    return strDest;
}


/*  Description: Copy the n first characters of strSrc to strDest and return
    strDest. If strSrc lenghth < strDest length fills strDest remainder with
    '\0'
    Parameters: char strDest[], const char strSrc[], size_t n
    Returns: char*
    PreConditions: strDest != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_ncopy(char strDest[], const char strSrc[], size_t n)
{
    assert(strDest);
    size_t l = ms_length(strDest);
    size_t i = 0U;
    for(;(i<n && strSrc[i]!='\0');i++)
        strDest[i]=strSrc[i];
    for(;i<l;i++)
        strDest[i]='\0';
    return strDest;
}

/*  Description: Concatenate strSrc to the end of strDest and return strDest.
    User's responsibility to ensure strDest can hold the extra chars added
    Parameters: char strDest[], const char strSrc[]
    Returns: char *
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_concat(char strDest[], const char strSrc[])
{
    assert(strSrc);
    assert(strDest);
    size_t l_Dest = ms_length(strDest);
    size_t i = 0U;
    for(;strSrc[i]!='\0';i++)
        strDest[l_Dest+i]=strSrc[i];
    strDest[l_Dest+i]='\0';
    return strDest;
}

/*  Description: Append n first bytes of strSrc to strDest. If strSrc length < n
    append it as a whole
    Parameters: char strDest[], const char strSrc[], size_t n
    Returns: char *
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_nconcat(char strDest[], const char strSrc[], size_t n)
{
    assert(strSrc);
    assert(strDest);
    size_t l_Dest = ms_length(strDest);
    size_t i = 0U;
    for(;(i<n && strSrc[i]!='\0');i++)
        strDest[l_Dest+i]=strSrc[i];
    strDest[l_Dest+i]='\0';
    return strDest;

}

/*  Description: Compares str1 to str2 character to character,until a different one 
	is found or end-of-string. Then depending on byte value difference it returns:
        negative: if str2[i] greater than str1[i]
        positive: if str1[i] greater than str2[i]
        equal to zero: if str1[i] == str2[i]
    Parameters: const char str1[], const char str2[]
    Returns: int
    PreConditions: str1 & str2 != NULL
    PostConditions: int is returned
    */
int ms_compare(const char str1[], const char str2[])
{
    assert(str1);
    assert(str2);
    size_t i=0U;
    while(str1[i]!='\0'){
        if(str1[i]>str2[i])
            return 1;
        if(str1[i]<str2[i])
            return -1;
        if(str2[i]=='\0')
            return 1;
        i++;
    }
    if(str2[i]!='\0')
        return -1;
    return 0;
}

/*  Description: Compares str1 to str2 character to character, up to n-th
    character, until a different one is found or end-of-string. Then depending 
    on byte value difference it returns:
        negative: if str2[i] greater than str1[i]
        positive: if str1[i] greater than str2[i]
        equal to zero: if str1[i] == str2[i]
    Parameters: const char str1[], const char str2[]
    Returns: int
    PreConditions: str1 & str2 != NULL
    PostConditions: int is returned
    */
int ms_ncompare(const char str1[], const char str2[], size_t n)
{
    assert(str1);
    assert(str2);
    size_t i=0U;
    while((str1[i]!='\0') && (i<n)){
        if(str1[i]>str2[i])
            return 1;
        if(str1[i]<str2[i])
            return -1;
        if(str2[i]=='\0')
            return 1;
        i++;
    }
    if(str2[i]!='\0')
        return -1;
    return 0;
}

/*  Description: Search for subtring needle in string haystack, return
    a char* point to the index it gets found at or NULL if not found
    Parameters: const char haystack[], const char needle[], size_t n
    Returns: int
    PreConditions: haystack & needle != NULL
    PostConditions: char* or NULL is returned 
    */
char *ms_search(const char haystack[], const char needle[])
{
    assert(haystack);
    assert(needle);
    size_t i=0U,j;
    size_t l_needle = ms_length(needle);
    size_t l_haystack = ms_length(haystack);
    while(i <= (l_haystack - l_needle)){
        if(haystack[i]==needle[0]){
            //k = i;
            j = 0U;
            while((haystack[i+j]==needle[j]) && j<l_needle)
                j++;
            if(j==l_needle)
                return (char*) &(haystack[i]);
        }
        i++;
    }
    return NULL;
}
