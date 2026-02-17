/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Save the Database.
*/
#include"header.h"     

// Function to save the database into a backup file
int save_database(main_node *arr[27])
{
        char back_up[20];      // Buffer to store backup file name

        // Loop until a valid backup file name is entered
        do
        {
                printf("Enter the backup file name : ");
                scanf("%s", back_up);

                // Validate backup file name
                if(validate_back_up_file(back_up) == SUCCESS)
                        break;
                else
                        printf("Error : BackUp file name is not valid!\nUasge : filename.txt\n");
        }while(1);

        // Open backup file in write mode
        FILE *fptr = fopen(back_up, "w");
        if(fptr == NULL)
        {
                printf("Error : Unable to open the %s file!\n", back_up);
                return FAILURE;
        }

        int flag = 0;          // Flag to check if database is empty

        // Traverse hash table
        for(int i = 0; i < 27; i++)
        {
                if(arr[i] != NULL)   // Check if index contains data
                {
                        flag = 1;
                        main_node *tempM = arr[i];  // Traverse main nodes

                        while(tempM != NULL)
                        {
                                // Write main node data to backup file
                                fprintf(fptr,"#%d;%s;%d;", i, tempM -> word, tempM -> file_count);

                                sub_node *tempS = tempM -> sub_link; // Traverse sub nodes

                                // Write sub node data
                                while(tempS != NULL)
                                {
                                        fprintf(fptr,"%s;%d;", tempS -> file_name, tempS -> word_count);
                                        tempS = tempS -> sub_link;
                                }

                                fprintf(fptr,"#\n");  // End of word entry
                                tempM = tempM -> main_link; // Move to next main node
                        }
                }
        }

        fclose(fptr);   // Close backup file

        if(flag == 0)   // If database is empty
        {
                printf("DataBase is empty!\n");
                return FAILURE;
        }
        else
                return SUCCESS; // Database saved successfully
}

// Function to validate backup file name
int validate_back_up_file(char *file)
{
        char *ptr = strstr(file, ".txt"); // Check for .txt extension

        if(ptr != NULL && strcmp(ptr, ".txt") == 0)
        {
                if(strlen(file) > 4) // Ensure filename exists before extension
                        return SUCCESS;
                else
                {
                        printf("File name is not mentioned only the extension is mentioned!\n");
                        return FAILURE;
                }
        }
}

