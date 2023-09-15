Minos Stavrakakis - csd4120
HY255 - Assignment2

1.	Ναι. How about assert(sizeof(strDest)>sizeof(strSrc)) για την 
	char *ms_copy(char *strDest, const char *strSrc) για παράδειγμα;


2.	Είναι δυνατόν. e.g. assert(n>0)	όπου n size_t variable.
	Κάτι τέτοιο δεν θα είχε νόημα καθότι ο τύπος size_t είναι 
	ορισμένος σαν unsigned και ως εκ τούτου πάντα θετικός.