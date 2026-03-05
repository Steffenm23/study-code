/*  Lab 7 Section 2
* Steffen Müller
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node
{
	double value;
	struct Node* next;

} Node;

Node* createNode(double value)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL)
	{
		printf("Memory allocation failed\n");
	}

	newNode->value = value;              // Speichert den Wert
	newNode->next = NULL;                 // setzt Nächsten Pointer auf NULL
	return newNode;


}

void printList(Node *head)
{
	Node* current = head;
	int index = 0;

	while (current != NULL) {             // Durchlaufen der Liste 
		printf(" Element der Liste an [%d]	", index);
		current = current->next;
		index++;
	}
}

int main()
{
	srand(time(NULL));
	Node* head = NULL;
	Node* temp;

	int arr[51];
	int randomNumber = rand() % 2;

	for (int i = 0; i < 50; i++) {      // Array mit 50 Zufallszahlen
		arr[i] = rand() % 100;
	}
	for (int i = 50; i > 3; i--) {       // Array um 3 verschieben
			arr[i] = arr[i - 1];
	}
	arr[3] = randomNumber;                 // am Index 3 neue Zahl einfügen

	Node* newNode = createNode((double)randomNumber);
	temp = head;
	for (int i = 0; i < 2, i++;) {
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;

	printf("Array:\n");             // Array wird ausgegeben
	for (int i = 0; i < 51, i++;) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}
	free(newNode);
	return 0;
}