#include "Set.h"
#include <assert.h>

/*Funktionen ar fardig*/
Set initializeSet(void)
{
	return createEmptyList();
}

/* Tips: tank pa att inte lagga till elementet om det redan finns i *set
   Postcondition: 'element' finns i set (tips: anvand isInSet() for att verifiera) */
void addToSet(Set* set, const Data element)
{
	if (!search(*set, element)) // we only want to do anything if we can't find the element in the set already
		addLast(set, element);

	assert(isInSet(*set, element));
}

/* Postcondition: 'element' finns INTE i set (tips: anvand isInSet() for att verifiera) */
void removeFromSet(Set* set, const Data element)
{
	removeElement(set, element);
}

int isInSet(const Set set, const Data element)
{
    return search(set, element); // Ersatt med ratt returvarde
}

/* Anvands for testning och felsokning */
void printSet(const Set set, FILE *textfile)
{
	printList(set, textfile);
}