#ifndef DIJKSTRA_H
# define DIJKSTRA_H
# include "./linkedGraph/linkedgraph.h"

# define LG_MAX 6
# define TRUE 1
# define FALSE 0


typedef struct dijElement {
	//int destNode; //도착노드
	int dirWeight; //직선 거리
	int minWeight;  //단축 거리
	int preNode; //이전 연결 노드
} dijElement;

dijElement *dijkstra(LinkedGraph *lg, int start);
#endif