/* MUSTAFA Taner - 315CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

TLista AlocCelula (); //aloca un element de tip lista generica
void AdaugaInLista (TLista *p, TLista nou); //adauga element nou intr-o lista

void Push (TLista *stiva, TLista nou); //introduce un element in stiva
TLista Pop (TLista *stiva); //scoate un element din stiva si-l returneaza
void AdaugaDisc (TLista *stiva, TLista nou); //adauga ordonat un element in stiva
int numarElementeStiva (TLista S); //returneaza numarul de elemente din stiva

void InsQ (TCoa *coada, TLista nou); //insereaza un element in coada
TLista ExtrQ (TCoa *coada); //scoate un element din coada

void Muta (int n, TLista *A, TLista *B, TLista *C); //functie recursiva
