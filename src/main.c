#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "map.h"

// size_t hash(char *key)
// {
// 	size_t index = 0;
//
// 	while (*key)
// 	{
// 		index += *key;
// 		key++;
// 	}
// 	return index;
// }

unsigned long hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

char	**str_arr_append(char **arr, char *s)
{
	char		**tmp;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	if (!arr)
	{
		tmp = ft_calloc(sizeof(char *), 2);
		tmp[0] = s;
		return tmp;
	}
	len = ft_strlen_2d(arr);
	tmp = ft_calloc(len + ft_strlen(s) + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		tmp[i] = arr[i];
		i++;
	}
	tmp[i] = s;
	free(arr);
	return (tmp);
}

static void print_bucket(t_bucket *bucket)
{
	while (bucket)
	{
		if (bucket->key && bucket->value)
			printf("key [%s] | value [%s]\n", bucket->key, bucket->value);
		else if (bucket->value)
			printf("key NONE | value [%s]\n", bucket->value);
		else if (bucket->key)
			printf("key [%s] | value NONE\n", bucket->key);
		bucket = bucket->next;
	}
}

static char *KEYS[] = {
	"key1",
	"key2",
	"key3",
	"key4",
	"key5",
	"key6",
	"key7",
	"key8",
	NULL,
};

int main()
{
	const size_t SIZE = 1;
	t_map *map = map_init(&hash, SIZE);
	assert(map && "map init failed");

	char **values = NULL;

	size_t i = 0;
	while (KEYS[i])
	{
		size_t tmp = i;
		// tmp -= 1;
		// if (tmp % 2)
		values = str_arr_append(values, ft_strjoin_free(ft_itoa(tmp), " value"));
		map_add(map, KEYS[i], values[i]);
		i++;
	}

	i = 0;
	while (i < map->capacity)
	{
		print_bucket(&map->buckets[i]);
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
			printf("map_get(%s) [%s]\n", KEYS[i], val);
		}
		i++;
	}

	map_free(map);
	ft_strfree_2d(values);
	return 0;
}
