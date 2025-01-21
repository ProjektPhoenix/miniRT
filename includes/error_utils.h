/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpriess <rpriess@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:35:19 by rpriess           #+#    #+#             */
/*   Updated: 2025/01/21 19:37:35 by rpriess          ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef ERROR_H
# define ERROR_H

int		error_return(char *mssg);
int		error_exit(char *mssg);
int		error_exit_status(char *mssg, int status);
int		perror_exit(char *mssg);

#endif