#include "./linkedgraph.h"
#include "./circular_queue.h"

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
		printf("pop vertex: %d\n", tmp);
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
	traversal_BFS(lg);
	//traversal_recursive_DFS(lg);
	//displayLinkedGraph(lg);
}