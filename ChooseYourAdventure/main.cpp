#include <iostream>
#include "Player.h"
#include "Story.h"
#include <string>
#include <Windows.h>
#include <cstdio>

using namespace std;


/* Storyline struct, pointer next is added for loop possibilities */
typedef struct Storylines
{
	string currentLine;
	struct Storylines* optionA;
	struct Storylines* optionB;
	struct Storylines* next;

}Storylines_t;

Storylines_t* g_start;

/* If Storyline is already present, then get it, else return new StoryLine with Line */
Storylines_t* getLine(Storylines_t** headRef, string Line)
{
	Storylines_t* current = *headRef;
	while (current != NULL)
	{
		if (!current->currentLine.compare(Line))
			return current;
		current = current->next;
	}
	return NULL;
}


void push(Storylines_t** headRef, string newLine, string optionA, string optionB)
{
	/* Check if Stroyline already exists, if so, then get it */
	Storylines_t* newStoryLine = getLine(headRef, newLine);

	/* If it did not exist then create it and set the Line */
	if((newLine != "") && (newStoryLine == NULL))
	{
		Storylines_t* newStoryLine = new Storylines_t;
		newStoryLine->currentLine = newLine;
		/* link the old list off the new node */
		newStoryLine->next = (*headRef);

		if ((*headRef) == NULL)
			g_start = newStoryLine;

		/* move the head to point to the new node */
		(*headRef) = newStoryLine;

		push(headRef, optionA, "", "");
		push(headRef, optionB, "", "");

		/* If it did exist, then update options */
		if ((newLine != "") && (newStoryLine != NULL)) {
			push(headRef, optionA, "", "");
			newStoryLine->optionA = getLine(headRef, optionA);

			push(headRef, optionB, "", "");
			newStoryLine->optionB = getLine(headRef, optionB);
		} 
	}
	else if ((newLine != "") && (newStoryLine != NULL)) {
		push(headRef, optionA, "", "");
		if(newStoryLine->optionA == NULL)
			newStoryLine->optionA = getLine(headRef, optionA);

		push(headRef, optionB, "", "");
		if (newStoryLine->optionB == NULL)
			newStoryLine->optionB = getLine(headRef, optionB);
	}

	return;
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);

	/* Enable buffering to prevent VS from chopping up UTF-8 byte sequences */
    setvbuf(stdout, nullptr, _IOFBF, 1000);

	/* Start with the empty list */
	Storylines_t* head = NULL;

	//TODO parse excel or smthing
	push(&head, u8"Éhes vagy", u8"Rendelsz", u8"Főzöl");
	push(&head, u8"Rendelsz",									u8"Sokára jön meg a kaja, megvárod.",	u8"Sokára jön meg a kaja, nem várod meg.");
	push(&head, u8"Sokára jön meg a kaja, megvárod.",			u8"Éhen haltál a gecibe.",				"");
	push(&head, u8"Sokára jön meg a kaja, nem várod meg.",		u8"Éhes vagy",							"");
	push(&head, u8"Főzöl",										u8"Bonyolultat főzől.",					u8"Egyszerűt főzöl");
	push(&head, u8"Bonyolultat főzől.",							u8"Éhen haltál a gecibe.",				"");
	push(&head, u8"Egyszerűt főzöl",							u8"Jóllaktál :)",						"");

	Storylines_t* head_local = g_start;

	cout << u8"Gépelj egyest az első opció választásához. Kettest a másodikéhoz." << endl << endl;

	while (1) {
		cout << head_local->currentLine << endl << endl;

		if ((head_local->optionA == NULL) && (head_local->optionB == NULL))
		{
			cout << u8"Vége a játéknak" << endl;
			break;
		}


		/* option A always exists */
		if (head_local->optionB != NULL)
		{
			cout << "1: " << head_local->optionA->currentLine << endl;
			cout << "2: " << head_local->optionB->currentLine << endl;
			cout << "--------------------------------------------" << endl;
		}
		else
		{
			head_local = head_local->optionA;
			continue;
		}

		int answer;
		cin >> answer;
		if (answer == 1)
			head_local = head_local->optionA;
		else if (answer == 2)
			head_local = head_local->optionB;
	}
}