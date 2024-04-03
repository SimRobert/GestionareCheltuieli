#include <stdlib.h>
#include "cheltuiala_service.h"
#include "customSort.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

Imobil createImobil() {
	Imobil imobil;
	imobil.allCheltuieli = createEmpty(destroyCheltuiala);
	imobil.undoList = createEmpty(destroy);
	return imobil;
}

void destroyImobil(Imobil* imobil) {
	destroy(imobil->allCheltuieli);
	destroy(imobil->undoList);
}

int cmpSuma(Cheltuiala* c1, Cheltuiala* c2) {
	if (c1->suma == c2->suma)
		return 0;
	if (c1->suma > c2->suma)
		return 1;
	else
		return -1;
}

int cmpSumaD(Cheltuiala* c1, Cheltuiala* c2) {
	if (c1->suma == c2->suma)
		return 0;
	if (c1->suma < c2->suma)
		return 1;
	else
		return -1;
}

int cmpTip(Cheltuiala* c1, Cheltuiala* c2) {
	return strcmp(c1->tip, c2->tip);
}

int cmpTipD(Cheltuiala* c1, Cheltuiala* c2) {
	if (strcmp(c1->tip, c2->tip) > 0)
		return -1;
	if (strcmp(c1->tip, c2->tip) < 0)
		return 1;
	else
		return 0;
}

MyList* sortSuma(Imobil* imobil) {
	MyList* l = copyList(imobil->allCheltuieli, copyCheltuiala);
	sort(l, cmpSuma);
	return l;
}

MyList* sortSumaD(Imobil* imobil) {
	MyList* l = copyList(imobil->allCheltuieli, copyCheltuiala);
	sort(l, cmpSumaD);
	return l;
}

MyList* sortTip(Imobil* imobil) {
	MyList* l = copyList(imobil->allCheltuieli, copyCheltuiala);
	sort(l, cmpTip);
	return l;
}

MyList* sortTipD(Imobil* imobil) {
	MyList* l = copyList(imobil->allCheltuieli, copyCheltuiala);
	sort(l, cmpTipD);
	return l;
}


int addCheltuiala(Imobil* imobil, int numar, int suma, char* tip) {
	Cheltuiala* c = createCheltuiala(numar, suma, tip);
	int succes = valideaza(c);

	if (succes != 0) {
		destroyCheltuiala(c);
		return succes;
	}
	MyList* undo = copyList(imobil->allCheltuieli, copyCheltuiala);
	add(imobil->allCheltuieli, c);
	add(imobil->undoList, undo);
	return 0;
}
/*
int findCheltuiala(Imobil* imobil, int suma, char* tip) {
	int i = 0;
	Cheltuiala c;
	while (i < size(l)) {
		c = get(l, i);
		if ((strcmp(c.tip, tip) == 0) && (c.suma == suma)) return i;
		i++;
	}
	return -1;
}
*/

int findCheltuialaByNumber(Imobil* imobil, int numar) {
	int i = 0;
	Cheltuiala* c;
	while (i < imobil->allCheltuieli->lg) {
		c = get(imobil->allCheltuieli, i);
		if (c->numar == numar) return i;
		i++;
	}
	return -1;
}


int modificaCheltuiala(Imobil* imobil, int nr, int sum, char* tip) {
	Cheltuiala* c = createCheltuiala(nr, sum, tip);
	int validare = valideaza(c);
	if (validare == 0) {
		int index = findCheltuialaByNumber(imobil, nr);
		if (index != -1) {
			MyList* toUndo = copyList(imobil->allCheltuieli, copyCheltuiala);
			add(imobil->undoList, toUndo);

			c = setElem(imobil->allCheltuieli, index, c);
			destroyCheltuiala(c);
			return 0;
		}
	}
	destroyCheltuiala(c);
	return 1;
}

