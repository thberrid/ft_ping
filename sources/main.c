/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:23:46 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 11:23:49 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

t_pingdata	g_pingu;

int 		main(int ac, char **av)
{
	t_options	options;
	int			retrn;

	retrn = check_requirements(ac);
	ft_bzero(&g_pingu, sizeof(t_pingdata));
	if (retrn == e_error_none)
		retrn = ping_prepare(ac, av, &options);
	if (retrn == e_error_none)
		ping();
	print_return_code(retrn);
	return (retrn);
}
