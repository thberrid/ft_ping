/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:24:00 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 11:24:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <libft.h>
# include <ft_ping_errors.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netdb.h>

# define HELP_STRING "Usage: ft_ping [-v] [-c count] destination"

typedef struct	s_options
{
	char		help_required;
	char		verbose_required;
	int			count;
	int			ttl;
	char		*address;
}				t_options;

int				ping_loop(t_options *options);

int 			ping_prepare(int *sockfd, struct addrinfo **addrinfo, t_options *options);
unsigned short	checksum(void *data, int len);

#endif
