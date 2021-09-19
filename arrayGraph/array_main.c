#include "./arraygraph.h"
#define VERTEX 8

int main(void)
{
	/*
	 * 무방향 - 가중치 O X
	 * 방향 - 가중치 O X
	 */
	//ArrayGraph *undir = createArrayGraph(VERTEX); //무방향 그래프

	//printf("\x1b[32m====isEmpty====\n\x1b[0m");
	//ans = isEmptyAG(undir) == TRUE ? "YES" : "NO";
	//printf("isEmptyAG undir? %s\n", ans);
	
	//addVertexAG(undir, 2);
	//addVertexAG(undir, 3);
	//addVertexAG(undir, 0);
	//addVertexAG(undir, 5);
	
	//displayArrayGraph(undir);
	//printf("\n\x1b[32m====isEmpty====\n\x1b[0m");
	//ans = isEmptyAG(undir) == TRUE ? "YES" : "NO";
	//printf("isEmptyAG undir? %s\n", ans);

	////addEdgeAG(undir, 2, 3);
	////addEdgeAG(undir, 0, 5);
	//addEdgewithWeightAG(undir, 2, 3, 10);
	//addEdgewithWeightAG(undir, 0, 3, 5);
	//addEdgewithWeightAG(undir, 5, 0, 7);
	//displayArrayGraph(undir);
	
	//deleteArrayGraph(undir);
	
	////dir
	printf("\n---------dir----------\n");
	ArrayGraph *dir = createArrayDirectedGraph(VERTEX); //무방향 그래프
	char *ans;

	printf("\x1b[32m====isEmpty====\n\x1b[0m");
	ans = isEmptyAG(dir) == TRUE ? "YES" : "NO";
	printf("isEmptyAG dir? %s\n", ans);
	
	addVertexAG(dir, 2);
	addVertexAG(dir, 3);
	addVertexAG(dir, 0);
	addVertexAG(dir, 5);
	
	displayArrayGraph(dir);
	printf("\n\x1b[32m====isEmpty====\n\x1b[0m");
	ans = isEmptyAG(dir) == TRUE ? "YES" : "NO";
	printf("isEmptyAG dir? %s\n", ans);

	//addEdgeAG(dir, 2, 3);
	//addEdgeAG(dir, 0, 5);
	addEdgewithWeightAG(dir, 2, 3, 10);
	addEdgewithWeightAG(dir, 0, 3, 5);
	addEdgewithWeightAG(dir, 5, 0, 7);
	displayArrayGraph(dir);
	
	deleteArrayGraph(dir);
	system("leaks a.out");
	return 0;
}