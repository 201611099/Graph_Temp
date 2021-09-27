#include "./floyd.h"


int main(void)
{
	LinkedGraph *lg;
	LinkedGraph *mst;
	ListNode	*cur;
	int			start = 0;

	lg = createLinkedGraph(LG_MAX);

	for(int i=0; i<LG_MAX; i++)
	{
		addVertexLG(lg, i);
	}
	addEdgewithWeightLG(lg, 0, 1, 4);
	addEdgewithWeightLG(lg, 0, 2, 3);
	addEdgewithWeightLG(lg, 2, 1, 2);
	addEdgewithWeightLG(lg, 2, 3, 1);
	addEdgewithWeightLG(lg, 3, 4, 1);
	addEdgewithWeightLG(lg, 4, 5, 6);
	addEdgewithWeightLG(lg, 3, 5, 5);

	printf("\x1b[36m======= Original Linked Graph =======\x1b[0m\n");
	displayLinkedGraph(lg);

}