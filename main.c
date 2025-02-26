#include <stdio.h>
#include "contact.h"

void displayMenu()
{
    printf("\nAddress Book Menu:\n");
    printf("1. Add a contact\n");
    printf("2. Search for a contact\n");
    printf("3. Edit a contact\n");
    printf("4. Delete a contact\n");
    printf("5. List all contacts\n");
    printf("6. Save contacts to file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main()
{
    AddressBook addressBook;

    initialize(&addressBook);
    loadContacts(&addressBook);

    int choice;
    while (1)
    {
        displayMenu();
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            printf("Contacts:\n");
            listContacts(&addressBook);
            break;
        case 6:
            saveContacts(&addressBook);
            break;
        case 7:
            printf("Exiting program.\n");
            saveContacts(&addressBook);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
