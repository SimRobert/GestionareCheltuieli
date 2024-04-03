#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "MyList.h"

typedef struct {
	MyList* allCheltuieli;
	MyList* undoList;
}Imobil;

/*
* Creaza o entitate de tip Imobil care contine o
* lista de cheltuieli si una pentru undo
*/
Imobil createImobil();

/*
* Elibereaza memoria alocata pentru un Imobil
*/
void destroyImobil(Imobil* imobil);

/*
Compara numarul a doua cheltuieli si returneaza:
1 daca numarul primei cheltuieli e mai mare
0 daca numarul cheltuielii2 e mai mare

Cheltuiala c1 = cheltuiala 1
Cheltuiala c2 = cheltuiala 2
*/
//int comparare(Cheltuiala c1, Cheltuiala c2);

/*
sortare prin functie de comparare ca parametru (lab4)
MyList l = lista pe care o sortam
MyList lista_sortata = lista in care punem lista sortata
int tip_sortare = 1-crescator   2-descrescator
(*f) = functie de comparare
return int  = 1 daca tip_sortare>2 sau <1
			= 0 totu' ok
*/
//int sortare2(MyList* l, MyList* lista_sortata, int tip_sortare, int (*f)(Cheltuiala, Cheltuiala));

/*
adaugarea unei cheltuieli in lista de cheltuieli
MyList l = lista in care adaugam cheltuiala
int numar = numarul cheltuielii pe care dorim sa o adaugam
int suma = suma cheltuielii pe care dorim sa o adaugam
char tip = tipul cheltuielii pe care dorim sa o adaugam
return int  = 0, totu' ok
		   != 0, eroare la validarea cheltuielii
*/
int addCheltuiala(Imobil* imobil, int numar, int suma, char* tip);

/*
gasirea unei cheltuieli care are o suma si un tip dat intr-o lista
MyList l = lista in care cautam
suma = suma cheltuielii cautate
tip = tipul cheltuielii cautate
return: pozitia cheltuielii respective  sau -1 daca nu se afla in lista
*/
//int findCheltuiala(Imobil* imobil, int suma, char* tip);

/*
gasirea unei cheltuieli care are un numar dat
MyList l = lista in care cautam
numar = numarul cheltuielii cautate
return: pozitia cheltuielii respective  sau -1 daca nu se afla in lista
*/
int findCheltuialaByNumber(Imobil* imobil, int numar);

/*
modifica suma si tipul unei cheltuieli care are un numar dat si se afla in lista
MyList l = lista in care se face modificarea
nr = numarul cheltuielii pe care dorim sa o modificam
sum = suma noua a cheltuielii
tip =tipul nou al cheltuielii
return int = 0, totu' ok
		   = 1, eroare la validare cheltuiala
*/
int modificaCheltuiala(Imobil* imobil, int nr, int sum, char* tip);

/*
stergerea unei cheltuieli pe baza pozitiei acesteia in lista
MyList l = lista din care stergem o cheltuiala
nr = indexul cheltuielii pe care o stergem
return int = 0, totu' ok
		   = 1, nu exista cheltuiala pe indexul dat
*/
int deleteCheltuiala(Imobil* imobil, int nr);

/*
sortearea listei de cheltuieli pe baza sumei sau a numarului, crescator sau descrescator
MyList l = lista pe care dorim o sortam
MyList lista_sortata = lista sortata
ce_sortam = 1 sortare dupa suma    2 sortare dupa tip
tip_sortare = 1 crescator    2 descrescator
return int = 1, ce_sortam >2 sau <1 || tip_sortare <1 sau >2
		   = 0, totu' ok
*/
//int sortare(MyList* l, MyList* lista_sortata, int ce_sortam, int tip_sortare);

/*
returneaza o lista care contine cheltuielile unei liste, care au un substring in tip-ul acestora
MyList l = lista din care luam cheltuielile
substring = substringul cautat in tipul cheltuielilor din lista
return MyList = lista cu elementele filtrate
*/
MyList* filtrare_tip(Imobil* imobil, char* substring);

/*
returneaza o lista care contine cheltuielile unei liste, care au suma mai mica/mare decat o suma data
MyList = lista din care luam cheltuielile
tip_filtrare =  1 sumele cheltuielilor trebuie sa fie mai mari decat numarul dat
				2 sumele cheltuielilor trebuie sa fie mai mici decat numarul dat
numar = suma data                                                        ^
return MyList = lista cu elementele filtrate
*/
MyList* filtrare_suma(Imobil* imobil, int tip_filtrare, int numar);

/*
returneaza o lista care contine cheltuielile unei liste, care au numarul mai mic/mare decat un numar dat
MyList = lista din care luam cheltuielile
tip_filtrare =  1 numerele cheltuielilor trebuie sa fie mai mari decat numarul dat
				2 numerele cheltuielilor trebuie sa fie mai mici decat numarul dat
numar = numarul dat                                                        ^
return MyList = lista cu elementele filtrate
*/
MyList* filtrare_numar(Imobil* imobil, int tip_filtrare, int numar);

/*
* Returneaza o lista sortata de cheltuieli
* Criteriu de sortare: suma (crescator)
*
* @param imobil: Imobil cu medicamentele care se sorteaza (Imobil*)
*
* @return: o lista sortata de cheltuieli  (MyList*)
*/

MyList* sortSuma(Imobil* imobil);

/*
* Returneaza o lista sortata de cheltuieli
* Criteriu de sortare: tip (crescator)
*
* @param imobil: Imobil cu cheltuielile care se sorteaza (Imobil*)
*
* @return: o lista sortata de cheltuieli  (MyList*)
*/


MyList* sortTip(Imobil* imobil);

/*
* Returneaza o lista sortata de cheltuieli
* Criteriu de sortare: suma (descrescator)
*
* @param imobil: Imobil cu medicamentele care se sorteaza (Imobil*)
*
* @return: o lista sortata de cheltuieli  (MyList*)
*/

MyList* sortSumaD(Imobil* imobil);

/*
* Returneaza o lista sortata de cheltuieli
* Criteriu de sortare: tip (descrescator)
*
* @param imobil: Imobil cu cheltuielile care se sorteaza (Imobil*)
*
* @return: o lista sortata de cheltuieli  (MyList*)
*/

MyList* sortTipD(Imobil* imobil);

/*
* Reface ultima operatie
*
* @return: 1 daca undo-ul a fost realizat, 0 altfel (int)
* post: lista de cheltuieli este cea aferenta efectuarii ultimei operatii care a modificat-o
*/

int undo(Imobil* imobil);

int cerinta_noua(Imobil* imobil, char* string);

void test_service_full();
void testsortare();
void testfiltrari();
void testUndo();
void test_cerinta();