#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreClesWorker(Arbre234 a, int nbCle) {
  if (a == NULL || a->t == 0) {
    return 0;
  } else {
    return a->t - 1 + NombreClesWorker(a->fils [0], 0) + NombreClesWorker(a->fils [1], 0) + NombreClesWorker(a->fils [2], 0) + NombreClesWorker(a->fils [3], 0);
  }
}

int NombreCles (Arbre234 a) {
  
  if (a->t == 0) {
    return 0;
  } else {
    return NombreClesWorker(a, 0);
  }
}

int CleMax (Arbre234 a)
{
  if (a == NULL) return -1;

  Arbre234 current = a;

  while (current->fils[current->t] != NULL && current->fils[current->t]->t != 0)
  {
    current = current->fils[current->t];
  }
  return current->cles[current->t-1];
}

int CleMin (Arbre234 a)
{
  if (a == NULL) return -1;

  Arbre234 current = a;

  while (current->fils[0] != NULL && current->fils[0]->t != 0)
  {
    current = current->fils[0];
  }

  return current->cles[0] ;

}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */

  return NULL ;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  /* 
     calculer le nombre de feuilles, de 2-noeuds, 3-noeuds,et 4-noeuds
  */
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */
  
  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;
  
  afficher_arbre (a, 0) ;

    printf ("==== Nombre de Clé arbre ====\n") ;

    printf("Nombre de cle : %d\n", NombreCles(a));

    printf ("==== MIN MAX ====\n") ;

    printf("MIN : %d\n", CleMin(a));

    printf("MAX : %d\n", CleMax(a));

    printf ("==== Hauteur arbre ====\n") ;

}
