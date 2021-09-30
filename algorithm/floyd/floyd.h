#ifndef FLOYD_H
# define FLOYD_H

# include "./arrayGraph/arraygraph.h"

# define LG_MAX 6
# define VISITIED 1
# define NOT_VISITIED 0
# define INF 100000000

typedef struct {
	int	fromVertex;
	int toVertex;
	int weight;
} element;



#endif