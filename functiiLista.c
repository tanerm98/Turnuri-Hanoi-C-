/* MUSTAFA Taner - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

TLista AlocCelula () {
	TLista aux = (TLista) malloc (sizeof(Celula));
	if (!aux) {
		printf ("Eroare de alocare a unei celule!\n");
		return NULL;
	}
	aux->urm = NULL;
	aux->info = NULL;
	return aux;
}

void AdaugaInLista (TLista *SISTEME, TLista nou) {
	TLista p = (*SISTEME);
	if (p == NULL) {
		(*SISTEME) = nou;
		(*SISTEME)->urm = NULL;
		return;
	} else {
		while (p->urm != NULL) {
			p = p->urm;
		}
		p->urm = nou;
		nou->urm = NULL;
	}
}
