/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:44:51 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/11 14:10:37 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
int main()
{
	int pid;
	pid = fork();
	if(pid ==0)
	{
		printf("[Child] : Hello, world pid=%d\n",getpid());
		exit(0);
	}
	else
	{
		printf("[Parent] : Hello, world pid=%d\n",getpid());
		exit(0);
	}

	//output called : [Parent] -> [Child]
	//[Parent] : Hello, world pid=72176
	//[Child] : Hello, world pid=72192
}
