#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct details {
    char first_name[100];
    char last_name[100];
    int booking_date;
    struct details* next;
} details;
details* creatNode(char* first_name, char* last_name, int booking_date) {
    details* newNode = (details*)malloc(sizeof(details));
    strcpy(newNode->first_name, first_name);
    strcpy(newNode->last_name, last_name);
    newNode->booking_date = booking_date;
    newNode->next = NULL;
    return newNode;
}
void insert(details** head, char* first_name, char* last_name, int booking_date) {
    details* newNode = creatNode(first_name, last_name, booking_date);
    if (*head == NULL || (*head)->booking_date > booking_date) {
        newNode->next = *head;
        *head = newNode;
    } else {
        details* current = *head;
        while (current->next != NULL && current->next->booking_date < booking_date) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}
void print(details* head, char* list) {
    printf("%s:\n", list);
    details* temp = head;
    while (temp != NULL) {
        printf("%d %s %s\n", temp->booking_date, temp->first_name, temp->last_name);
        temp = temp->next;
    }
}

void delete(details** head, char* first_name, char* last_name) {
    details* temp = *head;
    details* prev = NULL;

    if (temp != NULL && strcmp(temp->first_name, first_name) == 0 && strcmp(temp->last_name, last_name) == 0) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL) {
        if (strcmp(temp->first_name, first_name) == 0 && strcmp(temp->last_name, last_name) == 0) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void moveList(details** trip, details** waitList) {
    if (*waitList != NULL) {
        details* moveNode = *waitList;
        *waitList = (*waitList)->next;
        moveNode->next = NULL;   
        insert(trip, moveNode->first_name, moveNode->last_name, moveNode->booking_date);
        free(moveNode);
    }
}

int main() {
    details* trip = NULL;
    details* booking = NULL;
    details* waitlist = NULL;
    int n;

    FILE* file = fopen("EASYTRIP.txt", "r");
    if (!file) {
        perror(" not able to  open the file");
        return 1;
    }

    fscanf(file, "%d", &n);

    int op_code, booking_date;
    char first_name[100], last_name[100];
    while (fscanf(file, "%d", &op_code) != EOF) {
        switch (op_code) {
        case 1:
            fscanf(file, "%s %s %d", first_name, last_name, &booking_date);
            insert(&booking, first_name, last_name, booking_date);
            if (n > 0) {
                insert(&trip, first_name, last_name, booking_date);
                n--;
            } else {
                insert(&waitlist, first_name, last_name, booking_date);
            }
            break;
        case 2:
            fscanf(file, "%s %s", first_name, last_name);
            delete(&booking, first_name, last_name);
            delete(&trip, first_name, last_name);
            delete(&waitlist, first_name, last_name);
            moveList(&trip, &waitlist);
            break;
        case 3:
            print(booking, "BOOKING");
            break;
        case 4:
            print(trip, "TRIP");
            break;
        case 8:
            print(waitlist, "WAITLIST");
            break;
        default:
            break;
        }
    }

    fclose(file);
    return 0;
}
