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
void feed(const char *username);
void createBlog(const char *username);
void showBlog();

void register_user(struct user *u)
{
    printf("============ REGISTER NOW ============\n");
    printf("Type your username: ");
    scanf("%s", u->username);
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
    fflush(stdout);
    login();
}

void login()
{
    printf("============ LOGIN NOW ============\n");
    char username[50];
    int password;

    printf("Type your username: ");
    scanf("%s", username);
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
        feed(username);
    }
    else
    {
        printf("Invalid username or password.\n");
    }
}

void feed(const char *username)
{
    printf("============ Welcome to Feed ============\n");
    printf("1. Create a Blog\n");
    printf("2. Show All Blogs\n");
    printf("3. Logout\n");
    printf("Choose option (1/2/3): ");
    int option;
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createBlog(username);
        break;
    case 2:
        showBlog();
        break;
    case 3:
        printf("Logged out successfully.\n");
        break;
    default:
        printf("Invalid option.\n");
    }
}

void createBlog(const char *username)
{
    struct blog b;
    strcpy(b.author, username);

    printf("Enter blog title: ");
    scanf(" %[^\n]%*c", b.title);

    printf("Enter blog content: ");
    scanf(" %[^\n]%*c", b.content);

    FILE *file = fopen("blog_info.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "Title: %s\nContent: %s\nAuthor: %s\n\n", b.title, b.content, b.author);
    fclose(file);

    printf("Blog created successfully!\n");
}

void showBlog()
{
    printf("============ All Blogs ============\n");
    FILE *file = fopen("blog_info.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[600];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
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
        register_user(&u);
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
