#include "Queue.h"
#include<assert.h>

/*Har ar det viktigt att ateranvanda koden som du redan skrivit for den lankade listan.
  Ateranvandning betyder inte att man kopierar koden eller skriver av den, ateranvander
  gor man genom att anropa redan implementerade funktioner.*/

/*Funktionen ar fardig*/
Queue initializeQueue(void)
{
    return NULL;
}

int queueIsEmpty(const Queue queue)
{
	return isEmpty(queue);
}

/*Postcondition: data ar tillagt sist i kon*/
void enqueue(Queue* queue, const Data data)
{
   //Tips: Att lagga till i en ko implementerad som en lankad lista ar precis som att lagga till forst eller sist i en lankad lista
	addLast(queue, data);
}

/* Precondition: kon ar ej tom */
void dequeue(Queue* queue)
{
    //Tips: Att ta bort fran en ko implementerad som en lankad lista ar precis som att ta bort sist eller forst i en lankad lista.
	removeFirst(queue);
}

/* Precondition: kon ar ej tom */
Data peekQueue(const Queue queue)
{
	assert(!isEmpty(queue));
    return queue->data;
}


/* Anvands for testning och felsokning
   Tips: det kan vara bra att ocksa notera i utskriften vart borjan respektive slutet pa kon ar */
void printQueue(const Queue queue, FILE *textfile)
{
	printList(queue, textfile);
}


