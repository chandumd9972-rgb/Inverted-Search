/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Create the Database.
*/
#include"header.h"     

// Function to create the inverted index database
int create_database(main_node *arr[27], Flist *head)
{
        if(head == NULL)        // Check if file list is empty
                return FAILURE;

        Flist *tempF = head;   // Pointer to traverse file list
        while(tempF != NULL)   // Loop through each file
        {
                FILE *ptr = fopen(tempF -> fname, "r");   // Open file in read mode
                if(ptr == NULL)                           // Check file open failure
                {
                        printf("Error : File opening not possible!!\n");
                        return FAILURE;
                }

                char ch;       // Variable to read character
                while ((ch = fgetc(ptr)) != EOF)   // Read file character by character
                {
                        int i = 0;                  // Index for buffer
                        char buffer[20];            // Buffer to store a word

                        // Read characters until space, newline, or EOF
                        while (ch != ' ' && ch != '\n' && ch != EOF)
                        {
                                buffer[i++] = ch;  // Store character into buffer
                                ch = fgetc(ptr);   // Read next character
                        }

                        buffer[i] = '\0';           // Null-terminate the word

                        if (i == 0)                 // Skip empty words
                                continue;

                        int index = check_for_index(buffer[0]); // Get index for word

                        if(arr[index] == NULL)      // If no main node at index
                        {
                                arr[index] = create_main_node(buffer, tempF -> fname, 1); // Create main node
                        }
                        else
                        {
                                main_node *tempM = arr[index];  // Traverse main nodes

                                while(tempM != NULL)            // Search for word
                                {
                                        if(strcmp(tempM -> word, buffer) == 0) // Word found
                                                break;

                                        if(tempM -> main_link == NULL) // End of list
                                                break;

                                        tempM = tempM -> main_link;   // Move to next main node
                                }

                                if(strcmp(tempM -> word, buffer) == 0) // If word exists
                                {
                                        sub_node *tempS = tempM -> sub_link; // Traverse sub nodes
                                        int found = 0;                       // Flag to check file existence

                                        while (tempS)                       // Search file in sub nodes
                                        {
                                                if (strcmp(tempS->file_name, tempF->fname) == 0)
                                                {
                                                        tempS->word_count++; // Increment word count
                                                        found = 1;
                                                        break;
                                                }

                                                if (tempS->sub_link == NULL) // End of sub list
                                                        break;

                                                tempS = tempS->sub_link;     // Move to next sub node
                                        }

                                        if (!found) // If file not found
                                        {
                                                tempS->sub_link = create_sub_node(tempF->fname,1); // Create sub node
                                                tempM->file_count++;   // Increment file count
                                        }
                                }
                                else
                                {
                                        tempM -> main_link = create_main_node(buffer, tempF -> fname, 1); // New main node
                                }
                        }
                }
                fclose(ptr);              // Close file
                tempF = tempF -> link;    // Move to next file
        }
        return SUCCESS;                   // Database creation successful
}

// Function to determine index based on character
int check_for_index(char ch)
{
        if(ch >= 'A' && ch <= 'Z')     // Uppercase letters
                return ch - 'A';
        else if(ch >= 'a' && ch <= 'z') // Lowercase letters
                return ch - 'a';
        else                            // Non-alphabetic characters
                return 26;
}

// Function to create a main node
main_node *create_main_node(char word[], char fname[], int file_count)
{
        main_node *new = malloc(sizeof(main_node)); // Allocate memory for main node
        if(new == NULL)                             // Check allocation failure
                return NULL;

        new -> file_count = file_count;             // Initialize file count
        new -> word = malloc(strlen(word) + 1);     // Allocate memory for word
        strcpy(new -> word, word);                  // Copy word
        new -> sub_link = create_sub_node(fname, 1); // Create first sub node
        new -> main_link = NULL;                    // Set main link to NULL

        return new;                                 // Return new main node
}

// Function to create a sub node
sub_node *create_sub_node(char fname[], int word_count)
{
        sub_node *new = malloc(sizeof(sub_node));   // Allocate memory for sub node
        if(new == NULL)                             // Check allocation failure
                return NULL;

        new -> file_name = malloc(strlen(fname) + 1); // Allocate memory for file name
        strcpy(new -> file_name, fname);              // Copy file name
        new -> word_count = word_count;               // Initialize word count
        new -> sub_link = NULL;                       // Set sub link to NULL

        return new;                                   // Return new sub node
}

// Function to get unique file names from file list
Flist* get_unique_elements(Flist *bkp_head, Flist *head)
{
        Flist *res_head = NULL;     // Result list head
        Flist *temp2 = head;        // Traverse second list

        while(temp2 != NULL)        // Loop through list
        {
                int found = 0;      // Flag to check duplicate
                Flist *temp1 = bkp_head; // Traverse backup list

                while(temp1 != NULL) // Search for duplicate
                {
                        if(strcmp(temp1 -> fname, temp2 -> fname) == 0)
                        {
                                found = 1;
                                break;
                        }
                        temp1 = temp1 -> link;
                }

                if(found == 0)      // If unique file name
                        insert_at_last(&res_head, temp2 -> fname);

                temp2 = temp2 -> link;   // Move to next node
        }

        return res_head;              // Return unique list
}

