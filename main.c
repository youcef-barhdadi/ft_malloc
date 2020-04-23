# include "ft_malloc.h"
int main(int argc, char **argv)
{

	char *a1 = ft_malloc(2);
	char *a4 = ft_malloc(40);
	char *a2 = ft_malloc(1000);
	char *a14 = ft_malloc(1330007);

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



	return (0);
}
