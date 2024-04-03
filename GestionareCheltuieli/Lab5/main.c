/*
7. Administrator imobil

Creati o aplicatie care petmite gestiunea de cheltuieli lunare pentru apartamentele dintr - un bloc.
Fiecare cheltuiala are : numarul apartamentului, suma, tipul(apa, canal, incalzire, gaz).
Aplicatia permite :
a) Adaugarea de cheltuieli pentru un apartament
b) Modificarea unei cheltuieli existente(tipul, suma)
c) Stergere cheltuiala
d) Vizualizare lista de cheltuieli filtrat dupa o proprietate(suma, tipul, apartament)
e) Vizualizare lista de cheltuieli ordonat dupa suma sau tip(crescator / descrescator)
*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "cheltuiala.h"
#include "MyList.h"
#include "cheltuiala_service.h"

#include <stdio.h>

void testAll() {
	testCreateDestroyValidate();
	testCreateList();
	testIterateList();
	testCopyList();
	//testSetElem();
	//testdelete();
	//testswap();
	testsortare();
	test_service_full();
	testfiltrari();
	testUndo();
	test_cerinta();
}


/*
Adaugarea cheltuiala la lista de cheltuieli
MyList l = lista in care dorim sa adaugam cheltuiala
*/
void adaugareCheltuiala(Imobil* imobil) {
	printf("Numar:");
	int numar;
	scanf_s("%d", &numar);

	printf("Suma:");
	int suma;
	scanf_s("%d", &suma);

	printf("Tip:");
	char tip[20];
	scanf_s("%s", tip, 20);

	int erori = addCheltuiala(imobil, numar, suma, tip);

	if (erori != 0) {
		printf("Cheltuiala invalida.\n");
	}
	else {
		printf("Cheltuiala adaugata.\n");
	}
}

/*
Modificarea unei cheltuieli existente(tipul, suma)
MyList l = lista in care dorim sa facem modificarea
*/
void modificareCheltuiala(Imobil* imobil) {
	printf("Numar apartament de modificat:");
	int nr;
	scanf_s("%d", &nr);

	printf("Suma:");
	int sum;
	scanf_s("%d", &sum);

	printf("Tip:");
	char tip[20];
	scanf_s("%s", tip, 20);

	int erori = modificaCheltuiala(imobil, nr, sum, tip);

	if (erori != 0) {
		printf("Eroare!\n");
	}
	else {
		printf("Succes!\n");
	}
}
/*
Stergere cheltuiala pe baza unui numar dat
MyList l = lista din care dorim sa stergem o cheltuiala
*/
void stergereCheltuiala(Imobil* imobil) {
	printf("Numar:");
	int nr;
	scanf_s("%d", &nr);


	int erori = deleteCheltuiala(imobil, nr);

	if (erori != 0) {
		printf("Eroare.\n");
	}
	else {
		printf("Succes!\n");
	}
}

/*
printarea listei de cheltuieli
MyList l = lista pe care o printam
*/
void printare_lista(MyList* l) {
	for (int i = 0; i < size(l); i++) {
		Cheltuiala* c = get(l, i);
		printf("Numar: %d, Suma: %d, Tip: %s\n", c->numar, c->suma, c->tip);
	}
}


/*
Vizualizare lista de cheltuieli ordonata dupa suma sau tip, crescator sau descrescator
MyList l = lista pe care o printam ordonat
*/
/*
void printare_sortata(Imobil* imobil) {
	MyList* lista_sortata;

	printf("Sortare dupa:\n1.Suma\n2.Tip\n");
	int ce_sortam = 0;
	scanf_s("%d", &ce_sortam);

	printf("Sortare\n1.Crescatoare\n2.Descrescatoare\n");
	int tip_sortare = 0;
	scanf_s("%d", &tip_sortare);

	int erori = sortare(l, &lista_sortata, ce_sortam, tip_sortare);

	if (erori != 0) {
		printf("Eroare.\n");
	}
	else {
		printare_lista(&lista_sortata);
	}
	destroy(&lista_sortata);
}
*/

/*
Printare lista de cheltuieli
MyList l = lista pe care o printam
*/
/*
void printare_simpla(MyList* l) {
	printare_lista(l);
}
*/

