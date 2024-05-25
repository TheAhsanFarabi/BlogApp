#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct blog
{
    char title[100];
    char content[500];
    char author[50];
};

struct user
{
    char username[50];
    int password;
};

// Function prototypes
void register_user(struct user *u);
void login();
void feed();
void showBlog();

void register_user(struct user *u)
{
    printf("============ REGISTER NOW ============\n");
    printf("Type your username: ");
    scanf("%s", u->username); // Correct usage of scanf without & for array
    printf("Type your password (INT): ");
    scanf("%d", &u->password);

    FILE *file = fopen("user_info.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "Username: %s Password: %d\n", u->username, u->password);
    fclose(file);

    login();
}

void login()
{
    printf("============ LOGIN NOW ============\n");
    char username[50];
    int password;

    printf("Type your username: ");
    scanf("%s", username); // Correct usage of scanf without & for array
    printf("Type your password (INT): ");
    scanf("%d", &password);

    FILE *file = fopen("user_info.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char file_username[50];
    int file_password;
    int logged_in = 0;

    while (fscanf(file, "Username: %s Password: %d\n", file_username, &file_password) != EOF)
    {
        if (strcmp(username, file_username) == 0 && password == file_password)
        {
            logged_in = 1;
            break;
        }
    }

    fclose(file);

    if (logged_in)
    {
        printf("Login successful! Welcome %s\n", username);
        feed();
    }
    else
    {
        printf("Invalid username or password.\n");
    }
}

void feed()
{
    printf("============ Welcome to Feed ============\n");
    // Placeholder for feed implementation
    printf("Feed functionality not implemented yet.\n");
}

void showBlog()
{
    // Placeholder for showing blog details
    printf("Show blog functionality not implemented yet.\n");
}

int main()
{
    printf("Welcome to BlogApp!\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("Choose option (1/2): ");
    int option = 0;
    scanf("%d", &option);

    if (option == 1)
    {
        struct user u;
        register_user(&u); // Pass by reference
    }
    else if (option == 2)
    {
        login();
    }
    else
    {
        printf("Invalid option.\n");
    }

    return 0;
}
