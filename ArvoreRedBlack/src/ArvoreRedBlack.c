/*
 ============================================================================
 Name        : ArvoreRedBlack.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreRedBlack.h"

NO* createNO(ITEM item, int color)
{
	NO *h = (NO *) malloc(sizeof(NO));
	h -> left = h -> right = NULL;
	h->item = item;
	h -> color = RED;
	return h;
}

NO* rotateLeft(NO* h)
{
	NO *child = h -> right;
	NO *childLeft = child -> left;

	child -> left = h;
	h -> right = childLeft;

	return child;
}
NO* rotateRight(NO* h)
{
	NO *child = h -> left;
	NO *childRight = child -> right;

	child -> right = h;
	h -> left = childRight;

	return child;
}

int isRed(NO *h)
{
	if (h == NULL)
	return 0;
	return (h -> color == RED);
}

void swapColors(NO *NO1, NO *NO2)
{
	int temp = NO1 -> color;
	NO1 -> color = NO2 -> color;
	NO2 -> color = temp;
}

NO* insert(NO* h, ITEM item)
{

	if (h == NULL)
		return createNO(item, BLACK);

	if (strcmp(item.chave, h ->item.chave) < 0)
		h -> left = insert(h -> left, item);

	else if (strcmp(item.chave, h ->item.chave) > 0)
		h -> right = insert(h -> right, item);

	else
		return h;

	if (isRed(h -> right) && !isRed(h -> left))
	{
		h = rotateLeft(h);
		swapColors(h, h -> left);
	}
	if (isRed(h -> left) && isRed(h -> left -> left))
	{
		h = rotateRight(h);
		swapColors(h, h -> right);
	}
	if (isRed(h -> left) && isRed(h -> right))
	{
		h -> color = !h -> color;
		h -> left -> color = BLACK;
		h -> right -> color = BLACK;
	}

	return h;
}

void percorre(NO *NO)
{
	if (NO)
	{
		percorre(NO -> left);
		printf("Chave: %s  Valor: %lf \n", NO -> item.chave,NO -> item.valor);
		percorre(NO -> right);
	}
}
NO* fixUp(NO* h){
	if (isRed(h->right))
	h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
	h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
	colorFlip(h);
	return h;
}
NO* colorFlip(NO* x)
{
	x->color = !x->color;
	x->left->color = !x->left->color;
	x->right->color = !x->right->color;
	return x;
}
NO* moveRedLeft(NO* h)
{
	colorFlip(h);
	if (isRed(h->right->left))
	{
	h->right = rotateRight(h->right);
	h = rotateLeft(h);
	colorFlip(h);
	}
	return h;
}
NO* moveRedRight(NO* h)
{
	colorFlip(h);
	if (isRed(h->left->left))
	{
	h = rotateRight(h);
	colorFlip(h);
	}
	return h;
}
ITEM* get(NO* root,ITEM item){
	NO* x = root;
	while (x != NULL)
	{
	int cmp = strcmp(item.chave, x->item.chave);
	if (cmp == 0) return &x->item;
	else if (cmp < 0) x = x->left;
	else if (cmp > 0) x = x->right;
	}
	return NULL;
}
NO* min(NO* root){
	NO* x = root;
	while (x != NULL)
		x = x->left;
	if (x == NULL)
		return NULL;
	else
		return x;
}
NO* deleteMin(NO* h){
	if (h->left == NULL)
	return NULL;
	if (!isRed(h->left) && !isRed(h->left->left))
	h = moveRedLeft(h);
	h->left = deleteMin(h->left);
	return fixUp(h);
}
NO* delete(NO* h, ITEM item)
{
		if (strcmp(item.chave, h->item.chave) < 0)
		{
			if (!isRed(h->left) && !isRed(h->left->left))
			h = moveRedLeft(h);
			h->left = delete(h->left, item);
		}
		else
		{
			if (isRed(h->left))
				h = rotateRight(h);
			if (strcmp(item.chave, h->item.chave) == 0 && (h->right == NULL))
				return NULL;
			if (!isRed(h->right) && !isRed(h->right->left))
				h = moveRedRight(h);
			if (strcmp(item.chave, h->item.chave) == 0)
			{
				h->item = *get(h->right, min(h->right)->item);
				h->item = min(h->right)->item;
				h->right = deleteMin(h->right);
				h->right->color=BLACK;
			}
			else h->right = delete(h->right, item);
		}
	return fixUp(h);
}

int main()
{
	NO *root = NULL;
	ITEM item;

	for(;;){
				scanf("%s %lf", item.chave, &item.valor);
				if(!strcmp(item.chave, "fim"))
					break;
				root = insert(root, item);
				root -> color = BLACK;
   }

	percorre(root);

	return 0;
}
