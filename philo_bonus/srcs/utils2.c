/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:35:48 by lorenzo           #+#    #+#             */
/*   Updated: 2024/08/14 17:27:36 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdio.h>

static char	*ft_strcpy(char *dest, char *src);
static unsigned int	digit_count(int nb);

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	digits;

	digits = digit_count(n);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (n == 0 || n == -2147483648)
	{
		if (n == 0)
			return (ft_strcpy(str, "0"));
		else
			return (ft_strcpy(str, "-2147483648"));
	}
	str[digits] = '\0';
	while (n != 0)
	{
		if (n < 0)
		{
			str[0] = '-';
			n *= -1;
		}
		str[--digits] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

int ft_strlen(char const *s1)
{
	int i  = 0;
	while(s1[i])
		i++;
	return i;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*result;
	size_t		s1len;
	size_t		s2len;
	char		*ret;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	ret = result;
	if (!result)
		return (NULL);
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (ret);
}

static unsigned int	digit_count(int nb)
{
	unsigned int	digits_count;

	digits_count = 0;
	if (nb == 0)
		return (1);
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
	{
		digits_count = 1;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		digits_count++;
	}
	return (digits_count);
}

static char	*ft_strcpy(char *dest, char *src)
{
	char	*orig;

	orig = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (orig);
}

