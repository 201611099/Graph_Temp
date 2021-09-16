#include "./list.h"

LinkedList	*createLinkedList(void)
{
	LinkedList	*lst;

	lst = (LinkedList *)malloc(sizeof(LinkedList));
	if (!lst)
		return (0);
	bzero(lst, sizeof(LinkedList));
	return (lst);
}

ListNode	*createListNode(int data)
{
	ListNode	*node;
	node = (ListNode *)malloc(sizeof(ListNode));
	if (!node)
		return (0);
	bzero(node, sizeof(ListNode));
	node->data = data;
	return (node);
}

t_bool	addLLElement(LinkedList *pList, int position, ListNode *element)
{
	ListNode	*cur;

	if (!pList)
		return (T_FALSE);
	if (pList->currentElementCount < position) //position을 인덱스로 생각(0부터 시작)
		return (T_FALSE);
	if (!pList->currentElementCount || !position)
	{
		if (!position && pList->currentElementCount)
			element->pLink = pList->headerNode;
		pList->headerNode = element;
		pList->currentElementCount++;
		return (T_TRUE);
	}
	cur = pList->headerNode;
	for (int i = 1; i < position; i++)
		cur = cur->pLink;
	element->pLink = cur->pLink;
	cur->pLink = element;
	pList->currentElementCount++;
	return (T_TRUE);
}

t_bool	removeLLElement(LinkedList *pList, int position)
{
	ListNode	*cur;
	ListNode	*next;

	if (!pList || !(pList->currentElementCount))
		return (T_FALSE);
	if (position >= pList->currentElementCount)
		return (T_FALSE);
	cur = pList->headerNode;
	if (!position)
	{
		pList->headerNode = cur->pLink;
		cur->pLink = 0;
		free(cur);
		pList->currentElementCount--;
		return (T_TRUE);
	}
	for (int i = 0; i < position - 1; i++)
		cur = cur->pLink;
	next = cur->pLink->pLink;
	if (!(cur->pLink->pLink)) //지우려고 하는 노드가 마지막 노드가 아닐 때
		cur->pLink->pLink = 0;
	free(cur->pLink);
	cur->pLink = next;
	pList->currentElementCount--;
	return (T_TRUE);
}

t_data	getLLElement(LinkedList *pList, int position)
{
	ListNode	*ret;

	if (!pList || position >= pList->currentElementCount)
		return (0);
	ret = pList->headerNode;
	for (int i = 0; i < position; i++)
		ret = ret->pLink;
	return (ret->data);
}

void	clearLinkedList(LinkedList *pList)
{
	ListNode	*cur;
	ListNode	*next;

	if (!pList || !(pList->currentElementCount))
		return ;
	cur = pList->headerNode;
	while (cur)
	{
		next = cur->pLink;
		free(cur);
		cur = next;
	}
	bzero(pList, sizeof(LinkedList));
}

int	getLinkedListLength(LinkedList *pList)
{
	return (pList->currentElementCount);
}

void	deleteLinkedList(LinkedList *pList)
{
	clearLinkedList(pList);
	free(pList);
}
