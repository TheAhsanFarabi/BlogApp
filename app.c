#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct definitions
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
    // Function to register a new user
    printf("============ REGISTER NOW ============\n");
    printf("Type your username: ");
    scanf("%s", u->username);
    fflush(stdin); // Clear input buffer

    printf("Type your password (INT): ");
    scanf("%d", &u->password);
    fflush(stdin); // Clear input buffer

    // Append the new user's details to the user_info.txt file
    FILE *file = fopen("user_info.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "Username: %s Password: %d\n", u->username, u->password);
    fclose(file);
    printf("Registration successful! Please login.\n");

    // Redirect user to login after registration
    login();
}

void login()
{
    // Function to login an existing user
    printf("============ LOGIN NOW ============\n");
    char username[50];
    int password;

    printf("Type your username: ");
    scanf("%s", username);
    fflush(stdin); // Clear input buffer

    printf("Type your password (INT): ");
    scanf("%d", &password);
    fflush(stdin); // Clear input buffer

    // Open user_info.txt to validate credentials
    FILE *file = fopen("user_info.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char file_username[50];
    int file_password;
    int logged_in = 0;

    // Check each line in the file for matching credentials
    while (fscanf(file, "Username: %s Password: %d\n", file_username, &file_password) != EOF)
    {
        if (strcmp(username, file_username) == 0 && password == file_password)
        {
            logged_in = 1;
            break;
        }
    }

    fclose(file);

    // If credentials are correct, proceed to the feed
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
    // Function to display the main feed with options
    printf("============ Welcome to Feed ============\n");
    while (1)
    {
        printf("1. Create a Blog\n");
        printf("2. Show All Blogs\n");
        printf("3. Logout\n");
        printf("Choose option (1/2/3): ");
        int option;
        scanf("%d", &option);
        fflush(stdin); // Clear input buffer

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
            return;
        default:
            printf("Invalid option.\n");
        }
    }
}

void createBlog(const char *username)
{
    // Function to create a new blog post
    struct blog b;
    strcpy(b.author, username);

    printf("Enter blog title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0'; // Remove newline character

    printf("Enter blog content: ");
    fgets(b.content, sizeof(b.content), stdin);
    b.content[strcspn(b.content, "\n")] = '\0'; // Remove newline character

    // Append the new blog to the blog_info.txt file
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
    // Function to display all blog posts
    printf("============ All Blogs ============\n");
    FILE *file = fopen("blog_info.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[600];
    // Print each line from the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}

int main()
{
    // Main function to start the program
    printf("Welcome to ByteBlog!\n");
    while (1)
    {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("Choose option (1/2): ");
        int option = 0;
        scanf("%d", &option);
        fflush(stdin); // Clear input buffer

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
    }

    return 0;
}
