/***********************************************************************
implementation file	: menu.h
Author				: Y. Cotronis
Purpose				: Menu structure.
Revision			: <Costas Chatzopoulos -1115201300202- 28/04/2015>
***********************************************************************/

#ifndef __MENU__
#define __MENU__

#include "menuType.h"

#define _existsMenu_ -1
#define _notExistsMenu_ -2
#define _lostCurrent_ -3
#define _createNodeFail_ -4
#define _createInfoFail_ -5
#define _isLast_ -6
#define _notIsLast_ -7
#define _isHead_ -8
#define _visitNodeFail_ -9
#define _hasChild_ -10
#define _noChild_ -11
#define _noParent_ -12
#define _nextFromHead_ -13
#define _insertNodeFail_ -14
#define _notEmptyCat_ -15
#define _emptyCat_ -16
#define _cutFree_ -17
#define _cutReserved_ -18
#define _nothingForPrint_ -19
#define _noInputFile_ -20
#define _isPlate_ -21

#define _maxLineChar_ 400

typedef struct mInfo * mInfoPtr;

void m_Import_(mInfoPtr info, FILE * in, int * code);
void m_Create_(mInfoPtr * info, char * n, int * code);
void m_EmptyCat_(mInfoPtr info, int * code);
void m_InsertNode_(mInfoPtr info, mItemType * data, int * code);
void m_PrintContent_(mInfoPtr info, FILE * out, int * code);
void m_ChangeContent_(mInfoPtr info, FILE * in, int * code);
void m_Next_(mInfoPtr info, int * code);
void m_Previous_(mInfoPtr info, int * code);
void m_InsertCat_(mInfoPtr info, int * code);
void m_MoveUp_(mInfoPtr info, int * code);
void m_MoveDown_(mInfoPtr info, int * code);
void m_Delete_(mInfoPtr info, int * code);
void m_MoveAfter_(mInfoPtr info, int * code);
void m_MovePrevious_(mInfoPtr info, int * code);
void m_Cut_(mInfoPtr info, int * code);
void m_Paste_(mInfoPtr info, int * code);
void m_PrintCat_(mInfoPtr info, FILE * out, int * code);
void m_DeleteCat_(mInfoPtr info, int * code);
void m_Destroy_(mInfoPtr * info, int * code);

#endif