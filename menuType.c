/***********************************************************************
implementation file	: menuType.c
Author				: <Costas Chatzopoulos -1115201300202- 28/04/2015>
Purpose				: Type of data menu.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menuType.h"

void IT_InitValue(mItemType * target){
	if (target != NULL){
		target->name = NULL;
		target->category = 1;
		target->price = 0.0;
	}
}

void IT_FreeValues(mItemType * target){
	if (target != NULL){
		if (target->name != NULL){
			free(target->name);
		}
		IT_InitValue(target);
	}
}

int IT_isPlate(mItemType * target){
	return (target->category == 0);
}

int IT_ReadValue(FILE *in, mItemType * data, int action){
	char _buffer[_buffSize];
	char anser = 'y';
	int count = 0;

	if (action == readValue){
		printf("\n--Type '1' for category or '0' for plate:");
		count += fscanf(in, "%d", &(data->category));
	}

	else if (action == changeValue){
		printf("\n--Old name of this %s is [%s], do you want to modify it? (y/n):", (data->category) ? "category" : "plate", data->name);
		do{
			count += fscanf(in, "%c", &anser);
		} while (anser != 'y' && anser != 'n');
	}

	if (anser == 'y'){
		printf("--Give name of %s (Max %d characters):", data->category ? "category" : "plate", _buffSize - 1);
		count += fscanf(in, "%s", _buffer);
		data->name = (char *)malloc(strlen(_buffer) * sizeof(char)+1);
		strcpy(data->name, _buffer);
	}

	anser = 'y';

	if (action == changeValue && data->category == 0){
		printf("\n--The old value of this plate is [%4.2f], do you want to modify it? (y/n):", data->price);
		do{
			count += fscanf(in, "%c", &anser);
		} while (anser != 'y' && anser != 'n');
	}

	if (!data->category && anser == 'y'){
		printf("--Give price of %s:", data->name);
		count += fscanf(in, "%f", &(data->price));
	}

	if (!data->category)
		printf("\n--Imported data: [%s] [%4.2f]\n", data->name, data->price);
	else
		printf("\n--Imported data: [%s]\n", data->name);

	return count;
}

void IT_SetValue(mItemType * target, mItemType source){
	char * name = target->name;
	if (name != NULL)
		free(name);
	target->name = (char *)malloc(strlen(source.name) * sizeof(char) + 1);
	strcpy(target->name, source.name);
	target->category = source.category;
	target->price = source.price;
}

int IT_PrintValue(FILE *out, mItemType * data, int depth){
	int count = 0, i;
	fprintf(out, "\n--");
	if (depth >= 0){
		for (i = 0; i < depth; i++)
			count += fprintf(out, "--");
	}
	else
		count += fprintf(out, "Deleted:");
		count += fprintf(out, "%s", (data->name != NULL) ? data->name : "Head");
	if (!data->category)
		count += fprintf(out, "  %4.2f", data->price);
	return count;
}