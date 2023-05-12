#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "affichage.h"

int menu_principal(void){
	//créeation de variable de position
	int x;
	int y;

	ToucheEnAttente();
	while(1){
		SourisPosition();
		x=_X;
		y=_Y;
		
		//affichage du menu principal sur le boutton jouer
		if((x>384) && (x<1114) && (y>384) && (y<460)){
			ChargerImageFond("./background/menu-jouer.png");
		}
		
		//afficage du menu principal sur le boutton quitter
		else if((x>384) && (x<1114) && (y>497) && (y<573)){
			ChargerImageFond("./background/menu-quitter.png");
		}

		//affichage du menu principal
		else{
			ChargerImageFond("./background/menu.png");
		}
		
		
		if(SourisCliquee()){
			x=_X;
			y=_Y;
			
			//quitter
			if((x>384) && (x<1114) && (y>497) && (y<572)){
				break;
			}

			//affichage du menu difficultée
			if((x>384) && (x<1114) && (y>384) && (y<459)){	
				ChargerImageFond("./background/menu-difficultee.png");
							
				while(1){
					if(SourisCliquee()){
						x=_X;
						y=_Y;

						if((x>68) && (x<488) && (y>266) && (y<696)){
							FermerGraphique();
							essay(3);
						}
						if((x>537) && (x<958) && (y>266) && (y<696)){
							FermerGraphique();
							essay(4);	
						}
						if((x>1007) && (x<1432) && (y>266) && (y<696)) {
							FermerGraphique();
							essay(5);
						}
					}
				}
			}
		}
	}
	FermerGraphique();
	return EXIT_SUCCESS;
}


int main(void){
	//création de la fenetre
	InitialiserGraphique();
	CreerFenetre(10,10,1500,844);
	
	//ouverture du menu principal
	menu_principal();
	
	return EXIT_SUCCESS;
}
