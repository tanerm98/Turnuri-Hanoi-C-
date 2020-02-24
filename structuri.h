/* MUSTAFA Taner - 315CB */

//reprezinta un disc
//memoreaza diametru si turnul pe care este momentan (A, B sau C)
typedef struct disc
{
	int dim;
	char C;
} Disc, *TDisc;

//reprezinta un element din coada de simulare a mutarilor
//memoreaza turnul sursa si cel destinatie
typedef struct mutari
{
	char sursa;
	char destinatie;
} Mutare, *TMutare;

//lista generica simplu inlantuita
typedef struct lista
{
	void *info;
	struct lista *urm;
} Celula, *TLista;

//reprezinta o coada
//memoreaza inceputul si sfarsitul cozii
typedef struct coada
{
	TLista fata, spate;
} Coada, *TCoa;

//reprezinta un sistem Hanoi
//memoreaza turnurile A, B, C
//memoreaza culoarea sistemului
//memoreaza coada cu simularile de mutari
typedef struct sistem
{
	char culoare[10];
	TLista A, B, C;
	TCoa sim;
} TSistem, *PSistem;


