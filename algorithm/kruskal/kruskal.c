#include "heap.h"
#include "./linkedGraph/linkedgraph.h"

#define LG_MAX 6

static int is_power_of_two(int num)
{
	return num && !((num-1) & num);
}

static void	printHeap(Heap *heap)
{
	for (int i = 1; i <= heap->currentElementCount; i++){
		printf("%d ", heap->pElement[i].weight);
	 // printf("tt : %d\n", is_power_of_two(i + 1));
	if (is_power_of_two(i + 1))
		printf("\n");
		//printf("a : %d\n", i);
	}
	printf("\n");
}

//int isCycle(LinkedGraph *mst)
//{
	
//}

void kruskal(LinkedGraph *mst, Heap *heap)
{
	int vertex[LG_MAX] = {0, };
	element	edge;
	//int i = 0;

	//while (heap->currentElementCount && i != LG_MAX - 1)
	while (heap->currentElementCount)
	{
		edge = heap->pElement[1];
		deleteMinHeap(heap);
		if (!vertex[edge.fromVertex] || !vertex[edge.toVertex])
		{
			addEdgewithWeightLG(mst, edge.fromVertex, edge.toVertex, edge.weight);
			vertex[edge.fromVertex] = 1;
			vertex[edge.toVertex] = 1;
			//i++;
		}
	}
	//if(isCycle(mst))
	//removeEdgeLG(mst, edge.fromVertex, edge.toVertex);
	//return (TRUE);
}

int main (void)
{
	LinkedGraph	*lg;
	LinkedGraph	*mst;
	Heap		*heap;
	element		elem;
	ListNode	*cur;

	lg = createLinkedGraph(LG_MAX);
	mst = createLinkedGraph(LG_MAX);
	heap = createHeap();
	for(int i=0; i<LG_MAX; i++)
	{
		addVertexLG(lg, i);
		addVertexLG(mst, i);
	}
	addEdgewithWeightLG(lg, 0, 1, 4);
	addEdgewithWeightLG(lg, 0, 2, 3);
	addEdgewithWeightLG(lg, 2, 1, 2);
	addEdgewithWeightLG(lg, 2, 3, 1);
	addEdgewithWeightLG(lg, 3, 4, 1);
	addEdgewithWeightLG(lg, 4, 5, 6);
	addEdgewithWeightLG(lg, 3, 5, 5);
	for (int i = 0; i < LG_MAX; i++)
	{
		cur = lg->ppAdjEdge[i]->headerNode;
		while (cur)
		{
			elem.fromVertex = i;
			elem.toVertex = cur->data;
			elem.weight = cur->weight;
			if (cur->data >= i)
				insertMinHeap(heap, elem);
			cur = cur->pLink;
		}
	}
	printf("\n\x1b[34m======== Initial Heap ========\x1b[0m\n");
	printHeap(heap);

	printf("\x1b[36m======= Original Linked Graph =======\x1b[0m\n");
	displayLinkedGraph(lg);
	
	kruskal(mst, heap);
	printf("\n\x1b[36m===== Minimun Spanning Tree(Kruskal) =====\x1b[0m\n");
	displayLinkedGraph(mst);

	deleteLinkedGraph(lg);
	deleteLinkedGraph(mst);
	//system("leaks a.out");
}