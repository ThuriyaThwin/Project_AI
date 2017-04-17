#ifndef CSP_H
#define CSP_H


/*
    STRUCTURE DU CSP :

    Une matrice de contrainte, qui est une matrice, tableau à deux dimensions.
    A une case [i][j] de notre matrice, est associé un pointeur vers un autre tableau à deux dimensions.
    Cet autre tableau à deux dimensions contient lui uniquement des entiers.

    Imaginons le problème des pigeons, 3 pigeons, 2 nids :

    Matrice de contraintes ( nombre de variable * nombre de variable ) :

    matrixConstraint = {

                        | var0  | var1  | var2  |
                ---------------------------------
                var0    | NULL  | *tab  | *tab  |
                ---------------------------------
                var1    | *tab  | NULL  | *tab  |
                ---------------------------------
                var2    | *tab  | *tab  | NULL  |

    };


    Les variables ici, ce sont nos trois pigeons.
    Pigeon 1 -> var0 ;
    Pigeon 2 -> var1 ;
    Pigeon 3 -> var2 ;

    A une case [i][j] nous pouvons donc associer soit NULL, soit un nouveau tableau à deux dimensions.
    pas de contrainte entre les deux variables <------^^^^              ^^^^^^-------> contrainte existe entre ces deux variables

    Notre tableau à deux dimensions d'entier représente les tuples ( couple de valeur ) que peuvent prendre deux variables soumises à une contrainte.
    Dans notre exemple :

    matrixValue = {

                | val0  | val1              <----- valeur de notre pigeon1
        -----------------------
        val0    |   0   |   1
        -----------------------
        val1    |   1   |   0

        ^^^-------------------------- valeur de notre pigeon0

    };

    Pour accéder à une valeur de notre tableau de tuples pour la contrainte entre variable0 et variable1 :

    int** matrixValue;
    int**** matrixConstraint;

    matrixConstraint[0][1] = matrixValue;
        -> traduction : contrainte entre 0 & 1 a pour tuples permis le tableau matrixValue.

    accéder aux tuples de la contrainte C( 0, 1 ) :
        matrixConstraint[0][1][0][0] == 0;
        matrixConstraint[0][1][0][1] == 1;
        matrixConstraint[0][1][1][0] == 1;
        matrixConstraint[0][1][1][1] == 0;


    Maintenant, lors de nos déplacements dans notre matrice de domaine grâce à nos différentres algorithmes il est possible d'effectuer l'opération suivante :

    " y a-t-il une contrainte entre le pigeon0 et le pigeon 1 ? "
        Si l'adresse matrixConstraint[0][1] != NULL
        Alors
            Nous regardons la valeur de pigeon0 et de pigeon1
            -> càd regarder dans la matrice de domaine quel est l'index de la colonne que la ligne 0 à mis à 1, et de même pour la ligne 1.
            Une fois ces deux index récupérés, nous pouvons parcourir l'ensemble des tuples autorisés par la contrainte.

            --> Si les deux index situés dans le domaine ne sont pas trouvés dans les tuples :

            imaginons :


            matrixDomain = {

                                | val0  | val1
                        ------------------------
                        var0    | 1     | 0                 <----- domaine0
                        ------------------------
                        var1    | 1     | 0                 <----- domaine1
                        ------------------------
                        var2    | 0     | 0
            };




            domaine0 = 0;
            domaine1 = 0;

            le tuple (0,0) ==  matrixConstraint[0][1][0][0] --> renvoie 0, donc non possible, contrainte violée !
                                index domain0  ------^^  ^^------- index domaine1
*/


typedef struct CSP {
    int**** matrixConstraint;
    int** matrixDomain;
} CSP;

CSP* initCSP(int nbVariable, int nbValue);
void freeCSP(CSP* csp, int nbVariable, int nbValue);
void printCSP(CSP* csp, int nbVariable, int nbValue);

int* newTab(int nbElement);
int** newMatrix(int lenDimOne, int lenDimTwo);
int**** newConstraintMatrix(int nbElement);

void freeConstraintMatrix(int**** matrix, int nbConstraintElement, int nbTupleElement);
void freeMatrix(int** matrix, int lenDimOne);
void printTab(int* tab, int nbElement);
void printMatrix(int** matrix, int lenDimOne, int lenDimTwo);

int checkForConstraint(CSP* csp, int indexRowVariable, int nbVariable, int nbValue);
int checkAllowedCouple(CSP* csp, int indexVarOne, int indexVarTwo, int nbValue);


#endif //CSP_H
