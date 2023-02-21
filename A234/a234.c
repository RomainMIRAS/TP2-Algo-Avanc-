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
  Arbre234 pred = NULL;

  while(current->t != 0){
    pred = current;
    current = (current->t == 4) ? current->fils[3] : current->fils[2];
  }

  return (pred->t == 4 ) ? pred->cles[2]: pred->cles[1];
}

int CleMin (Arbre234 a)
{
  if (a == NULL) return -1;

  Arbre234 current = a;
  Arbre234 pred = NULL;

  while(current->t != 0){
    pred = current;
    current = (current->t == 2) ? current->fils[1] : current->fils[0];
  }

  return (pred->t == 2 ) ? pred->cles[1]: pred->cles[0];

}

Arbre234 RechercherCle (Arbre234 a, int cle) { //42 lignes
  if (a == NULL || a->t == 0)
    return NULL;

  if (cle == a->cles[1])
    return a;

  if (a->cles[1] > cle) {
    if (a->t > 2) {
      if (cle == a->cles[0]) {
        return a;
      }
      return a->cles[0] > cle ? RechercherCle(a->fils[0], cle) : RechercherCle(a->fils[1], cle);
    } else {
      return RechercherCle(a->fils[1], cle);
    }
  } else { 
    if (a->t > 3) {
      if (a->cles[2] == cle) {
        return a;
      }
      return a->cles[2] < cle ? RechercherCle(a->fils[3], cle) : RechercherCle(a->fils[2], cle);
    }
  }
  return RechercherCle(a->fils[2], cle);
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  if (a->t == 0) {
    *feuilles += 1; 
  } else {
    switch (a->t)
    {
    case 2:
    *noeud2 += 1;
    AnalyseStructureArbre(a->fils[1],feuilles,noeud2,noeud3,noeud4);
    AnalyseStructureArbre(a->fils[2],feuilles,noeud2,noeud3,noeud4);
      break;
    case 3:
    *noeud3 += 1;
            AnalyseStructureArbre(a->fils[0],feuilles,noeud2,noeud3,noeud4);
        AnalyseStructureArbre(a->fils[1],feuilles,noeud2,noeud3,noeud4);
    AnalyseStructureArbre(a->fils[2],feuilles,noeud2,noeud3,noeud4);
      break;
    case 4:
    *noeud4 += 1; 
        AnalyseStructureArbre(a->fils[0],feuilles,noeud2,noeud3,noeud4);
    AnalyseStructureArbre(a->fils[1],feuilles,noeud2,noeud3,noeud4);
        AnalyseStructureArbre(a->fils[2],feuilles,noeud2,noeud3,noeud4);
    AnalyseStructureArbre(a->fils[3],feuilles,noeud2,noeud3,noeud4);
      break;
    default:
      break;
    }
  }
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

      printf ("==== Recherche Cle arbre ====\n") ;

    afficher_arbre (RechercherCle(a, 82), 0) ;

    printf ("==== Analyse Syntax ====\n") ;

    int feuille = 0;
    int noeud2 = 0;
    int noeud3 = 0;
    int noeud4 = 0;

    AnalyseStructureArbre(a,&feuille,&noeud2,&noeud3,&noeud4);

    printf("Feuille : %d\n", feuille);
    printf("Noeud 2 : %d\n", noeud2);
    printf("Noeud 3 : %d\n", noeud3);
    printf("Noeud 4 : %d\n", noeud4);
}
