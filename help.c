# include "ft_malloc.h"
unsigned char get_type(size_t size)
{
	if (size < 255 )
		return 1;
	if (size < 2048)
		return 2;
	return 3;


}
size_t get_zone_size(size_t size)
{
	int zone = get_type(size);
	if (zone == 1)
			return getpagesize() * 2;
	else if (zone == 2)
			return getpagesize() * 8;
	return size + sizeof(t_block) + sizeof(t_zone);
}


