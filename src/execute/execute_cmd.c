/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguelangelortizdelburgo <miguelangelor    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:03:39 by dlerma-c          #+#    #+#             */
/*   Updated: 2025/01/17 16:56:53 by miguelangel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>

static void	make_last_command(t_info *info, t_lst *lst, char *com, t_env **env)
{
	pid_t	child;
	char	**cmd;	

	cmd = create_cmd(lst, info);
	info->np--;
	child = fork();
	if (child < 0 || info->pipe[info->np] == NULL)
		exit(EXIT_FAILURE);
	if (child == 0)
	{
		signal_son();
		check_redir(info, lst, 1);
		close(info->pipe[info->np][0]);
		close(info->pipe[info->np][1]);
		if (check_built(lst, info, env) != 1)
			if (execve(com, cmd, info->env) == -1)
				error_cmd(cmd[0]);
		exit(EXIT_FAILURE);
	}
	else
		norm_cmd_father(info, cmd);
	output_check(child, 1);
}

static void	make_command(t_info *info, t_lst *lst, char *com, t_env **env)
{
	pid_t	child;
	char	**cmd;

	cmd = create_cmd(lst, info);
	child = fork();
	if (child < 0 || info->pipe[info->np] == NULL)
		exit(EXIT_FAILURE);
	if (child == 0)
	{
		signal_son();
		norm_cmd_child(lst, info, com);
		close(info->pipe[info->np][0]);
		dup2(info->pipe[info->np][1], STDOUT_FILENO);
		close(info->pipe[info->np][1]);
		check_redir(info, lst, 1);
		if (check_built(lst, info, env) != 1)
			if (execve(com, cmd, info->env) == -1)
				error_cmd(cmd[0]);
		exit(EXIT_FAILURE);
	}
	else
		norm_cmd_father(info, cmd);
}

static void	make_one_command(t_info *info, t_lst *lst, char *com, t_env **env)
{
	pid_t	child;
	char	**cmd;

	(void)env;
	cmd = create_cmd(lst, info);
	child = fork();
	if (child < 0)
		exit(EXIT_FAILURE);
	if (child == 0)
	{
		signal_son();
		check_redir(info, lst, 1);
		if (com != NULL)
			if (execve(com, cmd, info->env) == -1)
				error_cmd(cmd[0]);
		exit(0);
	}
	else
	{
		wait(&child);
		output_check(child, 0);
		free(cmd);
	}
}

void	search_command(t_info *info, t_lst *lst, char *com, t_env **env)
{
	if (info->nlst == 1 || (info->ex < 0 && info->pos == info->nlst - 1))
	{
		if (lst->built == 1)
			check_redir(info, lst, 1);
		if (check_built(lst, info, env) == 0)
			make_one_command(info, lst, com, env);
	}
	else
	{
		info->pipe[info->np] = (int *)ft_calloc(2, sizeof(int));
		if (info->pipe[info->np] == NULL)
			exit(EXIT_FAILURE);
		pipe(info->pipe[info->np]);
		// (info->pos == 0 || info->pos != 0) 
		if (info->pos != info->nlst - 1)
			make_command(info, lst, com, env);
		else if (info->pos == info->nlst - 1)
			make_last_command(info, lst, com, env);
		info->np++;
	}
}
