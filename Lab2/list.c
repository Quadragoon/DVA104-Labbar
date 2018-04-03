#include "list.h"
#include <stdlib.h>
#include <assert.h>

/*Det Šr helt tillŒtet att lŠgga till egna hjŠlpfunktioner men de befintliga funktionerna fŒr inte Šndras*/

/*Hjalpfunktion till add
  Allokerar minne for en ny nod
  om allokeringen lyckades initieras data samt pekare (pekare initieras till NULL).
  Den nya noden (eller NULL) returneras.*/
static struct node* createListNode(const Data data)
{
	assert(data != NULL);

	struct node* createdNode;
	createdNode = malloc(sizeof(struct node));

	if (createdNode == NULL)
		return NULL;

	createdNode->data = data;
	createdNode->next = NULL;
	createdNode->previous = NULL;

	return createdNode;
}

/*Returnera en tom lista - funktionen ar fardig*/
List createEmptyList(void)
{
	return NULL;
}


/*Ar listan tom?
  Returnerar 1 om den Šr tom, annars 0*/
int isEmpty(const List list)
{
	if (list == NULL)
		return 1;
	else
		return 0;
}

/*Lagg till nod forst i listan*/
/*Postcondition: Det nya datat ligger forst i listan (testa med assert)*/
void addFirst(List *list, const Data data)
{
	//Anropa createListNode for att skapa den nya noden
	//Glom inte att testa att den nya noden faktiskt kunde skapas/tilldelas minne innan du fortsatter
	//Tank pa att listan kan vara tom nar en ny nod laggs till
	assert(data != NULL);

	struct node* nodeToAdd;
	nodeToAdd = createListNode(data);
	if (nodeToAdd != NULL)
	{
		if (isEmpty(*list))
			*list = nodeToAdd;
		else
		{
			nodeToAdd->next = *list;
			nodeToAdd->next->previous = nodeToAdd;
			*list = nodeToAdd;
		}
	}
}

/*Lagg till nod sist i listan
  Tips, nar du hittat ratt plats kan du anvanda funktionen addFirst for att lagga till*/
void addLast(List *list, const Data data)
{
	if (isEmpty(*list))
		addFirst(list, data);
	else
	{
		struct node* nodeToCheck = *list;
		while (nodeToCheck->next != NULL)
			nodeToCheck = nodeToCheck->next;

		struct node* nodeToAdd;
		nodeToAdd = createListNode(data);
		if (nodeToAdd != NULL)
		{
			nodeToAdd->previous = nodeToCheck;
			nodeToCheck->next = nodeToAdd;
		}
	}
}

/*Ta bort forsta noden i listan
  Precondition: listan ar inte tom (testa med assert)
  Noden ska lankas ur och minnet frigoras, resten av listan ska finnas kvar*/
void removeFirst(List *list)
{
	//Glom inte att frigora minnet for den nod som lankas ur listan.
	//Tank pa att listans huvud efter bortlankningen maste peka pa den nod som nu ar forst.

	assert(!isEmpty(*list));

	struct node* nodeToRemove = *list;
	if (nodeToRemove->next != NULL)
		nodeToRemove->next->previous = NULL;
	*list = nodeToRemove->next;

	nodeToRemove->data = NULL;
	nodeToRemove->next = NULL;
	nodeToRemove->previous = NULL;
	free(nodeToRemove);
}

/*Ta bort sista noden i listan
  Precondition: listan ar inte tom (testa med assert)t*/
void removeLast(List *list)
{
	//Glom inte att frigora minnet for den nod som lankas ur listan.
	//Tank pa att den nod som nu ar sist inte pekar nagonstans, dess pekare maste nollstallas

	assert(!isEmpty(*list));

	struct node* nodeToRemove = *list;
	while (nodeToRemove->next != NULL)
		nodeToRemove = nodeToRemove->next;

	if (nodeToRemove->previous == NULL)
		*list = NULL;
	else
		nodeToRemove->previous->next = NULL;

	nodeToRemove->data = NULL;
	nodeToRemove->next = NULL;
	nodeToRemove->previous = NULL;
	free(nodeToRemove);
}

