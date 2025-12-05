#include "ingredient.h"

t_range *add_range(t_range *head, const char *line)
{
    long long lower, upper;
    if (sscanf(line, "%lld-%lld", &lower, &upper) != 2)
            return head;

    t_range *new_node = malloc(sizeof(t_range));
    if (!new_node)
        return head;

    new_node->lower = lower;
    new_node->upper = upper;
    new_node->next = NULL;

    if (!head)
        return new_node;

    t_range *current = head;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return head;
}

void free_range(t_range *head)
{
    t_range *current;
    while (head != NULL)
    {
        current = head;
        head = head->next;
        free(current);
    }
}

