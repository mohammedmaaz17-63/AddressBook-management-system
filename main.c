/*
Documentation:

Name: Mohammed Maaz
Reg No : 25031A_114
Start Date : 09/12/25

Description of project:

📒 Address Book in C

A Address Book application written in C that allows users to create, search, list, edit, and delete contacts.
The project also allows the user to save contacts in .csv file and reloads the previous saved work whenever user re-start the application.
Advantages of digital address book over manual addressbook: 
Manual addressbook are inefficient and difficult to maintain
If physical book is damaged or lost, it means the permanent data loss, so we are using digital address book
It is easy to search, edit and manage large contact list using digital address book
The digital address book is simple, relaible and portable solution to overcome the problems of physical address book
This project demonstrates core concepts of the C programming language such as structures, file handling, pointers, arrays, string manipulation, and modular programming.

*/

#include <stdio.h>
#include "contact.h"
void print_line()
{
    for(int i=1;i<22;i++)
    {
        printf("-");
    }
    printf("\n");
}
int main() 
{
    int choice;
    AddressBook addressBook;//addressBook is a variable name, and AddressBook is a datatype
    // addressBook.contactCount=0;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\nAddress Book Menu:\n");
        print_line();
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("7. Exit\n");
        print_line();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        print_line();
        
        
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
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                return 0;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);//It is more dependable than while(choice!=7), if we add any more operations in our menu
    
    return 0;
}
