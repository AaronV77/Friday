// #include "filesystem.h"

// struct file {
//     char * filename;
//     char * owner;
//     char * contents;
// };

// struct file files[5];

// void file_system_install() {

//     for (int i = 0; i < 5; i++) {
//         files[i].filename = (char*)malloc(6);
//         int address = (int)files[i].filename;
//         kprintf("Address %d: %d\n", i, address);
//         strcpy(files[i].filename, "EMPTY");
//     }
// }
// void edit_file(int location) {
//     kprintf("\n");
//     kprintf("Who is the owner?: ");
//     char * owner = get_user_input();
//     strcpy(files[location].owner, owner);
//     kprintf("Reprint: %s\n", files[location].owner);
//     free(owner);

//     kprintf("\nPlease add the contents: ");
//     char * contents = get_user_input();
//     strcpy(files[location].contents, contents);
//     kprintf("Reprint: %s\n", files[location].contents);
//     free(contents);

//     return;
// }

// void create_file(char * filename) {
//     int empty_slot = -1;
//     for (int i = 0; i < 5; i++) {
//         if (!strcmp(filename, files[i].filename)) {
//             edit_file(i);
//             return;
//         }
//         if (empty_slot == -1) {
//             if (!strcmp(files[i].filename, "EMPTY")) {
//                 empty_slot = i;
//             }
//         }
//     }

//     if (empty_slot != -1) {
//         kprintf("\n");
//         free(files[empty_slot].filename);
//         files[empty_slot].filename = (char*)malloc(strlen(filename));
//         strcpy(files[empty_slot].filename, filename);
        
//         kprintf("Who is the owner?: ");
//         char * owner = get_user_input();
//         files[empty_slot].owner = (char*)malloc(strlen(owner));
//         strcpy(files[empty_slot].owner, owner);
//         kprintf("Reprint: %s\n", files[empty_slot].owner);
//         free(owner);

//         kprintf("\nPlease add the contents: ");
//         char * contents = get_user_input();
//         files[empty_slot].contents = (char*)malloc(strlen(contents));
//         strcpy(files[empty_slot].contents, contents);
//         kprintf("Reprint: %s\n", files[empty_slot].contents);
//         free(contents);
//     }

//     return;
// }

// void display_file(char * filename) {
//     for (int i = 0; i < 5; i++) {
//         if (!strcmp(filename, files[i].filename)) {
//             kprintf("Here is your file:\n%s\n", files[i].contents);
//             return;
//         }
//     }
    
//     kprintf("\nSorry, your file wasn't found.\n");
//     return;
// }

// void delete_file(char * filename) {
//     for (int i = 0; i < 5; i++) {
//         if (!strcmp(filename, files[i].filename)) {
//             free(files[i].filename);
//             free(files[i].owner);
//             free(files[i].contents);
//             return;
//         }
//     }
    
//     kprintf("\nSorry, your file wasn't found.\n");
//     return;
// }