#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Window dimensions
const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 330;

// Board dimensions
const int BOARD_SIZE = 3;
const int CELL_SIZE = 100;

// Board state
int board[BOARD_SIZE][BOARD_SIZE] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

// Current player
int currentPlayer = 1;

// Initialize OpenGL
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

// Draw the board
void drawBoard()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw vertical lines
    for (int i = 1; i < BOARD_SIZE; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2i(i * CELL_SIZE, 0);
        glVertex2i(i * CELL_SIZE, WINDOW_HEIGHT);
        glEnd();
    }

    // Draw horizontal lines
    for (int i = 1; i < BOARD_SIZE; i++)
    {
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2i(0, i * CELL_SIZE);
        glVertex2i(WINDOW_WIDTH, i * CELL_SIZE);
        glEnd();
    }

    // Draw X and O
// Draw X and O
// Draw X and O
for (int i = 0; i < BOARD_SIZE; i++)
{
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        int value = board[i][j];
        if (value == 1)
        {
            // Draw bold X
            glLineWidth(3.0);
            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2i(j * CELL_SIZE + 10, i * CELL_SIZE + 10);
            glVertex2i((j + 1) * CELL_SIZE - 10, (i + 1) * CELL_SIZE - 10);
            glVertex2i(j * CELL_SIZE + 10, (i + 1) * CELL_SIZE - 10);
            glVertex2i((j + 1) * CELL_SIZE - 10, i * CELL_SIZE + 10);
            glEnd();
            glLineWidth(1.0); // Reset line width
        }
        else if (value == -1)
        {
            // Draw bold O (Circle)
            int centerX = j * CELL_SIZE + CELL_SIZE / 2;
            int centerY = i * CELL_SIZE + CELL_SIZE / 2;
            int radius = CELL_SIZE / 2 - 10;
            int numSegments = 100; // Number of line segments to approximate the circle

            glLineWidth(3.0);
            glBegin(GL_LINE_LOOP);
            glColor3f(0.0, 0.0, 1.0);
            for (int k = 0; k < numSegments; k++)
            {
                float theta = 2.0f * 3.1415926f * (float)k / (float)numSegments;
                float x = radius * cosf(theta);
                float y = radius * sinf(theta);
                glVertex2f(centerX + x, centerY + y);
            }
            glEnd();
            glLineWidth(1.0); // Reset line width
        }

// Check if the current row has a winning sequence
            if (board[i][0] == 1 && board[i][1] == 1 && board[i][2] == 1)
            {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glColor3f(0.0, 0.0, 0.0);
                glVertex2i(0, i * CELL_SIZE + CELL_SIZE / 2);
                glVertex2i(WINDOW_WIDTH, i * CELL_SIZE + CELL_SIZE / 2);
                glEnd();
                glLineWidth(1.0); // Reset line width
            }

// Check if the current column has a winning sequence
            if (board[0][j] == 1 && board[1][j] == 1 && board[2][j] == 1)
            {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glColor3f(0.0, 0.0, 0.0);
                glVertex2i(j * CELL_SIZE + CELL_SIZE / 2, 0);
                glVertex2i(j * CELL_SIZE + CELL_SIZE / 2, WINDOW_HEIGHT);
                glEnd();
                glLineWidth(1.0); // Reset line width
            }
// Check if the diagonal from top-left to bottom-right has a winning sequence
            if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1)
            {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glColor3f(0.0, 0.0, 0.0);
                glVertex2i(0, 0);
                glVertex2i(WINDOW_WIDTH, WINDOW_HEIGHT);
                glEnd();
                glLineWidth(1.0); // Reset line width
            }

// Check if the diagonal from top-right to bottom-left has a winning sequence
            if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)
            {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glColor3f(0.0, 0.0, 0.0);
                glVertex2i(WINDOW_WIDTH, 0);
                glVertex2i(0, WINDOW_HEIGHT);
                glEnd();
                glLineWidth(1.0); // Reset line width
            }

    }
}




    glFlush();
}

// Get the cell indices based on the mouse coordinates
void getCellIndices(int x, int y, int *row, int *col)
{
    *row = y / CELL_SIZE;
    *col = x / CELL_SIZE;
}

// Keyboard callback
void keyboard(unsigned char key, int x, int y)
{
    int row, col;

    switch (key)
    {
    case '1':
        row = 2;
        col = 0;
        break;
    case '2':
        row = 2;
        col = 1;
        break;
    case '3':
        row = 2;
        col = 2;
        break;
    case '4':
        row = 1;
        col = 0;
        break;
    case '5':
        row = 1;
        col = 1;
        break;
    case '6':
        row = 1;
        col = 2;
        break;
    case '7':
        row = 0;
        col = 0;
        break;
    case '8':
        row = 0;
        col = 1;
        break;
    case '9':
        row = 0;
        col = 2;
        break;
    default:
        return; // Ignore other keys
    }

    if (board[row][col] == 0)
    {
        board[row][col] = currentPlayer;
        currentPlayer *= -1;
        glutPostRedisplay();
    }
}

// Mouse callback
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int row, col;
        getCellIndices(x, WINDOW_HEIGHT - y, &row, &col);

        if (board[row][col] == 0)
        {
            board[row][col] = currentPlayer;
            currentPlayer *= -1;
            glutPostRedisplay();
        }
    }
}

// Check if there is a winner
// Check if there is a winner or a draw
int checkWinner()
{
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            return board[i][0];
    }

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++)
    {
        if (board[0][j] != 0 && board[0][j] == board[1][j] && board[0][j] == board[2][j])
            return board[0][j];
    }

    // Check diagonals
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return board[0][0];

    if (board[2][0] != 0 && board[2][0] == board[1][1] && board[2][0] == board[0][2])
        return board[2][0];

    // Check for a draw
    int isDraw = 1;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                isDraw = 0;
                break;
            }
        }
        if (!isDraw)
            break;
    }
    if (isDraw)
        return 2;

    return 0;
}


// Display callback
// Display callback
void display()
{
    drawBoard();
    int winner = checkWinner();

    // Display the text box
    glColor3f(0.2, 2.2, 0.2);
    glRecti(0, WINDOW_HEIGHT - 30, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Display the current player's turn or the winning message in the text box
    char message[20];

    if (winner == 0)
        sprintf(message, "Player %c's turn", currentPlayer == 1 ? 'X' : 'O');
    else if (winner == 1)
        sprintf(message, " Congo Player X wins!");
    else if (winner == -1)
        sprintf(message, "Congo Player O wins!");
    else if (winner == 2)
        sprintf(message, "It's a draw!");

    glColor3f(0.1, 0.1, 0.1);
    glRasterPos2i((WINDOW_WIDTH - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (unsigned char *)message)) / 2, WINDOW_HEIGHT - 20);
    for (int i = 0; message[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }

    glFlush();
}
// Reset Buttton
void handleKeyPress(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
    {
        // Reset the board
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[i][j] = 0;
            }
        }

        // Reset the current player
        currentPlayer = 1;

        glutPostRedisplay();
    }
}






int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Tic-Tac-Toe");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutKeyboardFunc(handleKeyPress);

    glutMainLoop();
    return 0;
}
