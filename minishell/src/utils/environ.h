#ifndef ENVIRON_H
# define ENVIRON_H

#include <libft.h>

t_list	*get_env(t_list **env, char *name);

char	*get_env_content(t_list **env, char *name);

#endif //ENVIRON_H
