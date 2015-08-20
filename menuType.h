/***********************************************************************
implementation file	: menu.c
Author				: Y. Cotronis
Purpose				: Type of data menu.
Revision			: <Costas Chatzopoulos -1115201300202- 28/04/2015>
***********************************************************************/

#ifndef __TSMENU__
#define __TSMENU__
#include <stdio.h>

#define readValue 1
#define changeValue 2

#define _buffSize 26

/*Struct node */

typedef struct node{
	char * name; 	// Name of category or Plate
	int category;	// 0 if Plate, 1 if category
	float price;	// Valid only if Plate
} mItemType;

void IT_InitValue(mItemType * target);
void IT_FreeValues(mItemType * target);
int IT_isPlate(mItemType * target);
void IT_SetValue(mItemType * target, mItemType source); // Lhs = Rhs
int IT_ReadValue(FILE *in, mItemType * data, int action);
int IT_PrintValue(FILE *out, mItemType * data, int depth);
#endif