#include <stdio.h>
#include <inttypes.h>

#define MAX_LENGTH 255
char *filename = "C:\\msys64\\home\\aymer\\LeetCode\\CC1_C\\src\\data.txt";


typedef struct Users{
int16_t id;
char firstname[64];
char lastname[100];
}Users;

void read_data() {
    Users user;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return; 
    }

    while (fscanf(fp, "%hd,%63[^,],%99[^,\n]", &user.id, user.firstname, user.lastname) == 3) {
        printf("id: %" PRId16 " name: %s last name: %s\n", user.id, user.firstname, user.lastname);
    }
    fclose(fp);
}

void input_data() {
    Users user;
    FILE *fp = fopen(filename, "a");
    
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return; 
    }
    
    char input[MAX_LENGTH];

    printf("Enter user data (id, first name, last name): ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
  
        if (sscanf(input, "%hd,%63[^,],%99[^\n]", &user.id, user.firstname, user.lastname) == 3) {
/*             for(int i = 0; i <= ;i++){
                //TODO When input data cant have same id
                if(&usre.id ==)
            }    */
            
            fprintf(fp, "%hd,%s,%s\n", user.id, user.firstname, user.lastname);
            printf("User data added successfully.\n");
        } else {
            printf("Error: Invalid input format. Please use 'id, first name, last name'.\n");
        }
    }

    fclose(fp);
}



void select_data(){

}

void delete_data(){

}