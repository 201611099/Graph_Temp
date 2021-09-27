#include "./dijkstra.h"

int	WeightCompare(LinkedGraph *lg, int fromVertex, int toVertex, dijElement *dElem)
{
	ListNode	*cur;
	int			cmpWeight;

	cur = lg->ppAdjEdge[fromVertex]->headerNode;
	while (cur)
	{
		if (cur->data == toVertex)
		{
			cmpWeight = dElem[toVertex].dirWeight + cur->weight;
			if (dElem[fromVertex].dirWeight > cmpWeight)
			{
				dElem[fromVertex].dirWeight = cmpWeight;
				dElem[fromVertex].preNode = cur->data;
				return (toVertex);
			}
			return (fromVertex);
		}
		cur = cur->pLink;
	}
	return (fromVertex);
}

void	recursiveDijkstra(LinkedGraph *lg, dijElement *dElem, int *S, int restart)
{
	ListNode *cur;
	int		adjacent = -1;
	int		tmp = 1;

	cur = lg->ppAdjEdge[restart]->headerNode;
	// 1. restart에 인접 노드들은 값 채우고
	for(int i=0; i<LG_MAX; i++)
		tmp *= S[i];
	if (tmp)
		return ;
	while (cur)
	{
		dElem[cur->data].dirWeight = cur->weight;
		dElem[cur->data].minWeight = cur->weight;
		dElem[cur->data].preNode = restart;
		S[cur->data] = TRUE;
		cur = cur->pLink;
	}
	// 2. 인접 노드를 거쳐가는 경로 검사 => 더 작은 가중치면 업데이트
	// 만약 이전 노드(restart)와 연결된 노드가 cur에도 연결되어 있다면
	// 그 연결된 노드(temp)를 거쳤을 때의 가중치와 비교해서 minWeight을 업데이트?
	for (int i = 0; i < LG_MAX; i++)
	{
		for (int j = i + 1; j < LG_MAX; j++)
		{
			if (dElem[i].preNode == dElem[j].preNode)
			{
				adjacent = WeightCompare(lg, i, j, dElem);
				//연결되어있다면 가중치 비교? 
			}
		}
	}
	if (adjacent == -1)
	{
		recursiveDijkstra(lg, dElem, S, lg->ppAdjEdge[restart]->headerNode->data);
	}
	recursiveDijkstra(lg, dElem, S, adjacent);
}

dijElement *dijkstra(LinkedGraph *lg, int start)
{
	ListNode	*cur;
	int	S[LG_MAX] = {FALSE, }; //노드 집합 -> 최단 거리를 찾으면 제거
	dijElement	dElem[LG_MAX]; //반환

	//init
	bzero(dElem, sizeof(dijElement) * LG_MAX);
	S[start] = TRUE;

	recursiveDijkstra(lg, dElem, S, start);
	for(int i=0; i < LG_MAX; i++)
	{
		printf("desNode: %d, dirWeight: %d, minWeight: %d, preNode: %d\n", i, dElem[i].dirWeight, dElem[i].minWeight, dElem[i].preNode);
	}
	return dElem;
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
	addEdgewithWeightLG(lg, 0, 1, 4);
	addEdgewithWeightLG(lg, 0, 2, 3);
	addEdgewithWeightLG(lg, 2, 1, 2);
	addEdgewithWeightLG(lg, 2, 3, 1);
	addEdgewithWeightLG(lg, 3, 4, 1);
	addEdgewithWeightLG(lg, 4, 5, 6);
	addEdgewithWeightLG(lg, 3, 5, 5);

	printf("\x1b[36m======= Original Linked Graph =======\x1b[0m\n");
	displayLinkedGraph(lg);

	printf("\x1b[36m======= Dijkstra =======\x1b[0m\n");
	dijkstra(lg, start);

}