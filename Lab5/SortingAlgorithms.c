#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
        case BUBBLE_SORT:
        case INSERTION_SORT:
//      case SELECTION_SORT:
        case QUICK_SORT:
//      case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}

/* Antalet byten i en och samma algoritm kan vara olika beroende pa implementationen.
   Ibland ligger datat redan pa ratt plats och da kan man valja att testa det och inte gora
   ett byte (vilket ger extra jamforelse) eller sa kan man anda gora ett byte (med sig sjalv).
   Foljer man de algoritmer som vi gatt igenom pa forelasningarna exakt sa gor man en swap
   aven pa ett element som ligger pa ratt plats
 
    Nar du analyserar det data som genereras (result.txt) sa behover du ha detta i atanke */

/******************************************************************************************/
/* Era algoritmer har: */

static void bubbleSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	for (size = size; greaterThanOrEqualTo(size, 0, statistics); size--)
		for (int i = 0; lessThan(i, size - 1, statistics); i++)
			if (lessThan(arrayToSort[i + 1], arrayToSort[i], statistics))
				swapElements(&arrayToSort[i], &arrayToSort[i + 1], statistics);
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	for (int lowIterator = 1; lessThan(lowIterator, size, statistics); lowIterator++)
		for (int highIterator = lowIterator; greaterThan(highIterator, 0, statistics) &&
			greaterThan(arrayToSort[highIterator - 1], arrayToSort[highIterator], statistics); highIterator--)
			swapElements(&arrayToSort[highIterator - 1], &arrayToSort[highIterator], statistics);
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static int quickSort_partition(ElementType* arrayToSort, int lowBound, int highBound, Statistics* statistics)
{
	int pivot = arrayToSort[lowBound];
	int lowIterator = lowBound - 1;
	int highIterator = highBound + 1;
	while (1)
	{
		do
			lowIterator += 1;
		while (lessThan(arrayToSort[lowIterator], pivot, statistics));
		do
			highIterator -= 1;
		while (greaterThan(arrayToSort[highIterator], pivot, statistics));

		if (greaterThanOrEqualTo(lowIterator, highIterator, statistics))
			return highIterator;

		swapElements(&arrayToSort[lowIterator], &arrayToSort[highIterator], statistics);
	}
}

static void quickSort_sort(ElementType* arrayToSort, int lowBound, int highBound, Statistics* statistics)
{
	if (lessThan(lowBound, highBound, statistics))
	{
		int partitionBound = quickSort_partition(arrayToSort, lowBound, highBound, statistics);
		quickSort_sort(arrayToSort, lowBound, partitionBound, statistics);
		quickSort_sort(arrayToSort, partitionBound + 1, highBound, statistics);
	}
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	quickSort_sort(arrayToSort, 0, size - 1, statistics);
}


/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet är: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
