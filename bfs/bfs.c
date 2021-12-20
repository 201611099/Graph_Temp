#include "./linkedgraph.h"
#include "./circular_queue.h"

void traversal_recursive_internal_BFS(ArrayQueue **s, LinkedGraph *graph, int vertex)
{
	int tmp;
	ListNode *node;
	
	if (is_empty(*s))
		return ;
	tmp = dequeue(*s);
	printf("dequeue %d\n", tmp);
	node = graph->ppAdjEdge[tmp]->headerNode;
	while (node)
	{
		if (graph->pVertex[node->data] != VISITED)
		{
			graph->pVertex[node->data] = VISITED;
			enqueue(*s, node->data);
		}
		node = node->pLink;
	}
	traversal_recursive_internal_BFS(s, graph, tmp);
}

void traversal_recursive_BFS(LinkedGraph *graph)
{
	ArrayQueue *s = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	s = createArrayQueue(MAX);
	graph->pVertex[0] = VISITED;
	enqueue(s, 0);
	traversal_recursive_internal_BFS(&s, graph, 0);
	delete_queue(s);
}

void traversal_BFS(LinkedGraph *pGraph)
{
	ArrayQueue *s = (ArrayQueue *)malloc(sizeof(ArrayQueue));
	s = createArrayQueue(MAX);
	ListNode *u;

	pGraph->pVertex[0] = VISITED;
	u = pGraph->ppAdjEdge[0]->headerNode;
	enqueue(s, 0);
	while(!is_empty(s))
	{
		int tmp = dequeue(s);
		printf("dequeue vertex: %d\n", tmp);
		u = pGraph->ppAdjEdge[tmp]->headerNode;
		while (u)
		{
			if(pGraph->pVertex[u->data] != VISITED){
				pGraph->pVertex[u->data] = VISITED;
				enqueue(s, u->data);
			}
			u = u->pLink;
		}
	} 
	delete_queue(s);
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

	LinkedGraph *lg2 = createLinkedGraph(MAX);

	for(int i=0; i<MAX; i++){
		addVertexLG(lg2, i);
	}
	addEdgeLG(lg2, 0, 1);
	addEdgeLG(lg2, 0, 2);
	addEdgeLG(lg2, 1, 3);
	addEdgeLG(lg2, 1, 4);
	addEdgeLG(lg2, 4, 5);
	addEdgeLG(lg2, 2, 5);
	addEdgeLG(lg2, 2, 6);
	addEdgeLG(lg2, 3, 7);

	displayLinkedGraph(lg);
	printf("\n======BFS(Recursive)======\n");
	traversal_recursive_BFS(lg);
	printf("\n======BFS(Iteration)======\n");
	traversal_BFS(lg2);

	//deleteLinkedGraph(lg);
	//deleteLinkedGraph(lg2);
	//system("leaks a.out");
	return (0);
	//displayLinkedGraph(lg);
}