
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
		i++;
	if (!(res = ft_strnew(i)))
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}
