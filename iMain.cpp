#include <stdio.h>
#include <stdbool.h>
#include "iGraphics.h"
#include "iSound.h"
int screen_width = 1000;
int screen_height = 750;
int padding_x = 25;
int padding_y = 20;
float dx;
float dy;
int paddle_height = 15;
int paddle_width = 100;
int paddle_x = (screen_width/2) - (paddle_width/2);
int paddle_y = 15;
int ball_radius = 10;
int lives = 1;
int score = 0;
float ball_x = paddle_x + paddle_width / 2;
float ball_y = paddle_height + paddle_y + ball_radius;
int dbx = 0, dby = 0;
bool isGameOver = false;
int gameState = 0;
int max_menu_optn = 1;
int selected_menu_idx = 1; // please start from 1 (not 0) for this ;)
/*
gamestate:
0 = main menu
1 = game
2 = game over (i guess)
3 = Controls menu
*/

void gameOver(void);
void mainMenu(void);
void controlsMenu(void);


/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    // place your drawing codes here
    iClear();
    // printf("%d",selected_menu_idx);
    
    
    if (gameState == 0)
    {
        mainMenu();
        iSetColor(255,255,255);
        if (selected_menu_idx == 1){
            iFilledCircle(300,500,5);
        }
        else if (selected_menu_idx == 2){
            iFilledCircle(300,450,5);
        }
        else if (selected_menu_idx == 3){
            iFilledCircle(300,400,5);
        }
        else if (selected_menu_idx == 0){
            iFilledCircle(300,500,5);
            selected_menu_idx = 1;
        }
    }

    if (gameState == 1)
    {
        iSetColor(85, 115, 250);
        iFilledRectangle(paddle_x + dbx, paddle_y + dby, paddle_width, paddle_height);
        iSetColor(213, 105, 43);
        iFilledCircle(ball_x, ball_y, ball_radius);
        iSetColor(255, 0, 0);
        iText(padding_x, screen_height-padding_y, "Lives: ", GLUT_BITMAP_HELVETICA_18);

        if (lives == 3)
        {
            iText(padding_x*3, screen_height-padding_y, "3", GLUT_BITMAP_HELVETICA_18);
        }
        else if (lives == 2)
        {
            iText(padding_x*3, screen_height-padding_y, "2", GLUT_BITMAP_HELVETICA_18);
        }
        else if (lives == 1)
        {
            iText(padding_x*3, screen_height-padding_y, "1", GLUT_BITMAP_HELVETICA_18);
        }
        iText(screen_width - 110, screen_height-padding_y, "Score", GLUT_BITMAP_HELVETICA_18);
        iText(screen_width - 50, screen_height-padding_y, "2000", GLUT_BITMAP_HELVETICA_18);
        if (lives < 1 && !isGameOver)
        {

            iPlaySound("assets/sounds/mus_gameover.wav", true);
            isGameOver = true;
            gameState = 2;
        }
    }
    if (gameState == 2)
    {
        //iShowImage(0, 0, "assets/images/gameover1.jpg");
        gameOver();
        iSetColor(255,255,255);
        if (selected_menu_idx == 1){
            iFilledCircle(300,350,5);
        }
        else if (selected_menu_idx == 2){
            iFilledCircle(300,300,5);
        }
        else if (selected_menu_idx == 0){
            iFilledCircle(300,350,5);
            selected_menu_idx = 1;
        }
        
    }
    if (gameState == 3)
    {
        controlsMenu();
        iSetColor(255,255,255);
        if (selected_menu_idx == 1){
            iFilledCircle(300,350,5);
        }
        if (selected_menu_idx == 2){
            iFilledCircle(300,300,5);
        }
        else {
            iFilledCircle(300,350,5);
            selected_menu_idx = 1;
        }
    }
}

