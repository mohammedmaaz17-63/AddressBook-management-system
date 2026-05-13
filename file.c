#include <stdio.h>
#include "file.h"
#include<string.h>
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

//My logic to load contacts from file
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE*fptr = fopen("file.csv","r");
    if(fptr==NULL)
    {
        printf(RED "The file doesn't exist in the current folder\n" RESET);
        return;
    }
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    if (addressBook->contactCount > MAX_CONTACTS)
    {
        addressBook->contactCount = MAX_CONTACTS;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr," %[^,], %[^,], %[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);

}

//My logic to Save contact to the file
void saveContactsToFile(AddressBook*addressBook)
{
    FILE*fptr=fopen("file.csv","w");
    if(fptr==NULL)
    {
        printf(RED "The file doesn't exist in the current folder\n" RESET);
        return;
    }
    fprintf(fptr,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s, %s, %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

//CREATING CONTACTS
//My logic to validate the name
int validate_name(char name_str[])
{
    int i=0;
    while(name_str[i]!='\0')
    {
        if((name_str[i]>='A' && name_str[i]<='Z')|| (name_str[i]>='a' && name_str[i]<='z') || name_str[i]=='.' || name_str[i]==' ')
        {
            i++;
            continue;//If this string element contains any one of these then i will skip this iteration and go to next iteration
        }
        else
        {
            printf(RED "Enter the name properly\n" RESET);
            return 0;
        }
    }
    return 1;
    
}

//My logic to validate the phone number
int validate_phone(char phone_str[],AddressBook*addressBook)
{
    int i=0;
    int len=strlen(phone_str);
    while(phone_str[i]!='\0')
    {
        if(len==10 && (phone_str[i]>='0' && phone_str[i]<='9'))
        {
            i++;
            continue;//If this string element contains any one of these then i will skip this iteration and go to next iteration
        }
        else
        {
            printf(RED "Enter the phone number properly\n" RESET);
            return 0;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)//I am writing this to check if my phone number is unique
    {
        if(strcmp(addressBook->contacts[i].phone,phone_str)==0)
        {
            printf(YELLOW "This Phone No. is already taken, Enter a different Phone No.\n" RESET);
            return 0;
        }
    }
    
    return 1;

}

//My logic to validate the email
int validate_email(char email_str[],AddressBook*addressBook)
{
    int i=0;
    int flag=0;//To check if my email contain @
    int flag1=0;//To check if my email contain .com or .in
    while(email_str[i]!='\0')
    {
        if(email_str[i]=='@')
        {
            flag=1;
            i++;
            continue;//if this string element contains @, i will skip this iteration and go to next iteration
        }
        int len=strlen(email_str);
        if (len < 5)
        {
            printf(RED "Enter the email properly\n" RESET);
            return 0;
        }
        if(strcmp(email_str + len-4, ".com") == 0 || strcmp(email_str + len-3, ".in")==0)//It is to check if my email is ending with .com or .in
        {
            flag1=1;
            i++;
            continue;//if this string element contains .com or .in at the last, i will skip this iteration
        }
        if((email_str[0]>='a' && email_str[0]<='z') && ((email_str[i]>='a' && email_str[i]<='z') || (email_str[i]=='_') || (email_str[i]=='.') || (email_str[i]>='0' && email_str[i]<='9') || email_str[i]=='@'))
        {
            i++;
            continue;//If this string element contains any one of these then i will skip this iteration and go to next iteration
        }
        else//This else is only for the above if statement
        {
            printf(RED "Enter the email properly\n" RESET);
            return 0;
        }
        
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email_str)==0)
        {
            printf(YELLOW "This email is already taken, Enter a different email\n" RESET);
            return 0;
        }
    }
    if(flag==0)//It means my email doesn't contain @
    {
        printf(RED "Enter the email properly\n" RESET);
        return 0;
    }
    if(flag1==0)//It means my email doesn't contain .com or .in
    {
        printf(RED "Enter the email properly\n" RESET);
        return 0;
    }
    return 1;
}

//SEARCHING CONTACTS 
//My logic to search the contact by name
void search_by_name(AddressBook *addressBook)
{
    char my_name[100];
    Contact samenames[100];//I am creating with the datatype of Contact because i want to store name,phone,email and print all the three details
    printf(BLUE "Enter the Name : " RESET);
    scanf(" %[^\n]",my_name);
    int sim_contact=0;
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcasecmp(addressBook->contacts[i].name,my_name)==0)//If i get any matching name in my addressbook i will print all the details of that person
        {
            samenames[sim_contact]=addressBook->contacts[i];//Here i am storing all the similar contacts in the array
            sim_contact++;//I am incrementing this to find how many similar contacts are present
           
            printf("| %-4d  | %-15s | %-12s | %-25s  |\n",sim_contact, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
    }
    
    if(sim_contact==0)//I didn't find any matching name in my addressbook
    {
        printf(RED "No results found\n" RESET);
        return;
    }

    //If multiple matches are found
    if(sim_contact>1)
    {
        int contactChoice;
        do
        {
            printf(BLUE "Enter one of the above number to select a particular contact : " RESET);
            scanf("%d",&contactChoice);
            for(int i=0;i<sim_contact;i++)
            {
                if(contactChoice -1 == i)
                {
                    printf(CYAN "Your contact is : \n" RESET);
                    printf("----------------------------------------------------------------------\n");
                    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
                    printf("----------------------------------------------------------------------\n");

                    printf("| %-4d  | %-15s | %-12s | %-25s  |\n",contactChoice, samenames[i].name, samenames[i].phone, samenames[i].email);
                    printf("----------------------------------------------------------------------\n");
                }
            }
            
        } while (contactChoice>sim_contact);
        
    }
}

//My logic to search the contact by phone
void search_by_phone(AddressBook *addressBook)
{
    char my_phone[100];
    printf(BLUE "Enter the Phone No. : " RESET);
    scanf(" %[^\n]",my_phone);
    int ret=1;
    int flag=0;
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    int j=0;//To keep track of serial number 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        ret=strcmp(addressBook->contacts[i].phone,my_phone);//If i get any matching number in my addressbook i will print all the details of that person
        if(ret==0)//I found a matching number in my addressbook
        {
            flag=1;
            printf("| %-4d  | %-15s | %-12s | %-25s  |\n",++j, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
    }
    if(flag==0)//I didn't find any matching number
    {
        printf(RED "No results found\n" RESET);
        searchContact(addressBook);
    }
}

//My logic to search the contact by email
void search_by_email(AddressBook *addressBook)
{
    char my_email[100];
    printf(BLUE "Enter the email\n" RESET);
    scanf(" %[^\n]",my_email);
    int ret=1;
    int flag=0;
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    int j=0;//To keep track of serial number 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        ret=strcmp(addressBook->contacts[i].email,my_email);//If i get any matching email in my addressbook i will print all the details of that person
        if(ret==0)//I found a matching email in my addressbook
        {
            flag=1;
            printf("| %-4d  | %-15s | %-12s | %-25s  |\n",++j, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
    }
    if(flag==0)//I didn't find any matching email in my addressbook
    {
        printf(RED "No results found\n" RESET);
        return;
    }
}

//EDITING CONTACTS
//My logic to edit the name by Phone No.
void edit_by_PhoneNo(AddressBook*addressBook)
{
    char phone_str[50];
    printf(BLUE "Enter the phone number : " RESET);
    scanf(" %[^\n]",phone_str);
    int found=0;//To check if i found the contact in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone_str)==0)
        {
            found=1;
            char newname_str[100];
            do
            {
                printf(CYAN "Enter the new name : " RESET);
                scanf(" %[^\n]",newname_str);
            } while (validate_name(newname_str)==0);//Here if my name is invalid i will run the loop and ask for the user to enter the name again
            //If his name is valid i will proceed further
            strcpy(addressBook->contacts[i].name,newname_str);
            printf(GREEN "Your contact name has been edited successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid phone number\n" RESET);
    }
}

//My logic to edit the name by email
void edit_by_email(AddressBook*addressBook)
{
    char email_str[50];
    printf(BLUE "Enter the email : " RESET);
    scanf(" %[^\n]",email_str);
    int found=0;//To check if i found the email in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email_str)==0)
        {
            found=1;
            char newname_str[100];
            do
            {
                printf(CYAN "Enter the new name : " RESET);
                scanf(" %[^\n]",newname_str);
            } while (validate_name(newname_str)==0);//Here if my name is invalid i will run the loop and ask for the user to enter the name again
            //If his name is valid i will proceed further
            strcpy(addressBook->contacts[i].name,newname_str);
            printf(GREEN "Your contact name has been edited successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid email\n" RESET);
    }
}

//My logic to edit the name
void edit_name(AddressBook*addressBook)
{
    char name_str[50];
    printf(BLUE "Enter the Name from the address book that you want to edit : " RESET);
    scanf(" %[^\n]",name_str);
    int index=-1;//No contact found
    int count=0;//To check how many times i found the name in my addressbook
    int i=0;
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    int j=0;//To keep track of number of multiple contacts with same name
    for(i=0;i<addressBook->contactCount;i++)
    {   
        if(strcasecmp(addressBook->contacts[i].name,name_str)==0)
        {
            count++;
            index=i;//To store position
            printf("| %-4d  | %-15s | %-12s | %-25s  |\n",++j, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
    }
    if(count==1)
    {
        char newname_str[100];
        char name_str[50];
        do
        {
            printf(CYAN "Enter the new name : " RESET);
            scanf(" %[^\n]",newname_str);
        } while (validate_name(newname_str)==0);//Here if my name is invalid i will run the loop and ask for the user to enter the name again
        //If his name is valid i will proceed further
        strcpy(addressBook->contacts[index].name,newname_str);
        printf(GREEN "Your name has been edited successfully\n" RESET);
    }

    if(count>1)
    {
        printf(CYAN "Since there are many contacts with the same name\n" RESET);
        printf(CYAN "Select one of the below options to edit your name\n" RESET);
        printf("1. Edit using Phone number\n");
        printf("2. Edit using email\n");
        printf("3. Exit\n");
        int option;
        printf(BLUE "Enter the option to edit your name " RESET);
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                edit_by_PhoneNo(addressBook);
                break;

            case 2:
                edit_by_email(addressBook);
                break;

            case 3:
                break;

            default:
                printf(RED "Enter a valid option\n" RESET);
        }
    }
    
    if(count==0)
    {
        printf(RED "Enter a valid or existing name\n" RESET);
    }
}

//My logic to edit the Phone No.
void edit_PhoneNo(AddressBook*addressBook)
{
    char phone_str[50];
    printf(BLUE "Enter the phone number from the address book that you want to edit: " RESET);
    scanf(" %[^\n]",phone_str);
    int found=0;//To check if i found the contact in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone_str)==0)
        {
            found=1;
            char ph_str[100];
            int duplicate;//To check if my new number already exist in the addressbook
            do
            {
                duplicate=0;
                char phone_str[50];
                do
                {
                    printf(CYAN "Enter the new number : " RESET);
                    scanf("  %[^\n]",ph_str);
                } while (validate_phone(ph_str,addressBook)==0);//Here if my phone number is invalid i will run the loop and ask for the user to enter the phone number again
                
                for(int j=0;j<addressBook->contactCount;j++)
                {
                    if(strcmp(addressBook->contacts[j].phone,ph_str)==0)
                    {
                        duplicate = 1;
                        printf(YELLOW "This number is already taken, Enter a different number\n" RESET);
                        break;
                    }
                }
            } while (duplicate==1);//I will prompt the user to enter the new number until he enters a unique number
            
            //If he enters a unique number then
            strcpy(addressBook->contacts[i].phone,ph_str);//I will copy my new number into addressbook and store it in the place of old number
            printf(GREEN "Your Phone No. has been edited successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid phone number\n" RESET);
    }
}

//My logic to edit the email
void edit_email(AddressBook*addressBook)
{
    char email_str[50];
    printf(BLUE "Enter the email from the address book that you want to edit: " RESET);
    scanf(" %[^\n]",email_str);
    int found=0;//To check if i found the contact in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email_str)==0)
        {
            found=1;
            char em_str[100];
            int duplicate;//To check if my new mail already exists in the addressbook
            do
            {
                duplicate=0;
                do
                {
                    printf(CYAN "Enter the new email : " RESET);
                    scanf(" %[^\n]",em_str);
                } while (validate_email(em_str,addressBook)==0);//Here if my email is invalid i will run the loop and ask for the user to enter the email again
                
                for(int j=0;j<addressBook->contactCount;j++)
                {
                    if(strcmp(addressBook->contacts[j].email,em_str)==0)
                    {
                        printf(YELLOW "This email is already taken, Enter a different email\n" RESET);
                        duplicate=1;
                        break;
                    }
                }
            } while (duplicate==1);//I will promp the user to enter a new email until he enters a unique email           
            //If he enters a unique mail
            strcpy(addressBook->contacts[i].email,em_str);//I will copy my new mail into addressbook and store it in the place of old email
            printf(GREEN "Your email has been edited successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid email\n" RESET);
    }   
}

//DELETING CONTACTS
//My logic to delete contact by phone Number
void delete_by_PhoneNo(AddressBook*addressBook)
{
    char phone_str[50];
    printf(BLUE "Enter the phone number : " RESET);
    scanf(" %[^\n]",phone_str);
    int found=0;//To check if i found the contact in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone_str)==0)
        {
            found=1;
            int j=i;
            for(j=i;j<addressBook->contactCount-1;j++)
            {
                addressBook->contacts[j]=addressBook->contacts[j+1];//Here i will swap the next contact with the present contact to delete the contact 
            }
            addressBook->contactCount--;
           
            printf(GREEN "Your contact has deleted successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid phone number\n" RESET);
    }
}

//My logic to delete contact by email
void delete_by_email(AddressBook*addressBook)
{
    char email_str[50];
    printf(BLUE "Enter the email : " RESET);
    scanf(" %[^\n]",email_str);
    int found=0;//To check if i found the email in my addressbook
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email_str)==0)
        {
            found=1;
            int j=i;
            for(j=i;j<addressBook->contactCount-1;j++)
            {
                addressBook->contacts[j]=addressBook->contacts[j+1];//Here i will swap the next contact with the present contact to delete the contact 
            }
            addressBook->contactCount--;
           
            printf(GREEN "Your contact has deleted successfully\n" RESET);
            break;
        }
    }
    if(found==0)
    {
        printf(RED "Enter the valid email\n" RESET);
    }
}

//My logic to delete contact by name
void delete_by_name(AddressBook*addressBook)
{
    char name_str[50];
    printf(BLUE "Enter the Name : " RESET);
    scanf(" %[^\n]",name_str);
    int count=0;//To check how many times i found the name in my addressbook
    int index=-1;
    printf("----------------------------------------------------------------------\n");
    printf("| %-4s | %-15s | %-12s | %-25s  |\n","SI.No", "Name", "Phone", "Email");
    printf("----------------------------------------------------------------------\n");
    int j=0;//To keep track of number of multiple contacts with same name
    for(int i=0;i<addressBook->contactCount;i++)
    {   
        if(strcasecmp(addressBook->contacts[i].name,name_str)==0)
        {
            count++;
            index=i;//To store the position
            printf("| %-4d  | %-15s | %-12s | %-25s  |\n",++j, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            printf("----------------------------------------------------------------------\n");
        }
    }

    if(count>1)
    {
        printf(CYAN "Since there are many contacts with the same name\n" RESET);
        printf(CYAN "Enter one of the below options\n" RESET);
        printf("1. Delete by Phone number\n");
        printf("2. Delete by email\n");
        printf("3. Exit\n");
        printf(BLUE "Enter the option to delete your contact : " RESET);
        int option;
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                delete_by_PhoneNo(addressBook);
                break;

            case 2:
                delete_by_email(addressBook);
                break;

            case 3:
                break;

            default:
                printf(RED "Enter a valid option\n" RESET);
        }
    }

    if(count==1)
    {
        for(int j=index;j<addressBook->contactCount-1;j++)
        {
            addressBook->contacts[j]=addressBook->contacts[j+1];//Here i will swap the next contact with the present contact to delete the contact 
        }
        addressBook->contactCount--;
        printf(GREEN "Your contact has deleted successfully\n" RESET);
    }
    
    if(count==0)
    {
        printf(RED "Enter a valid or existing name\n" RESET);
    }
}