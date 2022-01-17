//
// Created by Tadeusz Kondracki on 1/17/22.
//

#include <stdio.h>

int	ft_perror(char *err_msg)
{
	perror(err_msg);
	return (1);
}
