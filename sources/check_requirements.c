/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_requirements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:03 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/05 15:01:05 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static int		no_args(int ac)
{
	if (ac < 2)
	{
		ft_putendl(HELP_STRING);
		return (1);
	}
	return (0);
}

int			check_requirements(int ac)
{
	if (getuid() != 0)
		return (e_error_notroot);
	if (no_args(ac))
		return (e_error_opt_no_args);
	return (e_error_none);
} 

	