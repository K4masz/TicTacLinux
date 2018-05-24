#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


struct player {
    char sign;
    bool win;
};
struct player first;
struct player second;

void welcomeMessage() {
    printf("Hello,\nIt's Tic Tack Toe Game: Premium Edition! \nPress any key to continue...");
    getchar();
}

void drawBilboard() {
    printf("|--------------------------------------|\n|                                      |\n|            Tic Tac Toe               |\n|                        The Game      |\n|--------------------------------------|");
}

void drawMenu() {
    printf("\n\n1) New Game\n2) Credits\n3) Exit\n\n Choice:");

}

void clrscr() {
    system("@cls||clear");
}

void credits() {
    printf("Coded in C language by Tomasz Pawlik 2017 \nPress any key to return to menu...");
    getchar();
    clrscr();
}

void drawExitMessage() {
    printf("Thank you for playing Tic Tac Toe The Game.\nPress any key to continue...\n\n\n\n\n\n\n\n");
}

void chooseSign(struct player *f, struct player *s, int *pcOp) {
    printf("Choose your weapons: \n\n 1) I: X,  II: O \n 2) I: O,  II: X \n\n Choice:");
    int c;
    scanf_s("%d", &c);

    switch (c) {
        case 1:
            f->sign = 88; //kod Ascii dużej litery X
            s->sign = 79; //kod Ascii dużej litery O
            break;
        case 2:
            f->sign = 79;
            s->sign = 88;
            break;
    }

    printf("\t I: %c,  II: %c\n\nNow choose your opponent: \n\n 1) Mortal 2) PC\n\n Choice:", f->sign, s->sign);
    scanf_s("%d", &c);
    switch (c) {
        case 1:
            *pcOp = 0;
            break;
        case 2:
            *pcOp = 1;
            break;
    }


}

void drawGrid(char grid[9]) {

    clrscr();
    printf("|-------|-------|-------|\n|   %c   |   %c   |   %c   |\n|-------|-------|-------|\n|   %c   |   %c   |   %c   |\n|-------|-------|-------|\n|   %c   |   %c   |   %c   |\n|-------|-------|-------|\n\n\n",
           grid[0], grid[1], grid[2],
           grid[3], grid[4], grid[5],
           grid[6], grid[7], grid[8]);
}

void putSign(int pos, char grid[9], struct player *c) {
    pos--;
    grid[pos] = c->sign;
}

int getPos() {
    int d;
    printf("Enter the number of place you want to put a sign: ");
    scanf_s("%d", &d);
    return d;
}

int isEmptySpace(int pos, char grid[9]) {
    pos--;
    if (grid[pos] == 88 || grid[pos] == 79)
        return 0;
    else
        return 1;
}

int aiturn(char grid[9], int depth, struct player *current) {

    if ((grid[0] == grid[4] && grid[4] == grid[8]) ||
        (grid[1] == grid[4] && grid[4] == grid[7]) ||
        (grid[6] == grid[4] && grid[4] == grid[2]) ||
        (grid[6] == grid[3] && grid[3] == grid[0]) ||
        (grid[2] == grid[5] && grid[5] == grid[8]) ||
        (grid[0] == grid[1] && grid[1] == grid[2]) ||
        (grid[3] == grid[4] && grid[4] == grid[5]) ||
        (grid[6] == grid[7] && grid[7] == grid[8]))
        return -10 + depth;


    int fullGridControlSum = 0;
    int y;
    for (y = 0; y < 9; y++) {
        if (isEmptySpace(y + 1, grid))
            fullGridControlSum++;
    }
    if (fullGridControlSum == 9)
        return 0;


    struct player *non_current;
    if (&*current == &first)
        non_current = &second;
    else
        non_current = &first;

    int max = -INFINITY;
    int index = 0;

    int x;
    for (x = 0; x < 9; x++) {
        if (isEmptySpace(x + 1, grid) == 1) {
            char simulation[9];
            memcpy(simulation, grid, 9);
            simulation[x] = current->sign;

            int moveval = -(aiturn(simulation, depth + 1, non_current));

            if (moveval > max) {
                max = moveval;
                index = x;
            }
        }
    }

    if (depth == 0)
        putSign(index + 1, grid, current);

    return max;

}

void newGame() {
    clrscr();
    int pos;
    int pcOpponent;
    char grid[9] =
            {
                    '1', '2', '3',
                    '4', '5', '6',
                    '7', '8', '9'
            };

    struct player *current = &first;
    chooseSign(&first, &second, &pcOpponent);

    int i;
    for (i = 0; i < 9; i++) //main game loop
    {
        drawGrid(grid);

        if (&*current == &first)
            printf("Player one\n");
        else
            printf("Player two\n");

        if (&*current == &first || (&*current == &second && pcOpponent == 0)) //Logic for human players
        {
            pos = getPos();
            if (isEmptySpace(pos, grid) == 1 && (pos < 10 && pos > 0))
                putSign(pos, grid, current);
            else {
                printf("\nYou have chosen the wrong place, your turn will be skipped.\n");
                usleep(2000000); //works in microseconds (1second = 1 000 000 microseconds)
            }
        } else //logic for AI
            aiturn(grid, 0, current);


        drawGrid(grid);

        if ((grid[0] == grid[4] && grid[4] == grid[8]) ||
            (grid[1] == grid[4] && grid[4] == grid[7]) ||
            (grid[6] == grid[4] && grid[4] == grid[2]) ||
            (grid[6] == grid[3] && grid[3] == grid[0]) ||
            (grid[2] == grid[5] && grid[5] == grid[8]) ||
            (grid[0] == grid[1] && grid[1] == grid[2]) ||
            (grid[3] == grid[4] && grid[4] == grid[5]) ||
            (grid[6] == grid[7] && grid[7] == grid[8])) {
            current->win = true;
            printf("Win.\nPress any key to continue...");
            getchar();
            char l;
            scanf_s("%c", &l);
            clrscr();
            drawBilboard();
            drawMenu();
            break;
        }

        if (&*current == &first)
            current = &second;
        else
            current = &first;
    }
    if (i == 9) {
        printf("Draw.\nPress any key to continue...");
        getchar();
        char l;
        scanf_s("%c", &l);
        clrscr();
        drawBilboard();
        drawMenu();
    }


}


int main() {
    welcomeMessage();
    clrscr();
    drawBilboard();
    drawMenu();
    int a;
    bool exit = false;
    do {
        scanf_s("%d", &a);
        switch (a) {
            case 1:
                clrscr();
                newGame();
                break;
            case 2:
                clrscr();
                credits();
                clrscr();
                drawBilboard();
                drawMenu();
                break;
            case 3:
                clrscr();
                drawExitMessage();
                getchar();
                exit = true;
                break;
        }
    } while (exit == false);

    return 0;
}
