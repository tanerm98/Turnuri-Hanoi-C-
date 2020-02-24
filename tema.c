/* MUSTAFA Taner - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "functii.h"

void printeaza (TLista q, FILE*out)  //afiseaza turnurile HANOI
{
	TLista stivaux = NULL, temp = NULL;

	while (q != NULL) {
		temp = Pop (&q);
		Push (&stivaux, temp);	
	}

	while (stivaux->urm != NULL) {
		temp = Pop (&stivaux);
		fprintf (out, " %d", ((TDisc)(temp->info))->dim);
		Push (&q, temp);
	}

	temp = Pop (&stivaux);
	fprintf (out, " %d\n", ((TDisc)(temp->info))->dim);
	Push (&q, temp);
}

void afisare (TLista SISTEME, FILE*out, char culoare[10]) { //afiseaza un sistem
	TLista p = SISTEME, q, r;
	char nume[30];
	int ok = 0;

	while (p!=NULL) {
		if ( !strcmp(culoare, ((PSistem)(p->info))->culoare) ) {

			strcpy (nume, "A_");
			strcat (nume, ((PSistem)(p->info))->culoare);
			fprintf (out, "%s:", nume);
			q = ((PSistem)(p->info))->A;
			if (((TDisc)(q->info))->dim != 0) {
				printeaza (q, out);
			} else {
				fprintf(out, "\n");
			}
			

			strcpy (nume, "B_");
			strcat (nume, ((PSistem)(p->info))->culoare);
			fprintf (out, "%s:", nume);
			q = ((PSistem)(p->info))->B;
			if (((TDisc)(q->info))->dim != 0) {
				printeaza (q, out);
			} else {
				fprintf(out, "\n");
			}

			strcpy (nume, "C_");
			strcat (nume, ((PSistem)(p->info))->culoare);
			fprintf (out, "%s:", nume);
			q = ((PSistem)(p->info))->C;
			if (((TDisc)(q->info))->dim != 0) {
				printeaza (q, out);
			} else {
				fprintf(out, "\n");
			}

			return;
		} else {
			p = p->urm;
		}
	}
	
	//daca se cere afisare fara sa se fi facut un add pt o anumita culoare:
	strcpy (nume, "A_");
	strcat (nume, culoare);
	fprintf (out, "%s:\n", nume);
	strcpy (nume, "B_");
	strcat (nume, culoare);
	fprintf (out, "%s:\n", nume);
	strcpy (nume, "C_");
	strcat (nume, culoare);
	fprintf (out, "%s:\n", nume);
}

void eliberare (TLista *sisteme)
{//se elibereaza toata memoria
	TLista p, q, r, s;
	p = (*sisteme);
	while (p != NULL) {
		q = p;
		p = p->urm;
		//se elibereaza turnurile fiecarui sistem
		r = ((PSistem)(q->info))->A;
		while (r != NULL) {
			s = r;
			r = r->urm;
			free (s->info);
			free (s);
		}
	
		r = ((PSistem)(q->info))->B;
		while (r != NULL) {
			s = r;
			r = r->urm;
			free (s->info);
			free (s);
		}

		r = ((PSistem)(q->info))->C;
		while (r != NULL) {
			s = r;
			r = r->urm;
			free (s->info);
			free (s);
		}
		//se elibereaza coada cu simularile
		if (((PSistem)(q->info))->sim != NULL) {
			r =  ((PSistem)(q->info))->sim->fata;
			while (r != NULL) {
				s = r;
				r = r->urm;
				free (s->info);
				free (s);
			}
		}
		//se elibereaza tot sistemul
		free (((PSistem)(q->info))->sim);
		free (q->info);
		free (q);
	}
}

void add (TLista *SISTEME, char culoare[30], int diam, FILE*out) //adauga disc
{
	TLista p = (*SISTEME), sis = NULL;

	//creeam un disc nou
	TDisc disc = (TDisc) malloc (sizeof(Disc));
	disc->dim = diam;
	disc->C = 'A';

	TLista DiscNou = AlocCelula();
	if (!DiscNou) {
		printf ("Eroare de alocare!\n");
		eliberare (SISTEME);	
		return;
	}
	DiscNou->info = disc;

	//cautam sistemul de culoarea ceruta
	while ((p != NULL) && (p->info != NULL)) {
		if ( !strcmp( ((PSistem)(p->info))->culoare, culoare ) ) {
			sis = p;
			break;
		} else {
			p = p->urm;
		}
	}

	if (sis == NULL) {
		//daca nu exista, il creeam
		PSistem hanoi = (PSistem) malloc (sizeof(TSistem));
		if (!hanoi) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		hanoi->sim = NULL;
		strcpy (hanoi->culoare, culoare);
		hanoi->A = hanoi->B = hanoi->C = NULL;

		AdaugaDisc (&(hanoi->A), DiscNou);
		
		//un turn gol are un disc de dimensiune 0 
		//(pentru a retine daca este turnul A, B sau C)
		disc = (TDisc) malloc (sizeof(Disc));
		if (!disc) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		disc->dim = 0;
		disc->C = 'B';
		DiscNou = AlocCelula();
		if (!DiscNou) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		DiscNou->info = disc;
		AdaugaDisc (&(hanoi->B), DiscNou);

		disc = (TDisc) malloc (sizeof(Disc));
		if (!disc) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		disc->dim = 0;
		disc->C = 'C';
		DiscNou = AlocCelula();
		if (!DiscNou) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		DiscNou->info = disc;
		AdaugaDisc (&(hanoi->C), DiscNou);
		

		TLista SisNou = AlocCelula();
		if (!SisNou) {
			printf ("Eroare de alocare!\n");
			eliberare (SISTEME);	
			return;
		}
		SisNou->info = hanoi;

		AdaugaInLista (SISTEME, SisNou);

	} else {
		//daca exista, adaugam ordonat
		AdaugaDisc (&((PSistem)(sis->info))->A, DiscNou);
	}
}

void Simulare (TCoa *sim, int n, TLista *A, TLista *B, TLista *C) {
	//creeaza coada in care se memoreaza simularea mutarilor
	if (n == 1) {
		TLista nou = AlocCelula();
		TMutare trans = (TMutare) malloc (sizeof(Mutare));

		trans->sursa = ((TDisc)((*A)->info))->C;
		trans->destinatie = ((TDisc)((*C)->info))->C;
		
		nou->info = trans;
		InsQ (sim, nou);	
	} else {
		Simulare (sim, n-1, A, C, B);
		Simulare (sim, 1, A, B, C);
		Simulare (sim, n-1, B, A, C);
	}
}

TLista play (TLista *SISTEME, char culoare[10], FILE*out) {
//apeleaza SIMULARE pentru sistemul cerut si returneaza pointer la sistem
	TLista p = (*SISTEME), r;

	while (p!=NULL) {
		r = p->urm;
		if ( !strcmp( ((PSistem)(p->info))->culoare, culoare) ) {
			if ( ((PSistem)(p->info))->sim != NULL ) {
				//verifica daca exista deja o simulare
				return p;
			} else { //initializeaza coada pt simulare
				((PSistem)(p->info))->sim = (TCoa) malloc (sizeof(Coada));
				if (!((PSistem)(p->info))->sim) {
					printf ("Eroare de alocare!\n");
					eliberare (SISTEME);	
					return NULL;
				}

				((PSistem)(p->info))->sim->fata = ((PSistem)(p->info))->sim->spate = NULL;

				int nr = numarElementeStiva ( ((PSistem)(p->info))->A );

				Simulare ( &((PSistem)(p->info))->sim, nr, 
				&((PSistem)(p->info))->A, &((PSistem)(p->info))->B,
				&((PSistem)(p->info))->C);
			}
			break;
		}
		p = r;
	}

	return p;
}

void Transporta (TLista *p, char sursa, char destinatie) {
	TLista *S, *D, temp1;

	//identifica care disc este sursa si care e destinatia dintre A, B si C
	if (sursa == 'A') {
		S = &((PSistem)((*p)->info))->A;
	}
	if (sursa == 'B') {
		S = &((PSistem)((*p)->info))->B;
	}
	if (sursa == 'C') {
		S = &((PSistem)((*p)->info))->C;
	}

	if (destinatie == 'A') {
		D = &((PSistem)((*p)->info))->A;
	}
	if (destinatie == 'B') {
		D = &((PSistem)((*p)->info))->B;
	}
	if (destinatie == 'C') {
		D = &((PSistem)((*p)->info))->C;
	}
	
	temp1 = Pop(S);
		if ((*S) == NULL) {
		//daca s-a scos si ultimul element din turn, trebuie introdus
		//un disc de dimensiune 0, care memoreaza ce turn este (A,B,C)
			TDisc disc = (TDisc) malloc (sizeof(Disc));
			if (!disc) {
				printf ("Eroare de alocare!\n");	
				return;
			}
			disc->dim = 0;
			disc->C = ((TDisc)(temp1->info))->C;
			TLista DiscNou = AlocCelula();
			if (!DiscNou) {
				printf ("Eroare de alocare!\n");	
				return;
			}
			DiscNou->info = disc;
			AdaugaDisc (S, DiscNou);
		}

		if (((TDisc)((*D)->info))->dim == 0) {
		//daca exista doar discul de diametru 0, i se modifica diametrul
			((TDisc)((*D)->info))->dim = ((TDisc)(temp1->info))->dim;

			free (temp1->info);
			free (temp1);
		} else {
			((TDisc)(temp1->info))->C = ((TDisc)((*D)->info))->C;
			Push (D, temp1);
		}
	
}

void arataCoada (TCoa r, int x, FILE*out) {
//muta o coada in alta, pentru a o afisa, apoi o muta inapoi
	TLista temp;
	int i;

	TCoa coadaux = (TCoa) malloc (sizeof(Coada));
	coadaux->fata = coadaux->spate = NULL;

	for (i = 0; i < x; i++) {
		if (r->fata != NULL) {
			temp = ExtrQ (&r);
			fprintf (out, " %c->%c", 
			((TMutare)(temp->info))->sursa, 
			((TMutare)(temp->info))->destinatie);
			InsQ (&coadaux, temp);
		}
	}
	
	while (r->fata != NULL) {
		temp = ExtrQ (&r);
		InsQ (&coadaux, temp);
	}

	while (coadaux->fata != NULL) {
		temp = ExtrQ (&coadaux);
		InsQ (&r, temp);
	}
	free (coadaux);
	
}

int main (int argc, char**argv)
{
	FILE *in = fopen (argv[1], "r");
	if (!in) {
		printf ("Eroare de deschidere fisier!\n");
		return 0;
	}
	FILE *out = fopen (argv[2], "w");
	if (!out) {
		printf ("Eroare de deschidere fisier!\n");
		return 0;
	}
	int N, i, x, j;
	char comanda[15], culoare[10], nume[15];

	TLista SISTEME = NULL, r, p, aux;
	TLista S, D, temp1;
	TCoa cod = NULL;

	//citirea comenzilor
	fscanf (in, "%d", &N);
	for (j = 1; j <= N; j++) {
		fscanf (in, "%s", comanda);

		if ( !strcmp(comanda, "add") ) {
			fscanf (in, "%s %d", culoare, &x);
			add (&SISTEME, culoare, x, out);
		}

		if ( !strcmp(comanda, "play") ) {
			fscanf (in, "%s %d", culoare, &x);
			//p = pointer la sistemul de culoare
			p = play (&SISTEME, culoare, out);
			//play creeaza si coada de cimulari
			r = ((PSistem)(p->info))->sim->fata;
			for (i = 1; i <= x; i++) {
				if (r != NULL) {
					if (((PSistem)(p->info))->sim->fata == NULL) {
						break;
					}
					r = ExtrQ( &((PSistem)(p->info))->sim );

					//se parcurge coada de simulari si se executa mutarile
					Transporta (&p, ((TMutare)(r->info))->sursa, 
					((TMutare)(r->info))->destinatie);

					//se sterg mutarile facute din coada
					free (r->info);
					free (r);

					r = ((PSistem)(p->info))->sim->fata;	
				} else {
					break;
				}
			}
		}

		if ( !strcmp(comanda, "show_moves") ) {
			fscanf (in, "%s %d", culoare, &x);
			p = play (&SISTEME, culoare, out);

			strcpy (nume, "M_");
			strcat (nume, culoare);
			fprintf (out, "%s:", nume);

			//se printeaza coada de simulari
			if (((PSistem)(p->info))->sim->fata != NULL) {
				cod = ((PSistem)(p->info))->sim;
				arataCoada (cod, x, out);
			}
			fprintf (out, "\n");
		}

		if ( !strcmp(comanda, "show") ) {
			fscanf (in, "%s", culoare);
			afisare (SISTEME, out, culoare);
		}

		
	}

	eliberare (&SISTEME);	

	fclose (in);
	fclose (out);
	return 0;
}
