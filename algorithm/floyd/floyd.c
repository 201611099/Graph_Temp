#include "./floyd.h"

void	printFloyd(int **ret)
{

	printf( "    ");
	for (int i = 0; i < LG_MAX; i++)
	{
		printf( "|\x1b[33m%4d\x1b[0m", i);
	}
	printf("\n  ----------------------------------\n");
	for (int i = 0; i < LG_MAX; i++)
	{
		printf( "\x1b[33m%4d\x1b[0m", i);
		for (int j = 0; j < LG_MAX; j++)
			printf("| %3d", ret[i][j]);
		printf("\n");
	}
}
int **initFloyd(ArrayGraph *lg)
{
	//int ret[LG_MAX][LG_MAX];
	int **ret = (int **)malloc(sizeof(int *) * LG_MAX);
	
	for(int i=0; i < LG_MAX; i++)
	{
		ret[i] = (int *)malloc(sizeof(int) * LG_MAX);
	}
	for(int i=0; i < LG_MAX; i++)
	{
		for (int j = 0; j < LG_MAX; j++ )
		{
			ret[i][j] = lg->ppAdjEdge[i][j];
			if (ret[i][j] == 0 && i != j)
				ret[i][j] = INF;
		}
	}
	return ret;
}

int **floyd(ArrayGraph *lg)
{
	int **ret = initFloyd(lg);
	//printFloyd(ret);
	for (int i=0; i < LG_MAX; i++) //거쳐가는 노드
	{
		for (int j=0; j < LG_MAX; j++) //출발노드 
		{
			for (int k=0; k < LG_MAX; k++) //도착노드
			{
				if (ret[j][k] > ret[j][i]+ ret[i][k])
					ret[j][k] = ret[j][i]+ ret[i][k]; 
			}
		}
	}
	return ret;
}


int main(void)
{
	ArrayGraph *lg;

	lg = createArrayGraph(LG_MAX);

	for(int i=0; i<LG_MAX; i++)
	{
		addVertexAG(lg, i);
	}
	addEdgewithWeightAG(lg, 0, 1, 1);
	addEdgewithWeightAG(lg, 0, 2, 4);
	addEdgewithWeightAG(lg, 2, 1, 2);
	addEdgewithWeightAG(lg, 2, 3, 1);
	addEdgewithWeightAG(lg, 3, 4, 8);
	addEdgewithWeightAG(lg, 4, 5, 4);
	addEdgewithWeightAG(lg, 3, 5, 3);

	printf("\x1b[36m======= Original Array Graph =======\x1b[0m\n");
	displayArrayGraph(lg);

	printf("\x1b[36m======= Floyd =======\x1b[0m\n");
	int **ret = floyd(lg);
	printFloyd(ret);
	for(int i=0; i<LG_MAX; i++)
		free(ret[i]);
	free(ret);
	system("leaks a.out");
}