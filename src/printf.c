/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:41:59 by alexanfe          #+#    #+#             */
/*   Updated: 2024/10/29 18:43:06 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}


int vft_printf(const char *fmt, va_list ap)
{
    int count = 0;

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            if (*fmt == 's')
                count += ft_putstr(va_arg(ap, char *));
            else if (*fmt == 'c')
                count += ft_putchar(va_arg(ap, int));
        }
        else
        {
            write(1, fmt, 1);
            count++;
        }
        fmt++;
    }
    return count;
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int count;

    va_start(ap, fmt);
    count = vft_printf(fmt, ap);
    va_end(ap);
    return count;
}
