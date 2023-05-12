#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#define GRILLE_X 4
#define GRILLE_Y 4

int Trouvee(int* found, int carte){
	int i;
	for (i=0;i<10;i++){
		if (found[i] == carte) return 1;
	}
	return 0;
}

void DefinirSprite(int c[10]){
	//Insère les couleurs dans le tableau c pris en argument
	c[0] = ChargerSprite("./test_sprite.png");
	c[1] = ChargerSprite("./test_sprites.png");
	c[2] = ChargerSprite("./test_sprites.png");
	c[3] = ChargerSprite("./test_sprites.png");
	c[4] = ChargerSprite("./test_sprites.png");
	c[5] = ChargerSprite("./test_sprites.png");
	c[6] = ChargerSprite("./test_sprites.png");
	c[7] = ChargerSprite("./test_sprites.png");
	c[8] = ChargerSprite("./test_sprites.png");
	c[9] = ChargerSprite("./test_sprites.png");
}

int ZoneRectangle(int upper_x, int upper_y, int lower_x, int lower_y){
	//upper_x et upper_y sont les coordonnées du point supérieur gauche du rectangle
	//lower_x et lower_y sont les coordonnées du point inferieur droit du rectangle
	//La fonction renvoie 1 si la souris est dans la zone et renvoie 0 si elle n'y est pas
	SourisPosition();
	int pos_x = _X;
	int pos_y = _Y;
	if ((pos_x >= upper_x) && (pos_x <= lower_x) && (pos_y >= upper_y) && (pos_y <= lower_y))
		return 1;
	else return 0;
}


void DessinerGrille(int x_g, int y_g, int x_fen, int y_fen, int triche, int* found, int tab[4][5]){
	// Dessine la grille des cartes en noir si le mode de triche est désactivé et dévoile les cartes si le mode triche est activé
	int i,j;
	int c[10];
	int x = 0;
	int y = 0;
	int l_case = (x_fen-((10*x_g)+10))/x_g;
	int h_case = (y_fen-((10*y_g)+10))/y_g;
	DefinirSprite(c);
	if (triche == 0){
		ChoisirCouleurDessin(CouleurParNom("black"));
		for(i=10;i<x_fen-10;i+=l_case+10){
			for(j=10;j<y_fen-10;j+=h_case+10){
				if (Trouvee(found, tab[x][y])){
					AfficherSprite(c[tab[x][y]-1],i,j);
				}
				else{
					ChoisirCouleurDessin(CouleurParNom("black"));
					RemplirRectangle(i,j,l_case,h_case);
				}
				x++;
			}
			y++;
			x=0;
		}
	}
	if (triche == 1){
		for(i=10;i<x_fen-10;i+=l_case+10){
			for(j=10;j<y_fen-10;j+=h_case+10){
				AfficherSprite(c[tab[x][y]-1],i,j);
				//RemplirRectangle(i,j,l_case,h_case);
				x++;
			}
			y++;
			x=0;
		}
	}
}

void Jeu(int x_g, int y_g, int x_fen, int y_fen, int* carte, int tab[4][5]){
	int l_case = (x_fen-((10*x_g)+10))/x_g;
	int h_case = (y_fen-((10*y_g)+10))/y_g;
	int x = 0;
	int y = 0;
	int i,j;
	int c[10];
	DefinirSprite(c);
	for(i=10;i<x_fen-10;i+=l_case+10){
		for(j=10;j<y_fen-10;j+=h_case+10){
			if (ZoneRectangle(i,j,i+l_case,j+h_case)){
					AfficherSprite(c[tab[x][y]-1],i,j);
					RemplirRectangle(i,j,l_case,h_case);
					carte[0] = tab[x][y];
					carte[1] = x;
					carte[2] = y;
			}
			x++;
		}
		y++;
		x=0;
	}

}
					
void GenererGrille(int x_grille, int y_grille, int tab[4][5]){
	srand(Microsecondes());
	int i,j;
	int coos[2];
	for (i=0;i<x_grille;i++){
		for (j=0;j<y_grille;j++){
			tab[i][j] = 0;
		}
	}
	coos[0] = rand()%x_grille;
	coos[1] = rand()%y_grille;
	for (i=0;i<(x_grille*y_grille)/2;i++){
		for (j=0;j<2;j++){
			while (1){
				coos[0] = rand()%x_grille;
				coos[1] = rand()%y_grille;
				if (tab[coos[0]][coos[1]] == 0) break;
			}
			tab[coos[0]][coos[1]] = i+1;
		}
	}
}


void Triche(int* triche){
	*triche = -(*triche);
}

int Victoire(int* found, int x_grille, int y_grille){
	int i,j;
	for (i=0;i<(x_grille*y_grille)/2;i++){
		if (found[i] == 0) return 0;
	}
	return 1;
}


void InsereTableau(int val, int* tab){
	int i;
	for (i=0;i<10;i++){
		if (tab[i] == 0){
			tab[i] = val;
			break;
		}
	}
}

int main(void){
	int tab[4][5] = {{},{},{},{}};
	int o;
	int timerStop;
	int i,j;
	int x=1;
	int temps;
	int touche;
	int retourne_time = 0;
	int found[10] = {};
	int carte_1[3] = {0,-1,-1};
	int carte_2[3] = {0,-1,-1};
	GenererGrille(GRILLE_Y, GRILLE_X, tab);
	InitialiserGraphique();
	CreerFenetre(10,10,1500,844);
	ChoisirCouleurDessin(CouleurParComposante(0,0,0));
	DessinerGrille(GRILLE_X,GRILLE_Y,1500,844,0,found,tab);
	while(1){	
		if (ToucheEnAttente()){
			touche = Touche();
			if (touche == XK_t){
				Triche(&x);
				if (x==-1){
					DessinerGrille(GRILLE_X,GRILLE_Y,1500,844,1,found,tab);
					timerStop = 1;
				}
				else{
					DessinerGrille(GRILLE_X,GRILLE_Y,1500,844,0,found,tab);
					timerStop = 0;
				}
			}
			if (touche == XK_space)
				break;
			touche = 0;
	}
		if (SourisCliquee()){
			if (x==1){
				
				if (carte_1[0] == 0){
					Jeu(GRILLE_X,GRILLE_Y,1500,844,carte_1,tab);
					if (Trouvee(found,carte_1[0])){
						carte_1[0] = 0;
					}
				}		
				else if (carte_2[0] == 0){
					Jeu(GRILLE_X,GRILLE_Y,1500,844,carte_2,tab);
					if (carte_1[1] == carte_2[1] && carte_1[2] == carte_2[2]) carte_2[0] = 0;
					if (Trouvee(found,carte_2[0])) carte_2[0] = 0;
				}
			}
		}
		if (carte_1[0] == carte_2[0] && carte_1[0] != 0){
			InsereTableau(carte_1[0], found);
		}
		if (carte_1[0] != 0 && carte_2[0] != 0){
			carte_1[0] = 0;
			carte_1[1] = -1;
			carte_1[2] = -1;
			carte_2[0] = 0;
			carte_2[1] = -1;
			carte_2[2] = -1;
			temps = Microsecondes();
			retourne_time = Microsecondes()+1000000;
			while (temps < retourne_time){
				temps = Microsecondes();
			}
			DessinerGrille(GRILLE_X,GRILLE_Y,1500,844,0,found,tab);

		}
		if (Victoire(found,GRILLE_X,GRILLE_Y)){
			printf("Victoire !\n");
			break;
		}
		
	}
	FermerGraphique();
	return EXIT_SUCCESS;
}
