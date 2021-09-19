#include "linkedgraph.h"

// 그래프 생성
LinkedGraph* createLinkedGraph(int maxVertexCount)
{
	LinkedGraph * rt;
	
	rt = (LinkedGraph *)malloc(sizeof(LinkedGraph));
	if (!rt)
	{
		printf("malloc error!\n");
		return NULL;
	}
	rt->maxVertexCount = maxVertexCount;
	rt->currentVertexCount = 0;
	rt->currentEdgeCount = 0;
	rt->graphType = GRAPH_UNDIRECTED;
	rt->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
	if (!rt->pVertex)
	{
		printf("malloc error!\n");
		free(rt);
		return NULL;
	}
	rt->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * maxVertexCount);
	if (!rt->ppAdjEdge)
	{
		printf("malloc error!\n");
		//free(rt->pVertex);
		//free(rt);
		//return NULL;
		exit(1);
	}
	for (int i = 0; i < maxVertexCount; i++)
	{
		rt->ppAdjEdge[i] = createLinkedList();
		if (!rt->ppAdjEdge[i])
		{
			printf("malloc error!\n");
			exit(1);
		}
	}
	return (rt);
}

LinkedGraph* createLinkedDirectedGraph(int maxVertexCount)
{
	LinkedGraph *rt;
	int i;

	rt = (LinkedGraph *)malloc(sizeof(LinkedGraph));
	if(!rt)
	{
		printf("LinkedGraph* malloc error");
		return NULL;
	}
	rt->maxVertexCount = maxVertexCount;
	rt->currentVertexCount = 0;
	rt->currentEdgeCount = 0;
	rt->graphType = GRAPH_DIRECTED;
	rt->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList *) * maxVertexCount);
	if (!rt->ppAdjEdge)
	{
		printf("ppAdjEdge malloc error\n");
		exit(1);
	}
	for (int i = 0; i < maxVertexCount; i++)
	{
		rt->ppAdjEdge[i] = createLinkedList();
		if (!rt->ppAdjEdge[i])
		{
			printf("ppAdjEdge* malloc error\n");
			exit(1);
		}
	}
	rt->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
	if(!rt->pVertex)
	{
		printf("pVertex malloc error\n");
		exit(1);
	}
	return rt;
}

// 그래프 삭제
void deleteLinkedGraph(LinkedGraph* pGraph)
{	
	for(int i=0; i<pGraph->maxVertexCount; i++)
	{
		if (checkVertexValid(pGraph, i) == TRUE)
			removeVertexLG(pGraph, i);
		free(pGraph->ppAdjEdge[i]);
	}
	free(pGraph->ppAdjEdge);
	free(pGraph->pVertex);
	free(pGraph);
}

// 공백 그래프 여부 판단
int isEmptyLG(LinkedGraph* pGraph)
{
	return pGraph->currentVertexCount == 0;
}

// 노드 추가
int addVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID))
	{
		printf("invalid input");
		return FALSE;
	}
	pGraph->currentVertexCount++;
	pGraph->pVertex[vertexID] = USED;
	return (TRUE);
}

// 간선 추가
int addEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!pGraph)
	{
		printf("Graph does not exist!\n");
		return (FALSE);
	}
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
	{
		printf("범위초과\n");
		return (FALSE);
	}
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		addLLElementLast(pGraph->ppAdjEdge[toVertexID], createListNode(fromVertexID, 1));
	addLLElementLast(pGraph->ppAdjEdge[fromVertexID], createListNode(toVertexID, 1));
	return (TRUE);
}

int addEdgewithWeightLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
		if (!pGraph)
	{
		printf("Graph does not exist!\n");
		return (FALSE);
	}
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
	{
		printf("범위초과\n");
		return (FALSE);
	}
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		addLLElementLast(pGraph->ppAdjEdge[toVertexID], createListNode(fromVertexID, weight));
	addLLElementLast(pGraph->ppAdjEdge[fromVertexID], createListNode(toVertexID, weight));
	return (TRUE);
}

