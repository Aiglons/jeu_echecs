# include <stdio.h>

/* note : 
'0' --> blank case
'lowercase' --> black piece
'uppercase' --> white piece
'p' --> pawn
'r' --> rook
'n' --> knight
'b' --> bishop
'k' --> king
'q' --> queen
*/


// GLOBAL VARIABLES ---------------------------------------------------------------------------------------
const int size_chessboard = 64; // 8 * 8  


// SECONDARY FUNCTIONS ------------------------------------------------------------------------------------
void init_chessboard(char* chessboard, const int size)
{
    for (int i = 0; i < size_chessboard; i++)
    {
        size_chessboard[i] = '0';
    }
}


// MAIN FUNCTION ------------------------------------------------------------------------------------------
int main (int argc, char ** argv){  
    char *chessboard = (char *) malloc(sizeof(char) * 8 * 8); //array of a classic chessboard
    init_chessboard(chessboard, size_chessboard);
    return 0;
}
