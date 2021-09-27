#ifndef FLOYD_H
# define FLOYD_H

# include "./linkedGraph/linkedgraph.h"

# define LG_MAX 6
# define VISITIED 1
# define NOT_VISITIED 0

typedef struct {
	int	fromVertex;
	int toVertex;
	int weight;
} element;



#endif