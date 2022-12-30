#ifndef MINISHELL_H
#define MINISHELL_H

#define PIPE 0
#define INF 1
#define SUP 2
#define ADD 3
#define HERDOC 4
#define CMD 5
#define SQUOT 6
#define DQUOT 7
 
#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct s_env
{
    char *value;
    char *name;
    struct s_env *next;
}   t_env;

typedef struct element {
    int type;
    int space;
    int nbr_args;
    char **args;
    char *cmd;
    int pip[2];
    struct element *next;
    struct element *prev;
}   t_element;

t_element *tokeniser(char *line);
t_element *parser(char *line);
t_element *last(t_element *s);
int grammar(t_element *s);
char *add(char **str, char *s);
t_element *norm_one(t_element *el);
void expender(t_element *s, char **env);
void delete_quote(t_element *s);
void    printferror(char *str);
int     check_is_digit(int x);
int     check_special_caract(char *arg);
t_env   *identique_var(char  *arg, t_env **variable);
void    unset(t_env **variable ,t_element *command);
void    pwd(void);
void    ft_exit(t_element *command);
long    check_exit_status(char *str);
void    export(t_env **env, t_element *command);
void    display_env(t_env **envt);
int	    check_builtings(t_element *command);
void	is_builting(t_element *cmd, t_env **envv);
void    echo(char **arg);
void    print_echoarg(char **arg);
int     check_echo_n(char *arg);
void    cd(t_element *command, t_env **env);
void    checkhome(t_env *pwd, t_env *oldpwd, t_env **env);
void	refresh_oldpwd(t_env	**env, t_env *pwd);
t_env	*finder_getter(t_env	*env, char *name);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *receive_name(char *allstr);
char    *receive_name_export(char *allstr);
char    *receive_value(char *allstr);
t_env	*ft_lstnew(char *allstr, int flag);
void	ft_lstadd_back(t_env *new, t_env **alst);
t_env   *build_env(char **env);
void	refresh_pwd(t_env **env);
void	ft_lstadd_back(t_env *new, t_env **alst);
void    env_initialisation(t_env **env);
char    *receive_value_export(char *allstr);
t_env	*env_finder(t_env	*env, char *name);
void	printf_env(t_env **env);
int     check_plus(char *str, char c, char x);
int     check_caract(char *str, char c);
void    handle_pipe(t_element *node, t_env **env);
void	check_arg(t_element *command);
void    ft_env2(t_env *env, t_element *command);
void    ft_remove_from_env(t_env **begin_list, t_env *data_ref);
t_env   *env_finder(t_env	*env, char *name);
t_env    *exportnameonly(t_element *command);
void    execve_cmd(t_element *command, t_env **env, char **argv);
char    *join_get_acces(char **splited_path, char *cmd);
int     check_accecs_exec(char *joined_path);
char    **convertto_doublep(t_env *env);
int	    ft_lstsize_env(t_env *lst);
char    *convertto_char(t_env *env);
char	*ft_concatenate(const char *s1, const char *s2, const char *s3);
void    check_cmd(t_element *command, t_env **envv);
int	    ft_isdigit(int x);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_lstsize_elem(t_element *lst);
int getsize(char **str);
#endif