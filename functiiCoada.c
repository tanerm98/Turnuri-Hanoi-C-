/* MUSTAFA Taner - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

void InsQ (TCoa *coada, TLista nou)
{
	if ( (*coada)->fata == NULL) {
		(*coada)->fata = (*coada)->spate = nou;
		(*coada)->spate->urm = NULL;
	} else {
		(*coada)->spate->urm = nou;
		(*coada)->spate = (*coada)->spate->urm;
	}
}

TLista ExtrQ (TCoa *coada)
{
	TLista temp;
	if ( (*coada)->fata == (*coada)->spate ) {
		temp = (*coada)->fata;
		(*coada)->fata = (*coada)->spate = NULL;
	} else {
		temp = (*coada)->fata;
		(*coada)->fata = (*coada)->fata->urm;
	}
	return temp;
}
