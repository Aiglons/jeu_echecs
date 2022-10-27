# include "game_data.h"
# include "logic_data.h"
# include "chessboard_manager.h"
# include <ctype.h>
# include <wchar.h>


// VARIABLES GLOBALES --------------------------------------------------------------

// variables pour savoir la derniere modif de chess_virtual
char elt_replaced;
char pos_init;
char pos_dest;

extern char chessboard[8][8];


// FONCTIONS -----------------------------------------------------------------------

int is_same_color(const char p1, const char p2)
{
    if( (isupper(p1) && isupper(p2)) || (islower(p1) && islower(p2)) )
    {
        return 1;
    }
    // pas de la meme couleur T-T (no racismo)
    return 0;
}


int check_out_of_range(const int posX, const int posY)
{
    if(posX < 0 || posX >= 8 || posY < 0 || posY >= 8)
    {
        return 1;
    }
    return 0;
}


int find_king_pos(const char signature)
{
    for (int i = 0; i < 8; i ++)
    {
        for (int j = 0; j < 8; j ++)
        {
            if(chessboard[i][j] == signature)
            {
                return j + i * 8;
            }
        }
    }

    return -1; // bizarre qu'il n'y a pas de roi 
}


void reset_allies(int pos_allies[16])
{
    for (int i = 0; i < 16; i++)
    {
        pos_allies[i] = -1;
    }
}


// On recupere un ensemble de pieces alliees 
void collect_allies(int pos_pieces_allies[16], const char signature_ally)
{
    reset_allies(pos_pieces_allies); // on reset les pos des allies
    char element;
    int ind_array = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j ++)
        {
            element = chessboard[i][j];   
            if(is_same_color(element, signature_ally)) // on a trouve un allie
            {
                pos_pieces_allies[ind_array] = j + i * 8;
                ind_array ++;
            }

            if(ind_array == 16) // on a rempli au maximum notre tableau !
            {
                return;
            }
        }
    }
}


void make_move(const int position, const int destination)
{
    pos_init = position;
    pos_dest = destination;
    elt_replaced = chessboard[VPOS(destination)][HPOS(destination)];

    chessboard[VPOS(destination)][HPOS(destination)] = chessboard[VPOS(position)][HPOS(position)];
    chessboard[VPOS(position)][HPOS(position)] = '0';    
}
 
void undo_move()
{    
    chessboard[VPOS(pos_dest)][HPOS(pos_dest)] = chessboard[VPOS(pos_init)][HPOS(pos_init)];
    chessboard[VPOS(pos_dest)][HPOS(pos_dest)] = elt_replaced;    
}
