/***********************************************************************
implementation file	: menu.c
Author				: Y. Cotronis
Purpose				: Menu structure.
Revision			: <Costas Chatzopoulos -1115201300202- 28/04/2015>
Purpose				: Implementation of all functions of the menu.
***********************************************************************/

#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define _printNode 1
#define _deleteNode -1

typedef struct mNode * mNodePtr;

/*Struct mInfo, Informative node.*/

struct mInfo {
	char * name;
	mNodePtr start;
	mNodePtr current;
	mNodePtr cutToPaste;
};

/*Struct mNode, Node Data Storage menu.*/

struct mNode {
	mNodePtr up, right, down, left;
	mItemType data;
};


/***Private functions***/

int _existsMenu(mInfoPtr info){
	return (info != NULL);
}

mNodePtr _createNode(){
/*
* This function just creates a new node, initialize all fields and finally, return it.
*/
	mNodePtr node = (mNodePtr)malloc(sizeof(struct mNode));
	if (node != NULL){
		node->up = NULL;
		node->right = NULL;
		node->down = NULL;
		node->left = NULL;
		IT_InitValue(&(node->data));
		return node;
	}
	else
		return NULL;
}

mNodePtr _insertNode(mInfoPtr info, mNodePtr source){
/*
* Insert a node at the next from current in category.
* Assign the appropriate values in the pointers, info->temp = NULL; and return it
* if node are not _isHead_ and not NULL!
*/
	if (source != NULL){
		source->up = info->current->up;
		source->left = info->current;
		if (!_isLast(info->current))
			info->current->right->left = source;
		source->right = info->current->right;
		info->current->right = source;
		return source;
	}
	else
		return NULL;
}

mNodePtr _removeNode(mNodePtr target){
/*
* Warning! This function will remove any node (including Heads!) from menu list
* it's the user's responsibility to check if target is Head or not!
*
* Remove a node from current category.
* if node has parent, then the down pointer of parent will update to NULL,
* node->up = NULL, node->right = NULL, node->down: As before , node->left = NULL and return it
* if node are not _isHead_ and not NULL!
*/
	if (target != NULL){
		if (!_isHead(target))
			target->left->right = target->right;
		else
			if (_hasParrent(target))
				target->up->down = NULL;
		target->up = NULL;
		if (!_isLast(target)){
			target->right->left = target->left;
			target->right = NULL;
		}
		
		target->left = NULL;
		return target;
	}
	else
		return NULL;
}

int _freeNode(mNodePtr * target){
/*
* This function just free a node and initialize all fields.
*/
	if (*target != NULL){
		(*target)->up = NULL;
		(*target)->right = NULL;
		(*target)->down = NULL;
		(*target)->left = NULL;
		IT_FreeValues(&((*target)->data));
		free(*target);
		*target = NULL;
		return 1;
	}
	else
		return 0;
}

int _recVisitNode(mNodePtr point, int action, FILE * out){
/*
* This recursive function accesses all nodes from 
* Head (if action == _printNode) to Last,
* with priority nodes that have children (Sub-Categories).
*/
	static int depth = 0;
	if (point != NULL && (_isHead(point) || action == _deleteNode)){
		mNodePtr next = NULL;
		do{
			next = point->right;
			if (action == _printNode && !_isHead(point))
				if (!IT_PrintValue(out, &(point->data), depth))
					return 0;

			/*-Recursive call if current node have children.-*/
			if (_hasChild(point)){
				depth++;
				_recVisitNode(point->down, action, out);
				depth--;
			}
			/*-*********************************************-*/

			if (action == _deleteNode && !_isStart(point)){
				if (!_hasChild(point)){
					/*Update the parrent information for _hasChild_*/
					if (_isHead(point) && _hasParrent(point))
						point->up->down = NULL;
					IT_PrintValue(stdout, &(point->data), -1);
					point = _removeNode(point);
					_freeNode(&point);
				}
			}
		} while ((point = next) != NULL);
		return 1;
	}
	else
		return 0;
}

int _isStart(mNodePtr target){
	return (target->up == NULL && target->down == NULL && target->left == NULL);
}

