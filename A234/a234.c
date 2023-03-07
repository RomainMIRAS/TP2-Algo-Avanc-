#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __A234_H__
  #define __A234_H__
  #include "a234.h"
#endif

#define MAX_FILE_SIZE       32
#define MAX_PILE_SIZE       32
////////////////////////////////////////////////////////////

/// FILE

///////////////////////////////////////////////////////////*

typedef struct {
  int tete ;
  int queue ;
  Arbre234 Tab [MAX_FILE_SIZE] ;
} file_t, *pfile_t ;

pfile_t creer_file ()
{
  pfile_t f = (pfile_t) malloc (sizeof (file_t));
  if (f == NULL)
    return NULL;

  //Set tab à nulle
  for (int i = 0; i < MAX_FILE_SIZE; i++)
    f->Tab[i] = NULL;
  f->tete = 0;
  f->queue = 0;
  return f;

}

int detruire_file (pfile_t f)
{  
  if (f == NULL)
    return -1;
  free (f);
  return 0;
}

int file_vide (pfile_t f)
{
  return (f->tete == f->queue);
}

int file_pleine (pfile_t f)
  {
  return (f->tete == (f->queue + 1) % (MAX_FILE_SIZE+1));
  }

Arbre234 defiler (pfile_t f)
  {
  if (file_vide (f))
    return NULL;
  f->tete = (f->tete + 1) % (MAX_FILE_SIZE+1);
  return f->Tab[f->tete];
  }

int enfiler (pfile_t f, Arbre234 p)
{
  if (file_pleine (f))
    return -1;
  f->queue = (f->queue + 1) % (MAX_FILE_SIZE+1);
  f->Tab[f->queue] = p;
  return 0;
}



////////////////////////////////////////////////////////////

/// PILE

///////////////////////////////////////////////////////////*

typedef struct {
  int sommet ;
  Arbre234 Tab [MAX_PILE_SIZE] ;
} pile_t, *ppile_t ;


ppile_t creer_pile ()
{
  ppile_t p = (ppile_t) malloc (sizeof (pile_t));
  if (p == NULL)
    return NULL;

  //Set tab à nulle
  for (int i = 0; i < MAX_PILE_SIZE; i++)
    p->Tab[i] = NULL;
  p->sommet = 0;
  return p;
}

int detruire_pile (ppile_t p)
{
  // Free tab
  for (int i = 0; i < MAX_PILE_SIZE; i++)
    free (p->Tab[i]);
  // Free pile

  free (p);
  return 0;
}  

int pile_vide (ppile_t p)
{
  return p->sommet == 0;
}

int pile_pleine (ppile_t p)
 {
  return p->sommet == MAX_PILE_SIZE;
  } 

Arbre234 depiler (ppile_t p)
{
  if (pile_vide (p))
    return NULL;
  p->sommet--;
  return p->Tab[p->sommet];
}

int empiler (ppile_t p, Arbre234 pn)
  {
  if (pile_pleine (p))
    return -1;
  p->Tab[p->sommet] = pn;
  p->sommet++;
  return 0;
  }


#define max(a,b) ((a)>(b)?(a):(b))


////////////////////////////////////////////////////////////

/// ARBRE 234

///////////////////////////////////////////////////////////*

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

int sommeNoeud (Arbre234 a) {

  if (a == NULL) {
    return 0;
  }

  switch (a->t)
  {
  case 0:
    return 0;
  
  case 2:
    return a->cles[1];

    case 3:
    return a->cles[1] + a->cles[0];

    case 4:
    return a->cles[1] + a->cles[0] + a->cles[2];


  default:
    return 0;
  }
}

Arbre234 noeud_max_worker (Arbre234 a, Arbre234 currentMax, int value) {

  if (a == NULL || a->t == 0) {
    return currentMax;
  }

  if (value < sommeNoeud(a)) {
    value = sommeNoeud(a);
    currentMax = a;
  }

  Arbre234 temp = NULL;
  Arbre234 temporaire = NULL;

  if (a->t > 3) { // Ici on gère tout les fils 3
    temp = sommeNoeud(noeud_max_worker(a->fils[3], currentMax, value)) > value ? noeud_max_worker(a->fils[3], currentMax, value): currentMax;
  }

  if (a->t > 2) { // Ici on gère tout les fils 0
    temporaire = sommeNoeud(noeud_max_worker(a->fils[0], currentMax, value)) > value ? noeud_max_worker(a->fils[0], currentMax, value): currentMax;
  }

  temp = sommeNoeud(temp) > sommeNoeud(temporaire) ? temp : temporaire;

  if (a->t > 0) { // Ici on gère tout les fils 1 et 2s
    Arbre234 temp1 = sommeNoeud(noeud_max_worker(a->fils[1], currentMax, value)) > value ? noeud_max_worker(a->fils[1], currentMax, value): currentMax;
    Arbre234 temp2 = sommeNoeud(noeud_max_worker(a->fils[2], currentMax, value)) > value ? noeud_max_worker(a->fils[2], currentMax, value): currentMax;
    temporaire = sommeNoeud(temp1) > sommeNoeud(temp2) ? temp1: temp2;
  }

  temp = sommeNoeud(temp) > sommeNoeud(temporaire) ? temp : temporaire;

  return temp;
}

