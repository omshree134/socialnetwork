#include <stdio.h>
#include <string.h>

#define MAX_USERS 100

void addFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2);
void displayNetwork(int graph[MAX_USERS][MAX_USERS], int userCount);
void viewFriends(int graph[MAX_USERS][MAX_USERS], int user, int userCount);
void removeFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2);
void mutualFriends(int graph[MAX_USERS][MAX_USERS], int u1, int u2, int userCount);
int isConnected(int graph[MAX_USERS][MAX_USERS], int u1, int u2);
int dfs(int graph[MAX_USERS][MAX_USERS], int u1, int u2, int visited[], int userCount);

int main() {
    int graph[MAX_USERS][MAX_USERS] = {0};
    int userCount = 0;
    int choice, u1, u2;

    printf("====================================\n");
    printf(" Welcome to the Advanced Social Network!\n");
    printf("====================================\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add User\n");
        printf("2. Add Friend\n");
        printf("3. Remove Friend\n");
        printf("4. Display Network\n");
        printf("5. View Friends of a User\n");
        printf("6. Check Direct Connection\n");
        printf("7. Show Mutual Friends\n");
        printf("8. Check Indirect Connection\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (userCount < MAX_USERS) {
                userCount++;
                printf("User %d added. Total users: %d\n", userCount, userCount);
            } else {
                printf("User limit reached! Cannot add more users.\n");
            }
            break;
        case 2:
            if (userCount < 2) {
                printf("At least two users are required to add a friendship.\n");
                break;
            }
            printf("Enter two user IDs to add friendship (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount && u1 != u2) {
                addFriend(graph, u1 - 1, u2 - 1);
            } else {
                printf("Invalid user IDs or self-connection not allowed.\n");
            }
            break;
        case 3:
            printf("Enter two user IDs to remove friendship (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount && u1 != u2) {
                removeFriend(graph, u1 - 1, u2 - 1);
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 4:
            displayNetwork(graph, userCount);
            break;
        case 5:
            printf("Enter user ID to view friends (1 to %d): ", userCount);
            scanf("%d", &u1);
            if (u1 > 0 && u1 <= userCount) {
                viewFriends(graph, u1 - 1, userCount);
            } else {
                printf("Invalid user ID.\n");
            }
            break;
        case 6:
            printf("Enter two user IDs to check direct connection (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount) {
                if (isConnected(graph, u1 - 1, u2 - 1)) {
                    printf("Users %d and %d are directly connected.\n", u1, u2);
                } else {
                    printf("Users %d and %d are not directly connected.\n", u1, u2);
                }
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 7:
            printf("Enter two user IDs to show mutual friends (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount) {
                mutualFriends(graph, u1 - 1, u2 - 1, userCount);
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 8:
            printf("Enter two user IDs to check indirect connection (1 to %d): ", userCount);
            scanf("%d %d", &u1, &u2);
            if (u1 > 0 && u1 <= userCount && u2 > 0 && u2 <= userCount) {
                int visited[MAX_USERS] = {0};
                if (dfs(graph, u1 - 1, u2 - 1, visited, userCount)) {
                    printf("Users %d and %d are indirectly connected.\n", u1, u2);
                } else {
                    printf("Users %d and %d are not connected.\n", u1, u2);
                }
            } else {
                printf("Invalid user IDs.\n");
            }
            break;
        case 9:
            printf("Exiting the program. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Add friend
void addFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2) {
    graph[u1][u2] = 1;
    graph[u2][u1] = 1;
    printf("Friendship added between User %d and User %d.\n", u1 + 1, u2 + 1);
}

// Remove friend
void removeFriend(int graph[MAX_USERS][MAX_USERS], int u1, int u2) {
    if (graph[u1][u2] == 1) {
        graph[u1][u2] = 0;
        graph[u2][u1] = 0;
        printf("Friendship removed between User %d and User %d.\n", u1 + 1, u2 + 1);
    } else {
        printf("No friendship exists between User %d and User %d.\n", u1 + 1, u2 + 1);
    }
}

// Display network as adjacency matrix
void displayNetwork(int graph[MAX_USERS][MAX_USERS], int userCount) {
    printf("\nSocial Network (Adjacency Matrix):\n");
    printf("   ");
    for (int i = 0; i < userCount; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");

    for (int i = 0; i < userCount; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < userCount; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

// View friends of a specific user
void viewFriends(int graph[MAX_USERS][MAX_USERS], int user, int userCount) {
    printf("Friends of User %d: ", user + 1);
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (graph[user][i] == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No friends found.");
    }
    printf("\n");
}

// Check if users are directly connected
int isConnected(int graph[MAX_USERS][MAX_USERS], int u1, int u2) {
    return graph[u1][u2];
}

// Show mutual friends
void mutualFriends(int graph[MAX_USERS][MAX_USERS], int u1, int u2, int userCount) {
    printf("Mutual friends between User %d and User %d: ", u1 + 1, u2 + 1);
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (graph[u1][i] == 1 && graph[u2][i] == 1) {
            printf("%d ", i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No mutual friends found.");
    }
    printf("\n");
}

// Depth-First Search (DFS) to check indirect connections
int dfs(int graph[MAX_USERS][MAX_USERS], int u1, int u2, int visited[], int userCount) {
    if (u1 == u2) {
        return 1;
    }
    visited[u1] = 1;

    for (int i = 0; i < userCount; i++) {
        if (graph[u1][i] == 1 && !visited[i]) {
            if (dfs(graph, i, u2, visited, userCount)) {
                return 1;
            }
        }
    }
    return 0;
}
