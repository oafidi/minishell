#include "../includes/minishell.h"

static char	*join_three(char start, char *s, char last)
{
	size_t	len;
	char	*res;
	size_t	i;
	size_t	j;
	size_t	add;

	len = 0;
	if (s)
		len = ft_strlen(s);
	add = 0;
	if (start)
		add++;
	if (last)
		add++;
	res = malloc(len + add + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	if (start)
		res[i++] = start;
	while (s && s[j])
		res[i++] = s[j++];
	if (last)
		res[i++] = last;
	res[i] = '\0';
	return (res);
}

int	count_words(char start, char *s, char last)
{
	int		count;
	char	*temp;
	int		i;

	temp = join_three(start, s, last);
	if (!temp)
		return (0);
	i = 0;
	count = 0;
	while (temp[i])
	{
		while (is_space(temp[i]))
			i++;
		if (temp[i])
			count++;
		while (temp[i] && !is_space(temp[i]))
			i++;
	}
	free(temp);
	return (count);
}