/*
Vizualizare lista de cheltuieli filtrat dupa o proprietate(suma, tipul, apartament)
MyList l = lista pe care o filtram/printam
*/
void printare_filtrata(Imobil* imobil) {

	printf("Filtrare dupa:\n1.Numar\n2.Suma\n3.tip\n");
	int ce_filtram = 0;
	scanf_s("%d", &ce_filtram);

	int erori = 0;
	int numar = 0;
	int tip_filtrare = 0;
	MyList* filtrate;
	switch (ce_filtram) {
	case(3)://tip
		printf("Substring cautat: ");
		char substring[20];
		scanf_s("%s", substring, 20);
		filtrate = filtrare_tip(imobil, substring);
		break;
	case(2)://suma
		printf("1.Mai mare decat un numar\n2.Mai mic decat un numar\n: ");
		scanf_s("%d", &tip_filtrare);
		printf("Numar: ");
		scanf_s("%d", &numar);
		filtrate = filtrare_suma(imobil, tip_filtrare, numar);
		break;
	case(1)://numar
		printf("1.Mai mare decat un numar\n2.Mai mic decat un numar\n: ");
		scanf_s("%d", &tip_filtrare);
		printf("Numar: ");
		scanf_s("%d", &numar);
		filtrate = filtrare_numar(imobil, tip_filtrare, numar);
		break;
	default:
		printf("Input introdus gresit\n");
		return;
	}
	if (erori != 0) {
		printf("Eroare.\n");
	}
	else {
		printf("Lista filtrata:\n");
		printare_lista(filtrate);
		destroy(filtrate);
	}
}
/*
Printare lista sortata cu functie ca parametru (lab4)
MyList l = lista pe care o printam/sortam
*/
/*
void printare_sortata2(MyList* l) {
	MyList lista_sortata;
	printf("Sortare\n1.Crescatoare\n2.Descrescatoare\n");
	int tip_sortare = 0;
	scanf_s("%d", &tip_sortare);

	int erori = sortare2(l, &lista_sortata, tip_sortare, comparare);

	if (erori != 0) {
		printf("Eroare.\n");
	}
	else {
		printare_lista(&lista_sortata);
	}
	destroy(&lista_sortata);
}
*/



void sortBySuma(Imobil* imobil) {
	MyList* l = sortSuma(imobil);
	printare_lista(l);
	destroy(l);
}

void sortBySumaD(Imobil* imobil) {
	MyList* l = sortSumaD(imobil);
	printare_lista(l);
	destroy(l);
}

void sortByTip(Imobil* imobil) {
	MyList* l = sortTip(imobil);
	printare_lista(l);
	destroy(l);
}

void sortByTipD(Imobil* imobil) {
	MyList* l = sortTipD(imobil);
	printare_lista(l);
	destroy(l);
}

void undoMain(Imobil* imobil) {
	int succ = undo(imobil);
	if (succ)
		printf( "Undo a fost realizat.\n" );
	else
		printf( "Nu se mai poate face undo.\n" );
}

void cerinta(Imobil* imobil) {
	printf("Tip:");
	char cuv[20];
	scanf_s("%s", cuv, 20);
	int suma = cerinta_noua(imobil, cuv);
	printf("Cheltuielile totale pentru tipul ales sunt in valoare de: %d", suma);
}

void run() {
	Imobil imobil = createImobil();
	int ruleaza = 1;
	int cmd = 0;
	while (ruleaza) {
		printf("0.Exit \n"
			"1. Adaugare"  
			"\n2. Modificare"
			"\n3. Stergere"
			"\n4. Printare Filtrata"
			"\n5. Sortare suma cresc"
			"\n6. Sortare suma desc"
			"\n7. Sortare tip cresc "
			"\n8. Sortare tip desc "
			"\n9. Printare simpla"
			"\n10. Undo" 
			"\n11. Cheltuieli totale ");
		printf("\nComanda dvs este: ");
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 0:
			ruleaza = 0;
			break;
		case 1:
			adaugareCheltuiala(&imobil);
			break;
		case 2:
			modificareCheltuiala(&imobil);
			break;
		case 3:
			stergereCheltuiala(&imobil);
			break;
		case 4:
			printare_filtrata(&imobil);
			break;
		case 5:
			sortBySuma(&imobil);
			break;
		case 6:
			sortBySumaD(&imobil);
			break;
		case 7:
			sortByTip(&imobil);
			break;
		case 8:
			sortByTipD(&imobil);
			break;
		case 9:
			printare_lista(imobil.allCheltuieli);
			break;
		case 10:
			undoMain(&imobil);
			break;
		case 11:
			cerinta(&imobil);
			break;
		default:
			printf("Comanda invalida!\n");
		}
	}
	destroyImobil(&imobil);
}

int main() {
	//testAll();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}