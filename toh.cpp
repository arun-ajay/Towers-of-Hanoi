#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <time.h>
using namespace std;
//
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}


void draw_box(int x,int y,int array[], int top, char letter)
{
    if (top == -1)
    {
        gotoxy(x,y+2);
        cout << "  " << letter << "  ";
        return;
    }
    int y_store = y;
    char horizontal_line = 205;
    char vertical_line=186;
    char TR_border_corner = 187;
    char TL_border_corner = 201;
    char BL_border_corner = 200;
    char BR_border_corner = 188;
    char BL_border_corner_surface = 204;
    char graphic = 219;
    int bottom_block = array[0];
    int max_char = bottom_block*2 - 1;
    gotoxy(x,y);
    int count,row_char_limit,space_limit;
    int print_tracker;
    int i = 0;
    int y_tracker = 0;
    for (i = 0; i <= top; i++)
    {
        if (array[i] == bottom_block)
        {
            while(y_tracker < 3)
            {
                gotoxy(x,y-y_tracker);
                if(y_tracker == 0)
                {
                    cout << BL_border_corner;

                    for (print_tracker = 0; print_tracker < max_char; print_tracker ++)
                    {
                        cout << horizontal_line;
                    }

                    cout << BR_border_corner;
                    y_tracker ++;
                }
                else if (y_tracker == 1)
                {
                    cout << vertical_line;
                    for(print_tracker = 0; print_tracker < max_char; print_tracker ++)
                    {
                        cout << graphic;
                    }
                    cout << vertical_line;
                    y_tracker ++;
                }
                else if (y_tracker == 2)
                {
                    cout << TL_border_corner;
                    for(print_tracker = 0; print_tracker < max_char; print_tracker ++)
                    {
                        cout << horizontal_line;
                    }
                    cout << TR_border_corner;
                    y_tracker ++;
                }
            }
            continue;
        }
        y -= y_tracker;
        row_char_limit = array[i]*2 - 1;
        space_limit = (max_char - row_char_limit) / 2;
        y_tracker = 0;
        gotoxy(x,y);

        while (y_tracker < 3)
        {
            gotoxy(x+space_limit,y-y_tracker);
            if(y_tracker == 0)
            {

                cout << BL_border_corner;
                for (print_tracker = 0; print_tracker < row_char_limit; print_tracker ++)
                {
                    cout << horizontal_line;
                }
                cout << BR_border_corner;
                y_tracker ++;
            }
            else if (y_tracker == 1)
            {
                cout << vertical_line;
                for(print_tracker = 0; print_tracker < row_char_limit; print_tracker ++)
                {
                    cout << graphic;
                }
                cout << vertical_line;
                y_tracker ++;
            }
            else if (y_tracker == 2)
            {

                cout << TL_border_corner;
                for(print_tracker = 0; print_tracker < row_char_limit; print_tracker ++)
                {
                    cout << horizontal_line;
                }
                cout << TR_border_corner;
                y_tracker ++;
            }
        }
    }

    gotoxy(x,y_store+2);
    for (print_tracker = 1; print_tracker <= (max_char+1)/2; print_tracker ++)
        cout << " ";
    cout << letter;

}



