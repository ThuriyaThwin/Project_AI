#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){
    /*
        Tableau permettant de stocker la contrainte violée la plus profonde pour chaque variable i
    */
    int* tabDeepestVariable = createNewTab(csp->nbVariable);

    int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    long int nb = 0;

    // TANT QUE la toute dernière valeur de la première variable n'est pas "vue", on continue
    while(csp->matrixDomain[0][csp->nbValue-1] != -1){

        ++nb;
        csp->matrixDomain[Iposition][Jposition] = 1;
        checkC = checkForConstraint(csp, Iposition);

        printf("[%d][%d]\n", Iposition, Jposition);

        //Non violation:
        if( checkC < 0 ){
            addCheckedValue(csp, Iposition, Jposition); // Sauvegarde

            //Variables à instancier restante
            //Le but est ici de descendre dans l'arbre
            if( Iposition < csp->nbVariable-1 ){
                ++Iposition; //Passage à la prochaine variable
                Jposition = 0; //On reprend à la valeur 0
                tabDeepestVariable[Iposition] = 0; //init contrainte plus profonde pour la prochaine variable
            }

            //Toutes les variables sont instanciées -> solution trouvée !
            //Le but est ici de remonter dans l'arbre
            else {
                csp->matrixDomain[Iposition][Jposition] = -1;
                //printf("FOUND\n");
                //printTab(csp->tabCheckedValue, csp->nbVariable);

                //Tester si nous sommes sur la dernière valeur possible pour la dernière variable
                if( Jposition == csp->nbValue-1 ){
                    //ici, il on remonte avec un simple backtrack
                    while( Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1 ){
                        initTab(csp->matrixDomain[Iposition], csp->nbValue, 0);
                        tabDeepestVariable[Iposition] = 0; //remise à 0
                        --Iposition; //backtrack simple vers la valeur antérieur
                    }
                    Jposition = csp->tabCheckedValue[Iposition]; //Reprise de la descente dans l'arbre à partir de la valeur j
                    csp->matrixDomain[Iposition][Jposition] = -1; //On indique qu'il s'agit d'un cas vu
                }
                //Dans tous les cas, passage à la prochaine valeur
                ++Jposition;
            }
        }

        else{ //violation:

            //csp->matrixDomain[Iposition][Jposition] = -1; //On indique que la variable a fail

            //Sauvegarde pour la variable i, de la contrainte violée la plus profonde dans l'arbre de recherche par toutes ces valeurs:
            if( checkC > tabDeepestVariable[Iposition] )
                tabDeepestVariable[Iposition] = checkC;

            //Est-ce qu'on a atteint la toute dernière valeur possible pour une variable i
            if( Jposition == csp->nbValue-1 ){
                //csp->matrixDomain[Iposition][Jposition] = -1;
                //Si c'est le cas, alors nous somme dans un cas de backjumping:
                /*
                    Ici on veut revenir sur la variable la plus profonde dans l'arbre de recherche qui est en cause de l'échec:

                    Il nous faut donc faire un backjumping jusqu'à arriver à la variable en question, tout en s'assurant de bien "balayer"
                    derrière soit.
                */

                //if( Iposition == csp->nbVariable-1 ){
                    /*int indexVar = tabDeepestVariable[Iposition];
                    while( Iposition != indexVar ){
                        initTab(csp->matrixDomain[Iposition], csp->nbValue, 0);
                        tabDeepestVariable[Iposition] = 0; //remise à 0 du compteurs
                        --Iposition; //On décrémente, remontée dans l'arbre
                    }*/
                //}
                //else{
                    initTab(csp->matrixDomain[Iposition], csp->nbValue, 0);
                    tabDeepestVariable[Iposition] = 0; //remise à 0 du compteurs
                    --Iposition; //On décrémente, remontée dans l'arbre
                /*}*/


                //Une fois arrivé à notre variable en question, il nous faut vérifier que la valeur j instanciée à cet instant n'est pas la toute dernière.
                //Sinon, on recherche à trouver la prochaine variable qui n'est pas instanciée à la dernière valeur:
                while( Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1 ){
                    initTab(csp->matrixDomain[Iposition], csp->nbValue, 0);
                    tabDeepestVariable[Iposition] = 0;
                    --Iposition;
                }
                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;
            }

            //Dans tous les cas, on passe à la prochaine valeur
            ++Jposition;
        }
    }

    printf("\n>>>> %lu itérations.\n", nb);
    free( tabDeepestVariable );
}