// 노드의 유효성 점검
int checkVertexValid(LinkedGraph* pGraph, int vertexID)
{
	return (pGraph || vertexID < pGraph->maxVertexCount || vertexID >= 0);
}

// 노드 제거
int removeVertexLG(LinkedGraph* pGraph, int vertexID)
{
	if (!checkVertexValid(pGraph, vertexID))
	{
		printf("invalid input\n");
		return (FALSE);
	}
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		removeEdgeLG(pGraph, vertexID, i);
		//if (getGraphTypeLG(pGraph) == GRAPH_DIRECTED)
		//	removeEdgeLG(pGraph, i, vertexID);
	}
	pGraph->pVertex[vertexID] = NOT_USED;
	return (TRUE);
}

// 간선 제거
int removeEdgeLG(LinkedGraph* pGraph, int fromVertexID, int toVertexID)
{
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID))
		return (FALSE);
	deleteGraphNode(pGraph->ppAdjEdge[fromVertexID], toVertexID);
	if ((getGraphTypeLG(pGraph)) == GRAPH_UNDIRECTED)
		deleteGraphNode(pGraph->ppAdjEdge[toVertexID], fromVertexID);
	return (TRUE);
}


void deleteGraphNode(LinkedList* pList, int delVertexID) //연결된 곳에서 노드 삭제
{
	ListNode *cur;
	ListNode *tmp;

	if (findGraphNodePosition(pList, delVertexID) == FALSE)
	{
		//printf("edge does not exist!, vertexID == %d\n", delVertexID);
		return ;
	}
	cur = pList->headerNode;
	if (cur->data == delVertexID)
	{
		pList->headerNode = cur->pLink;
		bzero(cur, sizeof(ListNode));
		free(cur);
		return ;
	}
	// pre(cur) cur(tmp) next
	while (cur->pLink->data != delVertexID)
		cur = cur->pLink;
	tmp = cur->pLink; //지워야할 노드
	cur->pLink = tmp->pLink;
	bzero(tmp, sizeof(ListNode));
	free(tmp);
}

int findGraphNodePosition(LinkedList* pList, int vertexID) //vertex 존재 유무 true false
{
	ListNode *cur;

	cur = pList->headerNode;
	//for(int i=0; i<pList->currentElementCount; i++)
	while (cur)
	{
		if (cur->data == vertexID)
		{
			return (TRUE);
		}
		cur = cur->pLink;
	}
	return (FALSE);
}

// 간선 개수 반환
int getEdgeCountLG(LinkedGraph* pGraph)
{
	int	cnt;
	
	cnt = 0;
	for (int i = 0; i < pGraph->maxVertexCount; i++)
		cnt += pGraph->ppAdjEdge[i]->currentElementCount;
	if (pGraph->graphType == GRAPH_UNDIRECTED)
		cnt /= 2;
	return (cnt);
}

// 노드 개수 반환
int getVertexCountLG(LinkedGraph* pGraph)
{
	return pGraph->currentVertexCount;
}

// 최대 노드 개수 반환
int getMaxVertexCountLG(LinkedGraph* pGraph)
{
	return pGraph->maxVertexCount;
}

// 그래프 종류 반환
int getGraphTypeLG(LinkedGraph* pGraph)
{
	return pGraph->graphType;
}

// 그래프 정보 출력
void displayLinkedGraph(LinkedGraph* pGraph)
{
	printf("===== display linkedGraph =====\n   ");
	for(int i=0; i<pGraph->maxVertexCount; i++) {
		if (pGraph->pVertex[i] == USED)
			printf("\x1b[32m%-3d \x1b[0m", i); //vertex
		else
			printf("\x1b[31m%-3d \x1b[0m", i); //vertex
	}
	printf("\n---------------------------------------\n");
	for(int i=0; i<pGraph->maxVertexCount; i++){
		printf("\x1b[31m%d \x1b[0m|", i);
		ListNode *tmp = pGraph->ppAdjEdge[i]->headerNode;
		while (tmp)
		{
			printf("%-3d & %-3d |", tmp->data, tmp->weight);
			tmp = tmp->pLink;
		}
		printf("\n");
	}
	printf("-------------------------------------\n");
}