int _isLast(mNodePtr node){
	return (node->right == NULL);
}

int _isHead(mNodePtr node){
	return (node->down == NULL && node->left == NULL);
}

int _hasParrent(mNodePtr node){
	return (node->up != NULL);
}

int _hasChild(mNodePtr node){
	return (node->down != NULL);
}


/***Public functions***/

void m_Import_(mInfoPtr info, FILE * in, int * code){
	if (_existsMenu(info)){
		if (in != NULL){
			char line[_maxLineChar_];
			float x = 0.0;
			while ( fgets(line, 1000, in) != NULL){

				printf("%s\n", line);
			}
			fclose(in);
		}
		else *code = _noInputFile_;
	}
	else *code = _notExistsMenu_;
}

void m_Create_(mInfoPtr * info, char * n, int * code){
	*code = 0;
	if (!_existsMenu(*info)){
		mNodePtr headNode = _createNode();
		if (headNode != NULL){
			*info = (mInfoPtr)malloc(sizeof(struct mInfo));
			if ((*info) != NULL){
				(*info)->start = headNode;
				(*info)->current = headNode;
				(*info)->cutToPaste = NULL;
				(*info)->name = (char *)malloc(strlen(n) * sizeof(char)+1);
				strcpy((*info)->name, n);
			}
			else *code = _createInfoFail_;
		}
		else *code = _createNodeFail_;
	}
	else *code = _existsMenu_;
}

void m_EmptyCat_(mInfoPtr info, int * code){
	if(_existsMenu(info)){
		*code = (_isHead(info->current) && _isLast(info->current)) ? _emptyCat_ : _notEmptyCat_;
	}
	else
		*code = _notExistsMenu_;
}

void m_InsertNode_(mInfoPtr info, mItemType * data, int * code){
	*code = 0;
	if(_existsMenu(info)){
		mNodePtr newNode = _createNode();
		if (newNode != NULL){
			mNodePtr current = _insertNode(info, newNode);
			if (current != NULL){
				info->current = current;
				IT_SetValue(&(info->current->data), *data);
				IT_FreeValues(data);
			}
			else *code = _insertNodeFail_;
		}
		else *code = _createNodeFail_;
	}
	else *code = _notExistsMenu_;
}

void m_PrintContent_(mInfoPtr info, FILE * out, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			if (! IT_PrintValue(out, &(info->current->data), 0))
				*code = _nothingForPrint_;
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_ChangeContent_(mInfoPtr info, FILE * in, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			mItemType oldData;
			IT_InitValue(&oldData);
			IT_SetValue(&oldData, info->current->data);
			if (IT_ReadValue(in, &oldData, changeValue) != 0)
				IT_SetValue(&info->current->data, oldData);
			IT_FreeValues(&oldData);
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_Next_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isLast(info->current)){
			info->current = info->current->right;
			/*
			IT_PrintValue(stdout, &(info->current->data), 0);
			*/
		}
		else *code = _isLast_;
	}
	else *code = _notExistsMenu_;
}

void m_Previous_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			info->current = info->current->left;
			/*
			IT_PrintValue(stdout, &(info->current->data), 0);
			*/
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_InsertCat_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!IT_isPlate(&(info->current->data))){
			if (!_isHead(info->current)){
				if (!_hasChild(info->current)){
					mNodePtr newNode = _createNode();
					newNode->up = info->current;
					info->current->down = newNode;
				}
				else *code = _hasChild_;
			}
			else *code = _isHead_;
		}
		else  *code = _isPlate_;
	}
	else *code = _notExistsMenu_;
}

void m_MoveUp_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (_hasParrent(info->current)){
			info->current = info->current->up;
			/*
			IT_PrintValue(stdout, &(info->current->data), 0);
			*/
		}
		else *code = _noParent_;
	}
	else *code = _notExistsMenu_;
}

