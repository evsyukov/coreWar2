#include "asm.h"

int			is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int			is_num_from_ind(const char *str, size_t index)
{
	if (str[index] == '-')
		++index;
	if (str[index] == '\0')
		return (0);
	while (str[index] != '\0' && ft_isdigit(str[index]))
		++index;
	if (str[index] == '\0')
		return (1);
	return (0);
}

static int	is_valid_label_char(char c)
{
	size_t	index;

	index = 0;
	while (LABEL_CHARS[index] != '\0')
	{
		if (c == LABEL_CHARS[index])
			return (1);
		++index;
	}
	return (0);
}

int			is_label(const char *str, size_t len)
{
	size_t	index;

	if (str[len - 1] != LABEL_CHAR)
		return (0);
	index = 0;
	while (index < len - 1)
	{
		if (!is_valid_label_char(str[index]))
			return (0);
		++index;
	}
	return (1);
}

int			is_instr(const char *str)
{
	size_t	index;

	index = 0;
	while (index < NUM_OF_INSTR)
	{
		if (!ft_strcmp(str, INSTRS[index]))
		return (1);
		++index;
	}
	return (0);
}
