#include "headers/password-manager.h"

int main(){
    int choice;
    printf(ANSI_COLOR_WHITE_BLUE "  WELCOME TO THE PASSWORD MANAGER  \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_BLACK_WHITE "        OPTIONS AVAILABLE          \n" ANSI_COLOR_RESET);
   
    do{
        printf(ANSI_COLOR_YELLOW);
        printf("\n1. Save a new password");
        printf("\n2. Open a saved password");
        printf("\n3. Display all the references");
        printf("\n4. Erase the vault");
        printf("\n5. Exit the password manager\n");
        printf(ANSI_COLOR_RESET);
        printf(ANSI_COLOR_WHITE "Enter your choice: " ANSI_COLOR_RESET);
        scanf("%d", &choice);

        switch (choice){
            case 1:
                save_password();
                break;
            case 2:
                open_password();
                break;
            case 3:
                display_references();
                break;
            case 4:
                erase_vault();
                break;
            case 5:
                break;
            default:
                printf(ANSI_COLOR_ERROR "    ***Enter a valid choice***     \n" ANSI_COLOR_RESET);
                break;
        }

    } while (choice > 5);

    return 0;
}

void key_generator(char *key, int n){
    srand((unsigned int)(time(NULL)));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < n - 1; i++)
    {
        key[i] = charset[rand() % (sizeof charset - 1)];
    }

    key[n - 1] = '\0';
}

void cipher(const char *input, char *output, const char *key){
    for (int i = 0; i < strlen(input); i++){
        output[i] = input[i] ^ key[i];
    }

    output[strlen(input)] = '\0';
}

void save_password(){
    char reference[MAX_REFERENCE_LENGTH], password[MAX_PASSWORD_LENGTH], encrypted[MAX_PASSWORD_LENGTH], key[MAX_PASSWORD_LENGTH];

    printf("Enter your reference: ");
    scanf("%s", reference);

    printf("Enter your password: ");
    scanf("%s", password);

    key_generator(key, strlen(password));

    cipher(password, encrypted, key);

    FILE *fp = fopen("password-vault/vault.txt", "a");
    if (fp == NULL){
        printf(ANSI_COLOR_ERROR "     ***File failed to open***     \n" ANSI_COLOR_RESET);
    }else{
        fprintf(fp, "%s %s %s\n", reference, encrypted, key);
        fclose(fp);
        printf(ANSI_COLOR_CYAN "Your password has been encrypted and saved!\n" ANSI_COLOR_RESET);
    }
}

void open_password(){
    char input_reference[MAX_REFERENCE_LENGTH], reference[MAX_REFERENCE_LENGTH], encrypted[MAX_PASSWORD_LENGTH], key[MAX_PASSWORD_LENGTH], decrypted[MAX_PASSWORD_LENGTH];

    printf("Enter reference word: ");
    scanf("%s", input_reference);

    FILE *fp = fopen("password-vault/vault.txt", "r");
    if (fp == NULL){
        printf(ANSI_COLOR_ERROR "     ***File failed to open***     \n" ANSI_COLOR_RESET);
    }else{
        while (fscanf(fp, "%s %s %s", reference, encrypted, key) == 3){
            if (strcmp(reference, input_reference) == 0){
                break;
            }
        }

        fclose(fp);
    }

    cipher(encrypted, decrypted, key);
    printf(ANSI_COLOR_BLUE "Decrypted password: %s\n" ANSI_COLOR_RESET, decrypted);
}

void display_references(){
    char reference[MAX_REFERENCE_LENGTH], encrypted[MAX_PASSWORD_LENGTH], key[MAX_PASSWORD_LENGTH];

    printf("The references are:\n");

    FILE *fp = fopen("password-vault/vault.txt", "r");
    if (fp == NULL){
        printf(ANSI_COLOR_ERROR "     ***File failed to open***     \n" ANSI_COLOR_RESET);
    }else{
        while (fscanf(fp, "%s %s %s", reference, encrypted, key) == 3){
            printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, reference);
        }

        fclose(fp);
    }
}

void erase_vault(){
    if (remove("password-vault/vault.txt") == 0){
        printf(ANSI_COLOR_CYAN "Password vault deleted successfully!\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_ERROR "  ***Unable to delete the vault***  \n" ANSI_COLOR_RESET);
    }
}
