#include "./circular_queue.h"


int	main()
{
	ArrayQueue	*queue;
	
	queue = createArrayQueue(5);
	if (queue == NULL)
		return (1);
	printf("Empty: %s\nFull: %s\n", is_empty(queue) == TRUE ? "TRUE" : "FALSE", is_full(queue) == TRUE ? "TRUE" : "FALSE");
	enqueue(queue, 'A');
	enqueue(queue, 'B');
	enqueue(queue, 'C');
	enqueue(queue, 'D');
	enqueue(queue, 'E');

	printf("====enqueue * 5====\n");
	display_queue(queue);
	printf("Empty: %s\nFull: %s\n", is_empty(queue) == TRUE ? "TRUE" : "FALSE", is_full(queue) == TRUE ? "TRUE" : "FALSE");

	printf("\n===dequeue====\n");
	printf("dequeue: %c\n", dequeue(queue));
	printf("dequeue: %c\n", dequeue(queue));
	printf("dequeue: %c\n", dequeue(queue));
	printf("dequeue: %c\n", dequeue(queue));
	printf("dequeue: %c\n", dequeue(queue));

	printf("\n====dequeue * 5====\n");
	display_queue(queue);
	printf("Empty: %s\nFull: %s\n", is_empty(queue) == TRUE ? "TRUE" : "FALSE", is_full(queue) == TRUE ? "TRUE" : "FALSE");

	enqueue(queue, 'F');
	printf("dequeue: %c\n", dequeue(queue));
	enqueue(queue, 'A');
	enqueue(queue, 'B');

	printf("\n====enqueue->dequeue->(enqueue * 2)====\n");
	display_queue(queue);
	printf("Empty: %s\nFull: %s\n", is_empty(queue) == TRUE ? "TRUE" : "FALSE", is_full(queue) == TRUE ? "TRUE" : "FALSE");

	delete_queue(queue);
	system("leaks a.out");
	system("rm a.out");
	return(0);
}