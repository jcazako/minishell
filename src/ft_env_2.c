/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcazako <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 12:21:42 by jcazako           #+#    #+#             */
/*   Updated: 2016/06/11 15:39:42 by jcazako          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_linkcpy(char *unset, t_list **env_c)
{
	t_list	*tmp;
	t_list	*box;
	int		len;

	len = ft_strlen(unset);
	tmp = *env_c;
	if (ft_strnstr(((t_shell*)(tmp->content))->str, unset, len))
	{
		tmp = *env_c;
		*env_c = (*env_c)->next;
		freed(&tmp);
		return ;
	}
	while (tmp->next)
	{
		if (ft_strnstr(((t_shell*)(tmp->next->content))->str, unset, len))
		{
			box = tmp->next;
			tmp->next = tmp->next->next;
			freed(&box);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	start_unset(char **str)
{
	(*str)++;
	while (**str && ft_check_charset(**str, " \t\n"))
		(*str)++;
}

void		unset_ft_env(char **str, t_list **env_c)
{
	char	*tmp;
	int		i;
	char	*unset;

	i = 0;
	unset = NULL;
	start_unset(str);
	tmp = *str;
	while (tmp[i] && !ft_check_charset(tmp[i], " \t\n"))
		i++;
	if (!(tmp = ft_strsub(*str, 0, i)))
		return ;
	if (check_arg(tmp))
	{
		unsetenv_format();
		free(tmp);
		return ;
	}
	if (!(unset = ft_strjoin(tmp, "=")))
		return ;
	free(tmp);
	if (*env_c)
		del_linkcpy(unset, env_c);
	free(unset);
	(*str) += i;
}
