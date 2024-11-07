/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   printf.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alexanfe <alexanfe@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/29 18:41:59 by alexanfe		  #+#	#+#			 */
/*   Updated: 2024/10/29 18:43:06 by alexanfe		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_puthex(unsigned long num)
{
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789abcdef";
	if (num >= 16)
		count += ft_puthex(num / 16);
	count += write(1, &hex[num % 16], 1);
	return (count);
}

int ft_putupperhex(unsigned long num)
{
	int		count;
	char	*hex;

	count = 0;
	hex = "0123456789ABCDEF";
	if (num >= 16)
		count += ft_putupperhex(num / 16);
	count += write(1, &hex[num % 16], 1);
	return (count);
}

int	ft_putptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += ft_puthex(ptr);
	return (count);
}

int	ft_putnbr(int nbr)
{
	long	num;
	int		count;

	num = nbr;
	count = 0;
	if (num < 0)
	{
		count += ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		count += ft_putnbr(num / 10);
	count += ft_putchar((num % 10) + '0');
	return (count);
}

int	ft_putunbr(unsigned int nbr)
{
	int		count;

	count = 0;
	if (nbr >= 10)
		count += ft_putnbr(nbr / 10);
	count += ft_putchar((nbr % 10) + '0');
	return (count);
}

int	vft_printf(const char *fmt, va_list ap)
{
	int	count;

	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 'c')
				count += ft_putchar(va_arg(ap, int));
			else if (*fmt == 's')
				count += ft_putstr(va_arg(ap, char *));
			else if (*fmt == 'p')
				count += ft_putptr(va_arg(ap, unsigned long));
			else if (*fmt == 'd' || *fmt == 'i')
				count += ft_putnbr(va_arg(ap, int));
			else if (*fmt == 'u')
				count += ft_putunbr(va_arg(ap, int));
			else if (*fmt == 'x')
				count += ft_puthex(va_arg(ap, unsigned int));
			else if (*fmt == 'X')
				count += ft_putupperhex(va_arg(ap, unsigned int));
			else if (*fmt == '%')
				count += ft_putchar('%');
			else
				count += ft_putchar(*fmt);
		}
		else
		{
			write(1, fmt, 1);
			count++;
		}
		fmt++;
	}
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, fmt);
	count = vft_printf(fmt, ap);
	va_end(ap);
	return (count);
}
