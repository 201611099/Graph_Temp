#include "list.h"

void	printLinkedList(LinkedList *pList)
{
	ListNode	*cur;

	if (!pList || !pList->currentElementCount)
		return ;
	cur = pList->headerNode;
	while (cur)
	{
		printf("%d -> ", cur->data);
		cur = cur->pLink;
	}
	printf("\b\b\b  \n");
}