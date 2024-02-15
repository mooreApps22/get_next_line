/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:06:34 by smoore            #+#    #+#             */
/*   Updated: 2024/01/07 18:21:26 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char				*str;
	size_t				len;
	struct s_list		*next;
}						t_list;

void	str_copy(char *dest, const char *src, size_t n);
void	pop_head(t_list **head);
int		has_newline(t_list *head);
size_t	len_of_newline(t_list *head);
char	*ft_substr(char const *s, size_t start, size_t size);
char	*get_next_line(int fd);

#endif
