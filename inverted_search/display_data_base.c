/*
	Name : Chandu M D
	Date : 22 dec 2025
	Description : Inverted Search project.
		      Displaying the Database.
*/
#include"header.h"     

// Function to print the list of valid file names
void print_valid_files(Flist *head)
{
        if (head == NULL)   // Check if file list is empty
        {
                printf("INFO : List is empty\n");
        }
        else
        {
                // Traverse and print file names
                while (head)
                {
                        printf("%s -> ", head -> fname); // Print file name
                        head = head -> link;             // Move to next node
                }

                printf("NULL\n"); // Indicate end of list
        }
}

// Function to display the contents of the database
void display_database(main_node *arr[27])
{
        int flag = 0;   // Flag to check if database is empty

        // Print table header
        printf("-------------------------------------------------------------------------------\n");
        printf("Index\tWord\t\tFilecount\tFilename[Wordcount]\n");
        printf("-------------------------------------------------------------------------------\n");

        // Traverse hash table indices
        for(int i = 0; i < 27; i++)
        {
                if(arr[i] != NULL)   // Check if index has data
                {
                        flag = 1;
                        main_node *tempM = arr[i]; // Traverse main node list

                        // Traverse main nodes
                        while(tempM != NULL)
                        {
                                // Print main node details
                                printf("[%d]\t%-10s\t%d\t\t", i, tempM -> word, tempM -> file_count);

                                sub_node *tempS = tempM -> sub_link; // Traverse sub nodes

                                // Print sub node details
                                while(tempS != NULL)
                                {
                                        printf("%s[%d] ", tempS -> file_name, tempS -> word_count);
                                        tempS = tempS -> sub_link; // Move to next sub node
                                }

                                printf("\n"); // New line for next entry
                                tempM = tempM -> main_link; // Move to next main node
                        }
                }
        }

        // If database contains no data
        if(flag == 0)
        {
                printf("DataBase is empty!\n");
        }

        printf("-------------------------------------------------------------------------------\n"); // Footer line
}