/*
function iMouseMove() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes hfloat
}

/*5unction iMouseDrag() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }
}

/*
function iMouseWheel() is called when the user scrolls the mouse wheel.
dir = 1 for up, -1 for down.
*/
void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if (gameState == 0) // main menu
    {
        switch(key)
        {
        case 'w':
            if (selected_menu_idx>1){
                selected_menu_idx--;
            }
            break;
        case 's':
            if (selected_menu_idx<3){
                selected_menu_idx++;
            }
            break;
        case ' ':
            if (selected_menu_idx == 1)
                gameState = 1;
            else if (selected_menu_idx == 2)
            {
                gameState = 3; // Controls menu
            }
            else if (selected_menu_idx == 3)
                exit(0);
            selected_menu_idx = 0;
            break;
        default:
            break;
        }
    }

    if (gameState == 1) // main game
    {
        switch (key)
        {
        case 'w':
            dby += 20;
            if (dby >= 350)
                dby -= 20;
            break;
        case 's':
            dby -= 20;
            if (dby <=0)
                dby += 20;
            break;
        case 'd':
            dbx += 20;
            if ((450 + dbx) >= 900)
                dbx -= 20;
            if (dx == 0 && dy == 0)
            {
                ball_x += 20;
                if (ball_x >= (900 + paddle_width / 2))
                {
                    ball_x -= 20;
                }
            }
            break;
        case 'a':
            dbx -= 20;
            if ((450 + dbx) <= 0)
                dbx += 20;
            if (dx == 0 && dy == 0)
            {
                ball_x -= 20;
                if (ball_x <= paddle_width / 2)
                {
                    ball_x += 20;
                }
            }
            break;
        // place your codes for other keys here
        case ' ':
        {
            dx = 10;
            dy = 10;
        }
        default:
            break;
        }
    }
    if (gameState == 2) // game over
    {
        switch(key)
        {
        case 'w':
            if (selected_menu_idx>1){
                selected_menu_idx--;
            }
            break;
        case 's':
            if (selected_menu_idx<2){
                selected_menu_idx++;
            }
            break;
        case ' ':
            if (selected_menu_idx == 1)
                gameState = 0;
            else if (selected_menu_idx == 2)
            {
                exit(0);
            }
            selected_menu_idx = 0;
            break;
        default:
            break;
        }
    }
    
    if (gameState == 3) // controls menu
    {
        switch(key)
        {
        case 'w':
            if (selected_menu_idx>1){
                selected_menu_idx--;
            }
            break;
        case 's':
            if (selected_menu_idx<2){
                selected_menu_idx++;
            }
            break;
        case ' ':
            if (selected_menu_idx==1)
                gameState = 0;
            if (selected_menu_idx==2)
                exit(0);
            selected_menu_idx = 0;
            break;
            
        default:
            break;
        }

    }
}
void ballMotion()
{
    ball_x += dx;
    ball_y += dy;

    if (ball_x + ball_radius > screen_width || ball_x - ball_radius < 0)
    {
        dx *= (-1);
    }

    if (ball_y + ball_radius > screen_height)
    {
        dy *= (-1);
    }

    if (((ball_x > (450 + dbx)) && ball_x < (550 + dbx)) && ball_y < (paddle_height + paddle_y + dby + ball_radius))
    {
        dy *= (-1);
        score += 2000; // score +2000 every time it hits paddle, but cant display it rn :(
    }
    if (ball_y < paddle_y)
    {
        lives--;
        dbx = dby = 0;
        dx = dy = 0;
        ball_x = paddle_x + dbx + paddle_width / 2;
        ball_y = paddle_height + paddle_y + ball_radius;
    }
}
/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    switch (key)
    {
    case GLUT_KEY_END:
        // do something
        break;
    // place your codes for other keys here
    default:
        break;
    }
}



// *********************************************************************************************
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    iSetTimer(15, ballMotion);

    // place your own initialization codes here.
    iInitializeSound();
    iInitialize(screen_width, screen_height, "Breaking Ball");
    return 0;
}

void gameOver(void)
{
    iSetColor(255, 0, 0);
    iText(350,450,"You played like a total novice. Wanna quit?",GLUT_BITMAP_HELVETICA_18);
    iText(450,500,"HAHAHAHA",GLUT_BITMAP_HELVETICA_18);
    iSetColor(255,255,255);
    iText(350,350,"You think getting rid of me would be that easy?");
    iText(400,300,"Yeah, I better quit :(");
    //iPlaySound("assets/sounds/mus_gameover.wav", true);
}

void mainMenu(void)
{


    //iShowImage(0, 0, "assets/images/mainmenu.png");
    iSetColor(255,255,255);
    iText(350,700,"Do you like BALLS?",GLUT_BITMAP_HELVETICA_18);
    iText(350,500,"PLAY GAME");
    iText(350,450,"CONTROLS");
    iText(350, 400, "QUIT");

}

void controlsMenu(void){
    iSetColor(255,255,255);
    iText(350,450,"You don't know how to play DXBALL?",GLUT_BITMAP_HELVETICA_18);
    iText(450,500,"LOL NOOB",GLUT_BITMAP_HELVETICA_18);
    iText(420,350,"Just wanted to check");
    iText(360,300,"I don't wanna play this shit anymore");
}




