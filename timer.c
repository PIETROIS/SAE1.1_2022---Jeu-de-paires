#include <stdlib.h>
#include <graph.h>
#include <stdio.h>

unsigned long timer(unsigned long temps_ecoule, unsigned long temps_microsec){
	unsigned long temps_actuel = Microsecondes();
	if (temps_actuel > temps_microsec + 1000000){
		temps_microsec = temps_actuel;
		temps_ecoule += 1;
	}
	return temps_ecoule;
}
