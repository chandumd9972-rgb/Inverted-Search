/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Search the Database.
*/
#include"header.h"     

// Function to search a word in the database
void search_database(main_node *arr[27])
{
        char word[20];   // Buffer to store the word to be searched

        // Prompt user to enter the word
        printf("Enter the word you want to search : ");
        scanf("%s", word);

        // Get index based on first character of the word
        int index = check_for_index(word[0]);

        int found = 0;   // Flag to check whether word is found

        main_node *tempM = arr[index]; // Pointer to traverse main nodes at index

        // Traverse main node list
        while(tempM != NULL)
        {
                // Check if word matches
                if(strcmp(tempM -> word, word) == 0)
                {
                        found = 1;   // Mark word as found

                        // Print file count
                        printf("\n\n[%d]\t", tempM -> file_count);

                        sub_node *tempS = tempM -> sub_link; // Traverse sub nodes

                        // Print file names and word counts
                        while(tempS != NULL)
                        {
                                printf("%s\t%d\t", tempS -> file_name, tempS -> word_count);
                                tempS = tempS -> sub_link; // Move to next sub node
                        }

                        printf("\n\n"); // Formatting output
                }

                tempM = tempM -> main_link; // Move to next main node
        }

        // If word not found in database
        if(found == 0)
                printf("Word not found!!!\n");
}

