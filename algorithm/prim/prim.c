#include "prim.h"

element	findMinEdge(LinkedGraph *lg, int *Vertex)
{
	element		Edge;
	ListNode	*cur;

	bzero(&Edge, sizeof(element));
	for (int i = 0; i < LG_MAX; i++)
	{
		if (!Vertex[i])
			continue ;
		cur = lg->ppAdjEdge[i]->headerNode;
		if (!cur)
			continue ;
		while (cur)
		{
			if (!Edge.weight || (0 < cur->weight && Edge.weight >= cur->weight))
			{
				Edge.fromVertex = i;
				Edge.toVertex = cur->data;
				Edge.weight = cur->weight;
			}
			cur = cur->pLink;
		}
	}
	return Edge;
}

LinkedGraph *prim(LinkedGraph *lg, int start)
{
	LinkedGraph	*mst;
	int 		Vertex[LG_MAX] = {NOT_VISITIED, }; //노드들의 집합인데 선택되는 순간 1
	int 		idx = 0;
	element 	Edge;

	if (start >= LG_MAX || start < 0)
	{
		printf("Vertex Index: 0 ~ %d\n", LG_MAX);
		return (NULL);
	}
	mst = createLinkedGraph(LG_MAX);
	for (int i = 0; i < LG_MAX; i++)
		addVertexLG(mst, i);
	Vertex[start] = VISITIED;
	while(idx < LG_MAX - 1)
	{
		//printf("idx: %d\n", idx);
		Edge = findMinEdge(lg, Vertex);
		if (!Vertex[Edge.fromVertex] || !Vertex[Edge.toVertex])
		{
			addEdgewithWeightLG(mst, Edge.fromVertex, Edge.toVertex, Edge.weight);
			Vertex[Edge.fromVertex] = VISITIED;
			Vertex[Edge.toVertex] = VISITIED;
			idx++;
		}
		else
			removeEdgeLG(lg, Edge.fromVertex, Edge.toVertex);
	}
	return mst;
}

int main(void)
{
	LinkedGraph *lg;
	LinkedGraph *mst;
	ListNode	*cur;
	int			start = 0;

	lg = createLinkedGraph(LG_MAX);

	for(int i=0; i<LG_MAX; i++)
	{
		addVertexLG(lg, i);
	}
	addEdgewithWeightLG(lg, 0, 1, 4);
	addEdgewithWeightLG(lg, 0, 2, 3);
	addEdgewithWeightLG(lg, 2, 1, 2);
	addEdgewithWeightLG(lg, 2, 3, 1);
	addEdgewithWeightLG(lg, 3, 4, 1);
	addEdgewithWeightLG(lg, 4, 5, 6);
	addEdgewithWeightLG(lg, 3, 5, 5);

	printf("\x1b[36m======= Original Linked Graph =======\x1b[0m\n");
	displayLinkedGraph(lg);

	mst = prim(lg, start);
	printf("\n\x1b[36m===== Minimun Spanning Tree(Prim) =====\x1b[0m\n");
	displayLinkedGraph(mst);

}