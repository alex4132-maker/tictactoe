#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initializeField(char field[3][3]) {
	int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            field[i][j] = '-';  // Initialize the field with '-'
        }
    }
}

void printField(char field[3][3]) {
	int i, j;
    printf("\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%c  ", field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int checkWin(char field[3][3], char player) {
	int i, j;
    // Check rows and columns
    for (i = 0; i < 3; i++) {
        if ((field[i][0] == player && field[i][1] == player && field[i][2] == player) || // Row check
            (field[0][i] == player && field[1][i] == player && field[2][i] == player)) { // Column check
            return 1; // Win found
        }
    }
    // Check diagonals
    if ((field[0][0] == player && field[1][1] == player && field[2][2] == player) || 
        (field[0][2] == player && field[1][1] == player && field[2][0] == player)) {
        return 1; // Win found
    }
    return 0; // No win
}

int checkDraw(char field[3][3]) {
	int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (field[i][j] == '-') {
                return 0; // Not a draw
            }
        }
    }
    return 1; // Draw
}

// Function to make the computer's move
void computerMove(char field[3][3], char computerChar) {
    int row, col;
    // Randomly select an empty cell for the computer
    do {
        row = rand() % 3; // Generate a random row (0, 1, or 2)
        col = rand() % 3; // Generate a random column (0, 1, or 2)
    } while (field[row][col] != '-'); // Repeat until an empty cell is found

    field[row][col] = computerChar; // Place the computer's character on the field
}

int main(int argc, char *argv[]) {
    char field[3][3];
    char char_selection;
    int user_input_i, user_input_j;
    
    // Seed the random number generator
    srand(time(NULL));

    initializeField(field);
    printField(field);

    // Ask for player's character
    do {
        printf("Choose 'x' or 'o': ");
        scanf(" %c", &char_selection);
        if (char_selection != 'x' && char_selection != 'o') {
            printf("Invalid selection. Please enter 'x' or 'o'.\n");
        }
    } while (char_selection != 'x' && char_selection != 'o');

    char computerChar = (char_selection == 'x') ? 'o' : 'x'; // Assign the other character to the computer

    while (1) {
        // Player's move
        printf("Your turn. Enter position (row column between 1 and 3): ");
        scanf("%d %d", &user_input_i, &user_input_j);

        // Validate the input
        if (user_input_i < 1 || user_input_i > 3 || user_input_j < 1 || user_input_j > 3) {
            printf("Invalid position. Please try again.\n");
            continue;
        }

        // Check if the cell is already taken
        if (field[user_input_i - 1][user_input_j - 1] != '-') {
            printf("Cell already taken. Please try again.\n");
            continue;
        }

        // Place the player's character on the board
        field[user_input_i - 1][user_input_j - 1] = char_selection;
        printField(field);

        // Check for win
        if (checkWin(field, char_selection)) {
            printf("Congratulations! You win!\n");
            break;
        }

        // Check for draw
        if (checkDraw(field)) {
            printf("It's a draw!\n");
            break;
        }

        // Computer's move
        printf("Computer's turn...\n");
        computerMove(field, computerChar);
        printField(field);

        // Check for win
        if (checkWin(field, computerChar)) {
            printf("Computer wins!\n");
            break;
        }

        // Check for draw
        if (checkDraw(field)) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}