int deleteCheltuiala(Imobil* imobil, int nr) {
	int index = findCheltuialaByNumber(imobil, nr);
	Cheltuiala* c;
	if (index != -1) {
		MyList* toUndo = copyList(imobil->allCheltuieli, copyCheltuiala);
		add(imobil->undoList, toUndo);

		c = deleteC(imobil->allCheltuieli, index);
		destroyCheltuiala(c);
		return 0;
	}
	return 1;
}
/*
int sortare(MyList* l, MyList* lista_sortata, int ce_sortam, int tip_sortare) {
	if (ce_sortam > 2 || ce_sortam < 1 || tip_sortare < 1 || tip_sortare > 2) return 1;
	Cheltuiala c1, c2;
	*lista_sortata = copyList(l);
	int i, j;

	switch (ce_sortam) {

	case(1)://suma
		switch (tip_sortare) {
		case(1)://crescator
			for (i = 0; i < size(lista_sortata) - 1; i++)
				for (j = 0; j < size(lista_sortata) - 1; j++) {
					c1 = get(lista_sortata, j);
					c2 = get(lista_sortata, j + 1);
					if (c1.suma > c2.suma)
						swap(lista_sortata, j, j + 1);
				}
			break;

		case(2)://descrescator
			for (i = 0; i < size(lista_sortata) - 1; i++)
				for (j = 0; j < size(lista_sortata) - 1; j++) {
					c1 = get(lista_sortata, j);
					c2 = get(lista_sortata, j + 1);
					if (c1.suma < c2.suma)
						swap(lista_sortata, j, j + 1);
				}
			break;
		}
		break;
	case(2)://tip
		switch (tip_sortare) {
		case(1)://crescator
			for (i = 0; i < size(lista_sortata) - 1; i++)
				for (j = 0; j < size(lista_sortata) - 1; j++) {
					c1 = get(lista_sortata, j);
					c2 = get(lista_sortata, j + 1);
					if (strcmp(c1.tip, c2.tip) > 0)
						swap(lista_sortata, j, j + 1);
				}
			break;

		case(2)://descrescator
			for (i = 0; i < size(lista_sortata) - 1; i++)
				for (j = 0; j < size(lista_sortata) - 1; j++) {
					c1 = get(lista_sortata, j);
					c2 = get(lista_sortata, j + 1);
					if (strcmp(c1.tip, c2.tip) < 0)
						swap(lista_sortata, j, j + 1);
				}
			break;
		}
		break;
	}

	return 0;
}

int sortare2(MyList* l, MyList* lista_sortata, int tip_sortare, int (*f)(Cheltuiala, Cheltuiala)) {
	if (tip_sortare > 2 || tip_sortare < 1) return 1;
	*lista_sortata = copyList(l);
	Cheltuiala c1, c2;
	int i, j;
	switch (tip_sortare) {
	case(1)://crescator
		for (i = 0; i < size(lista_sortata) - 1; i++)
			for (j = 0; j < size(lista_sortata) - 1; j++) {
				c1 = get(lista_sortata, j);
				c2 = get(lista_sortata, j + 1);
				if (f(c1, c2) == 1) {
					swap(lista_sortata, j, j + 1);
				}
			}
		break;
	case(2)://descrescator
		for (i = 0; i < size(lista_sortata) - 1; i++)
			for (j = 0; j < size(lista_sortata) - 1; j++) {
				c1 = get(lista_sortata, j);
				c2 = get(lista_sortata, j + 1);
				if (f(c1, c2) == 0) {
					swap(lista_sortata, j, j + 1);
				}
			}
		break;
	}
	return 0;
}
*/



MyList* filtrare_tip(Imobil* imobil, char* substring) {
	if (strcmp(substring, "") != 0) {
		MyList* rez = createEmpty(destroyCheltuiala);
		for (int i = 0; i < imobil->allCheltuieli->lg; i++) {
			Cheltuiala* c = get(imobil->allCheltuieli, i);
			if (strstr(c->tip, substring) != NULL) {
				add(rez, createCheltuiala(c->numar, c->suma, c->tip));
			}
		}
		return rez;}
	else {
		return copyList(imobil->allCheltuieli, copyCheltuiala);
	}
}

MyList* filtrare_suma(Imobil* imobil, int tip_filtrare, int numar) {
	if (numar >= 0) {
		MyList* rez = createEmpty(destroyCheltuiala);
		switch (tip_filtrare) {
		case (1)://mai mare
			for (int i = 0; i < imobil->allCheltuieli->lg; i++) {
				Cheltuiala* c = get(imobil->allCheltuieli, i);
				if (c->suma > numar) {
					add(rez, createCheltuiala(c->numar,c->suma, c->tip));
				}
			}
			break;
		case (2)://mai mic
			for (int i = 0; i < imobil->allCheltuieli->lg; i++) {
				Cheltuiala* c = get(imobil->allCheltuieli, i);
				if (c->suma < numar) {
					add(rez, createCheltuiala(c->numar,c->suma, c->tip));
				}
			}
			break;
		}
		return rez;}
	else {
		return copyList(imobil->allCheltuieli, copyCheltuiala);
	}
}

