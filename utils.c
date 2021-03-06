#include "asm.h"

size_t		skip_whitespaces(const char *line, size_t index)
{
	while (is_whitespace(line[index]) == 1)
		++index;
	return (index);
}

char	*char_to_string(char c)
{
	char *str;

	// TO DO
//	if ((str = (char *)malloc(sizeof(char) * 2)) == NULL)
//		return (NULL);
	MFAIL((str = (char *)malloc(sizeof(char) * 2)));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*get_cor_file_name(char *file_name)
{
	char	*cor_file_name;
	size_t	len_file_name;
	size_t	len_cor_file_name;

	len_file_name = ft_strlen(file_name);
	len_cor_file_name = len_file_name + 2;
	cor_file_name = (char *)malloc(sizeof(char) * (len_cor_file_name + 1));
	if (cor_file_name == NULL)
		print_error_and_exit();
	ft_memcpy(cor_file_name, file_name, len_cor_file_name - 3);
	ft_memcpy(&(cor_file_name[len_cor_file_name - 3]), "cor", 3);
	cor_file_name[len_cor_file_name] = '\0';
	return (cor_file_name);
}

void	fill_value_to_hex(char *str, int32_t value,
									size_t start, size_t size)
{
	size_t	shift;
	size_t	index_str;
	size_t	num;

	shift = 0;
	while (size != 0)
	{
		index_str = start + size - 1;
		num = (value >> shift) & 0xFF;
		if (num == 0)
			break ;
		str[index_str] = (uint8_t)num;
		shift += 8;
		--size;
	}
}
