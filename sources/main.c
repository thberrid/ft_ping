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
#include <ft_ping_parser.h>

t_pingdata	*g_pingu;

int 		main(int ac, char **av)
{
	t_options	options;
	int			retrn;

	retrn = check_requirements(ac);
	if (retrn == e_error_none)
		retrn = parsing(ac, av, &options);
	signal(SIGALRM, ping_send);
	signal(SIGINT, sig_int);
	retrn = ping_prepare(options);
	if (retrn == e_error_none)
	{
		ping_print_intro(options);
		ping_send(SIGALRM);
	}
	print_return_code(retrn);
	return (retrn);
}
