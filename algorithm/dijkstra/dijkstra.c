#include "./dijkstra.h"

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

dijElement *initDijkstra(LinkedGraph *lg, int start)
{
	dijElement *dijk = (dijElement *)malloc(sizeof(dijkstra) * LG_MAX);
	ListNode *tmp;
	
	bzero(dijk, sizeof(dijElement) * LG_MAX);
	for(int i=0; i < LG_MAX; i++)	
	{
		dijk[i].minWeight = INF;
		if (i == start)
		{
			dijk[i].visited = TRUE;
			dijk[i].minWeight = 0;
			dijk[i].preNode = i;
			continue ;
		}
		tmp = lg->ppAdjEdge[start]->headerNode;
		while(tmp)
		{
			if (tmp->data == i)
			{
				dijk[i].minWeight = tmp->weight;
				dijk[i].preNode = start;
				break ; 
			}
			tmp = tmp->pLink;
		}
	}
	return dijk;
}

void	printDijkstra(dijElement *dij)
{
	for(int i=0; i < LG_MAX; i++)
	{
		printf("vertex %d | minWeight %d | preNode %d | visited %d\n", i, dij[i].minWeight, dij[i].preNode, dij[i].visited);
	}	
}

int	isAllVisited(dijElement *dij)
{
	for (int i = 0; i < LG_MAX; i++)
	{
		if (!dij[i].visited)
			return FALSE;
	}
	return (TRUE);
}

void	updateHeap(Heap **h, dijElement *dijE)
{
	deleteHeap(*h);
	*h = createHeap();
	element tmp;

	for(int i=0; i <LG_MAX; i++)
	{
		if (!dijE[i].visited)
		{
			tmp.vertexID = i;
			tmp.weight = dijE[i].minWeight;
			insertMinHeap(*h, tmp);
		}
	}	
}

dijElement *dijkstra(LinkedGraph *lg, int start)
{
	dijElement *dijE = initDijkstra(lg, start);
	Heap *h = createHeap();
	element min;
	element tmp;
	ListNode *tempList;

	//가장 작은 거리를 찾아서
	//거리를 거쳐 가는 노드를 업데이트
	for(int i=0; i <LG_MAX; i++)
	{
			tmp.vertexID = i;
			tmp.weight = dijE[i].minWeight;
			insertMinHeap(h, tmp);
	}
	while(!isAllVisited(dijE))
	{
		printf("heap==========\n");
		printHeap(h);
		min = h->pElement[1];
		deleteMinHeap(h);
		dijE[min.vertexID].visited = TRUE;
		tempList = lg->ppAdjEdge[min.vertexID]->headerNode; //최소 경로와 연결된 인접노드들
		while(tempList)
		{
			if (!dijE[tempList->data].visited)
			{
				if(dijE[tempList->data].minWeight > dijE[min.vertexID].minWeight + tempList->weight)			
				{
					dijE[tempList->data].minWeight = dijE[min.vertexID].minWeight + tempList->weight;
					dijE[tempList->data].preNode = min.vertexID;
				}
			}
			tempList = tempList->pLink;
		}	
		updateHeap(&h, dijE);
	}
	return dijE;
} 

int main(void)
{
	LinkedGraph *lg;
	ListNode	*cur;
	int			start = 0;

	lg = createLinkedGraph(LG_MAX);

	for(int i=0; i<LG_MAX; i++)
	{
		addVertexLG(lg, i);
	}
	addEdgewithWeightLG(lg, 0, 1, 1);
	addEdgewithWeightLG(lg, 0, 2, 4);
	addEdgewithWeightLG(lg, 2, 1, 2);
	addEdgewithWeightLG(lg, 2, 3, 1);
	addEdgewithWeightLG(lg, 3, 4, 8);
	addEdgewithWeightLG(lg, 4, 5, 4);
	addEdgewithWeightLG(lg, 3, 5, 3);

	printf("\x1b[36m======= Original Linked Graph =======\x1b[0m\n");
	displayLinkedGraph(lg);

	printf("\x1b[36m======= Dijkstra =======\x1b[0m\n");
	dijElement *rt = dijkstra(lg, start);
	printDijkstra(rt);

}