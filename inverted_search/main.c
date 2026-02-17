/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Main.c file.
		      validating the command line arguments.
*/

#include"header.h"    

int main(int argc, char *argv[])
{
        int db_created = 0;    // Flag to track database creation
        int db_updated = 0;    // Flag to track database update
        Flist *head = NULL;   // Linked list for input file names
        Flist *bkp_head = NULL; // Linked list for backup file names
        main_node *arr[27];   // Hash table for inverted index

        for(int i = 0; i < 27; i++)
                arr[i] = NULL; // Initialize hash table

        if(argc == 1)          // Check if no input files are passed
        {
                printf("Error : No text files passed!\n");
                return FAILURE;
        }

        // Read and validate input files
        if(read_validate(argc, argv, &head) == FAILURE)
        {
                printf("Read and Validation failed!\n");
                return FAILURE;
        }
        else
        {
                printf("Read and Validation successful!\n\n");
                print_valid_files(head); // Display valid file list
        }

        int ch, flag = 0;     // Menu choice variable
        do{
                printf("\n========== INVERTED SEARCH MENU ==========\n\n");

                printf("1. Create DataBase\n");
                printf("2. Display DataBase\n");
                printf("3. Search DataBase\n");
                printf("4. Save DataBase\n");
                printf("5. Update DataBase\n");
                printf("6. Exit\n");

                printf("\n==========================================\n");

                printf("Enter your choice!\n\n");
                scanf("%d", &ch); // Read user choice

                switch(ch)
                {
                        case 1: // Create database
                                {
                                        if(db_created == 1) // Prevent duplicate creation
                                        {
                                                printf("DataBase is already created!!\n");
                                                break;
                                        }

                                        if(db_updated == 1) // Handle update-before-create case
                                        {
                                                Flist *res_head = get_unique_elements(bkp_head, head);
                                                print_valid_files(res_head);
                                                create_database(arr, res_head);
                                                free_flist(res_head); // Free temporary list
                                        }
                                        else
                                        {
                                                create_database(arr, head); // Create database normally
                                        }

                                        db_created = 1; // Mark database as created
                                        printf("DataBase is created successfully!!!\n");
                                        break;
                                }

                        case 2: // Display database
                                display_database(arr);
                                break;

                        case 3: // Search word in database
                                search_database(arr);
                                break;

                        case 4: // Save database to file
                                if(save_database(arr) == SUCCESS)
                                        printf("DataBase saved successfully!!!\n");
                                else
                                        printf("DataBase was not saved!!\n");
                                break;

                        case 5: // Update database from backup
                                {
                                        if(db_updated == 1) // Prevent multiple updates
                                        {
                                                printf("Database already updated!!\n");
                                                break;
                                        }

                                        if(db_created == 1) // Disallow update after creation
                                        {
                                                printf("Update not allowed after Create DB!!\n");
                                                break;
                                        }

                                        if(update_database(arr, &bkp_head) == SUCCESS)
                                        {
                                                db_updated = 1; // Mark database as updated
                                                printf("Database updated successfully!!!\n");
                                        }
                                        else
                                                printf("Database not updated!!!\n");

                                        break;
                                }

                        case 6: // Exit program
                                printf("Exiting....\n");
                                return SUCCESS;

                        default: // Invalid menu option
                                printf("Enter correct option!!\n");
                }

        }while(ch != 6); // Loop until exit option

        free_database(arr); // Free entire database memory
        free_flist(head);   // Free file list memory

        return SUCCESS;     // Program executed successfully
}

