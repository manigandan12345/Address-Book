#ifndef CONTACT_H
#define CONTACT_H

typedef struct
{
    char name[50];
    char phone[15];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[100];
    int contactCount;
} AddressBook;

void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void saveContacts(AddressBook *addressBook);
void loadContacts(AddressBook *addressBook);

#endif
