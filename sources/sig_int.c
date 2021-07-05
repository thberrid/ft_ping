/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:44:51 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/05 19:45:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void		sig_int(int signum)
{
	ft_printf("\n\nsignum: %d\n\n", signum);
	ping_print_stats(addrinfo);
	exit(SIGINT);
}