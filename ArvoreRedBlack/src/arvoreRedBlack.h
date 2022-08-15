/*
 * arvoreRedBlack.h
 *
 *  Created on: 2 de jun. de 2022
 *      Author: 1a226866863
 */

#ifndef ARVOREREDBLACK_H_
#define ARVOREREDBLACK_H_
#define RED 1
#define BLACK 0


typedef char CHAVE [21];

typedef struct {
	CHAVE chave;
	int retirado;
	double valor;
}ITEM;

typedef struct NO_TAG *PONT;

typedef struct NO_TAG{
	ITEM item;
	PONT left, right;
	int color;
}NO;

typedef PONT ARVORE;


NO* rotateLeft(NO*);
NO* rotateRight(NO*);
void swapColors(NO*, NO*);
NO* insert(NO*, ITEM);
void percorre(NO*);
int isRed(NO*);
NO* delete(NO*,ITEM);
NO* moveRedLeft(NO*);
NO* moveRedRight(NO*);
NO* colorFlip(NO*);
NO* min(NO*);
ITEM* get(NO*,ITEM);
NO* deleteMin(NO*);


#endif /* ARVOREREDBLACK_H_ */
