#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "file.h"
#include "SimulationTraffic.h"
#include "projet.h"
#include "constantes.h"

int occVert=0;
int occRouge=0;
int occOrange=0;
int main(){


	srand(time(NULL));
	clock_t debutProgramme,finProgramme;
 	float tempsEcoule;
 
 	debutProgramme = clock();

	informationsRoute *informationsRoute1=(informationsRoute*)malloc(sizeof(informationsRoute)*NBR_MAX);
	informationsRoute *informationsRoute2=(informationsRoute*)malloc(sizeof(informationsRoute)*NBR_MAX);
	float DebutHeure=debutHeure*3600.0;
	File*route1=simulationTraffic(DebutHeure,informationsRoute1);

	File *route2=simulationTraffic(DebutHeure,informationsRoute2);
	int *feu=Feu();
	GestionTraffic(route1,route2,informationsRoute1,informationsRoute2,feu[3]+feu[5]+feu[4]);
	lectureFichier();
	printf("\n\t\t***********************************************\n\n");
	printf("\n\nConsulter le fichier stats.txt pour le compte rendu journalier et resultats.txt pour le tableau de bord.\n\n\n");
	printf("\t\tISMIN EI17 : PROJET REALISE PAR KHATIB OMAR\n");	

	

	finProgramme = clock();
 
	tempsEcoule = ((double)finProgramme-debutProgramme) / CLOCKS_PER_SEC;
 	printf("temps d'execution : %.2f secondes\n",tempsEcoule);

	
	return 0;}