void m_MoveDown_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			if (_hasChild(info->current)){
				info->current = info->current->down;
				/*
				IT_PrintValue(stdout, &(info->current->data), 0);
				*/
			}
			else
				*code = _noChild_;
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_Delete_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		mNodePtr next = info->current->right;
		if (!_isLast(info->current)) {
			mNodePtr toDel = NULL;

			/*_Delete_ Head-Last node of next:
			If next node has empty sub-category, then free next and _hasChild_ him*/
			if (_hasChild(next) && _isLast(next->down)){
				toDel = _removeNode(next->down);
				_freeNode(&toDel);
			}

			/*_Delete_ next node:*/
			if (!_hasChild(next)){
				toDel = _removeNode(next);
				_freeNode(&toDel);
			}
			else *code = _hasChild_;
		}
		else *code = _isLast_;
	}
	else *code = _notExistsMenu_;
}

void m_MoveAfter_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			if (!_isLast(info->current)){
				mNodePtr first, second, third, fourth;
				second = info->current;
				first = second->left;
				third = second->right;
				fourth = third->right;

				first->right = third;
				third->left = first;

				if (_isLast(third))
					second->right = NULL;
				else{
					second->right = fourth;
					fourth->left = second;
				}
				third->right = second;
				second->left = third;
			}
			else *code = _isLast_;
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_MovePrevious_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current)){
			if (!_isHead(info->current->left)){
				mNodePtr first, second, third;
				third = info->current;
				second = third->left;
				first = second->left;

				first->right = third;
				third->left = first;
				second->left = third;
				second->right = third->right;

				if (!_isLast(third)){
					third->right->left = second;
				}
				third->right = second;
			}
			else *code = _nextFromHead_;
		}
		else *code = _isHead_;	
	}
	else *code = _notExistsMenu_;
}

void m_Cut_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (!_isHead(info->current) ){
			if (info->cutToPaste == NULL){
				mNodePtr cut, left;
				left = info->current->left;
				cut = _removeNode(info->current);
				if (cut != NULL){
					info->cutToPaste = cut;
					info->current = left;
				}
				else *code = _lostCurrent_;
			}
			else *code = _cutReserved_;
		}
		else *code = _isHead_;
	}
	else *code = _notExistsMenu_;
}

void m_Paste_(mInfoPtr info, int * code){
	*code = 0;
	if(_existsMenu(info)){
		if (info->cutToPaste != NULL){
			mNodePtr current = _insertNode(info, info->cutToPaste);
			if (current != NULL){
				info->current = current;
				info->cutToPaste = NULL;
			}
			else  
				*code = _insertNodeFail_;
		}
		else *code = _cutFree_;
	}
	else *code = _notExistsMenu_;
}

void m_PrintCat_(mInfoPtr info, FILE * out, int * code){
	if(_existsMenu(info))
		*code = (_recVisitNode(info->current, _printNode, out)) ? 0 : _visitNodeFail_;
	else 
		*code = _notExistsMenu_;
}

void m_DeleteCat_(mInfoPtr info, int * code){
	if (_existsMenu(info)){
		mNodePtr start = info->current;
		info->current = _hasParrent(info->current) ? info->current->up : info->start;
		*code = _recVisitNode(start, _deleteNode, NULL) ? 0 : _visitNodeFail_;
	}
	else 
		*code = _notExistsMenu_;
}

void m_Destroy_(mInfoPtr * info, int * code){
	*code = 0;
	if (_existsMenu(*info)){
		*code = _recVisitNode((*info)->start, _deleteNode, NULL) ? 0 : _visitNodeFail_;
		if ((*info)->name != NULL){
			free((*info)->name);
			(*info)->name = NULL;
		}

		if ((*info)->start != NULL)
			_freeNode(&((*info)->start));

		if ((*info)->cutToPaste != NULL){
			/*-Free all sub categories nodes from cutToPaste!-*/
			*code = _recVisitNode((*info)->cutToPaste, _deleteNode, NULL) ? 0 : _visitNodeFail_;
			/*-Free cutToPaste node---------------------------*/
			_freeNode(&((*info)->cutToPaste));
			(*info)->cutToPaste = NULL;
		}

		free(*info);
		*info = NULL;
	}
	else *code = _notExistsMenu_;
}