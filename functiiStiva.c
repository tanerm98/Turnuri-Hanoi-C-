/* MUSTAFA Taner - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

void Push (TLista *stiva, TLista nou)
{
	if ((*stiva) == NULL) {
		(*stiva) = nou;
		(*stiva)->urm = NULL;
	} else {
		nou->urm = (*stiva);
		(*stiva) = nou;
	}
}

TLista Pop (TLista *stiva)
{
	if ((*stiva) == NULL) {
		printf ("Stiva este nula!\n");
		return NULL;
	} else {
		TLista aux = (*stiva);
		(*stiva) = (*stiva)->urm;
		return aux;
	}
}

void AdaugaDisc (TLista *stiva, TLista nou)
{
	TLista stivaux = NULL, temp = NULL;
	while ( (*stiva) != NULL ) {
		temp = Pop (stiva);
		if ( ((TDisc)(temp->info))->dim < ((TDisc)(nou->info))->dim ) {
			Push (&stivaux, temp);
		} else {
			Push (stiva, temp);
			break;
		}
	}
	if ( stivaux != NULL) {
	}
	Push (stiva, nou);
	while (stivaux != NULL) {
		temp = Pop (&stivaux);
		Push (stiva, temp);
	}
}

int numarElementeStiva (TLista S) {
	TLista stivaux = NULL, temp = NULL;
	int contor = 0;
	while ( S != NULL ) {
		temp = Pop (&S);
		contor++;
		Push (&stivaux, temp);
	}
	while ( stivaux != NULL ) {
		temp = Pop (&stivaux);
		Push (&S, temp);
	}
	return contor;
}
