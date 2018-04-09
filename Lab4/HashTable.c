#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som ar Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key % tablesize; // TODO: this is stupid but works
}

/* Leta framat enligt principen oppen adressering
   Antalet krockar returneras via pekaren col i parameterlistan */
static int linearProbe(const HashTable* htable, Key key, unsigned int *col)
{
	int indexToSearch = hash(key, htable->size);
	int startIndex = indexToSearch;
	*col = 0;
	while (htable->table[indexToSearch].key != key && htable->table[indexToSearch].key != UNUSED)
	{
		*col++;
		indexToSearch++;
		if (indexToSearch >= htable->size)
			indexToSearch = 0;
		if (indexToSearch == startIndex)
			break;
	}

	if (htable->table[indexToSearch].key != key && htable->table[indexToSearch].key != UNUSED)
		return -1; // the lookup ended up going a full lap without finding the key or an empty space
	else
		return indexToSearch;
}

/*Allokera minne for hashtabellen*/
HashTable createHashTable(unsigned int size)
{
	// TODO? does this even work? it seems to, but I'm not convinced
	HashTable table;
	table.table = malloc(sizeof(struct Bucket) * size);
	table.size = size;
	for (int i = 0; i < table.size; i++)
		table.table[i].key = UNUSED;
	return table;
}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
/* Returnerar 1 om krock, annars 0 */
unsigned int insertElement(HashTable* htable, const Key key, const Value value)
{
	// Postcondition: det finns ett element for key i tabellen (anvand lookup() for att verifiera)
	int collisions = 0;
	int hashedIndex = linearProbe(htable, key, &collisions);

	if (hashedIndex != -1)
	{
		if (htable->table[hashedIndex].key == key)
			htable->table[hashedIndex].value = value;
		else
		{
			htable->table[hashedIndex].key = key;
			htable->table[hashedIndex].value = value;
		}
	}

    return (collisions > 0); //Ersatt med ratt varde
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
	int collisions = 0;
	int hashedIndex = linearProbe(htable, key, &collisions);

	if (hashedIndex != -1)
	{
		//htable->table[hashedIndex].value = ; // TODO: evaluate if this needs fixing
		htable->table[hashedIndex].key = UNUSED;
	}
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
	int collisions = 0;
	int hashedIndex = linearProbe(htable, key, &collisions);

	if (hashedIndex != -1 && htable->table[hashedIndex].key == key)
		return &(htable->table[hashedIndex].value);
	else
		return NULL;
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
	free(htable->table);
	htable->table = NULL;
	htable->size = 0;
	// Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
	if (htable != NULL)
		return htable->size;
	else
		return 0;
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	for (int i = 0; i < htable->size; i++)
	{
		if (htable->table[i].key != UNUSED)
		{
			printPerson(&(htable->table[i].value), i);
			printf("\n");
		}
	}
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
