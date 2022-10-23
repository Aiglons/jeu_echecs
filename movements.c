# include <stdio.h>
# include <ctype.h>

# define HPOS(a) (a) % 8 // l'abscisse de la position sur l'echequier
# define VPOS(a) (a) / 8 // l'ordonnee ...

/* note :
pos = x
pos horizontal = x % 8
pos vertical = x / 8

mouvement = {x, y, z, a}
x = mouvement horizontal
y = mouvement vertical
z = peut repeter ce mouvement ? (0 : nope, other value : yes)
a =  son mouvement est multi-directionnel ? (0 : nope, autre valeur : yes)
nb : if x = 0 et y = 0 --> la piece peut bouger dans toutes les directions ! 
*/


// VARIABLES GLOBALES -----------------------------------------------------------------------------
// un dictionnaire de mouvement pour chaque piece
const int size_dict_movement = 6;
const char piece_key[6] = {       'p',          'r',          'n',          'b',          'k',          'q'};
const int movement_value[6][4] = {{1, 0, 0, 0}, {1, 0, 1, 1}, {2, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};
/* NB : pour la suite, le fait que les x y sont positives sera tres important !!!
(surtout pour la fonction one_move) */


// PROTOTYPES ------------------------------------------------------------------------------------
int get_piece_key(const char signature);
int check_
int direction_move(const int position, const int destination, const int movement[4]); // -1
int check_movement(const int position, const int destination, const char signature); // faux --> 0 et vrai --> autres valeurs


// FONCTIONS -------------------------------------------------------------------------------------
int get_piece_key(const char signature)
{
    for (int i = 0; i <size_dict_movement; i++)
    {
        if(piece_key[i] == signature || toupper(piece_key[i]) == signature)
        {
            return i;
        }
    }
    return -1; // il n'a pas d'indice...
}

int one_move(const int position, const int destination, const int movement[4])
{
    int init_posH = HPOS(position);
    int init_posV = VPOS(position);
    int dest_posH = HPOS(destination);
    int dest_posV = VPOS(destination);

    if ((init_posH + movement[0]) < dest_posH && (init_posV + movement[1] < dest_posV))
    {
            // la piece reste en bas a gauche de la destination
        return (position + movement[0] + movement[1] * 8); 
    }

    // LE MOUVEMENT: x = movement[0] et y = movement[1] 
    if (movement[3] != 0) // la pièce est multi-directionnelle
    {
        if ((init_posH - movement[0]) > dest_posH && (init_posV - movement[1] > dest_posV))
        {
            // la piece est en haut a droite de la destination
            return (position - movement[0] - movement[1] * 8); 
        }
        if ((init_posH - movement[0]) > dest_posH && (init_posV + movement[0] < dest_posV))
        {
            // la piece est en bas a droite de la destination
            return(position + movement[1] + movement[0] * 8);
        }
        if ((init_posH + movement[0]) < dest_posH && (init_posV + movement[1] < dest_posV))
        {
            //la piece est en haut a gauche de la destination
            return(position - movement[0] + movement[1] * 8)
        }
        
    }
    
    // LE MOUVEMENT: x = movement[1] et x = movement[1] 
    if (movement[3] != 0)
    {
        if ((init_posH - movement[0]) > dest_posH && (init_posV - movement[1] > dest_posV))
        {
            // la piece est en haut a droite de la destination
            return (position - movement[0] - movement[1] * 8); 
        }
        if ((init_posH - movement[0]) > dest_posH && (init_posV + movement[0] < dest_posV))
        {
            // la piece est en bas a droite de la destination
            return(position + movement[1] + movement[0] * 8);
        }
        if ((init_posH + movement[0]) < dest_posH && (init_posV + movement[1] < dest_posV))
        {
            //la piece est en haut a gauche de la destination
            return(position - movement[0] + movement[1] * 8)
        }
        
    }

    return -1; // le mouvement ne peut pas aller au-dela de la destination    
}

int check_movement(int position, const int destination, const char signature)
{
    const int ind_key = get_piece_key(signature); // cherche le mouvement de la piece
    int inter_pos = position;

    // Il faut check le cas ou le pion peut manger en diagonale (peut-etre une fonction a part)

    if(movement_value[ind_key][2] != 0)
    {
        // le mouvement est repete avec une boucle while
        while(inter_pos != -1)
        {
            position = inter_pos;
            inter_pos = one_move(position, destination, movement_value[ind_key]);
        }
    }
    else
    {
        // le mouvement est repete une seule fois
        inter_pos = one_move(inter_pos, destination, movement_value[ind_key]);
    }
    
    if(inter_pos == destination)
    {
       return 1; // la piece est bien arrivee à son destination prevue
    }
    return 0;
}