/*Ta bort data ur listan (forsta forekomsten)
  Returnera 1 om datat finns, annars 0
  Tips, nar du hittar ratt nod kan du anvanda en av de ovanstaende funktionerna for att ta bort noden*/
int removeElement(List *list, const Data data)
{
	if (isEmpty(*list))
		return 0;

	struct node* nodeToRemove = *list;
	while (nodeToRemove->next != NULL && nodeToRemove->data != data)
		nodeToRemove = nodeToRemove->next;

	if (nodeToRemove->data != data)
		return 0; // We didn't find the data. Oh well.

	if (nodeToRemove->previous != NULL)
		nodeToRemove->previous->next = nodeToRemove->next;
	if (nodeToRemove->next != NULL)
		nodeToRemove->next->previous = nodeToRemove->previous;

	if (nodeToRemove == *list) // we're removing the first item, which acts as list index, so move the index up
		*list = nodeToRemove->next;

	nodeToRemove->data = NULL;
	nodeToRemove->next = NULL;
	nodeToRemove->previous = NULL;
	free(nodeToRemove);
	return 1; // We have found and removed the data. We will return this to report our success.
}

/*Finns data i listan?
  Om datat finns returneras 1, annars 0
  Tank pa att listan kan vara tom*/
int search(const List list, const Data data)
{
	if (isEmpty(list))
		return 0; // if the list is empty we won't find the requested data in it

	struct node* nodeToFind = list;
	while (nodeToFind->next != NULL && nodeToFind->data != data)
		nodeToFind = nodeToFind->next;

	if (nodeToFind->data == data)
		return 1; // The function found the data! Report this.
	else
		return 0; // Didn't find the data. Oh well.
}

/*Returnera antalet noder i listan*/
int numberOfNodesInList(const List list)
{
	if (isEmpty(list))
		return 0;

	struct node* currentNode;
	currentNode = list;
	int count = 1;

	while (currentNode->next != NULL)
	{
		currentNode = currentNode->next;
		count++;
	}

	return count; //Ersatt med ratt returvarde
}

/*Ta bort alla noder ur listan
  Glom inte att frigora minnet
  Postcondition: Listan ar tom, *list ar NULL (testa med assert)*/
void clearList(List* list)
{
	//Alla noder maste tas avallokeras en och en, det racker inte att endast frigora list.
	while (!isEmpty(*list))
		removeFirst(list);

	// Check that we've emptied the list successfully
	assert(*list == NULL);
}

/*Skriv ut listan
  Vid anropet kan man ange stdout som argument 2 for att skriva ut pa skarmen.
  Anvanda fprintf for att skriva ut.
  Den har typen av utskriftfunktion blir mer generell da man kan valja att skriva ut till skarmen eller till fil.*/
void printList(const List list, FILE *textfile)
{
	if (isEmpty(list))
		fprintf(textfile, "Empty list printed.");
	else
	{
		struct node* nodeToPrint = list;
		do
		{
			fprintf(textfile, "%d\n", nodeToPrint->data);
			nodeToPrint = nodeToPrint->next;
		} while (nodeToPrint != NULL);
	}
}

/*Returnera forsta datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getFirstElement(const List list)
{
	assert(list != NULL);

	struct node* firstElement;
	firstElement = list;

	return firstElement->data; //Ersatt med ratt returvarde
}

/*Returnera sista datat i listan
  Precondition: listan ar inte tom (testa med assert)*/
Data getLastElement(const List list)
{
	assert(list != NULL);

	struct node* listElement;
	listElement = list;

	while (listElement->next != NULL)
		listElement = listElement->next;

	return listElement->data; //Ersatt med ratt returvarde
}
