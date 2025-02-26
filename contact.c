#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
}

int isValidName(const char *name)
{
    return strlen(name) > 0;
}

int isValidPhone(const char *phone)
{
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }
    return strlen(phone) == 10;
}

int isValidEmail(const char *email)
{
    return strchr(email, '@') != NULL && strlen(email) > 0;
}

int isUniqueField(AddressBook *addressBook, const char *field, const char *value, int ignoreIndex)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == ignoreIndex)
            continue;
        if (strcmp(field, "name") == 0 && strcmp(addressBook->contacts[i].name, value) == 0)
        {
            return 0;
        }
        if (strcmp(field, "phone") == 0 && strcmp(addressBook->contacts[i].phone, value) == 0)
        {
            return 0;
        }
        if (strcmp(field, "email") == 0 && strcmp(addressBook->contacts[i].email, value) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= 100)
    {
        printf("Address book is full.\n");
        return;
    }
    Contact newContact;

    do
    {
        printf("Enter name: ");
        scanf("%s", newContact.name);
        if (!isValidName(newContact.name) || !isUniqueField(addressBook, "name", newContact.name, -1))
        {
            printf("Invalid or duplicate name. Try again.\n");
        }
    } while (!isValidName(newContact.name) || !isUniqueField(addressBook, "name", newContact.name, -1));

    do
    {
        printf("Enter phone: ");
        scanf("%s", newContact.phone);
        if (!isValidPhone(newContact.phone) || !isUniqueField(addressBook, "phone", newContact.phone, -1))
        {
            printf("Invalid or duplicate phone number. Try again.\n");
        }
    } while (!isValidPhone(newContact.phone) || !isUniqueField(addressBook, "phone", newContact.phone, -1));

    do
    {
        printf("Enter email: ");
        scanf("%s", newContact.email);
        if (!isValidEmail(newContact.email) || !isUniqueField(addressBook, "email", newContact.email, -1))
        {
            printf("Invalid or duplicate email. Try again.\n");
        }
    } while (!isValidEmail(newContact.email) || !isUniqueField(addressBook, "email", newContact.email, -1));

    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added successfully. Remember to save your changes if you wish to persist them.\n");
}

void searchContact(AddressBook *addressBook)
{
    char name[50];
    printf("Enter name to search: ");
    scanf("%s", name);
    printf("\n");

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].name, name))
        {
            printf("Name: %s, Phone: %s, Email: %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }
}

void editContact(AddressBook *addressBook) {
    char name[50];
    printf("Enter name to edit: ");
    scanf("%s", name);
    printf("\n"); 

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            printf("Editing contact %s\n", name);

            do {
                printf("Enter new name (or press Enter to skip): ");
                char newName[50];
                scanf("%s", newName);
                if (strlen(newName) > 0 && isValidName(newName) && isUniqueField(addressBook, "name", newName, i)) {
                    strcpy(addressBook->contacts[i].name, newName);
                } else if (strlen(newName) > 0) {
                    printf("Invalid or duplicate name. Keeping current name.\n");
                }
            } while (0);

            do {
                printf("Enter new phone: ");
                scanf("%s", addressBook->contacts[i].phone);
            } while (!isValidPhone(addressBook->contacts[i].phone));

            do {
                printf("Enter new email: ");
                scanf("%s", addressBook->contacts[i].email);
            } while (!isValidEmail(addressBook->contacts[i].email));

            saveContacts(addressBook); 
            printf("\nContact updated successfully.\n"); 
            return;
        }
    }
    printf("\nContact not found.\n"); 
}


void deleteContact(AddressBook *addressBook)
{
    char name[50];
    printf("Enter name to delete: ");
    scanf("%s", name);
    printf("\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            saveContacts(addressBook); 
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void saveContacts(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "w");
    if (!file) {
        printf("Error saving contacts to file.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully.\n");
}

void loadContacts(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "r");
    if (!file) {
        printf("No existing contacts found.\n");
        return;
    }

    addressBook->contactCount = 0;

    char line[150]; 
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (name && phone && email) {
            strcpy(addressBook->contacts[addressBook->contactCount].name, name);
            strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
            strcpy(addressBook->contacts[addressBook->contactCount].email, email);
            addressBook->contactCount++;
        }
    }

    fclose(file);
    printf("Contacts loaded successfully.\n");
}
