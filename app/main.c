/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseobk <minseobk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 14:27:32 by minseobk          #+#    #+#             */
/*   Updated: 2026/07/16 15:09:12 by minseobk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	char	*input;

	(void)argc;
	(void)argv;
	ctx_init(&ctx, envp);
	input = prompt(&ctx);
	printf("your input is: %s\n", input);
	ctx_clear(&ctx);
	return (0);
}
