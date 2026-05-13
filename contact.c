#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// Text color macros
#define RESET   "\033[0m"
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

//My funtion to list contacts
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    if(addressBook->contactCount <= 1)
    {
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        return;
    }
    //To arrange my name of the contacts in the ascending order
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)//If my strings are equal strcmp will return 0 and no swapping will happen. if not equal then the value of strcmp will be greater than zero and swapping will take place  
            {
                Contact temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
    
    //To print the contacts
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    int j=0;//To keep track of serial number 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("| %-4d  | %-15s | %-12s | %-25s  |\n",++j, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);   
        printf("----------------------------------------------------------------------\n");
    }
}

//My function to initialize 
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

//My function to save and exit
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//My logic to validate the name
int validate_name(char name_str[]);
//My logic to validate the phone number
int validate_phone(char phone_str[],AddressBook*addressBook);
//My logic to validate the email
int validate_email(char email_str[],AddressBook*addressBook);
//My function to create contact
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    // Check if address book is full
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf(RED "Address book is full\n" RESET);
        return;
    }
    //Creating name
    char name_str[50];
    do
    {
        printf(BLUE "Enter your name : " RESET);
        scanf(" %[^\n]",name_str);
    } while (validate_name(name_str)==0);//Here if my name is invalid i will run the loop and ask for the user to enter the name again
    
    //Creating Phone No.
    char phone_str[50];
    do
    {
        printf(BLUE "Enter your Phone No. : " RESET);
        scanf(" %[^\n]",phone_str);
    } while (validate_phone(phone_str,addressBook)==0);//Here if my phone number is invalid i will run the loop and ask for the user to enter the phone number again

    //Creating email
    char email_str[50];
    do
    {
        printf(BLUE "Enter your email : " RESET);
        scanf(" %[^\n]",email_str);
    } while (validate_email(email_str,addressBook)==0);//Here if my email is invalid i will run the loop and ask for the user to enter the email again
    printf(GREEN "Contact created successfully\n" RESET);
    strcpy(addressBook->contacts[addressBook->contactCount].name,name_str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone_str);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email_str);
    addressBook->contactCount++;
}

//My logic to search the contact by name
void search_by_name(AddressBook *addressBook);
//My logic to search the contact by phone
void search_by_phone(AddressBook *addressBook);
//My logic to search the contact by email
void search_by_email(AddressBook *addressBook);
//My function to search contact
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf(CYAN "Search Contact Menu\n" RESET);
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("4. Exit\n");
    int option;
    printf(BLUE "Enter the option to search for your contact : " RESET);
    scanf("%d",&option);
    switch (option)
    {
    case 1:
        search_by_name(addressBook);
        break;
    
    case 2:
        search_by_phone(addressBook);
        break;

    case 3:
        search_by_email(addressBook);
        break;

    case 4:
        break;//I will go back and print the Address Book Menu
    default:
        printf(RED "Enter a valid option\n" RESET);
    }
}

//My logic to edit the name
void edit_name(AddressBook*addressBook);
//My logic to edit the Phone No.
void edit_PhoneNo(AddressBook*addressBook);
//My logic to edit the email
void edit_email(AddressBook*addressBook);
//My function to edit contact
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf(CYAN "Edit Contact Menu\n" RESET);
    printf("1. Edit Name\n");
    printf("2. Edit Phone No.\n");
    printf("3. Edit email\n");
    printf("4. Exit\n");
    int option;
    printf(BLUE"Enter the option to edit your contact : " RESET);
    scanf("%d",&option);
    switch(option)
    {
        case 1: 
            edit_name(addressBook);
            break;

        case 2: 
            edit_PhoneNo(addressBook);
            break;
         
        case 3: 
            edit_email(addressBook);
            break;

        case 4:
            break;

        default:
            printf(RED "Enter a valid option to edit\n" RESET);
    }
}

//My logic to delete contact by name
void delete_by_name(AddressBook*addressBook);
//My logic to delete contact by phone Number
void delete_by_PhoneNo(AddressBook*addressBook);
//My logic to delete contact by email
void delete_by_email(AddressBook*addressBook);
//My function to delete contact
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf(CYAN "Delete Contact Menu\n" RESET);
    printf("1. Delete by Name\n");
    printf("2. Delete by PhoneNo.\n");
    printf("3. Delete by email\n");
    printf("4. Exit\n");
    int option;
    printf(BLUE "Select one of the above choices : " RESET);
    scanf("%d",&option);
    switch(option)
    {
        case 1: 
            delete_by_name(addressBook);
            break;

        case 2: 
            delete_by_PhoneNo(addressBook);
            break;
         
        case 3: 
            delete_by_email(addressBook);
            break;

        case 4:
            break;

        default:
            printf(RED "Enter a valid option to edit\n" RESET);
    }
}