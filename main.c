#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

void addFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2);
void displayNetwork(int graph[MAX_USERS][MAX_USERS], int userCount);
int isConnected(int graph[MAX_USERS][MAX_USERS], int u1, int u2);

int main() {
    int graph[MAX_USERS][MAX_USERS] = {0};
    int userCount = 0;
    int choice, u1, u2;

    printf("Welcome to the Social Network!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add User\n");
        printf("2. Add Friend\n");
        printf("3. Display Network\n");
        printf("4. Check Connection\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            userCount++;
            printf("User %d added. Total users: %d\n", userCount, userCount);
            break;
        case 2:
            if (userCount < 2) {
                printf("At least two users are required to add a friendship.\n");
                break;
            }
            printf("Enter two user IDs to add friendship (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount) {
                addFriend(graph, u1 - 1, u2 - 1);
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 3:
            displayNetwork(graph, userCount);
            break;
        case 4:
            printf("Enter two user IDs to check connection (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount) {
                if (isConnected(graph, u1 - 1, u2 - 1)) {
                    printf("Users %d and %d are connected.\n", u1, u2);
                } else {
                    printf("Users %d and %d are not connected.\n", u1, u2);
                }
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 5:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}


void addFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2) {
    graph[u1][u2] = 1;
    graph[u2][u1] = 1;
    printf("Friendship added between User %d and User %d.\n", u1 + 1, u2 + 1);
}
void displayNetwork(int graph[MAX_USERS][MAX_USERS], int userCount) {
    printf("\nSocial Network (Adjacency Matrix):\n");
    for (int i = 0; i < userCount; i++) {
        for (int j = 0; j < userCount; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

int isConnected(int graph[MAX_USERS][MAX_USERS], int u1, int u2) {
    return graph[u1][u2];
}
