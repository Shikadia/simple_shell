#ifndef SHELL_H
#define SHELL_H

/*
 * File: shell.h
 * Desc: This file contains prototypes for all the functions & struct
 *	 required for the project - (0x16. C - Simple Shell)
 * Auth: Chinedu .I. Otuka
 */

/* Macro definition for EXIT & EOF markers */
#define EXIT -3
#define _EOF -1

/* Standard C Library Headers */
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* External Variable Declaration */
extern char **environ;
/* Global program name */
char *name;
/* Global command history counter */
int cmdhistory;

/**
 * struct lnkd_lst - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct lnkd_lst
{
	char *dir;
	struct lnkd_lst *next;
} lnkd_lst;

/**
 * struct bultns - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @fpt: A function pointer to the builtin command's function.
 */
typedef struct bultns
{
	char *name;
	int (*fpt)(char **argv, char **first);
} bultns;

/* Function Prototypes */

void _setlineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *path_locator(char *command);
lnkd_lst *get_path(char *path);
int execute(char **args, char **first);
void free_list(lnkd_lst *head);
char *_itoa(int);
void split_line(char **line, ssize_t len);
char *env_value(char *var, int len);
void replace_var(char **args, int *ret);
char *get_args(char *line, int *ret);
int call_args(char **args, char **arg0, int *ret);
int run_args(char **args, char **arg0, int *ret);
int handle_args(int *ret);
int check_args(char **args);
void free_args(char **args, char **arg0);
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *str, char c);
int _strspn(char *str, char *prefix);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
int (*checkbuiltin(char *cmd))(char **, char **);
int shellexit(char **, char **);
void free_args(char **args, char **arg0);
int print_env(char **args, char __attribute__((__unused__)) **arg0);
int set_env(char **args, char __attribute__((__unused__)) **arg0);
int unset_env(char **args, char __attribute__((__unused__)) **arg0);
int _cd(char **args, char __attribute__((__unused__)) **arg0);
char **_envcopy(void);
void free_env(void);
char **_getenv(const char *var);
int _error(char **, int);
char *env_error(char **);
char *exit_error(char **);
char *cd_error(char **);
char *syntax_error(char **);
char *error126(char **);
char *error127(char **);
lnkd_lst *add_endnode(lnkd_lst **head, char *path);
void free_list(lnkd_lst *head);
ssize_t newLen(char *line);
void logical_ops(char *line, ssize_t *new_len);
int len_int(int n);
int run_commands(char *path, int *ret);
void handle_sig(int sig __attribute__((unused)));
char *path_populator(char *cmd);
lnkd_lst *retrive_path(char *path);
char *env_value(char *var, int len);
#endif
