#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct blog
{

    char title[100];
    char content[500];
};

struct user
{

    char username[50];
    int password;
};

void register()
{
    struct user u1;
    printf("Type your username: ");
    scanf("%s\n", &u1.username);
    printf("Type your password (INT): ");
    scanf("%d\n", &u1.password);
}

void login()
{
}

void feed()
{
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
        register();
    }
    else
    {
        login();
    }
}