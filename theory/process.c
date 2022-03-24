/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyubongchoi <kyubongchoi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:33:46 by kyubongchoi       #+#    #+#             */
/*   Updated: 2022/03/24 12:01:14 by kyubongchoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main()
{
	int pid;
	int status;
	printf("(before)one (pid:%d ppid:%d)\n", getpid(), getppid());
	pid = fork();
	if (pid == 0)
		printf("(child)two (pid:%d ppid:%d)\n", getpid(), getppid());
	else
	{
		// waitpid(-1, &status, 0);
		printf("(parent)two (pid:%d ppid:%d)\n", getpid(), getppid());

	}

	// (before)one (pid:2107 ppid:76056)
	// (child)two (pid:2108 ppid:2107)
	// (parent)two (pid:2107 ppid:76056)

	return (0);
}
