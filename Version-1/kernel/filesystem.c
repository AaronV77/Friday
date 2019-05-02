#include "filesystem.h"

struct file {
    char * filename;
    char * owner;
    char * contents;
};

struct file files[15];

void edit_file(int location) {
    kprintf("Who is the owner?: ");
    char * owner = get_user_input();
    files[location].owner = owner;
    free(owner);

    kprintf("Please add the contents: ");
    char * contents = get_user_input();
    files[location].contents = contents;
    free(contents);
    return;
}

void create_file(char * filename) {
    int empty_slot = -1;
    for (int i = 0; i < 15; i++) {
        if (!strcmp(filename, files[i].filename)) {
            edit_file(i);
            return;
        }
        if (empty_slot == -1) {
            if (strlen(files[i].filename) == 0) {
                empty_slot = i;
            }
        }
    }

    if (empty_slot != -1) {
        files[empty_slot].filename = filename;
        
        kprintf("Who is the owner?: ");
        char * owner = get_user_input();
        files[empty_slot].owner = owner;
        free(owner);

        kprintf("Please add the contents: ");
        char * contents = get_user_input();
        files[empty_slot].contents = contents;
        free(contents);
    }

    return;
}

void display_file(char * filename) {
    for (int i = 0; i < 15; i++) {
        if (!strcmp(filename, files[i].filename)) {
            kprintf("Here is your file:\n%s\n", files[i].contents);
            return;
        }
    }
    
    kprintf("Sorry, your file wasn't found.\n");
    return;
}

void delete_file(char * filename) {
    for (int i = 0; i < 15; i++) {
        if (!strcmp(filename, files[i].filename)) {
            files[i].filename = 0;
            files[i].owner = 0;
            files[i].contents = 0;
            return;
        }
    }
    
    kprintf("Sorry, your file wasn't found.\n");
    return;
}