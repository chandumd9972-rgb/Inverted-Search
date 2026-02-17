/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Update the Database.
*/
#include"header.h"     

// Function to update database from backup file
int update_database(main_node *arr[27], Flist **bkp_head)
{
        int flag = 0;           // Flag to check if database is already non-empty

        // Check whether database already contains data
        for(int i = 0; i < 27; i++)
        {
                if(arr[i] != NULL)
                {
                        flag = 1;
                        break;
                }
        }

        // If database is non-empty, do not allow update
        if(flag == 1)
                return NON_EMPTY_DATABASE;

        char bkp_file[20];      // Buffer to store backup file name

        // Loop until valid backup file name is entered
        do
        {
                printf("Enter the backup file name : ");
                scanf("%s", bkp_file);

                if(validate_bkp_file(bkp_file) == FAILURE) // Validate backup file
                        printf("BackUp file dosen't meet the requirement!!\n");
                else
                        break;
        }
        while(1);

        // Open backup file in read mode
        FILE *fp = fopen(bkp_file, "r");
        if(fp == NULL)
        {
                printf("Error : Unable to open the backup file!!!\n");
                return FAILURE;
        }

        char ch;    // Variable to read characters from file

        // Read backup file character by character
        while ((ch = fgetc(fp)) != EOF)
        {
                // Check for start of a word entry
                if (ch == '#')
                {
                        int index, file_count; // Variables for index and file count
                        char word[50];         // Buffer to store word

                        // Read index, word, and file count
                        fscanf(fp, "%d;%[^;];%d;", &index, word, &file_count);

                        // Allocate memory for new main node
                        main_node *mnew = malloc(sizeof(main_node));
                        if (mnew == NULL)
                                return FAILURE;

                        mnew -> word = malloc(strlen(word) + 1); // Allocate memory for word
                        strcpy(mnew->word, word);                // Copy word
                        mnew->file_count = file_count;           // Store file count
                        mnew->sub_link = NULL;                   // Initialize sub link
                        mnew->main_link = NULL;                  // Initialize main link

                        sub_node *sprev = NULL; // Pointer to previous sub node

                        // Loop through sub node entries
                        for (int i = 0; i < file_count; i++)
                        {
                                char fname[50]; // Buffer to store file name
                                int wcount;      // Word count

                                // Read file name and word count
                                fscanf(fp, "%[^;];%d;", fname, &wcount);

                                // Allocate memory for sub node
                                sub_node *snew = malloc(sizeof(sub_node));
                                if (snew == NULL)
                                        return FAILURE;

                                // Add file name to backup list if not already present
                                if(check_already_present(*bkp_head, fname) == FAILURE)
                                        insert_at_last(bkp_head, fname);

                                snew -> file_name = malloc(strlen(fname) + 1); // Allocate file name
                                strcpy(snew->file_name, fname);                // Copy file name
                                snew->word_count = wcount;                     // Store word count
                                snew->sub_link = NULL;                         // Initialize sub link

                                // Link sub nodes
                                if (sprev == NULL)
                                        mnew->sub_link = snew;
                                else
                                        sprev->sub_link = snew;

                                sprev = snew; // Move to next sub node
                        }

                        // Insert main node into hash table
                        if (arr[index] == NULL)
                        {
                                arr[index] = mnew;
                        }
                        else
                        {
                                main_node *temp = arr[index]; // Traverse main nodes
                                while (temp->main_link != NULL)
                                        temp = temp->main_link;

                                temp->main_link = mnew; // Insert at end
                        }

                        fgetc(fp); // Read ending '#'
                }
        }

        return SUCCESS; // Database updated successfully
}

// Function to validate backup file
int validate_bkp_file(char *file)
{
        // Check file name length
        if(strlen(file) > 4)
        {
                char *ptr = strstr(file, ".txt"); // Check .txt extension
                if(ptr != NULL && strcmp(ptr, ".txt") == 0)
                {
                        FILE *fptr = fopen(file, "r"); // Open file
                        if(fptr == NULL)
                        {
                                printf("Entered BackUp file is not available in the present directory!!!\n");
                                return FAILURE;
                        }
                        else
                        {
                                char line[1024]; // Buffer to store line
                                char ch;          // Character variable
                                int flag = 1;     // Validation flag

                                // Read file content line by line
                                while((ch = fgetc(fptr)) != EOF)
                                {
                                        int i = 0;
                                        while(ch != '\n' && ch != EOF)
                                        {
                                                line[i++] = ch;
                                                ch = fgetc(fptr);
                                        }
                                        line[i] = '\0';

                                        if (i == 0) // Skip empty lines
                                                continue;

                                        // Check backup format validity
                                        if(line[0] != '#' || line[i - 1] != '#')
                                        {
                                                flag = 0;
                                                fclose(fptr);
                                                return FAILURE;
                                        }
                                }

                                if(flag == 1) // If format is valid
                                {
                                        fclose(fptr);
                                        return SUCCESS;
                                }
                        }
                }
                else
                {
                        printf("Error : BackUp file mentioned is not of .txt extension!!!\n");
                        return FAILURE;
                }
        }
        else
        {
                printf("Error : The length of the BackUp file should be more than 4!!!\n");
                return FAILURE;
        }
}

// Function to check if file name already exists in file list
int check_already_present(Flist *head, char *fname)
{
        Flist *temp = head; // Pointer to traverse list

        while(temp != NULL)
        {
                if(strcmp(temp -> fname, fname) == 0) // Match found
                        return SUCCESS;

                temp = temp -> link; // Move to next node
        }

        return FAILURE; // File name not found
}

