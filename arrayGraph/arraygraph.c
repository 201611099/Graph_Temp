#include "arraygraph.h"

void	*mallocError(ArrayGraph *rt, int idx)
{
		printf("malloc error!");
		while (--idx > -1)
			free(rt->ppAdjEdge[idx]);
		free(rt->ppAdjEdge);
		free(rt);
		return (NULL);
}

// 그래프 생성
ArrayGraph* createArrayGraph(int maxVertexCount) //무방향 그래프 생성
{
	ArrayGraph *rt;
	int i;

	rt = (ArrayGraph *)malloc(sizeof(ArrayGraph));
	if (!rt)
	{
		printf("malloc error!");
		return NULL;
	}
	// bzero(rt, sizeof(ArrayGraph));
	rt->maxVertexCount = maxVertexCount;
	rt->currentVertexCount = 0;
	rt->graphType = GRAPH_UNDIRECTED;
	rt->ppAdjEdge = (int **)malloc(sizeof(int *) * maxVertexCount);
	if (!rt->ppAdjEdge)
	{
		printf("malloc error!");
		free(rt);
		return NULL;
	}
	for (i = 0; i < maxVertexCount; i++)
	{
		rt->ppAdjEdge[i] = (int *)malloc(sizeof(int) * maxVertexCount);
		if (!(rt->ppAdjEdge[i]))
			return (mallocError(rt, i));
		//bzero(rt->ppAdjEdge[i], sizeof(int));
		for (int j = 0; j < maxVertexCount; j++) //수정
			bzero(&(rt->ppAdjEdge[i][j]), sizeof(int)); //수정
	}
	rt->pVertex = (int *)malloc(sizeof(int) * maxVertexCount);
	if (!rt->pVertex)
		return (mallocError(rt, i));
	bzero(rt->pVertex, sizeof(int));
	return (rt);
}

ArrayGraph* createArrayDirectedGraph(int maxVertexCount) //방향 그래프 생성
{
	ArrayGraph	*rt;
	int i;

	rt = (ArrayGraph *)malloc(sizeof(ArrayGraph));
	if (!rt){
		printf("malloc error!");
		return NULL;
	}
	rt->maxVertexCount = maxVertexCount;
	rt->currentVertexCount = 0;
	rt->graphType = GRAPH_DIRECTED;
	rt->ppAdjEdge = (int **)malloc(sizeof(int *)* maxVertexCount);
	if (!rt->ppAdjEdge){
		printf("malloc error!");
		return NULL;
	}
	for(i=0; i<maxVertexCount; i++){
		rt->ppAdjEdge[i] = (int *)malloc(sizeof(int) * maxVertexCount);
		if (!rt->ppAdjEdge){
			return (mallocError(rt, i));;
		}
		bzero(rt->ppAdjEdge[i], sizeof(int));
	}
	rt->pVertex = (int *)malloc(sizeof(int)* maxVertexCount);
	if (rt->pVertex)
		return (mallocError(rt, i));
	bzero(rt->pVertex, sizeof(int));
	return rt;
}

// 그래프 삭제
void deleteArrayGraph(ArrayGraph* pGraph)
{
	int i;
	if (!pGraph)
	{
		printf("Graph does not exist\n");
		return ;
	}
	for (i = 0; i < pGraph->maxVertexCount; i++)
		removeVertexAG(pGraph, i);
	while (--i > -1)
		free(pGraph->ppAdjEdge[i]);
	free(pGraph->ppAdjEdge);
	free(pGraph);
}

// 공백 그래프 여부 판단
int isEmptyAG(ArrayGraph* pGraph) //TRUE, FALSE
{
	return (pGraph->currentVertexCount == 0);
}

// 노드 추가
int addVertexAG(ArrayGraph* pGraph, int vertexID) //0부터 시작이라는 가정 하에
{
	if (!pGraph)
	{
		printf("Graph does not exist!\n");
		return (FALSE);
	}
	// if (vertexID >= pGraph->maxVertexCount || vertexID < 0)
	if (!checkVertexValid(pGraph, vertexID))
	{
		printf("범위 초과\n");
		return (FALSE);
	}
	if (pGraph->pVertex[vertexID] == USED)
	{
		printf("이미 사용 중인 노드입니다\n");
		return (FALSE);
	}
	pGraph->pVertex[vertexID] = USED;
	pGraph->currentVertexCount++; //추가
	return (TRUE);
}

// 간선 추가
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID){
	if(!pGraph)
	{
		printf("Graph does not exist!\n");
		return (FALSE);
	}
	if (!checkVertexValid(pGraph,fromVertexID) ||!checkVertexValid(pGraph,toVertexID)){
		printf("범위초과\n");
		return (FALSE);
	}
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = USED;
	return (TRUE);
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight){
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID)) {
		printf("범위 초과\n");
		return (FALSE);
	}
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = weight;
	return (TRUE);
}

// 노드의 유효성 점검
int checkVertexValid(ArrayGraph* pGraph, int vertexID){
	return (pGraph || vertexID < pGraph->maxVertexCount || vertexID >= 0);
}

// 노드 제거
int removeVertexAG(ArrayGraph* pGraph, int vertexID){
	if (!checkVertexValid(pGraph, vertexID)) {
		printf("범위 초과\n");
		return (FALSE);
	}
	for (int i = 0; i < pGraph->maxVertexCount; i++)
	{
		if (pGraph->pVertex[i] == USED)
		{
			removeEdgeAG(pGraph, vertexID, i);
			removeEdgeAG(pGraph, i, vertexID);
		}
	}
	pGraph->pVertex[vertexID] = NOT_USED;
	return (TRUE);
}

// 간선 제거
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID){
	if (!checkVertexValid(pGraph, fromVertexID) || !checkVertexValid(pGraph, toVertexID)) {
		printf("범위 초과\n");
		return (FALSE);
	}
	pGraph->ppAdjEdge[fromVertexID][toVertexID] = NOT_USED;
	return (TRUE); 
}

// 그래프 정보 출력
void displayArrayGraph(ArrayGraph* pGraph){
	printf("===== display array =====\n");
	printf("   ");
	for(int i=0; i<pGraph->maxVertexCount; i++) {
		//printf("\x1b[31m%d \x1b[0m", pGraph->pVertex[i]);
		printf("\x1b[31m%d \x1b[0m", i); //vertex
	}
	printf("\n-------------------------\n");
	for(int i=0; i<pGraph->maxVertexCount; i++) {
		//printf("\x1b[31m%d \x1b[0m|", pGraph->pVertex[i]);
		printf("\x1b[31m%d \x1b[0m|", i);
		for(int j=0; j<pGraph->maxVertexCount; j++){
			printf("%d ", pGraph->ppAdjEdge[i][j]);
		}
		printf("\n");
	}
}
