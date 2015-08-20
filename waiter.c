/***********************************************************************
implementation file	: waiter.c
Author				: <Costas Chatzopoulos -1115201300202- 28/04/2015>
Purpose				: Client interface from menu.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "menuType.h"

#define _PrintOptions_ 0
#define _Create_ 1
#define _EmptyCat_ 2
#define _InsertNode_ 3
#define _PrintContent_ 4
#define _ChangeContent_ 5
#define _Next_ 6
#define _Previous_ 7
#define _InsertCat_ 10
#define _Up_ 11
#define _Down_ 12
#define _Delete_ 14
#define _MoveAfter_ 8
#define _MovePrevious_ 9
#define _Cut_ 16
#define _Paste_ 17
#define _PrintCat_ 13
#define _DeleteCat_ 15
#define _Destroy_ 18
#define _Import_ 19
#define _FailInput_ 20

void print_options(void);

int main(int argc, char *argv[]){
	int code = 0;
	int option;
	char _buffer[31];
	mInfoPtr food = NULL, cafe = NULL, menu = NULL;

	mItemType data;
	IT_InitValue(&data);
		
	print_options();
	do{
		printf("________________________________________________\n");
		printf("Give your choice (0-18 or any other key to exit)|:");
		if (scanf("%d", &option) != 1)
			option = _FailInput_;
		switch (option){
			case _Create_:
				if (menu == NULL){
					printf("-Give name of Restaurant (Max 30 characters):");
					if (scanf("%s", _buffer) == 1){
						m_Create_(&menu, _buffer, &code);
						if (code == _existsMenu_)
							printf("\n-Fail: The menu already exists!\n");
						else if (code == _createNodeFail_)
							printf("\n-Fail: Memory error, _createNodeFail_.\n");
						else if (code == _createInfoFail_)
							printf("\n-Fail: Memory error, _createInfoFail_.\n");
						else
							printf("\n-Success: The Menu '%s' was created\n", _buffer);
					}
					else
						printf("\n-Fail: The name is not given correctly, try again.\n");
				}
				else
					printf("\n-Fail: The menu already exists!\n");
				break;
			case _EmptyCat_:
				m_EmptyCat_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _emptyCat_)
					printf("\n-Success: The current category is empty..\n");
				else if (code == _notEmptyCat_)
					printf("\n-Success: The current category is not empty..\n");
				break;
			case _InsertNode_:
				if (menu != NULL){
					if (IT_ReadValue(stdin, &data, readValue) >= 2){
						m_InsertNode_(menu, &data, &code);
						if (code == _notExistsMenu_)
							printf("\n-Fail: To complete this action, you must create the menu!\n");
						else if (code == _createNodeFail_)
							printf("\n-Fail: Cannot create node\n");
						else if (code == _insertNodeFail_)
							printf("\n-Fail: The insertion of the node was failed!\n");
						else
							printf("\n-Success: The new node has imported..\n");
					}
					else
						printf("\n-Fail: Data input was not successful!\n");
				}
				else
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				break;
			case _PrintContent_:
				m_PrintContent_(menu, stdout, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: Cannot print Head nodes!\n");
				else if (code == _nothingForPrint_)
					printf("\n-Fail: No printing!\n");
				else
					printf("\n\n-Success: Print successfully complete.\n");
				break;
			case _ChangeContent_:
				m_ChangeContent_(menu, stdin, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: Cannot change data of Head nodes!\n");
				else
					printf("\n-Success: Change successfully complete.\n");
				break;
			case _Next_:
				m_Next_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isLast_)
					printf("\n-Fail: The current node is Last!\n");
				else
					printf("\n-Success: The current, now points at the next node.\n");
				break;
			case _Previous_:
				m_Previous_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: The current node is Head!\n");
				else
					printf("\n-Success: The current, now points at the previous node.\n");
				break;
			case _MoveAfter_:
				m_MoveAfter_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: Not moved because the current node is Head!\n");
				else if (code == _isLast_)
					printf("\n-Fail: Not moved because the current node Last!\n");
				else
					printf("\n-Success: The current node is now in a position after.\n");
				break;
			case _MovePrevious_:
				m_MovePrevious_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: Not moved because the current node is Head!\n");
				else if (code == _nextFromHead_)
					printf("\n-Fail: Not moved because current node is next from Head!\n");
				else
					printf("\n-Success: The current node is now in a position before.\n");
				break;
			case _InsertCat_:
				m_InsertCat_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isPlate_)
					printf("\n-Fail: The category was not inserted because current is plate!\n");
				else if (code == _isHead_)
					printf("\n-Fail: The category was not inserted because current is Head!\n");
				else if (code == _hasChild_)
					printf("\n-Fail: The category was not inserted because current has sub-category!\n");
				else
					printf("\n-Success: The category was inserted.\n");
				break;
			case _Up_:
				m_MoveUp_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _noParent_)
					printf("\n-Fail: The current node has no parent!\n");
				else
					printf("\n-Success: The current node, now points it's parent.\n");
				break;
			case _Down_:
				m_MoveDown_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: Cannot move down because current node is Head!\n");
				else if (code == _noChild_)
					printf("\n-Fail: The current node, doesn't have sub-category!\n");
				else
					printf("\n-Success: The current node, now points the bottom of.\n");
				break;
			case _PrintCat_:
				m_PrintCat_(menu, stdout, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _visitNodeFail_)
					printf("\n-Fail: To perform the print category, the current node should be Head!\n");
				else
					printf("\n\n-Success: Printing category now completed.\n");
				break;
			case _Delete_:
				m_Delete_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isLast_)
					printf("\n-Fail: The deletion of the next node, has failed because next node does not exists!\n");
				else if (code == _hasChild_)
					printf("\n-Fail: The deletion of the next node, has failed because next node has sub-category!\n");
				else
					printf("\n-Success: The next node successfully deleted\n");
				break;
			case _DeleteCat_:
				m_DeleteCat_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _visitNodeFail_)
					printf("\n-Fail: For delete category, current must point to Head!\n");
				else
					printf("\n\n-Success: Category successfully deleted.\n");
				break;
			case _Cut_:
				m_Cut_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _isHead_)
					printf("\n-Fail: It is not possible to cut the Head node!\n");
				else if (code == _cutReserved_)
					printf("\n-Fail: There is already a 'cut' node waiting to be pasted!\n");
				else if (code == _lostCurrent_)
					printf("\n-Error: Current node is NULL!\n");
				else
					printf("\n-Success: Cut successfully complete.\n");
				break;
			case _Paste_:
				m_Paste_(menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _cutFree_)
					printf("\n-Fail: There is nothing to paste!\n");
				else if (code == _insertNodeFail_)
					printf("\n-Fail: Paste the node failed!\n");
				else
					printf("\n-Success: Paste successfully complete.\n");
				break;
			case 0:
				print_options();
				break;
			default:
			case _Destroy_:
				m_Destroy_(&menu, &code);
				if (code == _notExistsMenu_)
					printf("\n-Fail: To complete this action, you must create the menu!\n");
				else if (code == _visitNodeFail_)
					printf("\n-Fail: The start pointer does not point on the top menu!\n");
				else
					printf("\n\n-Success: The menu was destroyed.\n");
				break;
			case _Import_:
				if (argc > 0){
					FILE * fp;
					fp = fopen(argv[1], "r");
					if (fp != NULL){
						m_Import_(menu, fp, &code);
						if (code == _notExistsMenu_)
							printf("\n-Fail: To complete this action, you must create the menu!\n");
						else if (code == _noInputFile_)
							printf("\n-Fail: No input file!\n");
						else
							printf("\n\n-Success: Import Complete.\n");
					}
					else
						printf("\n-Fail: Error opening file: [%s]\n",argv[1]);
				}
				else
					printf("\n-Fail: No input file!\n");
				break;
			case _FailInput_:
				fflush(stdin);
				printf("\n-Fail: Cannot accept input, try again!\n");
				break;
			}
	} while (option >= 0 && option < 21);
	return 0;
}

void print_options(void){
printf("\n\
%d) Print options\n\
%d) Create Menu\t\t\t %d) Insert Category\n\
%d) Empty Category\t\t %d) Move Up\n\
%d) Insert\t\t\t %d) Move Down\n\
%d) Print Content\t\t %d) Print Category\n\
%d) Change Content\t\t %d) Delete\n\
%d) Next\t\t\t\t %d) Delete all\n\
%d) Previous_\t\t\t %d) Cut\n\
%d) Move After\t\t\t %d) Paste\n\
%d) Move Previous\t\t %d) Destroy Menu\n\
%d) Import from file\n",
_PrintOptions_,
_Create_, _InsertCat_,
_EmptyCat_, _Up_,
_InsertNode_, _Down_,
_PrintContent_, _PrintCat_,
_ChangeContent_, _Delete_,
_Next_, _DeleteCat_,
_Previous_, _Cut_,
_MoveAfter_, _Paste_,
_MovePrevious_, _Destroy_,
_Import_);
}