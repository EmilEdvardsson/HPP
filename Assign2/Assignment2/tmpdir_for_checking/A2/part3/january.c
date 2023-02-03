#include <stdio.h>
#include <stdlib.h>

/* create struct for nodes */

struct day_temps {
    int day;
    float min_temp;
    float max_temp;
    struct day_temps *next;
};

void print_list(struct day_temps *head) {
    printf("day\tmin\t\tmax\n");
    while (head) {
        printf("%d\t%f\t%f\n", head->day, head->min_temp, head->max_temp);
        head = head->next;
    }
}

/* Function that adds nodes and always return root node */
struct day_temps *add_node(struct day_temps *head, int day, float min_temp, float max_temp) {
    struct day_temps *current = head;
    struct day_temps *prev = NULL;

    while (current && current->day < day) {
        prev = current;
        current = current->next;
    }

    if (current && current->day == day) {
        current->min_temp = min_temp;
        current->max_temp = max_temp;
    } else {
        struct day_temps *new_node = (struct day_temps *) malloc(sizeof(struct day_temps));
        new_node->day = day;
        new_node->min_temp = min_temp;
        new_node->max_temp = max_temp;
        new_node->next = current;

        if (prev) { //Check whether we are in the beginning of the list
            prev->next = new_node;
        } else {
            head = new_node;
        }
    }

    return head;
}

struct day_temps *delete_node(struct day_temps *head, int day) {
    struct day_temps *current = head;
    struct day_temps *prev = NULL;

    while (current && current->day < day) {
        prev = current;
        current = current->next;
    }
    if (!current || current->day != day) { //Day not in list.
        return head;
    }
    if (prev) {
        prev->next = current->next;
    } else {
        head = current->next;
    }
    free(current); //Free memory of node created in add_node func.

    return head;
}

int main() {
    char command;
    int day;
    float min_temp, max_temp;
    struct day_temps *head = NULL;

    /* keep taking more inputs until 'Q' is pressed */
    while (1) {
        printf("Enter command: ");
        scanf(" %c", &command);
        switch (command) {
            case 'A':
                scanf("%d%f%f", &day, &min_temp, &max_temp);
                head = add_node(head, day, min_temp, max_temp);
                break;
            case 'D':
                scanf("%d", &day);
                head = delete_node(head, day);
                break;
            case 'P':
                print_list(head);
                break;
            case 'Q':
                return 0;
            default:
                printf("Invalid command\n");
                break;
        }
    }
}
