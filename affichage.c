#include <stdlib.h>
#include <stdio.h>
#include <graph.h>

int Trouvee(int* found, int carte){
	//Cette fonction vérifie si la carte est présente dans le tableau found, qui contient toutes les paires trouvées
	int i;
	for (i=0;i<10;i++){
		if (found[i] == carte) return 1;
	}
	return 0;
}

void DefinirCouleurs(couleur c[10]){
	//Insère les couleurs dans le tableau c pris en argument
	c[0] = CouleurParNom("red");
	c[1] = CouleurParNom("blue");
	c[2] = CouleurParNom("green");
	c[3] = CouleurParNom("yellow");
	c[4] = CouleurParNom("pink");
	c[5] = CouleurParNom("brown");
	c[6] = CouleurParNom("grey");
	c[7] = CouleurParNom("light blue");
	c[8] = CouleurParNom("purple");
	c[9] = CouleurParNom("orange");
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
	couleur c[10];
	int x = 0;
	int y = 0;
	int l_case = (x_fen-((10*x_g)+10))/x_g;
	int h_case = (y_fen-((10*y_g)+10))/y_g;
	DefinirCouleurs(c);
	if (triche == 0){
		ChoisirCouleurDessin(CouleurParNom("black"));
		for(i=10;i<x_fen-10;i+=l_case+10){
			for(j=10;j<y_fen-10;j+=h_case+10){
				if (Trouvee(found, tab[x][y])){
					ChoisirCouleurDessin(c[tab[x][y]-1]);
				}
				else ChoisirCouleurDessin(CouleurParNom("black"));
				RemplirRectangle(i,j,l_case,h_case);
				x++;
			}
			y++;
			x=0;
		}
	}
	if (triche == 1){
		for(i=10;i<x_fen-10;i+=l_case+10){
			for(j=10;j<y_fen-10;j+=h_case+10){
				ChoisirCouleurDessin(c[tab[x][y]-1]);
				RemplirRectangle(i,j,l_case,h_case);
				x++;
			}
			y++;
			x=0;
		}
	}
}

void Jeu(int x_g, int y_g, int x_fen, int y_fen, int* carte, int tab[4][5]){
	//Fonction principale du jeu (Vérifie lors d'un clic si la souris a cliqué sur une carte, et vérifie l'emplacement de cette carte et son numéro de paire dans le tableau de la grille
	int l_case = (x_fen-((10*x_g)+10))/x_g;
	int h_case = (y_fen-((10*y_g)+10))/y_g;
	int x = 0;
	int y = 0;
	int i,j;
	couleur c[10];
	DefinirCouleurs(c);
	for(i=10;i<x_fen-10;i+=l_case+10){
		for(j=10;j<y_fen-10;j+=h_case+10){
			if (ZoneRectangle(i,j,i+l_case,j+h_case)){
					ChoisirCouleurDessin(c[tab[x][y]-1]);
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
	//Cette fonction génère la grille aléatoirement en fonction de la taille de la grille et l'insère sous forme de paires d'int de 1 à 10 dans le tableau tab
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
	//Cette fonction active ou désactive le mode de triche via une variable pour que dans n'importe quel partie du programme le mode de triche puisse être vérifié facilement
	*triche = -(*triche);
}

int Victoire(int* found, int x_grille, int y_grille){
	//Cette fonction vérifie les conditions de victoire en fonction de la taille de la grille, en vérifiant la liste des paires trouvées
	int i,j;
	for (i=0;i<(x_grille*y_grille)/2;i++){
		if (found[i] == 0) return 0;
	}
	return 1;
}


void InsereTableau(int val, int* tab){
	//Cette fonction insère dans un tableau (Dans l'utilisation ici le tableau des paires trouvées) une valeur à la suite des valeurs différentes de 0
	int i;
	for (i=0;i<10;i++){
		if (tab[i] == 0){
			tab[i] = val;
			break;
		}
	}
}

int essay(int grille_x){
	//Ancienne fonction main avant l'implémentation des menus, permet de jouer en fonction de la taille x de la grille
	//Les tailles prévues dans le jeu ont un y fixe, faisant que seul le x est nécessaire en paramètre.
	//Peu importe le grille_x en paramètre, le jeu s'adaptera dans une taille de fenêtre fixe.
	//La fonction ne renvoie rien puisque la fin du jeu signifie la fin du programme.
	char afficher_temps[20];
	int tab[4][5] = {{},{},{},{}};
	int o;
	unsigned long temps_microsec = Microsecondes();
	unsigned long temps_ecoule = 0;
	unsigned long temps_ancien = -1;
	unsigned long temps_actuel = 0;
	int i,j;
	int x=1;
	int temps;
	int touche;
	int retourne_time = 0;
	int found[10] = {};
	int carte_1[3] = {0,-1,-1};
	int carte_2[3] = {0,-1,-1};
	GenererGrille(4, grille_x, tab);
	InitialiserGraphique();
	CreerFenetre(10,10,1500,844);
	ChoisirCouleurDessin(CouleurParComposante(0,0,0));
	DessinerGrille(grille_x,4,1500,844,0,found,tab);
	while(1){
		if (x==1){
			temps_actuel = Microsecondes();
			if(temps_actuel > temps_microsec + 1000000){
				temps_microsec = temps_actuel;
				temps_ecoule = temps_ecoule + 1;
			}
		}
		if (temps_ecoule == temps_ancien+1){
			temps_ancien = temps_ecoule;
			ChoisirCouleurDessin(CouleurParNom("black"));
			RemplirRectangle(675,25,160,30);
			ChoisirCouleurDessin(CouleurParNom("white"));
			sprintf(afficher_temps,"Time : %03ds",temps_ecoule);
			EcrireTexte(700,50,afficher_temps,1);
		} 
		if (ToucheEnAttente()){
			touche = Touche();
			if (touche == XK_t){
				Triche(&x);
				if (x==-1){
					DessinerGrille(grille_x,4,1500,844,1,found,tab);
				}
				else{
					DessinerGrille(grille_x,4,1500,844,0,found,tab);
				}
			}
			if (touche == XK_space)
				break;
			touche = 0;
	}
		if (SourisCliquee()){
			if (x==1){
				
				if (carte_1[0] == 0){
					Jeu(grille_x,4,1500,844,carte_1,tab);
					if (Trouvee(found,carte_1[0])){
						carte_1[0] = 0;
					}
				}		
				else if (carte_2[0] == 0){
					Jeu(grille_x,4,1500,844,carte_2,tab);
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
			DessinerGrille(grille_x,4,1500,844,0,found,tab);

		}
		if (Victoire(found,grille_x,4)){
			ChargerImageFond("./background/ecran-victoire.png");
			while(Touche()!=XK_space){
			}
			break;
		}
		
	}
	FermerGraphique();
	return EXIT_SUCCESS;
} 


