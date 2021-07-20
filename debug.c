#include "asm.h"

char	*type_to_string_add(t_type_token type)
{
	if (type == 7)
		return ("REGISTER");
	else if (type == 8)
		return ("DIRECT");
	else if (type == 9)
		return ("DIRECT_LABEL");
	else if (type == 10)
		return ("INDIRECT");
	else if (type == 11)
		return ("INDIRECT_LABEL");
	else if (type == 12)
		return ("NEW_LINE");
	else if (type == 13)
		return ("END");
	return ("WRONG TYPE INPUT");
}

char	*type_to_string(t_type_token type)
{
	if (type == 0)
		return ("UNKNOWN");
	else if (type == 1)
		return ("NAME");
	else if (type == 2)
		return ("COMMENT");
	else if (type == 3)
		return ("INSTRUCTION");
	else if (type == 4)
		return ("STRING");
	else if (type == 5)
		return ("LABEL");
	else if (type == 6)
		return ("SEPARATOR");
	return (type_to_string_add(type));
}

void	print_token(t_token *token)
{
	if (token == NULL)
		return ;
	ft_putstr(token->str);
	write(1, " [", 2);
	ft_putstr(type_to_string(token->type_token));
	write(1, "]", 1);
}

void	print_token_list(t_token_list *token_list)
{
	t_token	*token;

	token = token_list->begin;
	while (token != NULL)
	{
		print_token(token);
		write(1, "\n", 1);
		token = token->next;
	}
}

void	print_arr(t_asm *asm_node)
{
	t_byte	**arr;
	size_t	len;
	size_t	index;

	arr = asm_node->arr;
	len = asm_node->len_arr;
	index = 0;
	while (index < len)
	{
		ft_putstr_fd("[value = ", 1);
		ft_putnbr_fd(arr[index]->value, 1);
		ft_putstr_fd(", size = ", 1);
		ft_putnbr_fd(arr[index]->num_bytes, 1);
		ft_putstr_fd("]", 1);
		ft_putstr_fd("\n", 1);
		++index;
	}
}

void	print_byte_array(const char *arr, size_t len)
{
	size_t	index;
	char	c;

	index = 0;
	while (index < len)
	{
		if (arr[index] == 0)
			write(1, "0", 1);
		else
		{
			c = arr[index];
			ft_putnbr(c);
		}
		write(1, " ", 1);
		++index;
	}
	write(1, "\n", 1);
}

void	print_malloc_free(void)
{
	ft_putstr("\nMalloc:");
	ft_putnbr(ml);
	ft_putstr(" Free:");
	ft_putnbr(fr);
	ft_putstr("\n");
}
