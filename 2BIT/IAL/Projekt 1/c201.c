// Lukas Pelanek
// xpelan03

/* c201.c *********************************************************************}
{* T�ma: Jednosm�rn� line�rn� seznam
**
**                     N�vrh a referen�n� implementace: Petr P�ikryl, ��jen 1994
**                                          �pravy: Andrea N�mcov� listopad 1996
**                                                   Petr P�ikryl, listopad 1997
**                                P�epracovan� zad�n�: Petr P�ikryl, b�ezen 1998
**                                  P�epis do jazyka C: Martin Tu�ek, ��jen 2004
**	                                      �pravy: Bohuslav K�ena, ��jen 2014
**
** Implementujte abstraktn� datov� typ jednosm�rn� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je cel� ��slo typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou typu tList.
** Definici konstant a typ� naleznete v hlavi�kov�m souboru c201.h.
** 
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu s v��e
** uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ tList:
**
**      InitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DisposeList ... zru�en� v�ech prvk� seznamu,
**      InsertFirst ... vlo�en� prvku na za��tek seznamu,
**      First ......... nastaven� aktivity na prvn� prvek,
**      CopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DeleteFirst ... zru�� prvn� prvek seznamu,
**      PostDelete .... ru�� prvek za aktivn�m prvkem,
**      PostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      Copy .......... vrac� hodnotu aktivn�ho prvku,
**      Actualize ..... p�ep��e obsah aktivn�ho prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal�� prvek seznamu,
**      Active ........ zji��uje aktivitu seznamu.
**
** P�i implementaci funkc� nevolejte ��dnou z funkc� implementovan�ch v r�mci
** tohoto p��kladu, nen�-li u dan� funkce explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* glob�ln� prom�nn� -- p��znak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/

	L->First = NULL;				//inicializace
	L->Act = NULL;

}

void DisposeList (tList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam L do stavu, v jak�m se nach�zel
** po inicializaci. Ve�ker� pam� pou��van� prvky seznamu L bude korektn�
** uvoln�na vol�n�m operace free.
***/

	L->Act = NULL;
	tElemPtr tmp = NULL;

	while (L->First != NULL){					// cyklus probiha dokud neni seznam prazdny
		tmp = L->First->ptr;					// do pomocne promenne nahraji druhy prvek
												// pokud existuje prvni prvek, tak ho zrusim
		free(L->First);
		L->First = tmp;							// uvolnim prvni prvek a na jeho pozici ulozim prvek druhy
	}
	
}

void InsertFirst (tList *L, int val) {
/*
** Vlo�� prvek s hodnotou val na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci Error().
**/
 
	tElemPtr first;

	if ((first = (tElemPtr) malloc(sizeof(struct tElem))) == NULL){
		Error();					// Pokud se nepovedlo alokovat pamet, vytiskneme chybove hlaseni
		return;
	}

	first->data = val;				//vlozeni prvku na prvni misto
	first->ptr = L->First;		

	L->First = first;
 
}

void First (tList *L) {
/*
** Nastav� aktivitu seznamu L na jeho prvn� prvek.
** Funkci implementujte jako jedin� p��kaz, ani� byste testovali,
** zda je seznam L pr�zdn�.
**/

	L->Act = L->First;					// prvni prvek se stava aktivnim

}

void CopyFirst (tList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci Error().
**/
	if (L->First == NULL){
		Error();
		return;
	}
	*val = L->First->data;			// pokud neni seznam prazdny, vratime hodnotu prvniho prvku seznamu
}

void DeleteFirst (tList *L) {
/*
** Zru�� prvn� prvek seznamu L a uvoln� j�m pou��vanou pam�.
** Pokud byl ru�en� prvek aktivn�, aktivita seznamu se ztr�c�.
** Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
	tElemPtr tmp = NULL;

	if (L->First == NULL){				//pokud je seznam prazdny nic se nedeje
		return;
	}

	if (L->First == L->Act){			// pokud je prvni prvek zaroven aktivni, ztraci se aktivita seznamu
		L->Act = NULL;
	}

	tmp = L->First;	
	L->First = L->First->ptr;			// smazani prvniho prvku
	free(tmp);


}	

void PostDelete (tList *L) {
/* 
** Zru�� prvek seznamu L za aktivn�m prvkem a uvoln� j�m pou��vanou pam�.
** Pokud nen� seznam L aktivn� nebo pokud je aktivn� posledn� prvek seznamu L,
** nic se ned�je.
**/
	if ((L->Act == NULL) || (L->Act->ptr == NULL)){
		return;
	}
	tElemPtr temp = L->Act->ptr;			// Do pomocne promenne nahraji dalsi prvek na seznamu
	L->Act->ptr = temp->ptr;				// Do naslednika ulozim odkaz na na naslednika nasledovnika

	free(temp);								// Uvolnim nasledovnika

}

void PostInsert (tList *L, int val) {
/*
** Vlo�� prvek s hodnotou val za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je!
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** zavol� funkci Error().
**/

	if (L->Act == NULL){
		return;							// Pokud neni seznam aktivni nic nedelam
	}
	tElemPtr tmp;

	if ((tmp = (tElemPtr) malloc(sizeof(struct tElem))) == NULL){
		Error();									// Alokace pameti pro dalsi prvek
		return;
	}
	tmp->data = val;
	tmp->ptr = L->Act->ptr;							// Prvek ukazuje na naslednika aktualniho prvku

	L->Act->ptr = tmp;								// Tento prvek se stava naslednikem 

}

void Copy (tList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam nen� aktivn�, zavol� funkci Error().
**/
	
	if (L->Act == NULL){
		Error();
		return;
	}

	*val = L->Act->data;				// Pokud je seznam aktivni, zkopirujeme hodnotu prvku
}

void Actualize (tList *L, int val) {
/*
** P�ep��e data aktivn�ho prvku seznamu L hodnotou val.
** Pokud seznam L nen� aktivn�, ned�l� nic!
**/
	
	if (L->Act == NULL){
		return;
	}

	L->Act->data = val;					// pokud je seznam aktivni, aktualizujeme hodnotu aktivniho prvku
}

void Succ (tList *L) {
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** V�imn�te si, �e touto operac� se m��e aktivn� seznam st�t neaktivn�m.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/

	if (L->Act == NULL){
		return;
	}

	L->Act = L->Act->ptr;

}

int Active (tList *L) {		
/*
** Je-li seznam L aktivn�, vrac� TRUE. V opa�n�m p��pad� vrac� FALSE.
** Tuto funkci implementujte jako jedin� p��kaz return. 
**/
	return L->Act != NULL;
}

/* Konec c201.c */
