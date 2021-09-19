#include "./linkedgraph.h"
#define MAX 6
int main(void)
{
	/*
	 * 무방향 - 가중치 O X
	 * 방향 - 가중치 O X
	 */
	//LinkedGraph *undir = createLinkedGraph(VERTEX); //무방향 그래프

	//printf("\x1b[32m====isEmpty====\n\x1b[0m");
	//ans = isEmptyLG(undir) == TRUE ? "YES" : "NO";
	//printf("isEmptyLG undir? %s\n", ans);
	
	//addVertexLG(undir, 2);
	//addVertexLG(undir, 3);
	//addVertexLG(undir, 0);
	//addVertexLG(undir, 5);
	
	//displayLinkedGraph(undir);
	//printf("\n\x1b[32m====isEmpty====\n\x1b[0m");
	//ans = isEmptyLG(undir) == TRUE ? "YES" : "NO";
	//printf("isEmptyLG undir? %s\n", ans);

	////addEdgeLG(undir, 2, 3);
	////addEdgeLG(undir, 0, 5);
	//addEdgewithWeightLG(undir, 2, 3, 10);
	//addEdgewithWeightLG(undir, 0, 3, 5);
	//addEdgewithWeightLG(undir, 5, 0, 7);
	//displayLinkedGraph(undir);
	
	//deleteLinkedGraph(undir);
	
	////dir
	printf("\n---------dir----------\n");
	LinkedGraph *dir = createLinkedDirectedGraph(MAX); //방향 그래프
	char *ans;

	printf("\x1b[32m====isEmpty====\n\x1b[0m");
	ans = isEmptyLG(dir) == TRUE ? "YES" : "NO";
	printf("isEmptyLG dir? %s\n", ans);
	
	addVertexLG(dir, 2);
	addVertexLG(dir, 3);
	addVertexLG(dir, 0);
	addVertexLG(dir, 5);
	
	displayLinkedGraph(dir);
	printf("\n\x1b[32m====isEmpty====\n\x1b[0m");
	ans = isEmptyLG(dir) == TRUE ? "YES" : "NO";
	printf("isEmptyLG dir? %s\n", ans);

	//addEdgeLG(dir, 2, 3);
	//addEdgeLG(dir, 0, 5);
	addEdgewithWeightLG(dir, 2, 3, 10);
	addEdgewithWeightLG(dir, 0, 3, 5);
	addEdgewithWeightLG(dir, 0, 1, 2);
	addEdgewithWeightLG(dir, 5, 0, 7);
	displayLinkedGraph(dir);
	
	deleteLinkedGraph(dir);
	system("leaks a.out");
}