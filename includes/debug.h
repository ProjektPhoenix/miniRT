/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 21:30:00 by rpriess           #+#    #+#             */
/*   Updated: 2024/11/06 21:38:50 by rpriess          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>

/*
Debug macro to print debug messages. In the code instead of printf(), debug()
can be used which prints to stderr with additional debug information. Otherwise
it is used exactly like printf(). Files in which debug() is used need to have the
debug.h header included.
When "NDEBUG" is provided as a flag during compilation (on command line or
through Makefile) as -NDEBUG (or -DNDEBUG !?), the debug macro is replaced with an empty
macro. As messages are printed to stderr they can easily be redirected together, e.g.
./miniRT 2> error_log.txt

For submission we will remove the debug macro from the code
including the macro below which is not allowed by norminette.
*/
# ifdef NDEBUG
# define debug(M, ...)
# else
# define debug(M, ...) fprintf(stderr, "\033[0;92mDEBUG %s:%s:%d: " M "\033[0m\n",\
        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
# endif

#endif