Arbre234 noeud_max (Arbre234 a) {
  if (a->t == 0) {
    return 0;
  } else {
    return noeud_max_worker(a, a, sommeNoeud(a));
  }
}


void Afficher_Cles_Largeur (Arbre234 a)
{

  pfile_t f = creer_file();

  enfiler(f,a);

  while(!file_vide(f)){
    Arbre234 noeud = defiler(f);
    if(noeud->t != 0){

      if (noeud->t == 2){
        printf("%d ",noeud->cles[1]);
      } else {
        for(int i = 0; i < noeud->t-1; i++){
        printf("%d ",noeud->cles[i]);
      }
      }
      printf("\n");
      switch (noeud->t)
      {
      case 2:
        enfiler(f,noeud->fils[1]);
        enfiler(f,noeud->fils[2]);
        break;
      case 3:
        enfiler(f,noeud->fils[0]);
        enfiler(f,noeud->fils[1]);
        enfiler(f,noeud->fils[2]);
        break;
      case 4:
        enfiler(f,noeud->fils[0]);
        enfiler(f,noeud->fils[1]);
        enfiler(f,noeud->fils[2]);
        enfiler(f,noeud->fils[3]);
        break;
      default:
        break;
      }
    }
  }

  detruire_file(f);

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  if (a->t == 0){
    return;
  } else {

    switch (a->t)
      {
      case 2:
        Affichage_Cles_Triees_Recursive(a->fils[1]);
        printf("Clef %d \n",a->cles[1]);
        Affichage_Cles_Triees_Recursive(a->fils[2]);
        break;
      case 3:
        Affichage_Cles_Triees_Recursive(a->fils[0]);
        printf("Clef %d \n",a->cles[0]);
        Affichage_Cles_Triees_Recursive(a->fils[1]);
        printf("Clef %d \n",a->cles[1]);
        Affichage_Cles_Triees_Recursive(a->fils[2]);
        break;
      case 4:
        Affichage_Cles_Triees_Recursive(a->fils[0]);
        printf("Clef %d \n",a->cles[0]);
        Affichage_Cles_Triees_Recursive(a->fils[1]);
        printf("Clef %d \n",a->cles[1]);
        Affichage_Cles_Triees_Recursive(a->fils[2]);
        printf("Clef %d \n",a->cles[2]);
        Affichage_Cles_Triees_Recursive(a->fils[3]);
    } 
  }
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

 pfile_t f = creer_file();

  enfiler(f,a);

  Arbre234 noeud = defiler(f);

  printf("CL2 :: %ls\n", noeud->cles);
  return;
}

Arbre234 getFather(Arbre234 a, int cle){
  if (a->t == 0){
    return NULL;
  } else {
    switch (a->t)
      {
      case 2:
        if (cle == a->cles[1]){
          return a;
        } else {
          return getFather(a->fils[1],cle) != NULL ? getFather(a->fils[1],cle) : getFather(a->fils[2],cle);
        }
        break;
      case 3:
        if (cle == a->cles[0]){
          return a;
        } else if (cle == a->cles[1]){
          return a;
        } else {
          return getFather(a->fils[0],cle) != NULL ? getFather(a->fils[0],cle) : getFather(a->fils[1],cle) != NULL ? getFather(a->fils[1],cle) : getFather(a->fils[2],cle);
        }
        break;
      case 4:
        if (cle == a->cles[0]){
          return a;
        } else if (cle == a->cles[1]){
          return a;
        } else if (cle == a->cles[2]){
          return a;
        } else {
          return getFather(a->fils[0],cle) != NULL ? getFather(a->fils[0],cle) : getFather(a->fils[1],cle) != NULL ? getFather(a->fils[1],cle) : getFather(a->fils[2],cle) != NULL ? getFather(a->fils[2],cle) : getFather(a->fils[3],cle);
        }
        break;
      default:
        return NULL;
    } 
  }
}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /**
   * Cas 1 : Clé à détruire est dans un nœud feuille avec plus de deux clés
    Cas 2 : Clé à détruire est dans un nœud interne
    - Plusieurs sous-cas
    Cas 3 : Clé à détruire est dans un nœud feuille
    avec une seule clé
    - Plusieurs sous-cas
  */

  Arbre234 arbre = *a;
  Arbre234 father = getFather(arbre,cle);

  RechercherCle(arbre,cle);
  return;
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

    printf ("==== Noeud Max ====\n") ;

    afficher_arbre (noeud_max(a), 0) ;

    printf ("==== Affichage Cles Largeur ====\n") ;

    Afficher_Cles_Largeur(a);

    printf ("==== Affichage Cles Triees Recursive ====\n") ;

    Affichage_Cles_Triees_Recursive(a);

    printf ("==== Affichage Cles Triees Non Recursive ====\n") ;

    Affichage_Cles_Triees_NonRecursive(a);

    printf ("==== Destruction Cle ====\n") ;

    //Detruire_Cle(&a, 82);

}
