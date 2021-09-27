#ifndef PRIM_H
# define PRIM_H

# define LG_MAX 6
# define VISITIED 1
# define NOT_VISITIED 1

#include "./linkedGraph/linkedgraph.h"

typedef struct {
	int	fromVertex;
	int toVertex;
	int weight;
} element;

LinkedGraph	*prim(LinkedGraph *lg, int start);

#endif