/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:49:20 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 15:49:57 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

static int	get_len(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count += 1;
	while (n != 0)
	{
		n /= 10;
		count ++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		start;

	ret = malloc(sizeof(char) * get_len(n)+ 1);
	if (!ret)
		return (0);
	start = get_len(n);
	ret[start] = '\0';
	start --;
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	while (n != 0)
	{
		if (n < 0)
			ret[start--] = (-(n % 10) + 48);
		else
			ret[start--] = (n % 10 + 48);
		n /= 10;
	}
	if (start == 0)
		ret[0] = '-';
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * len + 1);
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[n])
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}
