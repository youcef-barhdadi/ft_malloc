# include "ft_malloc.h"


int main(int argc, char **argv)
{

	char *a1 = ft_malloc(1);
	char *a4 = ft_malloc(27);
	char *a5 = ft_malloc(3);
	char *a6 = ft_malloc(4);

	a1[0] = 'a';



	ft_free(a6);
	ft_free(a1);
/*	char *a14 = ft_malloc(1330007);

	t_zone *z = g_zone;

	while (z)
	{
		printf("type %d\n", z->type);
		t_block *b = (t_block *)((void *)z + sizeof(t_zone));
		while (b)
		{
			printf("block size %lld is free %d\n", b->size, b->free);
			b = b->next;
		}
		z = z->next;
	}


*/
	return (0);
}