MyList* filtrare_numar(Imobil* imobil , int tip_filtrare, int numar) {
	if (numar >= 0) {
		MyList* rez = createEmpty(destroyCheltuiala);
		switch (tip_filtrare) {
		case (1)://mai mare
			for (int i = 0; i < imobil->allCheltuieli->lg; i++) {
				Cheltuiala* c = get(imobil->allCheltuieli, i);
				if (c->numar > numar) {
					add(rez, createCheltuiala(c->numar, c->suma, c->tip));
				}
			}
			break;
		case (2)://mai mic
			for (int i = 0; i < imobil->allCheltuieli->lg; i++) {
				Cheltuiala* c = get(imobil->allCheltuieli, i);
				if (c->numar < numar) {
					add(rez, createCheltuiala(c->numar, c->suma, c->tip));
				}
			}
			break;
		}
		return rez;}
	else {
		return copyList(imobil->allCheltuieli, copyCheltuiala);
	}
}

int undo(Imobil* imobil) {
	if (size(imobil->undoList) == 0) {
		return 0;
	}
	MyList* l = deleteC(imobil->undoList, imobil->undoList->lg - 1);
	destroy(imobil->allCheltuieli);
	imobil->allCheltuieli = l;
	return 1;
}

int cerinta_noua(Imobil* imobil, char* string) {
	int s = 0;
	MyList* rez = filtrare_tip(imobil, string);
	for (int i = 0; i < size(rez); i++) {
		Cheltuiala* c = get(rez, i);
		int val = c->suma;
		s = s + val;
		//destroyCheltuiala(c);
	}
	destroy(rez);
	return s;
}

void test_service_full() {
	Imobil imobil = createImobil();
	addCheltuiala(&imobil, 1, 150, "incalzire");
	addCheltuiala(&imobil, 2, 250, "gaze");
	addCheltuiala(&imobil, 3, 323, "apa");
	addCheltuiala(&imobil, 13, 49, "canal");
	addCheltuiala(&imobil, 7, 492, "apa");

	assert(addCheltuiala(&imobil, 6, 200, "canal") == 0);
	assert(addCheltuiala(&imobil, -1, 50, "apa") != 0);

	assert(findCheltuialaByNumber(&imobil, 13) == 3);
	assert(findCheltuialaByNumber(&imobil, 20) == -1);

	assert(modificaCheltuiala(&imobil, -1, 200, "apa") != 0);
	assert(modificaCheltuiala(&imobil, 1, 1500, "incalzire") == 0);

	assert(deleteCheltuiala(&imobil, 7) == 0);
	assert(deleteCheltuiala(&imobil, 69) != 0);

	destroyImobil(&imobil);
}

void testfiltrari() {

	Imobil imobil = createImobil();

	addCheltuiala(&imobil, 1, 150, "incalzire");
	addCheltuiala(&imobil, 2, 250, "gaze");
	addCheltuiala(&imobil, 3, 323, "apa");
	addCheltuiala(&imobil, 13, 49, "canal");
	addCheltuiala(&imobil, 7, 492, "apa");

	MyList* filtrata = filtrare_tip(&imobil, "bla");
	assert(filtrata->lg == 0);

	destroy(filtrata);
	filtrata = filtrare_tip(&imobil, "");
	assert(filtrata->lg == 5);

	destroy(filtrata);
	filtrata = filtrare_tip(&imobil, "apa");
	assert(filtrata->lg == 2);

	destroy(filtrata);
	filtrata = filtrare_numar(&imobil, 1, 5);
	assert(filtrata->lg == 2);

	destroy(filtrata);
	filtrata = filtrare_numar(&imobil, 2, 5);
	assert(filtrata->lg == 3);

	destroy(filtrata);
	filtrata = filtrare_numar(&imobil, 3, 5);
	assert(filtrata->lg == 0);

	destroy(filtrata);
	filtrata = filtrare_numar(&imobil, -1, -1);
	assert(filtrata->lg == 5);

	destroy(filtrata);
	filtrata = filtrare_suma(&imobil, 1, 100);
	assert(filtrata->lg == 4);

	destroy(filtrata);
	filtrata = filtrare_suma(&imobil, 2, 100);
	assert(filtrata->lg == 1);

	destroy(filtrata);
	filtrata = filtrare_suma(&imobil, 3, 100);
	assert(filtrata->lg == 0);

	destroy(filtrata);
	filtrata = filtrare_suma(&imobil, -1, -1);
	assert(filtrata->lg == 5);

	destroy(filtrata);
	destroyImobil(&imobil);

}

