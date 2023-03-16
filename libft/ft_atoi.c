/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 08:10:39 by jalevesq          #+#    #+#             */
/*   Updated: 2022/11/07 14:19:59 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isnbr(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_is_whitespace(str[i]))
		i++;
	if (ft_is_sign(str[i]))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isnbr(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

// #include <stdio.h>
// int main()
// {
// 	printf("0 ft %d\n",ft_atoi("0"));
// 	printf("0    %d\n",atoi("0"));
// 	printf("+ ft %d\n",ft_atoi("+300"));
// 	printf("+    %d\n",atoi("+300"));
// 	printf("- ft %d\n",ft_atoi("-300"));
// 	printf("-    %d\n",atoi("-300"));
// 	printf("-+ ft %d\n",ft_atoi("-+2147483"));
// 	printf("-+    %d\n",atoi("-+2147483"));
// 	printf("-- ft %d\n",ft_atoi("--300"));
// 	printf("--    %d\n",atoi("--300"));
// 	printf("INT MAX ft %d\n",ft_atoi("2147483647"));
// 	printf("INT MAX    %d\n",atoi("2147483647"));
// 	printf("INT MIN ft %d\n",ft_atoi("-2147483648"));
// 	printf("INT MIN    %d\n",atoi("-2147483648"));
// 	printf("INT OVER ft %d\n",ft_atoi("30000000000"));
// 	printf("INT OVER    %d\n",atoi("30000000000"));
// 	printf("-INT OVER ft %d\n",ft_atoi("-30000000000"));
// 	printf("-INT OVER    %d\n",atoi("-30000000000"));
// 	printf("+LONG ft %ld\n",ft_atoi("9223372036854775807"));
// 	printf("+LONG    %ld\n",atoi("9223372036854775807"));
// 	printf("-LONG ft %ld\n",ft_atoi("-9223372036854775808"));
// 	printf("-LONG    %ld\n",atoi("-9223372036854775808"));
// 	printf("LONG OVER ft %ld\n",ft_atoi("44444119223372036854775807"));
// 	printf("LONG OVER    %ld\n",atoi("44444119223372036854775807"));
// 	printf("-LONG OVER ft %ld\n",ft_atoi("-1000000000000000000000"));
// 	printf("-LONG OVER    %ld\n",atoi("-1000000000000000000000"));
// 	printf("UNSIGNED LONG MAX ft %ld\n",ft_atoi("18446744073709551615"));
// 	printf("UNSIGNED LONG MAX    %ld\n",atoi("18446744073709551615"));
// 	printf("-UNSIGNED LONG MAX ft %ld\n",ft_atoi("-18446744073709551615"));
// 	printf("-UNSIGNED LONG MAX    %ld\n",atoi("-18446744073709551615"));
// 	printf("UNSIGNED LONG OVER ft %d\n",ft_atoi("10000000000000000"));
// 	printf("UNSIGNED LONG OVER    %d\n",atoi("10000000000000000"));
// 	printf("-UNSIGNED LONG OVER ft %d\n",ft_atoi("-30000000000000000"));
// 	printf("-UNSIGNED LONG OVER    %d\n",atoi("-30000000000000000"));
// 	printf("ulongover1 ft %ld\n",ft_atoi("18446744073709551616"));
// 	printf("ulongover1    %ld\n",atoi("18446744073709551616"));
// 	printf("ulongover2 ft %ld\n",ft_atoi("18446744073709551617"));
// 	printf("ulongover2    %ld\n",atoi("18446744073709551617"));
// 	printf("ulongover3 ft %ld\n",ft_atoi("18446744073709551618"));
// 	printf("ulongover3    %ld\n",atoi("18446744073709551618"));
// 	printf("ulongover4 ft %ld\n",ft_atoi("18446744073709551619"));
// 	printf("ulongover4    %ld\n",atoi("18446744073709551619"));
// }