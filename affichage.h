#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define GRILLE_X 4
#define GRILLE_Y 4

int Trouvee(int found, int carte);

void DefinirCouleurs(couleur c[10]);

int ZoneRectangle(int upper_x, int upper_y, int lower_x, int lower_y);

void DessinerGrille(int x_g, int y_g, int x_fen, int y_fen, int triche, int* found, int tab[4][4]);

void Jeu(int x_g, int y_g, int x_fen, int y_fen, int* carte, int tab[4][4]);					
void GenererGrille(int x_grille, int y_grille, int tab[4][4]);

void Triche(int* triche);

int Victoire(int* found, int x_grille, int y_grille);

void InsereTableau(int val, int* tab);

int essay(int grille_x);

#endif /* AFFICHAGE_H */

