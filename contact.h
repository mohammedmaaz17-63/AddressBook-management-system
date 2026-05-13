#include<stdio.h>
#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;//Now my name of the datatype is contact not struct contact

typedef struct {
    Contact contacts[MAX_CONTACTS];//It is an array, where i am going to store the information, Contact is a datatype
    int contactCount;
} AddressBook;//Now my name of the datatype is Addressbook not struct Addressbook

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