void testsortare() {
	Imobil imobil = createImobil();

	addCheltuiala(&imobil, 1, 150, "incalzire");
	addCheltuiala(&imobil, 2, 150, "gaze");
	addCheltuiala(&imobil, 3, 323, "apa");
	addCheltuiala(&imobil, 13, 49, "canal");
	addCheltuiala(&imobil, 7, 492, "apa");

	MyList* sortata = sortSuma(&imobil);
	Cheltuiala* c0 = get(sortata, 0);
	Cheltuiala* c1 = get(sortata, 1);
	Cheltuiala* c2 = get(sortata, 2);
	Cheltuiala* c3 = get(sortata, 3);
	Cheltuiala* c4 = get(sortata, 4);

	assert(c0->suma == 49);
	assert(c1->suma == 150);
	assert(c2->suma == 150);
	assert(c3->suma == 323);
	assert(c4->suma == 492);

	destroy(sortata);

	sortata = sortSumaD(&imobil);
	c0 = get(sortata, 0);
	c1 = get(sortata, 1);
	c2 = get(sortata, 2);
	c3 = get(sortata, 3);
	c4 = get(sortata, 4);

	assert(c0->suma == 492);
	assert(c1->suma == 323);
	assert(c2->suma == 150);
	assert(c3->suma == 150);
	assert(c4->suma == 49);

	destroy(sortata);

	sortata = sortTip(&imobil);
	c0 = get(sortata, 0);
	c1 = get(sortata, 1);
	c2 = get(sortata, 2);
	c3 = get(sortata, 3);
	c4 = get(sortata, 4);

	assert(strcmp(c0->tip,"apa")==0);
	assert(strcmp(c1->tip, "apa") == 0);
	assert(strcmp(c2->tip, "canal") == 0);
	assert(strcmp(c3->tip, "gaze") == 0);
	assert(strcmp(c4->tip, "incalzire") == 0);

	destroy(sortata);

	sortata = sortTipD(&imobil);
	c0 = get(sortata, 0);
	c1 = get(sortata, 1);
	c2 = get(sortata, 2);
	c3 = get(sortata, 3);
	c4 = get(sortata, 4);

	assert(strcmp(c0->tip, "incalzire") == 0);
	assert(strcmp(c1->tip, "gaze") == 0);
	assert(strcmp(c2->tip, "canal") == 0);
	assert(strcmp(c3->tip, "apa") == 0);
	assert(strcmp(c4->tip, "apa") == 0);

	destroy(sortata);
	destroyImobil(&imobil);
}

void testUndo() {
	Imobil imobil = createImobil();
	addCheltuiala(&imobil, 1,250,"apa");
	modificaCheltuiala(&imobil, 1, 250, "gaz");
	deleteCheltuiala(&imobil, 1);

	undo(&imobil);
	MyList* rez = filtrare_tip(&imobil, "");
	assert(size(rez) == 1);
	Cheltuiala* c = get(rez, 0);
	assert(c->suma == 250);
	destroy(rez);

	undo(&imobil);
	rez = filtrare_tip(&imobil, "");
	assert(size(rez) == 1);
	c = get(rez, 0);
	assert(c->suma == 250);
	destroy(rez);

	undo(&imobil);
	rez = filtrare_tip(&imobil, "");
	assert(size(rez) == 0);
	destroy(rez);

	int moreUndo = undo(&imobil);
	assert(moreUndo == 0);
	destroyImobil(&imobil);
}
void test_cerinta() {
	Imobil imobil = createImobil();

	addCheltuiala(&imobil, 1, 155, "incalzire");
	addCheltuiala(&imobil, 2, 150, "gaze");
	addCheltuiala(&imobil, 3, 320, "apa");
	addCheltuiala(&imobil, 4, 490, "canal");
	addCheltuiala(&imobil, 5, 215, "apa");

	int suma = cerinta_noua(&imobil, "incalzire");
	assert(suma == 155);
	suma = cerinta_noua(&imobil, "gaze");
	assert(suma == 150);
	suma = cerinta_noua(&imobil, "apa");
	assert(suma == 535);
	suma = cerinta_noua(&imobil, "canal");
	assert(suma == 490);

	destroyImobil(&imobil);
}