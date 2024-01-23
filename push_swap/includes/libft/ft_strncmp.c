/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:17:46 by yioffe            #+#    #+#             */
/*   Updated: 2023/10/05 18:37:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0' && n > 1)
	{
		s1 ++;
		s2 ++;
		n --;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	str[] = "Hello";
	char	str2[] = "Hello";
	char	str3[] = "H";
	char	str4[] = "ello!F";

	printf("s1: %s\ns2: %s\nresult:%d\n", str, str2, ft_strncmp(str,str2, 4));
	printf("%d\n", strncmp(str, str2, 4));
	printf("s1: %s\ns2: %s\nresult:%d\n", str, str3, ft_strncmp(str,str3, 1));
	printf("%d\n", strncmp(str, str3, 1));
	printf("s1: %s\ns2: %s\nresult:%d\n", str, str4, ft_strncmp(str,str4, 6));
	printf("%d\n", strncmp(str, str4, 6));
	printf("s1: %s\ns2: %s\nresult:%d\n", str, str4, ft_strncmp(str,str4, 0));
	printf("%d\n", strncmp(str, str4, 0));
	return (0);
}*/
