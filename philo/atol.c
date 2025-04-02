/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazmoud <lazmoud@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:30:40 by lazmoud           #+#    #+#             */
/*   Updated: 2025/04/01 11:24:38 by lazmoud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <philo.h>

static int	find_sym(char sym, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (sym == base[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_derive_sign(char c, int *index)
{
	if (c == '-')
	{
		(*index)++;
		return (-1);
	}
	if (c == '+')
		(*index)++;
	return (1);
}

static int	fetch_digit(char digit, t_num *num)
{
	int	sym_i;
	int	blen;

	blen = ft_strlen((char *)num->base);
	sym_i = find_sym(digit, num->base);
	if (sym_i != -1)
	{
		if (((*num->number * blen) + sym_i) < 0)
			return (OVER_FLOW_DETECTED);
		*num->number = (*num->number * blen) + sym_i;
		return (SUCCESS);
	}
	return (DONE);
}

int	atol_loop(const char *str, int index, t_num *num)
{
	int	res;

	res = SUCCESS;
	*(num->number) = 0;
	while (res == SUCCESS)
	{
		res = fetch_digit(str[index], num);
		if (res == OVER_FLOW_DETECTED)
			return (OVER_FLOW_DETECTED);
		index++;
	}
	*num->number = (num->sign * (*num->number));
	return (SUCCESS);
}

t_result	ft_atol_base(const char *str, const char *base, long *where)
{
	t_num	num;
	int		index;
	int		tmp;

	if (!str)
		return (NAN);
	index = 0;
	num.sign = ft_derive_sign(str[index], &index);
	tmp = index;
	num.base = base;
	*where = 0;
	num.number = where;
	while (str[index] && find_sym(str[index], base) >= 0)
		index++;
	if ((str[index] && (find_sym(str[index], num.base) == -1)) || !index)
	{
		*(num.number) = 0;
		return (NAN);
	}
	return (atol_loop(str, tmp, &num));
}
