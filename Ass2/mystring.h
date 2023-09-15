/*  Minos Stavrakakis - csd4120
    HY255 - Assignment2
    mystring.h */

#include<stdio.h>
#include<assert.h>
#include<stddef.h>


/* Return the length of string pcStr.
   It is a checked runtime error for pcStr to be NULL. */
size_t ms_length(const char *pcStr);


/*  Description: Copy string strSrc to string strDest and return a pointer to
    strDest
    Parameters: char *strDest, const char *strSrc
    Returns: char*
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_copy(char *strDest, const char *strSrc);


/*  Description: Copy the n first characters of strSrc to strDest and return
    strDest. If strSrc lenghth < strDest length fills strDest remainder with
    '\0'
    Parameters: char *strDest, const char *strSrc, size_t n
    Returns: char*
    PreConditions: strSrc && strDest != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_ncopy(char *strDest, const char *strSrc, size_t n);


/*  Description: Append n first bytes of strSrc to strDest. If strSrc length < n
    append it as a whole
    Parameters: char *strDest, const char *strSrc, size_t n
    Returns: char *
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_nconcat(char *strDest, const char *strSrc, size_t n);


/*  Description: Compares str1 to str2 character to character,until a different
    one	is found or end-of-string. Then depending on byte value difference it
    returns:
        negative: if str2 greater than str1
        positive: if str1 greater than str2
        equal to zero: if str1 == str2
    Parameters: const char *str1, const char *str2
    Returns: int
    PreConditions: str1 & str2 != NULL
    PostConditions: int is returned
    */
int ms_compare(const char *str1, const char *str2);


/*i ms_compare sygrinei ta 2 strings kai epistresei 0 an einai isa,arnitiko
an to str2 einai megalytero apo to str1 kai thetiko an to str1 einai
megalytero apo to str2 kai vgazei error se pisriptwsi pou einai NULL*/
int ms_compare (const char * str1 , const char * str2);


/*  Description: Compares str1 to str2 character to character, up to n-th
    character, if a different one is found, depending on byte value
    difference it returns:
        negative: if str2 greater than str1
        positive: if str1 greater than str2
        zero:     if str1 == str2
    Parameters: const char *str1, const char *str2, size_t n
    Returns: int
    PreConditions: str1 & str2 != NULL
    PostConditions: int is returned
    */
int ms_ncompare(const char *str1, const char *str2, size_t n);


/*  Description: Search for subtring needle in string haystack, return
    a char* point to the index it gets found at or NULL if not found
    Parameters: const char *haystack, const char *needle
    Returns: int
    PreConditions: haystack & needle != NULL
    PostConditions: char* is returned
    */
char *ms_search(const char *haystack, const char *needle);

