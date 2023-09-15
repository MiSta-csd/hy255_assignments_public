/*  Minos Stavrakakis - csd4120
    HY255 - Assignment2
    mystring_ars.c */

#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "mystring.h"



/* Return the length of string pcStr.
   It is a checked runtime error for pcStr to be NULL. */
size_t ms_length(const char *pcStr)
{
  const char *pcStrEnd = pcStr;
  assert(pcStr); /* Works because NULL and FALSE are identical. */
  while (*pcStrEnd) /* Works because end-of-string and FALSE are identical. */
    pcStrEnd++;
  return pcStrEnd - pcStr;
}

/*  Description: Copy string strSrc to string strDest and return a pointer to
    strDest
    Parameters: char *strDest, const char *strSrc
    Returns: char*
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_copy(char *strDest, const char *strSrc)
{
    assert(strSrc && strDest); /* Works because NULL and FALSE are identical */
    char *temp = strDest;
    while((*strDest++ = *strSrc++)) /* Progresses ptr and copies until */
        ;                           /* end-of-strSrc (identical to false) */
    return temp;
}


/*  Description: Copy the n first characters of strSrc to strDest and return
    strDest. If strSrc lenghth < strDest length fills strDest remainder with
    '\0'
    Parameters: char *strDest, const char *strSrc, size_t n
    Returns: char*
    PreConditions: strSrc && strDest != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_ncopy(char *strDest, const char *strSrc, size_t n)
{
    assert(strSrc && strDest); /* Works because NULL and FALSE are identical. */
    char *temp = strDest;
    while ((*strDest++ = *strSrc++) && (--n))  /* copy until end-of-string or */
        ;              /* n first characters reached (n=0 identical as false) */
    return temp;
}

/*  Description: Concatenate strSrc to the end of strDest and return strDest.
    User's responsibility to ensure strDest can hold the extra chars added
    Parameters: char *strDest, const char *strSrc
    Returns: char *
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_concat(char *strDest, const char *strSrc)
{
    assert(strSrc && strDest); /* Works because NULL and FALSE are identical. */
    char *temp = strDest;
    while (*strDest)    /* Works because '\0' and FALSE are identical. */
        strDest++;
    while ((*strDest++ = *strSrc++)) /* same as above ^ */
        ;
    return temp;
}

/*  Description: Append n first bytes of strSrc to strDest. If strSrc length < n
    append it as a whole
    Parameters: char *strDest, const char *strSrc, size_t n
    Returns: char *
    PreConditions: strDest & strSrc != NULL
    PostConditions: char* to strDest is returned
    */
char *ms_nconcat(char *strDest, const char *strSrc, size_t n)
{
    assert(strSrc && strDest); /* Works because NULL and FALSE are identical. */
    char *temp = strDest;
    while (*strDest) /* Works because '\0' identical as false */
        strDest++;   /* Progress ptr to end of string */
   while ((*strDest++ = *strSrc++) && (--n)) /* copy until end-of-string or */
        ;            /* n first characters reached (n=0 identical as false) */
    return temp;
}

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
int ms_compare(const char *str1, const char *str2)
{
    assert(str1 && str2);  /* Works because NULL and FALSE are identical. */
    while (*str1 && (*str1++ == *str2++))  /* compares and progresses ptr */
        ;   /* ends in: dif char or end-of-str1 */
    return *(unsigned char*)str1 - *(unsigned char*)str2;
    /* cast for portability reasons */
}

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
int ms_ncompare(const char *str1, const char *str2, size_t n)
{
    assert(str1 && str2);  /* Works because NULL and FALSE are identical. */
    while (*str1 && (*str1++ == *str2++) && (--n))  /* compares and progresses */
        ;                   /* ptr ends in: dif char, end-of-str1 or n=0*/
                            /* all the above are identical to false */
    return *(unsigned char*)str1 - *(unsigned char*)str2;
    /* cast for portability reasons */
}

/*  Description: Search for subtring needle in string haystack, return
    a char* point to the index it gets found at or NULL if not found
    Parameters: const char *haystack, const char *needle
    Returns: int
    PreConditions: haystack & needle != NULL
    PostConditions: char* or NULL is returned
    */
char *ms_search(const char *haystack, const char *needle)
{
    assert(haystack && needle);  /* because NULL and FALSE are identical. */
    while(*haystack){  /* Works because '\0' and FALSE are identical. */
        char* start = (char*) haystack; /* cast to bypass 'const' */
        char* substr = (char*) needle;  /* cast to bypass 'const' */
        while((*substr) && (*haystack == *substr)){ /*  */
                haystack++;
                substr++;
        }
        if(!*substr)        /* Because true equals !(False) and False */
            return start;   /* identical to end-of-string */
        haystack = start+1;
    }
    return NULL;
}

