/*
        Name : Chandu M D
        Date : 22 dec 2025
        Description : Inverted Search project.
                      Header file.
		      * It will include all function prototypes and structures. 
*/

#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH


//All Macro's

#define SUCCESS 1
#define FAILURE 0
#define FILE_NOT_FOUND -1
#define FILE_EMPTY -2
#define NON_EMPTY_DATABASE -3

//Included header files

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Flist structure

typedef struct Flist
{
	char *fname;
	struct Flist *link;
}Flist;

//Sub node Structure

typedef struct sub
{
	char *file_name;
	int word_count;
	struct sub *sub_link;
}sub_node;

//Main node Structure

typedef struct main
{
	int file_count;
	char *word;
	sub_node *sub_link;
	struct main *main_link;
}main_node;

//Function Prototypes

int read_validate(int argc, char *argv[], Flist **head);
void print(Flist *Head);
int check_extension(char *str);
int check_file_existence_and_emptyness(char *file);
void remove_duplicates(char *argv[], int valid[], int *size);
int insert_at_last(Flist **head, char *file);
void print_valid_files(Flist *head);
int create_database(main_node *arr[27], Flist *head);
int check_for_index(char ch);
main_node  *create_main_node(char word[], char fname[], int file_count);
sub_node *create_sub_node(char fname[], int word_count);
void display_database(main_node *arr[27]);
void free_flist(Flist *head);
void free_sub_list(sub_node *head);
void free_main_list(main_node *head);
void free_database(main_node *arr[27]);
void search_database(main_node *arr[27]);
int validate_back_up_file(char *file);
int save_database(main_node *arr[27]);
int update_database(main_node *arr[27], Flist **bkp_head);
int validate_bkp_file(char *file);
int check_already_present(Flist *head, char *fname);
Flist* get_unique_elements(Flist *bkp_head, Flist *head);
#endif

