/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Free the Database.
*/

#include"header.h"     

// Function to free the file list
void free_flist(Flist *head)
{
    while (head != NULL)        // Traverse the file list
    {
        Flist *temp = head;    // Store current node
        head = head -> link;   // Move to next node

        free(temp -> fname);   // Free file name memory
        free(temp);            // Free file list node
    }
}

// Function to free the sub node list
void free_sub_list(sub_node *head)
{
    while (head != NULL)              // Traverse sub node list
    {
        sub_node *temp = head;        // Store current sub node
        head = head -> sub_link;      // Move to next sub node

        free(temp->file_name);        // Free file name memory
        free(temp);                  // Free sub node
    }
}

// Function to free the main node list along with sub nodes
void free_main_list(main_node *head)
{
    while (head != NULL)              // Traverse main node list
    {
        main_node *temp = head;       // Store current main node
        head = head -> main_link;     // Move to next main node

        free(temp -> word);           // Free word memory
        free_sub_list(temp -> sub_link); // Free associated sub list
        free(temp);                   // Free main node
    }
}

// Function to free the entire database
void free_database(main_node *arr[27])
{
    for (int i = 0; i < 27; i++)       // Traverse hash table
    {
        if (arr[i] != NULL)           // Check if index has data
        {
            free_main_list(arr[i]);   // Free main list at index
            arr[i] = NULL;            // Set index to NULL
        }
    }
}

