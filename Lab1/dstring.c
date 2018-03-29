#include "dstring.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

DString dstring_initialize(const char* str)
{
	// Precondition: str ar ej NULL - testas med en assert

	/* Tips:
	   - Allokera (t.ex. med malloc) tillrackligt med minne for att fa plats med str,
         glom inte att det maste finnas plats fšr \0 (nolltermineringen).
         Glom inte att testa sa att allokeringen lyckades
	   - Det ar tillatet att anvanda inbyggda strangfunktioner (som t.ex strcpy())
	   - Kom ihag att anvanda assert() */

	// Postcondition: returvardet innehaller samma strang som 'str' - behover inte testas med assert



    // **************** //
    // CODE BEGINS HERE //
    // **************** //

    // Precondition testing:
    assert(str != NULL);

    // Checking string length and allocating memory
    int stringLength;
    for (stringLength = 0; str[stringLength] != '\0'; stringLength++);
    DString returnString = malloc(sizeof(char) * (stringLength + 1));

    if (returnString == NULL)
        // Memory allocation failed! This is very very bad. Returning NULL.
        return NULL;

    // Write string to new string pointer
    strcpy_s(returnString, sizeof (char) * (stringLength + 1), str);

    // Postcondition checking
    assert(strcmp(str, returnString) == 0);

    // Return the newly allocated, written string
	return returnString;
}

int dstring_concatenate(DString* destination, DString source)
{
    // Precondition: destination ar ej NULL
	// Precondition: *destination ar ej NULL
	// Precondition: source ar ej NULL
    // Preconditions testas med asserts.

	/* Tips: 
	   - Tank pa att *destination redan ar en dynamiskt allokerad strang
	   - Tank pa att vi kommer att behova allokera mer minne for att fa plats med den har langre strangen.
         Minnet som *destination pekar pa behover utokas (realloc), hur stort ska det "nya" minnet bli?
         Glom inte att nolltermineringen maste fa plats.
         Nar du allokerar minne dynamiskt maste du alltid testa sa att allokeringen lyckades innan du
         borjar jobba med minnet.
       - Det ar tillatet att anvanda inbyggda funktioner (som t.ex. strcat()).
    */

    // Postcondition: *destination innehaller den gamla strangen ihopslagen med source - behšver inte testas med assert.

    // **************** //
    // CODE BEGINS HERE //
    // **************** //

    // Precondition testing:
    assert(destination != NULL);
    assert(*destination != NULL);
    assert(source != NULL);

    // Checking string length and allocating memory
    int sourceLength = 0;
    for (sourceLength = 0; source[sourceLength] != '\0'; sourceLength++);

    char* destinationString = *destination;
    int destinationLength = 0;
    for (destinationLength = 0; destinationString[destinationLength] != '\0'; destinationLength++);

    int bufferSize = sizeof(char) * (sourceLength + destinationLength + 1);
    *destination = realloc(*destination, bufferSize);

    if (destination == NULL)
        // Memory allocation failed! Returning 0.
        return 0;

    if (strcat_s(*destination, bufferSize, source) != 0)
        // If strcat_s doesn't return 0, we had some kind of problem. Returning a "function failed" value in that case.
        return 0;

	return 1;
}

void dstring_truncate(DString* destination, unsigned int truncatedLength)
{
	// Precondition: destination ar ej NULL, *destination ar ej NULL
    // langden (truncateLength) far inte vara negativ
    // Preconditions testas med asserts

	/* Tips:
	   - Anvand realloc for att frigora det overflodiga minnet
         (realloc frigor forst minnet och allokerar sedan nytt for den angivna storleken)
	   - glom inte nolltermineringen
     
     Vad hander om truncateLength ar langre an vad strangen ar?*/

	// Postcondition: *destination ar inte langre an 'truncatedLength' tecken - behover inte testas med assert

    // **************** //
    // CODE BEGINS HERE //
    // **************** //

    // Check preconditions
    assert(destination != NULL);
    assert(*destination != NULL);
    assert(truncatedLength >= 0);

    // Check how long the input string is
    char* destinationString = *destination;
    unsigned int stringLength;
    for (stringLength = 0; destinationString[stringLength] != '\0'; stringLength++);

    // If we're trying to truncate it beyond its length, we just don't do anything at all.
    if (truncatedLength > stringLength)
        return;

    // Calculate size of destination memory and allocate it
    int bufferSize = sizeof(char) * (truncatedLength + 1);
    *destination = realloc(*destination, bufferSize);

    if (*destination == NULL)
        // Memory allocation failed! Failure!
        return;

    // Can't forget the null terminant.
    destinationString = *destination;
    destinationString[truncatedLength] = '\0';
}

void dstring_print(DString str, FILE* textfile)
{
	// Precondition: textfile ar inte NULL - maste testas innan du forsoker skriva till filen
    /*Tank pa att filpekaren kopplas till filen innan funktionen anropas*/

	/* filpekaren far inte stangas, filen ska fungera som vanligt efter anropet */

    // **************** //
    // CODE BEGINS HERE //
    // **************** //

    // Check preconditions
    assert(str != NULL);
    assert(*str != NULL);
    assert(textfile != NULL);

    // And just, uh... Write it. This isn't very complicated.
    fprintf(textfile, "%s", str);
}

void dstring_delete(DString* stringToDelete)
{
	// Precondition: stringToDelete ar inte NULL

	// Postcondition: *stringToDelete ar NULL och minnet ar frigjort - behover inte testas med assert

    // **************** //
    // CODE BEGINS HERE //
    // **************** //

    assert(stringToDelete != NULL);
    assert(*stringToDelete != NULL);

    free(*stringToDelete);
    *stringToDelete = NULL;
}
