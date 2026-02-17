/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Validating the command line arguments.
		      -> File extension should be .txt
		      -> Duplicates file are not included.
		      -> If file is empty those files are not allowed.
*/

#include"header.h"     // Header file containing structure definitions and macros

// Function to read, validate command-line files, and store valid files in list
int read_validate(int argc, char *argv[], Flist **head)
{
        int size1 = 0, size2 = 0;    // Counters for valid files
        int valid[argc];            // Array to store valid argument indices

        // Check extension and filename validity
        for(int i = 1; i < argc; i++)
        {
                if(check_extension(argv[i]) == FAILURE) // Check .txt extension
                        printf("File %s is not .txt extension!\n", argv[i]);
                else
                {
                        if(strlen(argv[i]) <= 4)        // Check filename length
                                printf("File name is not mentioned!\n");
                        else
                                valid[size1++] = i;    // Store valid index
                }
        }

        printf("%d \n", size1);     // Print count of extension-valid files

        // Check file existence and emptiness
        for(int i = 0; i < size1; i++)
        {
                int result = (check_file_existence_and_emptyness(argv[valid[i]]));
                if(result == FILE_NOT_FOUND)
                        printf("File %s is not available in the present directory!\n", argv[valid[i]]);
                else if(result == FILE_EMPTY)
                        printf("File %s is empty!\n\n", argv[valid[i]]);
                else
                        valid[size2++] = valid[i]; // Store fully valid files
        }

        // Remove duplicate file names
        remove_duplicates(argv, valid, &size2);

        // Print valid file names
        for(int i = 0; i < size2; i++)
                printf("%s \n", argv[valid[i]]);

        // Insert valid files into linked list
        for(int i = 0; i < size2; i++)
        {
                if(insert_at_last(head, argv[valid[i]]) == FAILURE)
                {
                        printf("File were not able to load to list!\n");
                        return FAILURE;
                }
        }

        // Check whether at least one valid file exists
        if(size1 > 0 && size2 > 0)
                return SUCCESS;
        else
                return FAILURE;
}

// Function to check whether file has .txt extension
int check_extension(char *str)
{
        char *ptr = strstr(str, ".txt"); // Search for .txt substring
        if(ptr != NULL && (strcmp(ptr, ".txt") == 0))
                return SUCCESS;
        else
                return FAILURE;
}

// Function to check file existence and whether it is empty
int check_file_existence_and_emptyness(char *file)
{
        FILE *fptr = fopen(file, "r"); // Try opening file
        if(fptr == NULL)
                return FILE_NOT_FOUND;

        fseek(fptr, 0, SEEK_END); // Move file pointer to end
        int p = ftell(fptr);      // Get file size
        rewind(fptr);             // Reset file pointer

        if(p < 2)                 // Check if file is empty
        {
                fclose(fptr);
                return FILE_EMPTY;
        }

        fclose(fptr);             // Close file
        return SUCCESS;
}

// Function to remove duplicate file names from valid list
void remove_duplicates(char *argv[], int valid[], int *size)
{
        for(int i = 0; i < *size - 1; i++)
        {
                for(int j = i + 1; j < *size;)
                {
                        if(strcmp(argv[valid[i]], argv[valid[j]]) == 0) // Duplicate found
                        {
                                for(int k = j; k < *size - 1; k++)
                                {
                                        valid[k] = valid[k + 1]; // Shift elements
                                }
                                (*size)--; // Reduce size
                        }
                        else
                                j++; // Move to next index
                }
        }
}

// Function to insert a file name at the end of the file list
int insert_at_last(Flist **head, char *file)
{
        Flist *new = malloc(sizeof(Flist)); // Allocate memory for new node

        if(new == NULL)
        {
                return FAILURE;
        }

        new -> fname = malloc(strlen(file) + 1); // Allocate memory for file name
        if (new -> fname == NULL)
        {
                free(new);
                return FAILURE;
        }

        strcpy(new -> fname, file); // Copy file name
        new -> link = NULL;         // Initialize link

        if(*head == NULL)           // If list is empty
        {
                *head = new;
                return SUCCESS;
        }
        else
        {
                Flist *temp = *head; // Traverse list
                while(temp -> link != NULL)
                {
                        temp = temp -> link;
                }
                temp -> link = new;  // Insert at end
                return SUCCESS;
        }
}

