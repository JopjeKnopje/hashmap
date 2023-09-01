#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "map.h"

size_t hash(char *key)
{
	size_t index = 0;

	while (*key)
	{
		index += *key;
		key++;
	}
	return index;
}

static char *KEYS[] = {
	"key1",
	"key2",
	"key3",
	"key4",
	"key5",
	"key6",
	"key7",
	"key7",
	NULL,
};

int main()
{
	const size_t SIZE = 2;
	t_map *map = map_init(&hash, SIZE);

	size_t i = 0;
	while (KEYS[i])
	{
		map_add(map, KEYS[i], ft_itoa(i));
		i++;
	}

	i = 0;
	while (KEYS[i])
	{
		char *val = map_get_value(map, KEYS[i]);
		if (!val)
		{
			printf("no value for %ld\n", i);
		}
		else {
			printf("map_get [%s]\n", val);
		}
		i++;
	}


	map_free(map);
	return 0;
}
