#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

//linked list defining
typedef struct linked_node linked_node;
typedef struct linked_list linked_list;

struct linked_node {
    char *word;             // the word itslef
    int times;            // number of times this word showed up
   struct linked_node *next;
};

struct linked_list {    
   struct linked_node *head; 
   struct linked_node *tail;
};

struct linked_node *create_linked_node(char *node_word) { 
   struct linked_node *node = malloc(sizeof(linked_node));   
    node->word = node_word;
    node->times = 1; 
    node->next = NULL;
    return node;
}

void free_list(linked_node *head){
linked_node *rv=head;
while(head!=NULL){
    rv=head->next;
    free(head);
    head=rv;
    }
}

void insert_node_into_linked_list(struct linked_list *singly_linked_list,char *node_word) {
   struct linked_node *node = create_linked_node(node_word);
    if (!((singly_linked_list)->head)) {
            (singly_linked_list)->head = node;
                } 
    else {        
            (singly_linked_list)->tail->next = node;
                        } 
    (singly_linked_list)->tail = node;
}

void free_linked_node(struct linked_node *node) {
while (node) { 
      struct  linked_node *temp = node;
        node = node->next;
        free(temp);    
    }
}

// Complete the checkMagazine function below.
void printLinkedList(linked_node* head) {
    if (head != NULL) { 
       printf("word:%s times:%d \n", head->word,head->times); 
       printLinkedList(head->next);    }}

void checkMagazine(int magazine_count, 
    char** magazine, int note_count, char** note) {
//we will make a linked list from the magazine words, with the times its written
struct linked_list *magazine_words =malloc(sizeof(linked_list));
insert_node_into_linked_list(magazine_words,*magazine);
struct linked_node *p=(magazine_words)->head;
for(int i=1;i<magazine_count;i++,p=(magazine_words)->head){
    while(p){
        if(!(strcmp(p->word,magazine[i]))){    // goes in if equal
            (p->times)++;
            p=NULL;                             //next magazine word
        }
        else{
            p=p->next;  
            if(p==NULL)
            insert_node_into_linked_list(magazine_words,magazine[i]);  //no match,add to list
            }
        }
    }
//printLinkedList((magazine_words)->head);
// linked list for the note words with times written
struct linked_list *note_words =malloc(sizeof(linked_list));
insert_node_into_linked_list(note_words,note[0]);
p=(note_words)->head;
for(int i=1;i<note_count;i++,p=(note_words)->head){
   while(p){
        if(!(strcmp(p->word,note[i]))){    // goes in if equal
            (p->times)++;
            p=NULL;                             //next magazine word
        }
        else{
            p=p->next;  
            if(p==NULL)
            insert_node_into_linked_list(note_words,note[i]);  //no match,add to list
            }
        }
    }
//printLinkedList((note_words)->head);
// comparing the words, seeing if possible to write note with magazine
if(note_count>magazine_count)
    printf("No");
else{
    struct linked_node *p_mag=(magazine_words)->head;
    struct linked_node *p_not=(note_words)->head;
    for(int j=0;j<note_count;j++,p_mag=((magazine_words)->head)){
        while(p_mag){
        if(!(strcmp(p_not->word,p_mag->word))){
            if((p_not->times)<=(p_mag->times))
                p_mag=NULL;
            else{                 //print no and exit loop
                printf("No");
                p_mag=NULL;
                j=note_count;
            }
        }
        else{
            p_mag=p_mag->next;
            if(p_mag==NULL){
                printf("No");
                 j=note_count;
                }
            }   
        }
        if(!(p_not->next)){
            printf("Yes");
            j=note_count;
        }
        p_not=p_not->next;
    }

}
free_list((note_words)->head);
free_list((magazine_words)->head);

}



int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
