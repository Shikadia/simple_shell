#include "shell.h"

/**
 * add_endnode - Adds a node to the end of a  linked list.
 * @head: A pointer to the head of the  list
 * @path: The directory path for the new node
 *
 * Return: Returns (endnode) on SUCCESS and (NULL) on FAILURE
 */
lnkd_lst *add_endnode(lnkd_lst **head, char *path)
{
	lnkd_lst *tmp;
	lnkd_lst *endnode;

	endnode = malloc(sizeof(*endnode));
	if (!endnode)
		return (NULL);

	endnode->dir = path;
	endnode->next = NULL;

	if (*head)
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = endnode;
	}
	else
		*head = endnode;

	return (endnode);
}

/**
 * free_list - Frees a list_path linked list
 * @head: The head of the list_path list
 */
void free_list(lnkd_lst *head)
{
	lnkd_lst *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
