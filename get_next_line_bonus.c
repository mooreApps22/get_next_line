/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:36:15 by smoore            #+#    #+#             */
/*   Updated: 2024/01/11 17:34:01 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	push_new_tail(t_list **head, char *str, size_t len, int fd)
{
	t_list	*new;
	t_list	*current;

	new = malloc(sizeof(t_list));
	new->len = len;
	new->str = str;
	new->str[len] = '\0';
	new->next = NULL;
	if (!new)
		return ;
	if (head[fd] == NULL)
	{
		head[fd] = new;
		return ;
	}
	current = head[fd];
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	examine_buf(t_list	**head, char *buf, int fd)
{
	size_t	start;
	size_t	len;

	start = 0;
	while (buf[start] != '\0')
	{
		len = 0;
		if (buf[start + len] == '\n')
			len++;
		else
		{
			while (buf[start + len] != '\n' && buf[start + len] != '\0')
				len++;
			if (buf[start + len] == '\n')
				len++;
		}
		push_new_tail(head, ft_substr(buf, start, len), len, fd);
		start = start + len;
	}
}

void	read_file(t_list **head, int fd)
{
	ssize_t		nbytes;
	char		*buf;

	while (!has_newline(head[fd]))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (!nbytes || nbytes == -1)
		{
			free(buf);
			return ;
		}
		buf[nbytes] = '\0';
		examine_buf(head, buf, fd);
		free(buf);
	}
}

char	*make_line(t_list **head)
{
	char		*next_ln;
	size_t		len;
	size_t		i;
	int			j;

	if (*head == NULL)
		return (NULL);
	len = len_of_newline(*head);
	next_ln = malloc(len + 1);
	if (!next_ln)
		return (NULL);
	i = 0;
	while (i < len)
	{
		j = 0;
		while ((*head)->str[j] != '\0')
			next_ln[i++] = (*head)->str[j++];
		pop_head(head);
	}
	next_ln[i] = '\0';
	return (next_ln);
}

char	*get_next_line(int fd)
{
	static t_list	*head[4096];
	char			*next_ln;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!head[fd])
		head[fd] = NULL;
	read_file(head, fd);
	next_ln = make_line(&head[fd]);
	return (next_ln);
}
/*
int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*str;
	int		i;

	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
		return (1);
	i = 0;
	while (i < 10)
	{
		str = get_next_line(fd1);
		printf("%s", str);
		free(str);
		str = get_next_line(fd2);
		printf("%s", str);
		free(str);
		str = get_next_line(fd3);
		printf("%s", str);
		free(str);
		i++;
	}
	return (0);
}*/
