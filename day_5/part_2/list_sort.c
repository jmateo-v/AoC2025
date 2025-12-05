#include "ingredient.h"

t_range *sorted_merge(t_range *a, t_range *b)
{
    if (!a)
        return b;
    if (!b)
        return a;

    t_range *result = NULL;

    if (a->lower <= b->lower)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

void split_list(t_range *source, t_range **front, t_range **back)
{
    t_range *slow = source;
    t_range *fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void sort_ranges(t_range **head_ref)
{
    t_range *head = *head_ref;
    if (!head || !head->next)
        return;

    t_range *a;
    t_range *b;

    split_list(head, &a, &b);
    sort_ranges(&a);
    sort_ranges(&b);
    *head_ref = sorted_merge(a, b);
}
