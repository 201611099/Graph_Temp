#include "./linkedgraph.h"
#include "./stack_yejeong/stack_array.h"
# define MAX 8

void traversal_recursive_internal_DFS(Stack **s, LinkedGraph *graph, int vertex)
{
	int tmp;
	ListNode *node;
	
	if (IsEmpty(*s))
		return ;
	tmp = pop(*s);
	printf("pop %d\n", tmp);
	node = graph->ppAdjEdge[tmp]->headerNode;
	while (node)
	{
		if (graph->pVertex[node->data] != VISITED)
		{
			graph->pVertex[node->data] = VISITED;
			push(*s, node->data);
		}
		node = node->pLink;
	}
	traversal_recursive_internal_DFS(s, graph, tmp);
}

void traversal_recursive_DFS(LinkedGraph *graph)
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	init(s);
	graph->pVertex[0] = VISITED;
	push(s, 0);
	traversal_recursive_internal_DFS(&s, graph, 0);
}

void traversal_DFS(LinkedGraph *pGraph)
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	init(s);
	ListNode *u;

	pGraph->pVertex[0] = VISITED;
	u = pGraph->ppAdjEdge[0]->headerNode;
	push(s, 0);
	while(!IsEmpty(s))
	{
		int tmp = pop(s);
		printf("pop vertex: %d\n", tmp);
		u = pGraph->ppAdjEdge[tmp]->headerNode;
		while (u)
		{
			if(pGraph->pVertex[u->data] != VISITED){
				pGraph->pVertex[u->data] = VISITED;
				push(s, u->data);
			}
			u = u->pLink;
		}
	} 
}

int main(void){
	LinkedGraph *lg = createLinkedGraph(MAX);

	for(int i=0; i<MAX; i++){
		addVertexLG(lg, i);
	}
	addEdgeLG(lg, 0, 1);
	addEdgeLG(lg, 0, 2);
	addEdgeLG(lg, 1, 3);
	addEdgeLG(lg, 1, 4);
	addEdgeLG(lg, 4, 5);
	addEdgeLG(lg, 2, 5);
	addEdgeLG(lg, 2, 6);
	addEdgeLG(lg, 3, 7);

	displayLinkedGraph(lg);
	//traversal_DFS(lg);
	traversal_recursive_DFS(lg);
	//displayLinkedGraph(lg);
}