//collects the choices the user makes and does a check
int options(char choices[], int &win)
{
    int error;
    char option1, option2;
    fflush(stdin);
    cout << endl << "Move from: " << endl;
    cin >> option1;
    if (option1 == 'q')
    {
        cout << "Terminating program..." << endl;
        error = 0;
        win = 1;
        return error;

    }
    cout << endl << "To: " << endl;
    cin >> option2;
    if (option2 == 'q')
    {
        cout << "Terminating program..." << endl;
        error = 0;
        win = 1;
        return error;

    }
    int count = 0;

    if (option1 >= 'A' && option1 <= 'Z')
    {
        option1 += 32;
    }
    if (option2 >= 'A' && option2 <= 'Z')
    {
        option2 += 32;
    }
    if (option1 != option2)
    {
        switch(option1)
        {
            case 'a': case 'b': case 'c':
            count++;
        }
        switch(option2)
        {
            case 'a': case 'b': case 'c':
            count++;
        }
    }

    if(count != 2)
    {
        cout << "Row not recognized." << endl << "Please try again." << endl;
        error = 0;
        return error;
    }

    choices[0] = option1;
    choices[1] = option2;
}
int swapper_function(int &arraytop1, int &arraytop2, int array1[], int array2[])
{
    int error = 0;
        if((arraytop1 == -1 && arraytop2 == -1) || arraytop1 == -1)
    {
        cout << "Invalid move." << endl << "Try again." << endl;
        error = 0;
        return error;
    }
    if(arraytop2 == -1 || (array1[arraytop1] < array2[arraytop2]) )
    {
        arraytop2 ++;
        array2[arraytop2] = array1[arraytop1];
        array1[arraytop1] = 0;
        arraytop1 --;
    }
    else
    {
        cout << "Invalid move." << endl << "Try again." << endl;
        error = 0;
        return error;
    }
}
int solution_check2(int top, int &win, int cont)
{
    if(top==(2 + cont))
       return win=1;
}
int main()
{
    cout << "Welcome to Towers of Hanoi." << endl << "The goal is to shift all the blocks to either Row B or C in the same order as A." << endl << endl;
    cout << "How to play:" << endl << "Select a row and move its top block to another column." << endl << "A move is only valid if the block being moved is taking over any empty spot";
    cout << " or is placed above a bigger block." << endl << endl;
    int cont = 0;
    int round = 1;
    int xa = 20,xb = 30 ,xc = 40;
    int dy = 15, y = 10;
    do{

        int array1[10],array2[10],array3[10];
        int topA=2 + cont,topB = -1,topC = -1;

        int size = 3 + cont;
        int i;
        int count = 3 + cont;
        for (i = 0; i < size; i++)
        {
            array1[i] = count;
            count --;
        }
        for (i = 0; i < size; i++)
        {
            array2[i] = 0;
            array3[i] = 0;
        }
        int win = 0;
        char a,b,c;
        a = 'a';
        b = 'b';
        c = 'c';

        draw_box(xa,dy,array1,topA, a);
        draw_box(xb,dy,array2,topB, b);
        draw_box(xc,dy,array3,topC, c);
        cout << endl << endl;
        system("pause");


        //below begins game

        int error;
        int check;
        //time_t start = clock(),end = clock(),temp = clock(),temp2 = clock();
        //start = clock();
        do{
            system("cls");
            //below displays current matrix
            cout << "Round " << round << " (press q to quit)";
            draw_box(xa,y,array1,topA, a);
            draw_box(xb,y,array2,topB, b);
            draw_box(xc,y,array3,topC, c);


            //below checks the options the user made
            char choices[2];
            check = options(choices,win);
            if (check == 0)
            {
            //temp = clock();
            system("pause");
            continue;
            }
            //below attempts to swap blocks if possible
            if (choices[0] == a && choices[1] == b)
            error = swapper_function(topA, topB,array1,array2);
            else if (choices[0] == a && choices[1] == c)
            error = swapper_function(topA, topC,array1,array3);
            else if (choices[0] == b && choices[1] == a)
            error = swapper_function(topB, topA,array2,array1);
            else if (choices[0] == b && choices[1] == c)
            error = swapper_function(topB, topC,array2,array3);
            else if (choices[0] == c && choices[1] == a)
            error = swapper_function(topC, topA,array3,array1);
            else if (choices[0] == c && choices[1] == b)
            error = swapper_function(topC, topB,array3,array2);

            if(error == 0)
            {
                system("pause");
                continue;
            }
            cout << endl << "Shifting blocks..." << endl;
            //temp = clock();
            system("pause");
            //below checks if a solution was created.
            solution_check2(topB,win,cont);
            solution_check2(topC,win,cont);
        }while(win != 1);

        if (check == 0)
            return 0;
        system("cls");

        draw_box(xa,y,array1,topA, a);
        draw_box(xb,y,array2,topB, b);
        draw_box(xc,y,array3,topC, c);
        cout << endl << "Congrats! You've won!";
        cout << endl << "Proceed to next level? (Y/N)" << endl;
        char next_level_choice;
        cin >> next_level_choice;
        if (next_level_choice == 'y' || next_level_choice == 'Y')
        {
            cont ++;
            win = 0;
            round ++;
            system("cls");
        }
        else
        {
            cont = -1;
        }

        xa += 3;
        xb += 3;
        xc += 3;
        y += 5;
    }while(cont >= 0);
    return 0;
}
